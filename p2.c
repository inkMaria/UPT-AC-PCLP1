// Programul La furat
/*
Intr-un fisier text se gasesc 100 de cuvinte sub cate pe un rand,
creati minim 20 de teste automate pentru fiecare cuvant.
Fiecare test va fi marcat intr-un fisier propriu care va spune daca testul a trecut,
cine a facut testul si cand s-a realizat (_date_time_)
fiecare nume de test fisier va fi compus din numele cuvantului testat insotit de numarul testului.
Observatie: Testele le faci cum vrei. (o sa le fur, multumesc frumos!!!!)
*/
// aici nu mai e joaca, o sa imprumut cateva teste din cursul de la siruri de caractere si poate ce-am mai facut la lab
// Doamne ajuta
// AICI MERGE SSCANF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#define NR_TESTE 20
#define Autor "Maria"
#define data_si_ora time

const char *nume_teste[NR_TESTE] = {
    "testpalindrom", "testlungime_nenula", "testfara_spatii", "testlitere_mici",
    "testlitere_mari", "testprima_litera_mare", "testfara_cifre", "testare_vocale",
    "testare_consoane", "testincepe_cu_vocala", "testtermina_cu_vocala", "testfara_cratima",
    "testare_litera_a", "testare_subsir_er", "testprefix_al", "testfara_duble_consecutive",
    "testordine_alfabetica", "testfrecventa_max_1", "testascii_standard", "testformat_valid"};

void scrie_test(const char *cuvant, int nr_test, const char *nume_test, int trecut)
{
    char nume_fisier[256], buf_timp[32];
    snprintf(nume_fisier, sizeof(nume_fisier), "teste_fisier/%s/test_%s_%d.txt", cuvant, cuvant, nr_test);

    time_t acum = data_si_ora(NULL);
    struct tm *t = localtime(&acum);
    strftime(buf_timp, sizeof(buf_timp), "%Y-%m-%d %H:%M:%S", t);

    FILE *ft = fopen(nume_fisier, "w");
    if (ft == NULL)
    {
        perror(nume_fisier);
        return;
    }
    fprintf(ft, "Nume test: %s\n", nume_test);
    fprintf(ft, "Cuvant: %s\n", cuvant);
    fprintf(ft, "Status: %s\n", trecut ? "TRECUT" : "PICAT");
    fprintf(ft, "Autor: %s\n", Autor);
    fprintf(ft, "_date_time_: %s\n", buf_timp);
    fclose(ft);
}

char litera_mica(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

int este_litera(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int este_vocala(char c)
{
    c = litera_mica(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

/* Cele 20 de teste */
int t1_palindrom(const char *s)
{
    int n = strlen(s);
    for (int i = 0; i < n / 2; i++)
        if (litera_mica(s[i]) != litera_mica(s[n - 1 - i]))
            return 0;
    return n > 0;
}
int t2_nenul(const char *s) { return strlen(s) > 0; }
int t3_fara_spatii(const char *s) { return strchr(s, ' ') == NULL; }
int t4_litere_mici(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] < 'a' || s[i] > 'z')
            return 0;
    return s[0] != '\0';
}
int t5_litere_mari(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] < 'A' || s[i] > 'Z')
            return 0;
    return s[0] != '\0';
}
int t6_prima_mare(const char *s) { return (s[0] >= 'A' && s[0] <= 'Z'); }
int t7_fara_cifre(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] >= '0' && s[i] <= '9')
            return 0;
    return 1;
}
int t8_are_vocale(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (este_vocala(s[i]))
            return 1;
    return 0;
}
int t9_are_consoane(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (este_litera(s[i]) && !este_vocala(s[i]))
            return 1;
    return 0;
}
int t10_inc_vocala(const char *s) { return s[0] != '\0' && este_vocala(s[0]); }
int t11_ter_vocala(const char *s)
{
    int n = strlen(s);
    return n > 0 && este_vocala(s[n - 1]);
}
int t12_fara_cratima(const char *s) { return strchr(s, '-') == NULL; }
int t13_are_a(const char *s) { return strchr(s, 'a') != NULL || strchr(s, 'A') != NULL; }
int t14_are_er(const char *s) { return strstr(s, "er") != NULL; }
int t15_prefix_al(const char *s) { return strncmp(s, "al", 2) == 0; }
int t16_fara_duble(const char *s)
{
    for (int i = 0; s[i] && s[i + 1]; i++)
        if (s[i] == s[i + 1])
            return 0;
    return 1;
}
int t17_ord_alfab(const char *s)
{
    for (int i = 0; s[i] && s[i + 1]; i++)
        if (s[i] > s[i + 1])
            return 0;
    return s[0] != '\0';
}
int t18_frecv_1(const char *s)
{
    for (int i = 0; s[i]; i++)
        if (strchr(s + i + 1, s[i]))
            return 0;
    return 1;
}
int t19_ascii(const char *s)
{
    for (int i = 0; s[i]; i++)
        if ((unsigned char)s[i] > 127)
            return 0;
    return 1;
}
int t20_valid(const char *s)
{
    int n = strlen(s);
    if (n == 0 || n >= 99)
        return 0;
    for (int i = 0; s[i]; i++)
    {
        unsigned char c = (unsigned char)s[i];
        if (c < 32 || c == 127) /* caractere de control ASCII */
            return 0;
    }
    return 1;
}

int main(void)
{
    char s[100], cale_folder[150], m;

    int (*functii_test[NR_TESTE])(const char *) = {
        t1_palindrom, t2_nenul, t3_fara_spatii, t4_litere_mici,
        t5_litere_mari, t6_prima_mare, t7_fara_cifre, t8_are_vocale,
        t9_are_consoane, t10_inc_vocala, t11_ter_vocala, t12_fara_cratima,
        t13_are_a, t14_are_er, t15_prefix_al, t16_fara_duble,
        t17_ord_alfab, t18_frecv_1, t19_ascii, t20_valid};

    FILE *f = fopen("fisierul_cu_cuvintele.txt", "r+"); // l-am deschis, acum e bun si +-ul ala
    if (f == NULL)
    {
        perror("Eroare, plangi \n"); // chiar nu mi-a mers :') (am uitat sa fac fisierul)
        return 1;
    } // nu l-am furat din p1.c

    mkdir("teste_fisier", 0755); // ma cunosc cu mkdir de la terminal #linux lover

    printf("Ai nevoie sa vezi cuvintele din fisier in consola? y/n ");
    scanf("%c", &m);
    switch (m)
    {
    case 'n':
        printf("Multumesc frumos! ");
        break;
    case 'y':
        while (fscanf(f, "%99s", s) == 1)
        {
            printf("[%s] \n", s);
        } // AM PUS /n IN LOC DE \n lol T-T
        break;
    default:
        break;
    }
    rewind(f);                        // pun toporul [(fopen(f) dupa fclose(f)] la testul mare (si nota tot un topor 7)
    while (fscanf(f, "%99s", s) == 1) // Cursul septe (7), pagina 49
    {
        snprintf(cale_folder, sizeof(cale_folder), "teste_fisier/%s", s);
        mkdir(cale_folder, 0755);

        for (int i = 0; i < NR_TESTE; i++)
        {
            int ok = functii_test[i](s);
            scrie_test(s, i + 1, nume_teste[i], ok);
        }
    } // am invatat de la p1.c sa dau copy paste

    fclose(f); // singurul rand !scris de mine
    return 0;
}