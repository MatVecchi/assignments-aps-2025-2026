#include <stdio.h>


int verifica_percorso(int D, int tot_punti, int punti[], int C, int L, int M, int print_mode) {
    int rimosse = 0;
    int ultimo_tenuto = 0;

    for (int i = 1; i < tot_punti; i++) {
        int p = punti[i];
        
        int obbligatorio = (p == C || p == L);
        int prossimo_obbligatorio = (p < C) ? C : L;
        
        if (p - punti[ultimo_tenuto] < D || (!obbligatorio && prossimo_obbligatorio - p < D)) {
            
            if (obbligatorio) {
                return 0; 
            } else {
                rimosse++;
                if (print_mode) {
                    printf("%d ", p);
                }
            }
            
        } else {
            ultimo_tenuto = i;
        }
    }
    
    return rimosse <= M;
}

int main() {
    int L, N, M, C;

    scanf("%d %d %d", &L, &N, &M);

    int tot_punti = N + 2;
    int punti[tot_punti];
    
    punti[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &punti[i]);
    }
    punti[N + 1] = L;
    
    scanf("%d", &C);

    int best_D = 1;
    
    for (int d = L; d >= 1; d--) {
        if (verifica_percorso(d, tot_punti, punti, C, L, M, 0)) {
            best_D = d;
            break;
        }
    }

    printf("Spaziatura massima: %d\n", best_D);
    printf("Stazioni da chiudere: ");
    
    verifica_percorso(best_D, tot_punti, punti, C, L, M, 1);
    printf("\n");

    return 0;
}