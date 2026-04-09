#include <stdio.h>
#include <string.h>
#include <windows.h>

#define N 5
#define MAX_STRING_LENGTH 10

int canInsert(char names[][MAX_STRING_LENGTH], int count, const char str[MAX_STRING_LENGTH]);
void insert(char names[][MAX_STRING_LENGTH], int* count, const char str[MAX_STRING_LENGTH]);

int main(){
    char names[N * 2][MAX_STRING_LENGTH];
    int count = 0;
    int user = 0;
    for(int i = 0; i < N * 2; i++){
        printf("Utente %d inserisci un nome: ", (i % 2) + 1);
        scanf("%s", names[i]);
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);


        if(!canInsert(names, i, names[i])){
            user += (i % 2) + 1;
        }

        insert(names, &count, names[i]);
        QueryPerformanceCounter(&end);

        double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("Tempo: %.9f secondi\n", elapsed);


    }

    if(user != 0) {
        if(user > 2){
            printf("Entrambi gli utenti hanno inserito un nome non valido, chiusura programma...\n");
        } else {
            printf("L'utente %d ha inserito un nome non valido, chiusura programma...\n", user);
        }
    } else {
        printf("Tutti i nomi inseriti sono validi, chiusura programma...\n");
    }
    return 0;
}

int canInsert(char names[][MAX_STRING_LENGTH], int count, const char str[MAX_STRING_LENGTH]){
    if(count == 0) return 1;

    size_t last_len = strlen(names[count - 1]);
    char last_char = names[count - 1][last_len - 1];
    if(str[0] != last_char) return 0;

    for(int i = 0; i < count; i++){
        if(strcmp(names[i], str) == 0){
            return 0;
        }
    }

    return 1;
}

void insert(char names[][MAX_STRING_LENGTH], int* count, const char str[MAX_STRING_LENGTH]){
    if(!canInsert(names, *count, str)) return;
    
    strncpy(names[*count], str, MAX_STRING_LENGTH);
    (*count)++;
}