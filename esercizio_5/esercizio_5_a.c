#include <stdio.h>

typedef struct {
    int id;
    int reliability;
    int criticality;
} Candidate;

void find_best_team(int C, int P, Candidate candidates[], int best_team[], int *max_quality) {
    int solution_found = 0;
    int temp_team[C];
    
    *max_quality = -1000000000; 

    for (int i = 0; i < C; i++) {
        int threshold_rel = candidates[i].reliability;

        for (int j = 0; j < C; j++) {
            int threshold_crit = candidates[j].criticality;
            int theoretical_quality = threshold_rel - threshold_crit;
            
            int valid_count = 0;

            for (int k = 0; k < C; k++) {
                if (candidates[k].reliability >= threshold_rel && 
                    candidates[k].criticality <= threshold_crit) {
                    
                    temp_team[valid_count] = candidates[k].id;
                    valid_count++;
                }
            }

            if (valid_count >= P) {
                if (!solution_found || theoretical_quality > *max_quality) {
                    *max_quality = theoretical_quality;
                    solution_found = 1;
                    
                    for (int k = 0; k < P; k++) {
                        best_team[k] = temp_team[k];
                    }
                }
            }
        }
    }
}

int main() {
    int C, P;
    
    scanf("%d %d", &C, &P);

    Candidate candidates[C];
    int best_team[P];
    int max_quality;

    for (int i = 0; i < C; i++) {
        candidates[i].id = i + 1;
        scanf("%d %d", &candidates[i].reliability, &candidates[i].criticality);
    }
    
    find_best_team(C, P, candidates, best_team, &max_quality);
    
    printf("Selected candidates: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", best_team[i]);
    }
    printf("\nTeam quality: %d\n", max_quality);

    return 0;
}