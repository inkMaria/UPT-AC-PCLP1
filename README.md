# Laboratoare & Teme — Programarea Calculatoarelor (C)

Repository-ul meu personal în care adun temele de laborator, exercițiile de algoritmică și micile experimente scrise în **C** pe parcursul semestrului.

---

## Structura repository-ului

Fiecare temă sau set de exerciții are propriul branch dedicat, ca să păstrez lucrurile curate și organizate:

- **`main`** — prezentarea generală a repository-ului și punctul de pornire.
- **`tema1`** — Distanța Levenshtein (programare dinamică, alocare dinamică pe heap `int **`, meniu interactiv) + corelație încrucișată.
- **`tema2`** — Lucrul cu fișiere, șiruri de caractere și automatizare pe Linux:
  - `p1.c` — Programul „narcisist” (își citește propria sursă prin `__FILE__` și o copiază linie cu linie în `fisier.txt`).
  - `p2.c` — Testare automată a 100 de cuvinte cu 20 de funcții de validare fără `<ctype.h>`, vector de pointeri la funcții și generare automată de directoare (`mkdir`).
- **`laboratoare`** *(în lucru, adăugate treptat)* — exercițiile și problemele rezolvate la orele de laborator (tablouri, pointeri, șiruri de caractere, fișiere etc.).
- *(în curând)* **`tema3`**, ...

---

## Ce găsești pe aici

- Implementări scrise de la zero în **C**, cu focus pe înțelegerea memoriei (`malloc` / `free`, pointeri, buffere, lucru cu fișiere `FILE *`).
- Experimente cu biblioteci de sistem și POSIX pe Linux (`<sys/stat.h>` pentru crearea automată a directoarelor cu `mkdir`, `<time.h>` pentru timestamp-uri, macro-uri predefinite precum `__FILE__`).
- Exerciții de laborator adăugate treptat, pe măsură ce avansez cu materia.
- Cod modular, comentat onest (cu tot cu lecțiile învățate din greșeli și sesiunile de debugging).
- Documentație dedicată pe fiecare branch în parte (cum se compilează, exemple de rulare și progres).

---

## Cum navighezi între teme și laboratoare (Git)

```bash
# Vezi toate branch-urile disponibile
git branch -a

# Treci pe branch-ul unei teme sau al laboratoarelor
git checkout tema2
git checkout laboratoare
