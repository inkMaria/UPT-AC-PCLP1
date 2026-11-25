// program narcisist
/*
Cerinta: Realizati un program C care copiaza intr-un fisier text insusi programul scris.
*/
/*Ce notiuni mi-ar trebuii(cred eu):
     1.realloc:
     void *realloc(void *ptr, size_t dim_noua);
    2.fgets (siruri de caractere 100%)
     3.lucru cu fisierul (logic)
     4.sscanf ar merge
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    char s[100];
    FILE *f = fopen("fisier.txt", "w+"); // creaza fisierul nostru
    /* De ce am pus w+ si nu w?
    deoarece *citeste*, scrie si sterge conținutul vechi
    ... de fapt puteam si fara + (ca nu are ce citi)*/

    FILE *g = fopen(__FILE__, "r"); // mi-am deschis fisierul programului #smart
    if ((g == NULL) || (f == NULL))
    {
        perror("Eroare, plangi"); // normal, ar trb sa inchid cele doua fisiere separat, dar sunt haiter (nu stiu cum)
        if (f != NULL) fclose(f);
        if (g != NULL) fclose(g); //mersi gemini, la 00:44 nu gandesc 
        return 1;
    }
    while (fgets(s, sizeof(s), g) != NULL) // fgets, merge in fisierul p1.c si extrage dimensiunea cu sizeof, ADICA da ctrl copy
    {
        fputs(s, f); // aici da ctrl paste
    }

    fclose(f); // am inchis fisierul nostru text, noapte buna!
    fclose(g); // nu-l uitam nici pe asta
    return 0;
}
