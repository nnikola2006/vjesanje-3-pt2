#include <stdio.h>

void serija(int *niz, int n, int (*s)(int), int **pocetak, int *duzina);

int je_paran(int x) { return x % 2 == 0; }
int je_pozitivan(int x) { return x > 0; }

int main()
{
    int n;
    do
    {
        scanf("%d", &n);
    } while (n < 1);
    
    int* niz = (int*)calloc(n, sizeof(int));
    if(!niz)
    {
        printf("Greska u alociranju\n");
        return 0;
    }
    for(int i = 0; i < n; i++)
        scanf("%d", niz[i]);

    int* pocetak = NULL;
    int duzina;

    serija(niz, n, je_paran, &pocetak, &duzina);
    printf("Najduza serija parnih:\n");
    for(int i = 0; i < duzina; i++)
        printf("%d ", pocetak[i]);
    printf("\n");

    serija(niz, n, je_pozitivan, &pocetak, &duzina);
    printf("Najduza serija pozitivnih:\n");
    for(int i = 0; i < duzina; i++)
        printf("%d ", pocetak[i]);
    printf("\n");
    
    return 0;
}

void serija(int *niz, int n, int (*s)(int), int **pocetak, int *duzina)
{
    int max_duzina = 0;
    int trenutna_duzina = 0;
    int *trenutni_pocetak = NULL;
    *pocetak = NULL; // ovo je ustvari pocetak naseg najduzeg niza elemenata koji ispunjavaju uslov
    *duzina = 0; // duzina tog naseg najduzeg niza elemenata

    for(int i = 0; i < n; i++)
    {
        if(s(niz[i])) // element zadovoljava svojstvo
        {
            if(trenutna_duzina == 0) // pocetak nove serije
                trenutni_pocetak = &niz[i];

            trenutna_duzina++;

            if(trenutna_duzina > max_duzina)
            {
                max_duzina = trenutna_duzina;
                *pocetak = trenutni_pocetak;
                *duzina = max_duzina;
            }
        }
        else
        {
            trenutna_duzina = 0; // serija prekinuta
        }
    }
}
