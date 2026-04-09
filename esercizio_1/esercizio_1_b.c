#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5
#define MAX_STRING_LENGTH 10

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)
#define HASH_BITS 16

typedef struct Node {
    char name[MAX_STRING_LENGTH];
    struct Node* next;
} Node;

int canInsert(char lastStr[MAX_STRING_LENGTH], char str[MAX_STRING_LENGTH], Node** hashtable);
void insert(char str[MAX_STRING_LENGTH], Node** hashtable);

int main(int argc, char const *argv[])
{
    char lastStr[MAX_STRING_LENGTH] = "";
    char str[MAX_STRING_LENGTH];
    int user = 0;
    Node* names[hashsize(HASH_BITS)] = {NULL};
    for(int i = 0; i < N * 2; i++){
        printf("Utente %d inserisci un nome: ", (i % 2) + 1);
        scanf("%s", str);
        clock_t start = clock();
        if(!canInsert(lastStr, str, names)){
            user += (i % 2) + 1;
        }
        insert(str, names);
        strncpy(lastStr, str, MAX_STRING_LENGTH);
         clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tempo impiegato: %f secondi\n", time_spent);
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

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
  unsigned long hash, i;
  for (hash = 0, i = 0; i < len; i++) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash & hashmask(bits);
} 

int canInsert(char lastStr[MAX_STRING_LENGTH], char str[MAX_STRING_LENGTH], Node** hashtable){
    char last_char = lastStr[strlen(lastStr) - 1];
    if(str[0] != last_char && strlen(lastStr) > 0) return 0;
    
    unsigned long hash = oaat(str, strlen(str), HASH_BITS);
    Node* current = hashtable[hash];
    while(current != NULL){
        if(strcmp(current->name, str) == 0){
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void insert(char str[MAX_STRING_LENGTH], Node** hashtable){
    if(!canInsert(str, str, hashtable)) return;

    unsigned long hash = oaat(str, strlen(str), HASH_BITS);
    Node* new_node = malloc(sizeof(Node));
    new_node->next = hashtable[hash];
    strcpy(new_node->name, str);
    hashtable[hash] = new_node;
}