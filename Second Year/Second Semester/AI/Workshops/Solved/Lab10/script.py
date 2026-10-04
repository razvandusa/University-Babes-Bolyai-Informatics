from selenium_recaptcha_solver import RecaptchaSolver
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.service import Service as FirefoxService
from selenium.webdriver.support.ui import WebDriverWait, Select
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException, NoSuchElementException
import requests
import datetime
import time
import multiprocessing

URL = "https://academicinfo.ubbcluj.ro/ContracteStudii.aspx"
NTFY_TOPIC = "academicinfo_tudor_2024_xyz"
GECKODRIVER_PATH = "/opt/homebrew/bin/geckodriver"

TARGETS = []
materii = {
}

def send_notification(materie, current, max_students, semestru, inscris=False):
    status = f"[Sem {semestru}] Inscris automat!" if inscris else f"[Sem {semestru}] Loc disponibil! {current}/{max_students}"
    try:
        requests.post(
            f"https://ntfy.sh/{NTFY_TOPIC}",
            data=status.encode("utf-8"),
            headers={
                "Title": materie,
                "Priority": "urgent",
                "Tags": "warning,school",
                "Content-Type": "text/plain; charset=utf-8"
            },
            timeout=10
        )
    except Exception as e:
        print(f"[Sem {semestru}][NTFY ERROR] {e}")

def login(driver, url, username, password, max_retries=3):
    solver = RecaptchaSolver(driver=driver)

    while True:
        driver.get(url)
        time.sleep(3)

        driver.find_element(By.ID, "txtUsername").send_keys(username)
        driver.find_element(By.ID, "txtPassword").send_keys(password)

        try:
            recaptcha_iframe = WebDriverWait(driver, 5).until(
                EC.presence_of_element_located((By.XPATH, '//iframe[@title="reCAPTCHA"]'))
            )
            captcha_prezent = True
        except TimeoutException:
            captcha_prezent = False

        if captcha_prezent:
            captcha_rezolvat = False
            for attempt in range(1, max_retries + 1):
                try:
                    driver.execute_script("arguments[0].scrollIntoView(true);", recaptcha_iframe)
                    time.sleep(1)

                    try:
                        driver.switch_to.frame(recaptcha_iframe)
                        checked = driver.find_element(By.ID, "recaptcha-anchor").get_attribute("aria-checked")
                        driver.switch_to.default_content()
                        if checked == "true":
                            captcha_rezolvat = True
                            break
                    except Exception:
                        driver.switch_to.default_content()

                    solver.click_recaptcha_v2(iframe=recaptcha_iframe)
                    time.sleep(3)

                    try:
                        driver.switch_to.frame(recaptcha_iframe)
                        checked = driver.find_element(By.ID, "recaptcha-anchor").get_attribute("aria-checked")
                        driver.switch_to.default_content()
                        if checked == "true":
                            captcha_rezolvat = True
                            break
                    except Exception:
                        driver.switch_to.default_content()

                    response_token = driver.execute_script(
                        "return document.querySelector('textarea#g-recaptcha-response') ? "
                        "document.querySelector('textarea#g-recaptcha-response').value : '';"
                    )
                    if response_token:
                        captcha_rezolvat = True
                        break

                    time.sleep(3)

                except TimeoutException:
                    time.sleep(3)
                except Exception as e:
                    print(f"[LOGIN][CAPTCHA ERROR] încercarea {attempt}: {e}")
                    driver.switch_to.default_content()
                    time.sleep(3)

            if not captcha_rezolvat:
                print("[LOGIN] CAPTCHA nerezolvat, reîncerc...")
                time.sleep(5)
                continue

        try:
            driver.find_element(By.ID, "btnLogin").click()
        except NoSuchElementException:
            print("[LOGIN] ❌ Butonul de login nu a fost găsit.")
            time.sleep(3)
            continue

        try:
            WebDriverWait(driver, 15).until(
                lambda d: "Home.aspx" in d.current_url or "ContracteStudii.aspx" in d.current_url
            )
            if "Home.aspx" in driver.current_url:
                driver.get("https://academicinfo.ubbcluj.ro/ContracteStudii.aspx")
                WebDriverWait(driver, 10).until(
                    lambda d: "ContracteStudii.aspx" in d.current_url
                )
            return True
        except TimeoutException:
            print("[LOGIN] ⚠️ Timeout redirect, reîncerc...")
            time.sleep(3)
            continue

