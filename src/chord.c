#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <regex.h>

#include "chord.h"
#include "helper_functions.h"

#define NOTE_CHAR_MAX 5
#define QUALITY_CHAR_MAX 6

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

const char* known_chord_interval_names[] = {
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

interval_t perfect_unison = {PERFECT, 1};

// https://en.wikipedia.org/wiki/Chord_names_and_symbols_(popular_music)
interval_t known_chord_intervals[9][6] = {
    { {MAJOR, 3}, {PERFECT, 5}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // maj
    { {MINOR, 3}, {PERFECT, 5}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // min
    { {MAJOR, 3}, {AUGMENTED, 5}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // aug
    { {MINOR, 3}, {DIMINISHED, 5}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // dim
    { {MAJOR, 3}, {PERFECT, 5}, {MAJOR, 6}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // maj6
    { {MINOR, 3}, {PERFECT, 5}, {MAJOR, 6}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // min6
    { {MAJOR, 3}, {PERFECT, 5}, {MINOR, 7}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // dom7
    { {MAJOR, 3}, {PERFECT, 5}, {MAJOR, 7}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // maj7
    { {MINOR, 3}, {PERFECT, 5}, {MINOR, 7}, {PERFECT, 1}, {PERFECT, 1}, {PERFECT, 1} }, // min7
};

// helper functions


// constructors

chord_t* chord_new() {
    music_note_t root = {C, 4};
    return chord_new1(root);
}
chord_t* chord_new1(music_note_t root) {
    return chord_new2(root, MAJOR_TRIAD);
}

chord_t* chord_new2(music_note_t root, enum chord_quality chord_quality) {
    chord_t* chord = (chord_t*)malloc(sizeof(chord_t));
    chord->root = root;

    // set intervals from the chord_quality
    chord->intervalc = 0;
    for (int i=0; !interval_equals(known_chord_intervals[chord_quality][i], perfect_unison); i++) {
        chord_add_interval(chord, known_chord_intervals[chord_quality][i]);
    }
    return chord;
}

chord_t* chord_new_as_string(const char* name) {
    return chord_new_as_string1(name, 4);
}

chord_t* chord_new_as_string1(const char* name, int octave) {
    // parse through string
    int state = 0;
    int i = 0;
    char c;
    char* note_string;
    char* quality_string;
    int qsi = 1;
    while ((c = name[i++]) != '\0') {
        switch (state) {
            case 0:
                if (is_pitch(c)) {
                    note_string = (char*)calloc(NOTE_CHAR_MAX, sizeof(char));
                    note_string[0] = c;
                    state = 1;
                } else {
                    state = 4;
                }
                break;
            case 1:
                if (is_accent(c)) {
                    note_string[1] = c;
                    state = 2;
                } else {
                    note_string[1] = '\0';
                    quality_string = (char*)calloc(QUALITY_CHAR_MAX, sizeof(char));
                    quality_string[0] = c;
                    state = 3;
                }
                break;
            case 2:
                note_string[2] = '\0';
                quality_string = (char*)calloc(QUALITY_CHAR_MAX, sizeof(char));
                quality_string[0] = c;
                break;
            case 3:
                quality_string[qsi] = c;
                qsi++;
                break;
            default:
                break;
        }
    }

    if (state == 3) {

        // attempt music note construction
        // add octave to note string
        char octave_string[4];
        sprintf(octave_string, "%d", octave);
        strcat(note_string, octave_string);
        printf("note_string: %s\n", note_string);

        music_note_t* note = music_note_new_from_string(note_string);
        if (note == NULL) {
            return NULL;
        }

        // attempt chord quality construction
        quality_string[qsi] = '\0';
        enum chord_quality chord_quality;
        printf("quality_string: %s\n", quality_string);
        int quality_index = find_string(9, known_chord_interval_names, quality_string);
        printf("index: %i\n", quality_index);
        if (quality_index == -1) {
            return NULL;
        }
        chord_quality = quality_index;

        chord_t* chord = chord_new2(*note, chord_quality);
        music_note_free(note);

        return chord;
    }

    return NULL;
}

void chord_add_interval(chord_t* chord, interval_t interval) {
    if (chord->intervalc < INTERVAL_MAX) {
        // add
        chord->intervals[chord->intervalc] = interval;
        chord->intervalc++;
    }
}

int chord_contains_interval(chord_t* chord, interval_t interval) {
    // search
    for (int i=0; i<chord->intervalc; i++) {
        if (interval_equals(interval, chord->intervals[i])) {
            return 1;
        }
    }
    return 0;
}

const char* chord_to_string(chord_t* chord) {
    return "a chord";
}

music_note_t* chord_notes(chord_t* chord) {
    music_note_t* notes = (music_note_t*)calloc(chord->intervalc+1, sizeof(music_note_t));

    // root note
    notes[0] = chord->root;
    for (int i=1; i<chord->intervalc+1; i++) {
        music_note_t* note = music_note_new_from_midi_value(
            music_note_to_midi_value(chord->root) +
            interval_get_semitones(chord->intervals[i-1]));
        notes[i] = *note;
        music_note_free(note);
    }
    return notes;
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
