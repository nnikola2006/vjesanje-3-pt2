#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funkcija koja spaja dva stringa
char* dodaj(char *s1, char *s2);
// Funkcija koja sabira dva broja
int saberi(int a, int b);
// Glavna funkcija koja prolazi kroz argv i obrađuje -s i -b
void spoji_saberi(int argc, char *argv[], char* (*dodaj_f)(char*, char*), int (*saberi_f)(int, int));

int main(int argc, char *argv[])
{
    spoji_saberi(argc, argv, dodaj, saberi);

    return 0;
}

char* dodaj(char *s1, char *s2)
{
    size_t len = strlen(s1) + strlen(s2) + 1;
    char *rez = malloc(len);
    if(!rez)
    {
        printf("Greska pri alokaciji\n");
        exit(1);
    }
    
    strcpy(rez, s1);
    strcat(rez, s2);
    return rez;
}
int saberi(int a, int b)
{
    return a + b;
}
void spoji_saberi(int argc, char *argv[], char* (*dodaj_f)(char*, char*), int (*saberi_f)(int, int))
{
    char *rezString = calloc(1, sizeof(char));  // pocetni prazan string
    int suma = 0;
    int imaBrojeva = 0;

    if(!rezString)
    {
        printf("Greska u alokaciji\n");
        return;
    }
    
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-s") == 0) // obrada stringova
        {
            i++;
            while(i < argc && argv[i][0] != '-') // sve dok ne dodjemo do novog parametra
            {
                char *temp = dodaj_f(rezString, argv[i]);
                free(rezString);
                rezString = temp;
                i++;
            }
            i--; // jer ce se u for-u povecati
        }
        else if(strcmp(argv[i], "-b") == 0) // obrada brojeva
        {
            i++;
            while(i < argc && argv[i][0] != '-')
            {
                int broj = atoi(argv[i]);
                suma = saberi_f(suma, broj);
                imaBrojeva = 1;
                i++;
            }
            i--; // jer ce se u for-u povecati
        }
    }
    
    // Ispis rezultata
    if(imaBrojeva)
        printf("Suma brojeva je %d.", suma);
    
    if(strlen(rezString) > 0)
    {
        if(imaBrojeva) printf(" ");
        printf("\nString je '%s'.", rezString);
    }

    printf("\n");
    free(rezString);
}