def selecteaza_semestrul(driver, valoare):
    try:
        select_element = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "ctl00_ContentPlaceHolder1_ListBoxSemestre"))
        )
        driver.execute_script("arguments[0].scrollIntoView({block: 'center'});", select_element)
        time.sleep(1)
        driver.execute_script("window.scrollBy(0, -250);")
        time.sleep(1)
        driver.execute_script("""
            var select = arguments[0];
            var value = arguments[1];
            select.value = value;
            select.dispatchEvent(new Event('change', { bubbles: true }));
        """, select_element, valoare)
        time.sleep(3)
        return True
    except TimeoutException:
        print(f"❌ Lista de semestre nu a fost găsită.")
        return False
    except Exception as e:
        print(f"❌ Eroare la selectarea semestrului: {e}")
        return False

def bifeaza_disciplina(driver, checkbox_id):
    try:
        checkbox = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, checkbox_id))
        )
        driver.execute_script("arguments[0].scrollIntoView(true);", checkbox)
        time.sleep(1)
        driver.execute_script("arguments[0].click();", checkbox)
        time.sleep(3)
        return True
    except Exception as e:
        print(f"❌ Eroare la bifarea checkbox-ului {checkbox_id}: {e}")
        return False

def selecteaza_disciplina_alternativa(driver, semestru):
    try:
        facultate_select = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "ctl00_ContentPlaceHolder1_ddlAlteFacultati"))
        )
        driver.execute_script("""
            var select = arguments[0];
            select.value = '204';
            select.dispatchEvent(new Event('change', { bubbles: true }));
        """, facultate_select)
        time.sleep(3)

        linie_select = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "ctl00_ContentPlaceHolder1_DdlLinie"))
        )
        driver.execute_script("""
            var select = arguments[0];
            select.value = '2';
            select.dispatchEvent(new Event('change', { bubbles: true }));
        """, linie_select)
        time.sleep(3)

        specializare_select = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "ctl00_ContentPlaceHolder1_ddlAlteSectii"))
        )
        options = specializare_select.find_elements(By.TAG_NAME, "option")
        target_option = None
        for opt in options:
            text = opt.text
            if "An 3" in text and "nformatic" in text and ("ngleză" in text or "ngleza" in text or "nglish" in text):
                target_option = opt
                break

        if not target_option:
            print(f"[Sem {semestru}] ❌ Specializarea nu a fost găsită. Opțiuni: {[opt.text for opt in options]}")
            return False

        val = target_option.get_attribute("value")
        driver.execute_script("""
            var select = arguments[0];
            select.value = arguments[1];
            select.dispatchEvent(new Event('change', { bubbles: true }));
        """, specializare_select, val)
        time.sleep(3)
        return True

    except Exception as e:
        print(f"[Sem {semestru}] ❌ Eroare la selectarea disciplinei alternative: {e}")
        return False

