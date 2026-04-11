#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NEG -1000000000

int A, B, C;
int *memo;

int solve(int i) {
    if (i < 0) return NEG;     
    if (i == 0) return 0;
    if (memo[i] != NEG - 1)
        return memo[i];

    int best = NEG;

    int r1 = solve(i - A);
    if (r1 != NEG) best = (r1 + 1 > best) ? r1 + 1 : best;

    int r2 = solve(i - B);
    if (r2 != NEG) best = (r2 + 1 > best) ? r2 + 1 : best;

    int r3 = solve(i - C);
    if (r3 != NEG) best = (r3 + 1 > best) ? r3 + 1 : best;

    memo[i] = best;
    return best;
}

int main() {
    int T;
    scanf("%d %d %d %d", &T, &A, &B, &C);

    clock_t start = clock();
    memo = malloc((T + 1) * sizeof(int));
    for (int i = 0; i <= T; i++){
        memo[i] = NEG - 1;
    }

    int best_i = -1;
    int best_tasks = NEG;

    for (int i = T; i >= 0; i--) {
        int r = solve(i);
        if (r != NEG) {
            best_i = i;
            best_tasks = r;
            break;
        }
    }

    int leftover = T - best_i;
    
    clock_t end = clock();
    printf("compiti svolti: %d, residuo: %d\nTempo trascorso: %.5f", best_tasks, leftover, (double)(end - start) / CLOCKS_PER_SEC);

    free(memo);
    return 0;
}
