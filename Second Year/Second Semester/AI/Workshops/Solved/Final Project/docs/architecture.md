# Arhitectura sistemului

## 1. Overview

Sistemul transformă un text descriptiv (descriere de produs sau conținut educațional) într-un videoclip animat scurt, cu narațiune audio și subtitrări sincronizate. Arhitectura este construită în jurul unui **agent AI** care orchestrează un set de tools specializate, fiecare responsabilă pentru o etapă a procesului.

Filosofia de design: **un agent inteligent + tools simple**. Inteligența reală a sistemului se află în agentul LLM care decide ce tools să apeleze și cum, nu în complexitatea fiecărui tool individual. Această separare face sistemul modular, ușor de testat și extensibil.

Stack-ul ruleaza local + folosing API-uri gratuite, fără dependențe de servicii cloud plătite. Această alegere reflectă două obiective - accesibilitatea soluției pentru utilizatori cu buget zero (școli, ONG-uri, freelanceri) și controlul asupra datelor procesate.

**Platformă de dezvoltare:** macOS pe Apple Silicon. Stack-ul este cross-platform și poate rula și pe Linux/Windows cu modificări minime ale dependențelor si ale optimizarilor folosite.

## 2. Arhitectura pe layere

Sistemul este organizat pe 4 nivele, fiecare cu responsabilități clare:

User interface (Streamlit) - input text, butoane, preview video, download.

Agent orchestrator - LLM cu function calling (modele open-source rulate local folisng Ollama - Qwen 2.5 / gama de modele Gemma 4)

Tools - functii specializate: 
- scene_splitter (apeleaza API-ul unui alt model AI pentru a imbunatati performanta)
- text-to-speech: gTTS (Google text to speech) / Piper TTS (setup mai complicat, dar ruleaza local).
- subtitles
- video_assembler

Output - video.mp4 + subtitles.srt


### Layer 1 — User Interface

**Tehnologie:** Streamlit

**Rol:** primește textul de la utilizator, afișează progresul generării, livrează videoclipul final pentru preview și descărcare.

**De ce Streamlit:** este cel mai rapid framework Python pentru interfețe web simple. Nu necesită cunoștințe de frontend (HTML/CSS/JS), suportă nativ widget-uri pentru text, butoane, progress bars și preview video. Este open-source și gratis.

### Layer 2 — Agent Orchestrator

**Tehnologie:** Qwen 2.5 (7B) / Gemma E4B rulat local prin **Ollama**, cu function calling.

**Rol:** primește instrucțiunea de la utilizator în limbaj natural ("generează un video din textul ăsta"), planifică pașii necesari și apelează tools-urile în ordinea corectă. Gestionează și erorile — dacă un tool returnează output invalid, agentul poate re-apela tool-ul cu parametri ajustați.

**De ce Ollama:** simplifică deployment-ul local — un singur "ollama pull qwen2.5" și modelul e gata de folosit, expus pe un API compatibil OpenAI. Ollama are suport nativ pentru Apple Silicon (folosește framework-ul Metal pentru accelerare GPU), oferind performanță excelentă pe MacBook-uri cu chip M-series. Dacă vrem să migrăm pe API cloud în viitor, schimbăm doar `base_url`.

**De ce function calling (și nu pipeline liniar):** permite flexibilitate. Agentul poate sări pași, re-apela tools cu parametri diferiți, sau adăuga validări intermediare. Această flexibilitate va fi exploatată în etapa de îmbunătățiri (faza 4).

### Layer 3 — Tools

Fiecare tool este o **funcție Python** cu signature bine definită, expusă agentului prin schema de function calling. Tools-urile sunt deterministe și pot fi testate izolat.

#### Tool 1: `scene_splitter`
- **Input:** text brut (string)
- **Output:** listă de scene structurate - structured output (JSON cu titlu, narațiune, cuvinte cheie vizuale, durată estimată)
- **Tehnologie:** apel către LLM (API sau alt model rulat local - trebuie sa suporte structured output) cu un prompt specializat care include schema de output JSON
- **Rol:** transformă textul liber într-o structură pe scene, gata de procesat