def monitorizeaza(driver, semestru, username, password, checkbox_id=None):
    inscrise = set()
    while True:
        try:
            rows = driver.find_elements(By.XPATH, "//table[contains(@id, 'gvDisciplinePlanSectie') or contains(@id, 'GvDisciDeAltundeva')]//tr")

            for row in rows:
                try:
                    cod_element = row.find_element(By.XPATH, ".//span[contains(@id, 'lblCoddis')]")
                    cod = cod_element.text.strip()
                except:
                    continue

                if not cod or cod not in TARGETS:
                    continue

                try:
                    max_element = row.find_element(By.XPATH, ".//span[contains(@id, 'lblStudentiCurs')]")
                    current_element = row.find_element(By.XPATH, ".//span[contains(@id, 'lblTotalStudentiInscrisi')]")
                    max_str = max_element.text.strip()
                    current_str = current_element.text.strip()
                except:
                    continue

                if max_str == "max" or not max_str.isdecimal() or not current_str.isdecimal():
                    continue

                max_students = int(max_str)
                current = int(current_str)

                if cod not in inscrise and current < max_students:
                    print(f"[Sem {semestru}][{datetime.datetime.now()}] LOC DISPONIBIL: {materii.get(cod, cod)} ({current}/{max_students})")
                    send_notification(materii.get(cod, cod), current, max_students, semestru)

                    try:
                        btn = row.find_element(By.XPATH, ".//a[contains(@id, 'lnkAdauga')]")
                        driver.execute_script("arguments[0].click();", btn)
                        print(f"[Sem {semestru}] ✅ INSCRIS: {materii.get(cod, cod)}")
                        inscrise.add(cod)
                        send_notification(materii.get(cod, cod), current, max_students, semestru, inscris=True)
                        time.sleep(3)
                        continue
                    except:
                        pass

                    try:
                        checkbox = row.find_element(By.XPATH, ".//input[contains(@id, 'cbDiscipline') and not(@disabled)]")
                        driver.execute_script("arguments[0].click();", checkbox)
                        print(f"[Sem {semestru}] ✅ INSCRIS (checkbox): {materii.get(cod, cod)}")
                        inscrise.add(cod)
                        send_notification(materii.get(cod, cod), current, max_students, semestru, inscris=True)
                        time.sleep(3)
                    except Exception as e:
                        print(f"[Sem {semestru}][ADAUGA ERROR] {materii.get(cod, cod)}: {e}")

        except Exception as e:
            print(f"[Sem {semestru}][ERROR] {e}")

        time.sleep(30)
        try:
            driver.get(URL)
            time.sleep(3)

            if "txtUsername" in driver.page_source:
                print(f"[Sem {semestru}] Sesiune expirată, reautentificare...")
                if not login(driver, URL, username, password):
                    print(f"[Sem {semestru}] ❌ Reautentificare eșuată.")
                    continue

            if not selecteaza_semestrul(driver, str(semestru)):
                continue

            if checkbox_id:
                time.sleep(2)
                if bifeaza_disciplina(driver, checkbox_id):
                    time.sleep(2)
                    selecteaza_disciplina_alternativa(driver, semestru)

        except Exception as e:
            print(f"[Sem {semestru}][REFRESH ERROR] {e}")

def ruleaza_instanta(username, password, semestru, instanta, checkbox_id=None):
    print(f"[Instanta {instanta} | Sem {semestru}] Pornire...")
    service = FirefoxService(GECKODRIVER_PATH)
    driver = webdriver.Firefox(service=service)

    if login(driver, URL, username, password):
        if selecteaza_semestrul(driver, str(semestru)):
            if checkbox_id:
                if bifeaza_disciplina(driver, checkbox_id):
                    if selecteaza_disciplina_alternativa(driver, semestru):
                        monitorizeaza(driver, semestru, username, password, checkbox_id=checkbox_id)
                    else:
                        print(f"[Instanta {instanta}] ❌ Setup alternativă eșuat.")
                        driver.quit()
                else:
                    print(f"[Instanta {instanta}] ❌ Checkbox eșuat.")
                    driver.quit()
            else:
                monitorizeaza(driver, semestru, username, password)
    else:
        driver.quit()

if __name__ == '__main__':
    USERNAME = ""
    PASSWORD = ""

    instante = [
        (USERNAME, PASSWORD, 5, 1, None),
        (USERNAME, PASSWORD, 5, 2, None),
        (USERNAME, PASSWORD, 6, 1, None),
        (USERNAME, PASSWORD, 6, 2, None),
    ]

    procese = []
    for username, password, semestru, instanta, checkbox_id in instante:
        p = multiprocessing.Process(
            target=ruleaza_instanta,
            args=(username, password, semestru, instanta, checkbox_id)
        )
        procese.append(p)
        p.start()
        time.sleep(5)

    for p in procese:
        p.join()
