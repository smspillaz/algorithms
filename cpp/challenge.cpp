#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

inline int min(int a, int b) {
    if (a < b)
        return a;
    
    return b;
}

struct Score {
    int me;
    int my_friend;
};
    
    
Score best(struct Score score, int i, int *elements, int n_elements, int playing) {
    if (i >= n_elements) {
        return score;
    }
    
    int best_score = (playing ? score.me : score.my_friend);
    int best_i = i;
    
    int j = 1;
    
    for (; j <= min(3, n_elements - i); ++j) {
        int k = 0;
        for (; k < j; ++k) {
            if (playing) {
                score.me += elements[i + k];
            } else {
                score.my_friend = elements[i + k];
            }
        }

        printf ("%i %i - %i %i\n", score.me, score.my_friend, i + k, playing);

        score = best(score, i + k, elements, n_elements, (playing + 1)  % 2);
        
        if (playing) {
            if (score.me > best_score) {
                best_score = score.me;
                best_i = i + k;
            }
        } else {
            if (score.my_friend > best_score) {
                best_score = score.my_friend;
                best_i = i + k;
            }
        }
    }

    if (playing) {
        score.me = best_score;
    } else {
        score.my_friend = best_score;
    }
    
    return score;
}

int main() {
    int num_cases;
    scanf ("%i", &num_cases);
    
    while(num_cases--) {
        int n_elements;
        scanf("%i", &n_elements);
        int i = 0;
        int elements[n_elements];
        for (; i < n_elements; ++i) {
            scanf("%i", &elements[i]);
            printf("%i ", elements[i]);
        }
        printf("\n");

        Score s;
        s.me = 0;
        s.my_friend = 0;
        
        printf("%i\n", (best(s, 0, elements, n_elements, 1)).me);
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