#### Tool 2: `image_fetcher`
- **Input:** cuvinte cheie (string sau listă)
- **Output:** path local către o imagine descărcată
- **Tehnologie:** **Pexels API** (gratis, 200 requests/h, fără card de credit)
- **Rol:** găsește o imagine stock relevantă pentru fiecare scenă bazat pe keywords
- **Fallback:** dacă Pexels nu returnează rezultate, se folosește un set de imagini default din `data/fallback_images/`

#### Tool 3: `text_to_speech`
- **Input:** text de narat (string), limba (string)
- **Output:** path local către un fișier audio (.mp3 sau .wav)
- **Tehnologie principală:** **gTTS** (Google Text-to-Speech, gratis, necesită internet)
- **Tehnologie alternativă (faza 4):** **Piper TTS** — voci neurale locale, foarte rapide pe Apple Silicon
- **Rol:** generează narațiunea audio pentru fiecare scenă
- **Justificare alegere:** gTTS funcționează din 3 linii de cod, suportă multe limbi (inclusiv română), și produce voci decente. Pentru MVP este alegerea optimă. Piper TTS rămâne ca opțiune de upgrade pentru voci 100% locale și mai naturale.

#### Tool 4: `subtitle_generator`
- **Input:** path către fișier audio
- **Output:** path către fișier .srt sincronizat
- **Tehnologie:** **MLX Whisper** (Whisper optimizat pentru Apple Silicon prin framework-ul MLX) sau **openai-whisper** standard
- **Rol:** transcrie audio-ul cu timestamp-uri exacte pentru subtitrări sincronizate
- **Justificare:** MLX Whisper este implementarea oficială pentru Apple Silicon, mult mai rapidă decât varianta standard pe Mac. Folosește acceleratorul Neural Engine al chip-ului M4.

#### Tool 5: `video_assembler`
- **Input:** listă de scene cu imagine + audio + subtitrare per scenă
- **Output:** path către fișierul final `.mp4`
- **Tehnologie:** **MoviePy** (wrapper Python peste ffmpeg)
- **Rol:** combină toate elementele într-un singur videoclip cu tranziții simple, text overlay și sincronizare audio-vizuală

### Layer 4 — Output

Sistemul produce două fișiere finale:
- `output/video.mp4` — videoclipul asamblat (durată 30s–3min, în funcție de text)
- `output/subtitles.srt` — fișier de subtitrări separat, pentru cei care vor să-l încarce pe alte platforme (YouTube, Vimeo)

## 3. Flow de execuție

Mai jos este secvența completă a unui request:

```
1. User scrie text în UI Streamlit și apasă "Generate"
   │
2. UI trimite textul la Agent (Layer 2)
   │
3. Agent (Qwen 2.5 de ex.) primește textul și planifică:
   "Voi apela scene_splitter, apoi pentru fiecare scenă
    voi obține imagine + audio + subtitrare, apoi
    voi asambla video-ul final."
   │
4. Agent → scene_splitter(text) → JSON cu 4-6 scene
   │
5. Pentru fiecare scenă (în paralel sau secvențial):
   a. Agent → image_fetcher(keywords) → image.jpg
   b. Agent → text_to_speech(narration) → audio.mp3
   c. Agent → subtitle_generator(audio) → scene.srt
   │
6. Agent → video_assembler(scenes_data) → video.mp4
   │
7. UI primește path-ul și afișează preview + buton download
```

**Notă pe paralelism:** pașii 5a, 5b, 5c sunt independenți între scene și pot rula în paralel cu `concurrent.futures` pentru a reduce timpul total de generare. Această optimizare va fi implementată în faza 4 (Îmbunătățiri).


#### Cost total - 0 pe luna (presupunand ca se utilizeaza in anumite limite, care sunt deja relativ permisive).

## 5. Decizii tehnologice cheie

### LLM local vs cloud

