#include <stdio.h>

int is_valid(int D, int L, int M, int C, int N, int stations[]) {
    int count = 0;

    int last_kept = 0;
    for (int i = 0; i < N; i++) {
        if (stations[i] >= C) break;
        
        if (stations[i] - last_kept < D || C - stations[i] < D) {
            count++;
        } else {
            last_kept = stations[i];
        }
    }
    if (C - 0 < D) return 0;

    last_kept = C;
    for (int i = 0; i < N; i++) {
        if (stations[i] <= C) continue;
        
        if (stations[i] - last_kept < D || L - stations[i] < D) {
            count++;
        } else {
            last_kept = stations[i];
        }
    }
    if (L - C < D) return 0;

    return count <= M;
}

int main() {
    int L, N, M, C;

    scanf("%d %d %d", &L, &N, &M);

    int stations[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &stations[i]);
    }
    
    scanf("%d", &C);

    int low = 1, high = L;
    int best_D = 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (is_valid(mid, L, M, C, N, stations)) {
            best_D = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("Spaziatura massima: %d\n", best_D);
    printf("Stazioni da chiudere: ");

    int last_kept = 0;
    for (int i = 0; i < N; i++) {
        if (stations[i] >= C) break;
        if (stations[i] - last_kept < best_D || C - stations[i] < best_D) {
            printf("%d ", stations[i]);
        } else {
            last_kept = stations[i];
        }
    }
    
    last_kept = C;
    for (int i = 0; i < N; i++) {
        if (stations[i] <= C) continue;
        if (stations[i] - last_kept < best_D || L - stations[i] < best_D) {
            printf("%d ", stations[i]);
        } else {
            last_kept = stations[i];
        }
    }
    
    printf("\n");
    return 0;
}