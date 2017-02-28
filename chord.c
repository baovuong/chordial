#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>

#include "chord.h"

// using this for reference:
// https://en.wikipedia.org/wiki/List_of_chords


char* chord_quality_values[] = {"maj","min","aug","dim","dom"};
const char* chord_quality_names[] = {
    "major",
    "minor",
    "augmented",
    "diminished",
    "dominant"
};

int extensions[] = {0, 7, 9, 11, 13};

char* known_chord_interval_names[] = {
    "maj",
    "min",
    "aug",
    "dim",
    "maj6",
    "min6",
    "dom7",
    "maj7",
    "min7",
    // "aug7",
    // "dim7",
    // "maj9",
    // "min9"
    // "dom9",
    // "aug9",
    // "dim9",
};

// https://en.wikipedia.org/wiki/Chord_names_and_symbols_(popular_music)
interval_t known_chord_intervals[9][6] = {
    { {MAJOR, 3}, {PERFECT, 5}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // maj
    { {MINOR, 3}, {PERFECT, 5}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // min
    { {MAJOR, 3}, {AUGMENTED, 5}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // aug
    { {MINOR, 3}, {DIMINISHED, 5}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // dim
    { {MAJOR, 3}, {PERFECT, 5}, {MAJOR, 6}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // maj6
    { {MINOR, 3}, {PERFECT, 5}, {MAJOR, 6}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // min6
    { {MAJOR, 3}, {PERFECT, 5}, {MINOR, 7}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // dom7
    { {MINOR, 3}, {PERFECT, 5}, {MAJOR, 7}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // maj7
    { {MINOR, 3}, {PERFECT, 5}, {MINOR, 7}, {PERFECT, 0}, {PERFECT, 0}, {PERFECT, 0} }, // min7
};

// helper functions
int find_string(int array_length, char* array[], const char* value) {
    for (int i=0; i<array_length; i++) {
        if (strcmp(array[i], value) == 0) {
            return i;
        }
    }
    return -1;
}

// constructors

chord_t* chord_new() {
    music_note_t root = {C, 4};
    return chord_new1(root);
}
chord_t* chord_new1(music_note_t root) {
    chord_t* chord = (chord_t*)malloc(sizeof(chord_t));
    chord->intervalc = 0;
    chord->root = root;
    return chord;
}

chord_t* chord_new_as_string(const char* name) {
    return NULL;
}

void chord_add_interval(interval_t interval) {
    
}

const char* chord_to_string(chord_t* chord) {
    return "a chord";
}

unsigned int* chord_notes(chord_t* chord) {
    return NULL;
}

unsigned int* chord_notes_with_octave(chord_t* chord, unsigned char octave) {
    return NULL;
}


void chord_to_json_object(chord_t* chord, struct json_object* jchord) {
    if (jchord != NULL) {
        free(jchord);
    }
    jchord = json_object_new_object();
    json_object_object_add(jchord, "root", json_object_new_string(music_note_to_string(chord->root)));
}

void chord_free(chord_t* chord) {
    if (chord != NULL) {
        free(chord);
    }
}
