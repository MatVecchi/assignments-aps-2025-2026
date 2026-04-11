#include <stdio.h>
#include <time.h>

int main() {
    int T, A, B, C;
    scanf("%d %d %d %d", &T, &A, &B, &C);

    int best_tasks = 0;
    int best_leftover = T;

    int maxA = T / A;
    int maxB = T / B;
    int maxC = T / C;

    clock_t start = clock();
    for (int x = 0; x <= maxA; ++x) {
        for (int y = 0; y <= maxB; ++y) {
            for (int z = 0; z <= maxC; ++z) {
                int used = x*A + y*B + z*C;
                if (used > T) continue;
                int leftover = T - used;
                int tasks = x + y + z;
                if (leftover < best_leftover) {
                    best_leftover = leftover;
                    best_tasks = tasks;
                } else if (leftover == best_leftover && tasks > best_tasks) {
                    best_tasks = tasks;
                }
            }
        }
    }
    clock_t end = clock();
    printf("compiti svolti: %d, residuo: %d\nTempo trascorso: %.5f", best_tasks, best_leftover, (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
