# Distanța Levenshtein în C

Implementare modulară în **C** a algoritmului **Distanța Levenshtein** (numărul minim de inserări, ștergeri sau substituiri necesare pentru a transforma un șir `s` într-un șir `t`), cu alocare dinamică completă pe heap și meniu interactiv.

## Funcționalități

- **Meniu interactiv:**
  1. Rularea cazului din cerință (`"TEST"` vs `"TEXT"` -> rezultat `1`, matrice `5x5`).
  2. Citirea a două șiruri arbitrare de la tastatură și calcularea distanței dintre ele.
  3. Ieșire curată din program.
- **Alocare și eliberare dinamică (`malloc` / `free`):** matrice `int **` de dimensiune `(m+1) x (n+1)` și șiruri alocate exact la lungimea necesară (`len + 1`).
- **Arhitectură modulară:** `minim`, `matrice`, `eliberare_matrice`, `afisare_matrice`, `lungime_text`, `Distanta_Levenshtein`, `citeste_sirul`.

##  Exemplu
```text
=== Distanta Levenshtein ===
1. Testul din cerinta ("TEST" vs "TEXT")
2. Doua siruri citite de la tastatura
3. Afara (iesire)
Alegeti o optiune: 1

Matricea Levenshtein (5x5):
      ""   T   E   X   T 
 ""    0   1   2   3   4 
  T    1   0   1   2   3 
  E    2   1   0   1   2 
  S    3   2   1   1   2 
  T    4   3   2   2   1 
Rezultat "TEST" vs "TEXT": 1
```
# Wall of Shame (greșeli de care încă râd, dar m-au învățat carte)
1. else if trădător în minim(a, b, c): am crezut că-i elegant, dar dacă m > b era adevărat, sărea peste c și întorcea un „minim” care de fapt nu era minim.
2. return NULL; într-o funcție void: am vrut să „scap de erori la compilare” și i-am dat unei funcții care nu întoarce nimic un pointer nul. Compilatorul n-a gustat gluma.
3. Am încercat să fac free... punând malloc înăuntru: la funcția de eliberare de memorie am copiat din greșeală blocul de alocare. Curățenie făcută cu mătura murdară.
4. Am vrut să eliberez și coloanele: m-am întrebat de ce nu dau free pe coloane, până mi-am amintit că ele stau cuminte în interiorul fiecărei linii, nu au propriul malloc.
5. int *i, *k; la indicii de for: am făcut pointeri din bietii indici de buclă și m-am mirat de ce se plânge compilatorul.
6. Am încercat să înmulțesc buffer cu malloc(...): moment de inspirație abstractă în citeste_sirul, oprit brusc de regulile limbajului C.
7. Am numit un parametru int afisare_matrice fix ca funcția afisare_matrice: i-am dat funcției o criză de identitate în propriul ei corp.
8. Am confundat octeții cu biții la sizeof(): notă mentală salvată în caiet — sizeof întoarce octeți (bytes), nu biți.

# Ce am învățat (nivel boss de C)
1. Programare dinamică aplicată pe Levenshtein: am construit matricea d de dimensiune (m+1) x (n+1) cu linia 0 și coloana 0 pentru șirul gol, am mapat corect indexarea 1-based din pseudocod la 0-based în C (s[i - 1], t[j - 1]) și am ales la fiecare pas minimul dintre ștergere, inserare și potrivire/substituire.
2. Arhitectură de memorie pe heap (int **): alocare în două etape (linii pointeri + coloane elemente int per linie), verificare explicită NULL la fiecare malloc, rollback curat pe ramura de eroare și eliberare în ordine inversă (free(mat[i]) înainte de free(mat)) fără scurgeri de memorie.
3. Semnalizare curată a erorilor: NULL la alocările de memorie pe pointeri (int **, char *) și -1 pentru Distanta_Levenshtein (unde orice distanță validă este >= 0).
4. Aritmetică de pointeri & tipuri: diferența clară între size_t (întreg fără semn >= 0) și sizeof(...) (dimensiunea în octeți, nu biți), plus transmiterea prin adresă (int *l) pentru a întoarce lungimea șirului.
5. Gestiunea intrărilor (stdin) și a bufferelor: citire controlată cu fgets într-un buffer, curățarea caracterului '\n', alocare exactă len + 1 pentru terminatorul '\0' și golirea bufferului după scanf("%d", ...) ca să nu strice următoarea citire.
6. Meniu interactiv & flux de control: buclă while(1) cu switch, blocuri {} dedicate pe ramurile case, tratarea intrărilor invalide și ieșire controlată.
7. Formatare și workflow: alinierea matricei cu %3d, castare explicită, organizare pe funcții independente și pregătire de repo Git (README.md + .gitignore).

# Raport de lucru: AI vs. Eu
1. **Ce am făcut eu (~65%):** structura modulară și ideea de meniu, scrierea funcțiilor, debugging-ul, testarea, comentariile cu personalitate și notițele de pe caiet.
2. **Ce a făcut AI-ul (~35%):** explicațiile pas cu pas (pseudocod, pointeri `int **`, `size_t` vs `sizeof`, `free` în ordine inversă), curățarea bufferului după `scanf` și structurarea documentației.
3. **Ore lucrate (mă certam cu AI-ul și laptopul):** 4 ore.
# Compilare și rulare

```bash
gcc -Wall -Wextra -fsanitize=address -std=c23 main.c -o levenshtein
./levenshtein





