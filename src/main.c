# include <stdio.h>
# define D -2 // Dead
# define MAX_STATES 15
# define FINAL_STATES 6
# define ALPHABET 2

typedef struct {
    int states[MAX_STATES];
    int has_epsilon[MAX_STATES][2];
    int final_states[FINAL_STATES];
    char alphabet[ALPHABET];
    int transitions[ALPHABET][MAX_STATES];
    int inicial_state;
} Automata;

// Globals
Automata regex_automata;
char string[52];
int len_string = 0;

// Functions
Automata init_automata();
int check_epsilon_transitions(int index_start, int state);
void trasition_from_symbol(char symbol, int *current_state);
int process(int index_start, int inicial_state);
int is_final_state(int state);

int main() {
    regex_automata = init_automata();
    fgets(string, 52, stdin);
    while (string[len_string] != '\0' && string[len_string] != '\n') {
        len_string++;
    }
    if (process(0, regex_automata.inicial_state)){
        printf("sim\n");
    } else {
        printf("nao\n");
    }
    return 0;
}

Automata init_automata() {
    Automata automata = {
        .states = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        .alphabet = {'a', 'b'},
        .final_states = {0, 5, 7, 8, 12, 14},
        .inicial_state = 0,
        .transitions = {
            {D, D, 3, D, 5, D, 7, D, D, D, D, 12, D, D, D}, // A
            {D, D, D, 4, D, 6, D, D, D, D, 11, D, 13, 14, D}, // B
        },
        .has_epsilon = {{1, 8}, {2, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {1, 8}, {-1, -1}, {1, 8}, {9, -1}, {10, -1}, {-1, -1}, {-1, -1}, {9, -1}, {-1, -1}, {9, -1}}
    };
    return automata;
}

int is_final_state(int state) {
    int j;
    for (j = 0; j < FINAL_STATES; j++) {
        if (state == regex_automata.final_states[j]) {
            return 1;
        }
    }
    return 0;
}

void trasition_from_symbol(char symbol, int *current_state) {
    if (symbol == 'a') {
        *current_state = regex_automata.transitions[0][*current_state];
    } else if (symbol == 'b') {
        *current_state = regex_automata.transitions[1][*current_state];
    }
}

int check_epsilon_transitions(int index_start, int state) {
    int i;
    for (i = 0; i < 2; i++) {
        if (regex_automata.has_epsilon[state][i] != -1) {
            if (process(index_start, regex_automata.has_epsilon[state][i])) {
                return 1;
            }
        }
    }
    return 0;
}

int process(int current_index, int current_state) {
    if (current_index >= len_string) {
        if (is_final_state(current_state)) {
            return 1;
        }
        return 0;
    }
    int i;
    for (i = current_index; i < len_string; i++) {
        if (check_epsilon_transitions(i, current_state)) {
            return 1;
        }
        trasition_from_symbol(string[i], &current_state);
        if (current_state == D) {
            return 0;
        }
    }
    if (check_epsilon_transitions(i, current_state)) {
        return 1;
    }
    return is_final_state(current_state);
}
