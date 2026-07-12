#include <stdio.h>

int divide_into_channels(int N, int T, int idx, int durations[], int channels[], int sum1, int sum2, int memo[N+1][T+1]) {
    if (idx == N) {
        return 1; 
    }

    if (memo[idx][sum1] != -1) {
        return memo[idx][sum1] == 1;
    }

    int duration = durations[idx];

    if (sum1 + duration <= T) {
        channels[idx] = 1;
        if (divide_into_channels(N, T, idx + 1, durations, channels, sum1 + duration, sum2, memo)) {
            memo[idx][sum1] = 1;
            return 1;
        }
    }

    if (sum2 + duration <= T) {
        channels[idx] = 2;
        if (divide_into_channels(N, T, idx + 1, durations, channels, sum1, sum2 + duration, memo)) {
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

    int break_durations[N];
    int channels[N];
    int break_starts[N];

    int memo[N+1][T+1];

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= T; j++) {
            memo[i][j] = -1; 
        }
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &break_durations[i]);
        channels[i] = 0;
    }

    if (divide_into_channels(N, T, 0, break_durations, channels, 0, 0, memo)) {
        int timer_c1 = 0;
        int timer_c2 = 0;

        for (int i = 0; i < N; i++) {
            if (channels[i] == 1) {
                break_starts[i] = timer_c1;
                timer_c1 += break_durations[i];
                printf("Tecnico %d: in pausa da %d a %d (durata %d)\n", 
                       i + 1, break_starts[i], timer_c1, break_durations[i]);
            } else {
                break_starts[i] = timer_c2;
                timer_c2 += break_durations[i];
                printf("Tecnico %d: in pausa da %d a %d (durata %d)\n", 
                       i + 1, break_starts[i], timer_c2, break_durations[i]);
            }
        }
    } else {
        printf("No solution possible.\n");
    }

    return 0;
}