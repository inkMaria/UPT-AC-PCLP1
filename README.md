# Tema 2 — Programarea Calculatoarelor și Limbaje de Programare

Documentația și jurnalul de dezvoltare pentru cele două probleme din Tema 2 (`p1.c` și `p2.c`).

---

## Exercițiul 1: Programul „narcisist” (`p1.c`)

Un program în **C** care își citește propriul cod sursă și îl copiază într-un fișier text (`fisier.txt`), păstrând structura liniilor și formatarea.

### Cum funcționează
1. Deschide fișierul destinație `fisier.txt` în modul scriere (`"w+"`) și propriul fișier sursă prin macro-ul `__FILE__` în modul citire (`"r"`).
2. Verifică dacă vreunul dintre fișiere nu s-a putut deschide (`NULL`), afișează eroarea cu `perror` și închide eventualul fișier deschis înainte de a ieși.
3. Citește linie cu linie din sursă cu `fgets` și scrie fiecare linie în `fisier.txt` cu `fputs`.
4. Închide ambele fișiere cu `fclose` la final.

### Wall of Shame & Lecții învățate
1. **Prima încercare (`while (1)` cu `realloc` pe `int *v`):** am pornit cu un șablon de vector dinamic pentru numere întregi și am uitat complet `main` sau condiția de oprire (`undefined reference to main` + buclă infinită).
2. **A doua încercare (`fprintf(f, "%99s", s) == 0` + `fscanf`):** am încurcat ordinea argumentelor la `fscanf`, am pus condiția invers la `fprintf` și era să stric formatarea codului cu `%s` (care mănâncă spațiile și liniile goale).
3. **Lenea de la 00:44 la `fopen`:** am verificat `(g == NULL) || (f == NULL)` dintr-un foc, fără să închid separat fișierul care apucase să se deschidă (reparat ulterior cu `if (f != NULL) fclose(f);`).

### Împărțirea muncii (cine ce a făcut)
#### Ce am făcut eu:
1. Am ales ideea și structura fișierului (`p1.c` -> `fisier.txt`), am folosit `__FILE__` ca să-și deschidă singur sursa.
2. Am identificat că am nevoie de `fgets` pentru șiruri de caractere și lucru cu fișiere.
3. Am scris codul efectiv, am reparat bucla cu `fgets` + `fputs`, am testat compilarea cu `-Wall -Wextra -fsanitize=address` și am pus comentariile.

#### Ce a făcut AI-ul (Gemini):
1. Mi-a explicat de ce `fscanf` + `fprintf("%s")` nu merg pentru copiat cod și cum funcționează concret perechea `fgets` + `fputs`.
2. Mi-a dat hint-ul cu închiderea separată a fișierelor pe ramura de eroare (`if (f != NULL) fclose(f);`).
3. M-a ajutat să structurez acest `README.md`.

### Proces & Timp de gândire (~30 min)
Înainte și după ce am scris codul, mi-am luat cam **30 de minute** doar ca să înțeleg raționamentul din spate, nu doar sintaxa:

- **De ce `__FILE__` și nu un nume hardcodat?** Pentru că programul își cunoaște singur sursa la compilare, indiferent cum redenumesc fișierul `.c`.
- **De ce ordinea `deschid -> verific -> copiez -> închid`?** Ca să nu ajung în *segmentation fault* pe un pointer `NULL` și să nu las fișiere deschise pe ramura de eroare.
- **Cum circulă datele în `while`?** `fgets` aduce câte o bucată din sursă (cu tot cu `\n`), iar `fputs` o varsă exact la fel în `fisier.txt`, fără să piardă indentarea sau spațiile.

---

## Exercițiul 2: Testare Automată a Cuvintelor (`p2.c`)

Un program în **C** (Linux) care citește 100 de cuvinte dintr-un fișier text (`fisierul_cu_cuvintele.txt`), rulează automat **20 de teste** distincte pe fiecare cuvânt și salvează rezultatele organizate pe foldere (`teste_fisier/<cuvant>/test_<cuvant>_<nr>.txt`).

### Cum funcționează
1. Deschide `fisierul_cu_cuvintele.txt` în modul `"r+"`, verifică deschiderea (`NULL`) și creează directorul rădăcină `teste_fisier/` cu `mkdir(..., 0755)`.
2. Întreabă interactiv utilizatorul (`y/n`) dacă dorește afișarea cuvintelor în consolă; dacă se alege `y`, parcurge fișierul și resetează apoi cursorul la început cu `rewind(f)`.
3. Pentru fiecare cuvânt citit cu `fscanf(f, "%99s", s)`:
   - creează subfolderul `teste_fisier/<cuvant>/`,
   - rulează pe rând cele 20 de funcții de test printr-un vector de pointeri la funcții (`functii_test`),
   - generează pentru fiecare test un fișier propriu (`test_<cuvant>_<nr>.txt`) cu numele testului, cuvântul, statusul (`TRECUT` / `PICAT`), autorul (`Maria`) și data/ora execuției (`YYYY-MM-DD HH:MM:SS`).
