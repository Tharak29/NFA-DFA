#include <stdio.h>
#include <string.h>

#define MAX 10

int nfa[MAX][2][MAX];  
int nfa_count[MAX][2];  

int dfa[MAX][2][MAX];
int dfa_count[MAX][2];

int dfa_states[MAX][MAX];
int dfa_state_count = 0;

int nfa_states, final_state;

int is_new_state(int *state_set, int count) {
    for(int i=0; i<dfa_state_count; i++) {
        int match = 1;
        for(int j=0; j<count; j++) {
            if(dfa_states[i][j] != state_set[j]) {
                match = 0;
                break;
            }
        }
        if(match) return 0;
    }
    return 1;
}

void add_dfa_state(int *state_set, int count) {
    for(int i=0; i<count; i++)
        dfa_states[dfa_state_count][i] = state_set[i];
    dfa_state_count++;
}

int main() {

    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter final state: ");
    scanf("%d", &final_state);

    for(int i=0; i<nfa_states; i++) {
        for(int j=0; j<2; j++) {
            printf("Enter number of transitions from state %d on input %d: ", i, j);
            scanf("%d", &nfa_count[i][j]);

            for(int k=0; k<nfa_count[i][j]; k++) {
                printf("Enter state: ");
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    int temp[MAX], count;

    temp[0] = 0;
    count = 1;

    add_dfa_state(temp, count);

    for(int i=0; i<dfa_state_count; i++) {

        for(int input=0; input<2; input++) {

            int new_state[MAX];
            int new_count = 0;

            for(int j=0; j<count; j++) {
                int nfa_state = dfa_states[i][j];

                for(int k=0; k<nfa_count[nfa_state][input]; k++) {
                    new_state[new_count++] = nfa[nfa_state][input][k];
                }
            }

            if(new_count > 0 && is_new_state(new_state, new_count)) {
                add_dfa_state(new_state, new_count);
            }
        }
    }

    printf("\nDFA States:\n");
    for(int i=0; i<dfa_state_count; i++) {
        printf("State %d: { ", i);
        for(int j=0; j<count; j++)
            printf("%d ", dfa_states[i][j]);
        printf("}\n");
    }

    printf("\nDFA Final States:\n");
    for(int i=0; i<dfa_state_count; i++) {
        for(int j=0; j<count; j++) {
            if(dfa_states[i][j] == final_state)
                printf("State %d is Final\n", i);
        }
    }

    return 0;
}
