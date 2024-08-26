# include <stdio.h>
# define MOR -1

typedef struct {
    int states[13];
    int has_epsilon[13];
    int final_states[6];
    char alphabet[2];
    int transitions[3][13];
    int inicial_state;
    int size;
} Automata;

// Initialize an Automata struct with the appropriated values
Automata init_automata();
/*
Returns:
1 if the state given has at least one epsilon transition
0 if the state doesn't have an epsilon transition
-1 when the state is out of range
*/
int has_epsilon_transition(Automata automata, int state);

int main() {
    Automata regex_automata = init_automata();
    
    printf("Automatos");

    return 0;
}

Automata init_automata() {
    Automata automata = {
        .states = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        .alphabet = {'a', 'b'},
        .final_states = {1, 5, 7, 8, 11, 13},
        .inicial_state = 1,
        .transitions = {
            {2,}, // A
            {MOR}, // B
        }
    };
    return automata;
}

int has_epsilon_transition(Automata automata, int state) {
    if (state < 0 || state >= automata.size) {
        return -1;
    }
    return automata.has_epsilon[state];
}
