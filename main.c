// Sloganul Visual Studio-ului despre mine: "Programator prost, ma faci de ras!"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // e mai inchis la culoare, inseamna ca nu am utilizat nicio functie din biblioteca respectiva (INCA)

int minim(int a, int b, int c)
{
    int m = a;
    if (m > b)
        m = b;
    if (m > c)
        m = c;
    return m;
}

int **matrice(int linii, int coloane)
{
    int i, k;
    int **mat = (int **)malloc((size_t)linii * sizeof(int *)); // size_t e un tip de date intreg (>=0) returnat de sizeof
    if (mat == NULL)
    {
        return NULL; // am pus return NULL ca sa nu primesc erori la compilare
    }
    for (i = 0; i < linii; i++)
    {
        mat[i] = (int *)malloc((size_t)coloane * sizeof(int));
        if (mat[i] == NULL)
        {
            for (k = 0; k < i; k++)
            {
                free(mat[k]);
            }
            free(mat);
            return NULL;
        }
        /*
        Daca dai direct free(mat), stergi doar lista cu adresele liniilor,
        iar blocurile cu numerele liniilor raman blocate in RAM fara sa mai
        ai vreo adresa catre ele (memory leak). De aceea le eliberezi
        in ordine inversa: intai fiecare free(mat[i]), si abia la final free(mat).
        (Credit AI pentru explicatie)
        */
    }
    return mat;
}
void eliberare_matrice(int **matrice, int linii)
{
    if (matrice == NULL)
    {
        return;
    }

    for (int i = 0; i < linii; i++)
    {
        free(matrice[i]);
    }

    free(matrice);
}
/*
    De ce am facut 2 "curatenii"? ((free) si in eliberare_matrice si in matrice)
1. In functia matrice(), este planul de rezerva.
        Daca am alocat linia 0, linia 1, linia 2, si fix la linia 3
        crapa malloc (intoarce NULL), nu pot pur si simplu sa ies cu return NULL;
        (pentru ca liniile 0, 1, 2 deja ocupa memorie.)
        Asa ca doar pe acea ramura de eroare eliberez ce am apucat sa aloc pana atunci.
2. In functia eliberare_matrice e curatenia normala. (fara curatenie = dezordine in memorie)
*/
/*
    Nice! Si de ce nu ai eliberat si elementele din coloana?
        Pentru ca coloanele nu au un malloc separat al lor,
        ele sunt doar numerele aflate in interiorul fiecarei linii!
        (Credit AI, mersi mult de raspuns!)

*/
void afisare_matrice(int **d, const char *s, const char *t, int m, int n)
{
    printf("\nMatricea Levenshtein (%dx%d):\n      \"\" ", m + 1, n + 1); // Multumesc, Doamne, ca am scapat de EA
    for (int j = 0; j < n; j++)
    {
        printf("  %c ", t[j]);
    }
    printf("\n");
    for (int i = 0; i <= m; i++)
    {
        if (i == 0)
            printf(" \"\" ");
        else
            printf("  %c ", s[i - 1]);

        for (int j = 0; j <= n; j++)
        {
            printf("%3d ", d[i][j]);
        }
        printf("\n");
    }
}

/*
    STAI, DE CE SUNT 3 FOR-URI? (PRIMUL FOR PENTRU CE E?)
    Matricea d are m + 1 linii (de la 0 la m) si n + 1 coloane (de la 0 la n), pentru ca linia 0 si coloana 0 reprezinta sirul gol "".
    Primul for (j de la 0 la n - 1) este antetul de sus (literele din t).
    Afiseaza literele cuvantului t deasupra coloanelor 1..n (T  E  X  T).
    Are < n (nu <= n), pentru ca un cuvant de lungime n are indicii 0..n-1. (AM inteles!)
    Printeaza fiecare valoare d[i][j] aliniata frumos cu %3d. (Artist, imi place!)

*/
int lungime_text(const char *sir, int *l) // ca sa nu folosesc strlen (#hater_siruri)
{
    int contor = 0;
    while (sir[contor] != '\0')
        contor++;
    if (l != NULL)
    {
        *l = contor;
    }
    return contor;
} // cu l vreau sa returnez lungimea, mai clar

int Distanta_Levenshtein(const char *s, const char *t, int arata_matricea)
{
    int m = 0, n = 0;
    lungime_text(s, &m);
    lungime_text(t, &n);
    // poti da si NULL ca al doilea parametru
    int **d = matrice(m + 1, n + 1);
    if (d == NULL)
    {
        printf("Eroare alocare memorie #plangem \n");
        return -1;
    }
    for (int i = 0; i <= m; i++)
    {
        d[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        d[0][j] = j;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;

            d[i][j] = minim(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost);
        }
    }

    if (arata_matricea)
    {
        afisare_matrice(d, s, t, m, n);
    }

    int rezultat = d[m][n];
    eliberare_matrice(d, m + 1);

    return rezultat;
}
/*  Ce face return -1?
    O distanta Levenshtein este mereu un numar >= 0 (nu poti avea "minus 1 operatii de editare").
    Asa ca -1 este folosit ca semnal de eroare (la fel ca NULL la pointeri):
    ii spune celui care a apelat functia:
    "ceva a crapat pe drum (aici alocarea memoriei), nu am putut calcula o distanta valida".
    (Mai trebuie sa mai dau credit? #vai_de_mine)
*/

char *citeste_sirul(void)
{
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return NULL;
    }
    int len = lungime_text(buffer, NULL);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }
    char *sir = (char *)malloc((size_t)(len + 1) * sizeof(char));
    if (sir == NULL)
    {
        return NULL;
    }
    for (int i = 0; i <= len; i++)
    {
        sir[i] = buffer[i];
    }

    return sir;
}
// Am vrut sa fiu fancy si am facut si meniu
int main()
{
    int optiune = 0;

    while (1)
    {
        printf("\n=== Distanta Levenshtein ===\n");
        printf("1. Testul din cerinta (\"TEST\" vs \"TEXT\")\n");
        printf("2. Doua siruri citite de la tastatura\n");
        printf("3. Afara (iesire)\n");
        printf("Alegeti o optiune: ");

        if (scanf("%d", &optiune) != 1)
        {
            printf("Intrare invalida! Introduceti un numar.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
            continue;
        }
        /* Curatam restul liniei (inclusiv '\n'-ul lasat de scanf) */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        switch (optiune)
        {
        case 1:
        {
            int d_test = Distanta_Levenshtein("TEST", "TEXT", 1);
            if (d_test != -1)
            {
                printf("\nRezultat \"TEST\" vs \"TEXT\": %d\n", d_test);
            }
            break;
        }

        case 2:
        {
            printf("\nIntrodu primul sir: ");
            char *s1 = citeste_sirul();

            printf("Introdu al doilea sir: ");
            char *s2 = citeste_sirul();

            if (s1 != NULL && s2 != NULL)
            {
                int d_user = Distanta_Levenshtein(s1, s2, 1);
                if (d_user != -1)
                {
                    printf("\nRezultat \"%s\" vs \"%s\": %d\n", s1, s2, d_user);
                }
            }
            else
            {
                printf("Eroare la citirea/alocarea sirurilor!\n");
            }
            free(s1);
            free(s2);
            break;
        }
        case 3:
            printf("La revedere!\n");
            return 0;

        default:
            printf("Optiune invalida! Alege 1, 2 sau 3.\n");
            break;
        }
    }
    return 0;
}