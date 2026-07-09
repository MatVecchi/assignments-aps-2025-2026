#include <stdio.h>

int dividi_in_canali(int tecnico_corrente, int N, int T, int durate[], int canali[], int somma_c1, int somma_c2) {
    if (tecnico_corrente == N) {
        return 1; 
    }

    int durata = durate[tecnico_corrente];

    if (somma_c1 + durata <= T) {
        canali[tecnico_corrente] = 1;
        if (dividi_in_canali(tecnico_corrente + 1, N, T, durate, canali, somma_c1 + durata, somma_c2)) {
            return 1;
        }
    }

    if (somma_c2 + durata <= T) {
        canali[tecnico_corrente] = 2;
        if (dividi_in_canali(tecnico_corrente + 1, N, T, durate, canali, somma_c1, somma_c2 + durata)) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int T, N;
    
    if (scanf("%d %d", &T, &N) != 2) {
        return 1;
    }

    int durate_pause[N];
    int canali[N];
    int inizio_pause[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &durate_pause[i]);
        canali[i] = 0;
    }

    if (dividi_in_canali(0, N, T, durate_pause, canali, 0, 0)) {
        int timer_c1 = 0;
        int timer_c2 = 0;

        for (int i = 0; i < N; i++) {
            if (canali[i] == 1) {
                inizio_pause[i] = timer_c1;
                timer_c1 += durate_pause[i];
                printf("Tecnico %d: in pausa da min %d a min %d (durata %d)\n", 
                       i + 1, inizio_pause[i], timer_c1, durate_pause[i]);
            } else {
                inizio_pause[i] = timer_c2;
                timer_c2 += durate_pause[i];
                printf("Tecnico %d: in pausa da min %d a min %d (durata %d)\n", 
                       i + 1, inizio_pause[i], timer_c2, durate_pause[i]);
            }
        }
    } else {
        printf("Nessuna soluzione possibile.\n");
    }

    return 0;
}