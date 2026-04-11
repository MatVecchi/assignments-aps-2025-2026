#include <stdio.h>
#include <string.h>

#define N 5
#define MAX_STRING_LENGTH 10

int canInsert(char names[][MAX_STRING_LENGTH], int count, const char str[MAX_STRING_LENGTH]);
int insert(char names[][MAX_STRING_LENGTH], int* count, const char str[MAX_STRING_LENGTH]);

int main(){
    char names[N * 2][MAX_STRING_LENGTH];
    int count = 0;
    int user = 0;
    for(int i = 0; i < N * 2; i++){
        printf("Utente %d inserisci un nome: ", (i % 2) + 1);
        scanf("%s", names[i]);

        int res = insert(names, &count, names[i]);
        if(!res){
            user += (i % 2) + 1;
        }
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

int insert(char names[][MAX_STRING_LENGTH], int* count, const char str[MAX_STRING_LENGTH]){
    if(!canInsert(names, *count, str)) return 0;
    
    strncpy(names[*count], str, MAX_STRING_LENGTH);
    (*count)++;
    return 1;
}