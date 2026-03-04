import random

def MontyHall(schimba_usa=False, n_sim=1, afisare=False):
    succese = 0  #numarul de succese cand aleg masina
    
    for sim in range(n_sim):
        # i) Pozitionare aleatorie
        usi = ['c', 'c', 'm']
        random.shuffle(usi)
        
        # ii) Alegerea initiala aleatorie
        prima_alegere = random.randint(0, 2)
        
        # iii) Moderatorul alege o usa cu o capra care nu e cea aleasa
        optiuni_capra = [i for i in range(3) if usi[i] == 'c' and i != prima_alegere]
        capra_dezvaluita = random.choice(optiuni_capra)
        
        # iv) Daca se schimba usa se alege cealalta usa ramasa
        if schimba_usa:
            a_doua_alegere = [i for i in range(3) if i not in [prima_alegere, capra_dezvaluita]][0]
        else:
            a_doua_alegere = prima_alegere
        
        # verificare succes
        succes = (usi[a_doua_alegere] == 'm')
        if succes:
            succese += 1
        
        if afisare:
            print(f"\nSimulare {sim + 1}:")
            print(f"Asezarea: {usi}")
            print(f"Prima alegere: Usa {prima_alegere + 1}")
            print(f"Capra dezvaluită: Usa {capra_dezvaluita + 1}")
            print(f"A doua alegere: Usa {a_doua_alegere + 1}")
            print(f"Rezultat: {'SUCCES!' if succes else 'ESEC'}")

    # probabilitatea de castig
    return succese / n_sim

# Caz 1: nu schimbam usa
p_fara_schimb = MontyHall(schimba_usa=False, n_sim=10000)
print(f"Probabilitatea de a castiga fara a schimba usa: {p_fara_schimb:.2f}")

# Caz 2: schimbam usa
p_cu_schimb = MontyHall(schimba_usa=True, n_sim=10000)
print(f"Probabilitatea de a castiga daca schimbi usa: {p_cu_schimb:.2f}")