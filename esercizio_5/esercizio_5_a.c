#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    int reliability;
    int criticality;
} Candidate;

void evaluate_current_team(int P, Candidate *candidates, int *current_team, int *best_team, int *max_quality) {
    int min_reliability = INT_MAX;
    int max_criticality = INT_MIN;

    for (int i = 0; i < P; i++) {
        int index = current_team[i];
        if (candidates[index].reliability < min_reliability) {
            min_reliability = candidates[index].reliability;
        }
        if (candidates[index].criticality > max_criticality) {
            max_criticality = candidates[index].criticality;
        }
    }

    int quality = min_reliability - max_criticality;
    if (quality > *max_quality) {
        *max_quality = quality;
        for (int i = 0; i < P; i++) {
            best_team[i] = current_team[i];
        }
    }
}

void explore_decision_tree(int candidate_index, int selected, int C, int P, Candidate *candidates, int *current_team, int *best_team, int *max_quality) {
    if (selected == P) {
        evaluate_current_team(P, candidates, current_team, best_team, max_quality);
        return;
    }

    if (candidate_index == C) {
        return;
    }

    current_team[selected] = candidate_index;
    explore_decision_tree(candidate_index + 1, selected + 1, C, P, candidates, current_team, best_team, max_quality);
    explore_decision_tree(candidate_index + 1, selected, C, P, candidates, current_team, best_team, max_quality);
}

int main() {
    int C, P;
    int max_quality = INT_MIN;
    
    scanf("%d %d", &C, &P);

    Candidate candidates[C];
    int current_team[P];
    int best_team[P];

    for (int i = 0; i < C; i++) {
        candidates[i].id = i;
        printf("\nInserisci i dati per il candidato %d:\n", i + 1);
        scanf("%d %d", &candidates[i].reliability, &candidates[i].criticality);
    }

    explore_decision_tree(0, 0, C, P, candidates, current_team, best_team, &max_quality);

    if (max_quality != INT_MIN) {
        printf("La qualita massima ottenibile e: %d\n", max_quality);
        printf("Il team ottimo e composto dai candidati: ");
        for (int i = 0; i < P; i++) {
            printf("%d ", candidates[best_team[i]].id);
        }
    } else {
        printf("\nNessun team valido trovato.\n");
    }

    return 0;
}