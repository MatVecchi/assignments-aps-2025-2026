#include <stdio.h>

int dividi_in_canali_memo(int N, int T, int idx, int durate[], int canali[], int sum1, int sum2, int memo[N+1][T+1]) {
    if (idx == N) {
        return 1; 
    }

    if (memo[idx][sum1] != -1) {
        return memo[idx][sum1] == 1;
    }

    int durata = durate[idx];

    if (sum1 + durata <= T) {
        canali[idx] = 1;
        if (dividi_in_canali_memo(N, T, idx + 1, durate, canali, sum1 + durata, sum2, memo)) {
            memo[idx][sum1] = 1;
            return 1;
        }
    }

    if (sum2 + durata <= T) {
        canali[idx] = 2;
        if (dividi_in_canali_memo(N, T, idx + 1, durate, canali, sum1, sum2 + durata, memo)) {
            memo[idx][sum1] = 1;
            return 1;
        }
    }

    memo[idx][sum1] = 0;
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

    int memo[N+1][T+1];

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= T; j++) {
            memo[i][j] = -1; 
        }
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &durate_pause[i]);
        canali[i] = 0;
    }

    if (dividi_in_canali_memo(N, T, 0, durate_pause, canali, 0, 0, memo)) {
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