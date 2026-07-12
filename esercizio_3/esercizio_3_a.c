#include <stdio.h>

int divide_into_channels(int current_technician, int N, int T, int durations[], int channels[], int sum_c1, int sum_c2) {
    if (current_technician == N) {
        return 1; 
    }

    int duration = durations[current_technician];

    if (sum_c1 + duration <= T) {
        channels[current_technician] = 1;
        if (divide_into_channels(current_technician + 1, N, T, durations, channels, sum_c1 + duration, sum_c2)) {
            return 1;
        }
    }

    if (sum_c2 + duration <= T) {
        channels[current_technician] = 2;
        if (divide_into_channels(current_technician + 1, N, T, durations, channels, sum_c1, sum_c2 + duration)) {
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

    int break_durations[N];
    int channels[N];
    int break_starts[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &break_durations[i]);
        channels[i] = 0;
    }

    if (divide_into_channels(0, N, T, break_durations, channels, 0, 0)) {
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
        printf("Nessuna soluzione possibile.\n");
    }

    return 0;
}