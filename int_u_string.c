    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    #include <stdlib.h>
    
    char* formiraj(int n, ...);
    
    int main()
    {
        char* rez;
        rez = formiraj(3, 123, 456, 789);
    
        printf("%s\n", rez);
    
        free(rez);
    
        return 0;
    }   
    
    char* formiraj(int n, ...)
    {
        va_list pok_arg;
        char* rezultat = calloc(1, sizeof(char));    
        char temp[50];
    
        va_start(pok_arg, n);
        int broj; // broj koji se grabi iz arg 
        for(int i = 0; i < n; i++)
        {
            broj = va_arg(pok_arg, int);
    
            itoa(broj, temp, 10); // baza 10 (decimalni broj)
    
            rezultat = realloc(rezultat, strlen(rezultat) + strlen(temp) + 1);
            strcat(rezultat, temp);
        }
        va_end(pok_arg);
    
        return rezultat;
    }
