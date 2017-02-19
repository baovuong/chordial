#include <stdio.h>

#include "chord.h"

int main(int argc, char* argv[]) {
    chord_t* chord1 = chord_new(C, MAJOR, 3);
    chord_t* chord2 = chord_new_as_string("Fmaj11");

    printf("chord1: %s\n", chord_str(chord1));
    printf("chord2: %s\n", chord_str(chord2));


    printf("%d\n", C);

    // cleanup
    chord_delete(chord1);
    chord_delete(chord2);
    return 0;
}
