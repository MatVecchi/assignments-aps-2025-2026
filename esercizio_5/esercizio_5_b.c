#include <stdio.h>

typedef struct {
    int id;
    int reliability;
    int criticality;
} Candidate;

typedef struct {
    Candidate **array; 
    int size;
    int capacity;
} MaxHeap;

void swap_candidates(Candidate **a, Candidate **b) {
    Candidate *temp = *a;
    *a = *b;
    *b = temp;
}

void sift_up(MaxHeap *heap, int idx) {
    while (idx > 0 && heap->array[(idx - 1) / 2]->criticality < heap->array[idx]->criticality) {
        swap_candidates(&heap->array[(idx - 1) / 2], &heap->array[idx]);
        idx = (idx - 1) / 2;
    }
}

void sift_down(MaxHeap *heap, int idx) {
    int max_idx = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    
    if (left < heap->size && heap->array[left]->criticality > heap->array[max_idx]->criticality) {
        max_idx = left;
    }
    if (right < heap->size && heap->array[right]->criticality > heap->array[max_idx]->criticality) {
        max_idx = right;
    }
    
    if (max_idx != idx) {
        swap_candidates(&heap->array[idx], &heap->array[max_idx]);
        sift_down(heap, max_idx);
    }
}

void heap_push(MaxHeap *heap, Candidate *c) {
    heap->array[heap->size] = c;
    heap->size++;
    sift_up(heap, heap->size - 1);
}

void heap_pop(MaxHeap *heap) {
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    sift_down(heap, 0);
}

int cmp_rel_desc(const void *a, const void *b) {
    return ((Candidate*)b)->reliability - ((Candidate*)a)->reliability;
}

void find_best_team(int C, int P, Candidate candidates[], int best_team[], int *max_quality) {
    
    if (P == 1) {
        *max_quality = candidates[0].reliability - candidates[0].criticality;
        best_team[0] = candidates[0].id;
        for (int i = 1; i < C; i++) {
            int q = candidates[i].reliability - candidates[i].criticality;
            if (q > *max_quality) {
                *max_quality = q;
                best_team[0] = candidates[i].id;
            }
        }
        return;
    }

    qsort(candidates, C, sizeof(Candidate), cmp_rel_desc);

    MaxHeap heap;
    heap.capacity = P - 1;
    heap.size = 0;
    heap.array = malloc(sizeof(Candidate*) * heap.capacity);

    *max_quality = -1000000000;

    for (int i = 0; i < C; i++) {
        
        if (heap.size == P - 1) {
            
            int current_min_rel = candidates[i].reliability;
            int current_max_crit = candidates[i].criticality;
            if (heap.array[0]->criticality > current_max_crit) {
                current_max_crit = heap.array[0]->criticality;
            }

            int current_quality = current_min_rel - current_max_crit;

            if (current_quality > *max_quality) {
                *max_quality = current_quality;
                best_team[0] = candidates[i].id;
                
                for (int k = 0; k < P - 1; k++) {
                    best_team[k + 1] = heap.array[k]->id;
                }
            }
        }

        if (heap.size < P - 1) {
            heap_push(&heap, &candidates[i]);
        } else if (candidates[i].criticality < heap.array[0]->criticality) {
            heap_pop(&heap);
            heap_push(&heap, &candidates[i]);
        }
    }

    free(heap.array);
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