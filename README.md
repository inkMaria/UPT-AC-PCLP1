# Tema 2 — Exercițiul 1: Programul „narcisist” (`p1.c`)

Un program în **C** care își citește propriul cod sursă și îl copiază într-un fișier text (`fisier.txt`), păstrând structura liniilor și formatarea.

---

## Cum funcționează

1. Deschide fișierul destinație `fisier.txt` în modul scriere (`"w+"`) și propriul fișier sursă prin macro-ul `__FILE__` în modul citire (`"r"`).
2. Verifică dacă vreunul dintre fișiere nu s-a putut deschide (`NULL`), afișează eroarea cu `perror` și închide eventualul fișier deschis înainte de a ieși.
3. Citește linie cu linie din sursă cu `fgets` și scrie fiecare linie în `fisier.txt` cu `fputs`.
4. Închide ambele fișiere cu `fclose` la final.

## Wall of Shame & Lecții învățate
1. Prima încercare (while (1) cu realloc pe int *v): am pornit cu un șablon de vector dinamic pentru numere întregi și am uitat complet main sau condiția de oprire (undefined reference to main + buclă infinită).
2. A doua încercare (fprintf(f, "%99s", s) == 0 + fscanf): am încurcat ordinea argumentelor la fscanf, am pus condiția invers la fprintf și era să stric formatarea codului cu %s (care mănâncă spațiile și liniile goale).
3. Lenea de la 00:44 la fopen: am verificat (g == NULL) || (f == NULL) dintr-un foc, fără să închid separat fișierul care apucase să se deschidă (reparat ulterior cu if (f != NULL) fclose(f);).

## Împărțirea muncii (cine ce a făcut)
### Ce am făcut eu:
1. Am ales ideea și structura fișierului (p1.c -> fisier.txt), am folosit __FILE__ ca să-și deschidă singur sursa.
2. Am identificat că am nevoie de fgets pentru șiruri de caractere și lucru cu fișiere.
3. Am scris codul efectiv, am reparat bucla cu fgets + fputs, am testat compilarea cu -Wall -Wextra -fsanitize=address și am pus comentariile.

### Ce a făcut AI-ul (Gemini):
1. Mi-a explicat de ce fscanf + fprintf("%s") nu merg pentru copiat cod și cum funcționează concret perechea fgets + fputs.
2. Mi-a dat hint-ul cu închiderea separată a fișierelor pe ramura de eroare (if (f != NULL) fclose(f);).
3. M-a ajutat să structurez acest README.md.

## Compilare și rulare

```bash
gcc p1.c -o p1 -Wall -Wextra -fsanitize=address
./p1