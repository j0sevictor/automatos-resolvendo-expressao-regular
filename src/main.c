# include <stdio.h>
# define MOR -1

typedef struct {
    int states[13];
    int has_epsilon[13][2];
    int final_states[6];
    char alphabet[2];
    int transitions[3][13];
    int inicial_state;
    int size;
} Automata;

Automata regex_automata;
char string[52];
int len_string = 50;

Automata init_automata();
int has_epsilon_transition(Automata automata, int state);

int main() {
    regex_automata = init_automata();
    fgets(string, 52, stdin);
    
    return 0;
}

Automata init_automata() {
    Automata automata = {
        .states = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        .alphabet = {'a', 'b'},
        .final_states = {0, 4, 6, 9, 11},
        .inicial_state = 0,
        .transitions = {
            {MOR, 2, MOR, 4, MOR, 6, MOR, MOR, 9, MOR, MOR, MOR}, // A
            {MOR, MOR, 3, MOR, 6, MOR, MOR, 8, MOR, 10, 11, MOR}, // B
        },
        .has_epsilon = {{1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {1, -1}, {-1, -1}, {1, 7}, {-1, -1}, {-1, -1}, {7, -1}, {-1, -1}, {7, -1}},
        .size = 12,
    };
    return automata;
}

int has_epsilon_transition(Automata automata, int state) {
    if (state < 0 || state >= automata.size) {
        return -1;
    }
    return automata.has_epsilon[state][0];
}

int process(int index_start, int inicial_state) {
    int i, current_state;
    current_state = inicial_state;

    if (index_start >= len_string) {
        return 0;
    }

    int result;
    for (i = index_start; i < len_string; i++) {
        if (has_epsilon_transition(regex_automata, current_state)) {
            result = process(i, current_state);
        }

        if (string[i] == 'a') {
            current_state = regex_automata.transitions[0][current_state];
        } else if (string[i] == 'b') {
            current_state = regex_automata.transitions[1][current_state];
        }
    }

    if (has_epsilon_transition(regex_automata, current_state)) {
        process(i, current_state);
    }

    int j;
    for (j = 0; j < 5; j++) {
        if (current_state == regex_automata.final_states[j]) {
            return 1;
        }
    }

    return 0;
}