4. Închide fișierul sursă cu `fclose(f)`.

### Wall of Shame & Lecții învățate
1. **Cod executabil în afara funcțiilor:** la început am pus `if (f == NULL)` și `mkdir(...)` direct în zona globală, înainte de `main()` (`expected identifier or '('` la compilare).
2. **`switch (i < 20)` și `switch (NR_TESTE)`:** expresia `i < 20` dă doar `0` sau `1`, iar `NR_TESTE` e constantă (`20`), deci nu intra niciodată în `case 1..19`; am înlocuit complet `switch`-ul cu un vector de pointeri la funcții.
3. **Conflictul de nume `*teste(s, i)`:** aveam și funcția `teste()` și vectorul `const char *teste[]` în `main()`, plus un `*` în față pe o funcție `void`.
4. **Capcana `<ctype.h>` și modificarea șirului original:** în testul de palindrom suprascriam direct `s[k++]` (ceea ce strica cuvântul pentru restul testelor) și folosisem `tolower`/`isalpha` din `<ctype.h>`; am rescris toate verificările manual pe coduri ASCII (`'a'..'z'`, `'A'..'Z'`, `'0'..'9'`).
5. **Cursorul la final după afișare (`EOF`) și `/n` în loc de `\n`:** la opțiunea `y`, primul `while` citea fișierul până la capăt, iar al doilea `while` nu mai genera niciun test până nu am pus `rewind(f);` între ele.

### Împărțirea muncii (cine ce a făcut)
#### Ce am făcut eu:
1. Am stabilit arhitectura temei, lista celor 20 de teste inspirate din cursul și laboratorul de șiruri de caractere și organizarea pe foldere cu `mkdir` pe Linux.
2. Am venit cu ideea să înlocuim macro-ul `#define` propus inițial de AI cu o funcție `void scrie_test(...)` (mai sigură, cu verificare de tipuri și fără cod duplicat) și să scăpăm de `switch`-ul repetitiv.
3. Am impus restricția de laborator fără `<ctype.h>` și am integrat citirea din fișier, constantele (`Autor`, `NR_TESTE`) și meniul interactiv (`y/n`) pentru afișarea cuvintelor în consolă.
4. Am testat programul pe Linux, am depistat bug-urile pe parcurs (de la fișierul lipsă până la `/n` și cursorul rămas la final după afișare) și am curățat varianta finală.

#### Ce a făcut AI-ul (Gemini):
1. A venit inițial cu varianta pe `#define` și `switch` (pe care am refuzat-o ulterior în favoarea unei variante mai elegante).
2. M-a ajutat să structurez vectorul de pointeri la funcții (`int (*functii_test[20])(const char *)`) și a scris corpul funcțiilor de test pe coduri ASCII.
3. Mi-a semnalat bug-ul cu cursorul ajuns la `EOF` după opțiunea `y` (rezolvat cu `rewind(f)`) și a generat lista de 100 de cuvinte de test.

### Proces & Timp de gândire (~1h 30 min)
- **De ce vector de pointeri la funcții în loc de `switch`?** Pentru că 20 de `case`-uri într-o singură funcție sunt greu de urmărit și ușor de greșit; cu un vector de funcții, bucla din `main` are doar câteva linii.
- **De ce fără `<ctype.h>`?** Pentru a respecta cerința de laborator de a manipula caracterele direct prin aritmetică pe coduri ASCII (`c - 'A' + 'a'`, intervale `'a'..'z'`, `'0'..'9'`).
- **De ce `rewind(f)` după `switch`?** Pentru că un singur `FILE *` păstrează poziția cursorului în fișier; după prima parcurgere pentru afișare, cursorul rămâne la `EOF` și trebuie readus la început pentru rularea testelor.

---

## Structura proiectului

```text
TEMA2/
├── p1.c                        # Exercițiul 1: Programul „narcisist”
├── fisier.txt                  # Output generat de p1.c
├── p2.c                        # Exercițiul 2: Testare automată a cuvintelor
├── fisierul_cu_cuvintele.txt   # Fișierul de intrare pentru p2.c (100 de cuvinte)
├── README.md