**Decizia:** LLM local prin Ollama.

**Trade-off-uri:**

- Function calling mai puțin fiabil decât GPT-4 → necesită validare Pydantic + retry logic

**Mitigare:** vom implementa validare strictă a output-urilor cu Pydantic și un sistem de retry care reformulează prompt-ul dacă LLM-ul produce JSON invalid.

### TTS — gTTS vs. Piper TTS

**Decizia:** începem cu **gTTS** pentru simplitate, putem migra la **Piper TTS** dacă vrem voci 100% locale.

**Justificare:** gTTS funcționează din prima cu 3 linii de cod, suportă multe limbi (inclusiv română) și nu necesită download de modele.

### Subtitrari — MLX Whisper pe Apple Silicon

**Decizia:** MLX Whisper.

**Alternativa considerată:** `faster-whisper` (folosește CUDA, deci nu merge pe Mac), `openai-whisper` standard (merge dar e mai lent).

**De ce MLX Whisper:** este implementarea oficială Apple a modelului Whisper, optimizată pentru chip-urile M-series prin framework-ul MLX. Folosește atât GPU-ul integrat cât și Neural Engine-ul, oferind performanță superioară față de varianta standard. Pentru un fișier audio de 30 secunde, transcrierea durează 2-3 secunde pe M4.

### Asamblare video — MoviePy vs ffmpeg direct

**Decizia:** MoviePy.

**Justificare:** MoviePy este un wrapper Python peste ffmpeg care oferă API declarativ pentru concatenare clipuri, text overlay, fade in/out, audio mixing. Scrierea acelorași operațiuni direct cu comenzi ffmpeg ar fi mai verbose și mai greu de citit. Performanța este similară pentru cazul nostru de uz.

**Note pentru macOS:** MoviePy necesită `ffmpeg` instalat în sistem.

## 6. Structura repo orientativa

```
text-to-video-ai/
├── README.md                       
├── requirements.txt
├── .gitignore
├── .env.example
├── data/
│   ├── input_texts/                
│   ├── metadata.csv
│   ├── fallback_images/           
│   └── outputs/                   
├── docs/
│   ├── architecture.md             
│   ├── problem_statement.md       
│   ├── sdg_mapping.md             
│   ├── data_insights.md            
│   └── figures/
│       └── architecture_diagram.png
├── src/
│   ├── __init__.py
│   ├── agent.py                    # orchestrator principal
│   ├── config.py                   # paths, API keys, model names
│   ├── prompts/
│   │   └── scene_splitter.txt
│   ├── tools/
│   │   ├── __init__.py
│   │   ├── scene_splitter.py
│   │   ├── tts.py
│   │   ├── image_fetcher.py
│   │   ├── subtitles.py
│   │   └── video_assembler.py
│   ├── schemas.py                  # Pydantic models
│   └── ui/
│       └── app.py                  # Streamlit
├── notebooks/
│   ├── 01_problem_exploration.ipynb
│   └── 02_data_analysis.ipynb      
└── tests/
    ├── test_tools.py
    └── test_agent.py
```

## 7. Cerințe de sistem

**Configuratie hardware:**
- **Hardware:** MacBook Pro cu chip Apple M-series (M1/M2/M3/M4)
- **RAM unificată:** minim 16 GB (recomandat 24+ GB pentru a rula simultan LLM-ul și Whisper)
- **Disk:** 15 GB liber (pentru modele Ollama + outputs)
- **OS:** macOS 13+ (Ventura sau mai nou)
- **Python:** 3.10+
- **Dependențe sistem:** `ffmpeg` (instalabil cu `brew install ffmpeg`)

**Compatibilitate cross-platform:**
Stack-ul rulează și pe Linux/Windows cu următoarele ajustări:
- `mlx-whisper` se înlocuiește cu `faster-whisper` (NVIDIA) sau `openai-whisper`
- Restul componentelor (Ollama, Streamlit, MoviePy, gTTS, Pexels) sunt cross-platform native

