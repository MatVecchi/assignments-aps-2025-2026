#include <stdio.h>

int verify_path(int D, int total_points, int points[], int C, int L, int M, int print_mode) {
    int removed = 0;
    int last_kept = 0;

    for (int i = 1; i < total_points; i++) {
        int p = points[i];
        
        int mandatory = (p == C || p == L);
        int next_mandatory = (p < C) ? C : L;
        
        if (p - points[last_kept] < D || (!mandatory && next_mandatory - p < D)) {
            
            if (mandatory) {
                return 0; 
            } else {
                removed++;
                if (print_mode) {
                    printf("%d ", p);
                }
            }
            
        } else {
            last_kept = i;
        }
    }
    
    return removed <= M;
}

int main() {
    int L, N, M, C;

    scanf("%d %d %d", &L, &N, &M);

    int total_points = N + 2;
    int points[total_points];
    
    points[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &points[i]);
    }
    points[N + 1] = L;
    
    scanf("%d", &C);

    int best_D = 1;
    
    for (int d = L; d >= 1; d--) {
        if (verify_path(d, total_points, points, C, L, M, 0)) {
            best_D = d;
            break;
        }
    }

    printf("Spaziatura massima: %d\n", best_D);
    printf("Stazioni da chiudere: ");
    
    verify_path(best_D, total_points, points, C, L, M, 1);
    printf("\n");

    return 0;
}