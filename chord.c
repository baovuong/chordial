#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>

#include "chord.h"

// using this for reference:
// https://en.wikipedia.org/wiki/List_of_chords

char* pitch_class_names[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
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
    return chord_new1(0);
}
chord_t* chord_new1(music_note_t key) {
    return chord_new2(key, 0);
}
chord_t* chord_new2(music_note_t key, chord_quality_t chord_quality) {
    return chord_new3(key, chord_quality, 3);
}
chord_t* chord_new3(music_note_t key, chord_quality_t chord_quality, unsigned int interval) {
    chord_t* chord = (chord_t*)malloc(sizeof(chord_t));
    chord->key = key;
    chord->chord_quality = chord_quality;
    chord->interval = interval % 14;
    return chord;
}

chord_t* chord_new_as_string(const char* name) {

    char* valid_note = "ABCDEFG#";
    char* valid_quality = "adgijmnou";
    char* valid_number = "0123456789";

    // parsing time
    char note_str[3];
    char quality_str[4];
    unsigned int interval = 0;

    char c;
    int i = 0;
    int j = 0;
    int state = 0;
    while ((c = name[i++]) != '\0') {
        switch (state) {
            case 0:
                if (strchr(valid_note, c) != NULL) {
                    if (j < 3)
                        note_str[j++] = c;
                }
                else if (strchr(valid_quality, c) != NULL) {
                    note_str[j] = '\0';
                    j = 0;
                    quality_str[j++] = c;
                    state = 1;
                }
                break;
            case 1:
                if (strchr(valid_quality, c) != NULL) {
                    if (j < 4)
                        quality_str[j++] = c;
                }
                else if (strchr(valid_number, c) != NULL) {
                    quality_str[j] = '\0';
                    j = 0;
                    interval += c - '0';
                    state = 2;
                }
                break;
            case 2:
                if (strchr(valid_number, c) != NULL) {
                    interval *= 10;
                    interval += c - '0';
                }
                break;
            default:
                break;
        }
    }

    int note_index = find_string(12, note_values, note_str);
    int quality_index = find_string(5, chord_quality_values, quality_str);
    if (note_index >= 0 && quality_index >= 0) {
        return chord_new3(note_index, quality_index, interval);
    }

    return NULL;
}

const char* chord_str(chord_t* chord) {
    return "a chord";
}

unsigned int* chord_notes(chord_t* chord) {
    return NULL;
}

unsigned int* chord_notes_with_octave(chord_t* chord, unsigned char octave) {
    return NULL;
}


void chord_to_json_object(chord_t* chord, struct json_object** jchord) {
    if (*jchord != NULL) {
        free(*jchord);
    }
    *jchord = json_object_new_object();
    json_object_object_add(*jchord, "key", json_object_new_string(note_values[(int)chord->key]));
    json_object_object_add(*jchord, "quality", json_object_new_string(chord_quality_names[(int)chord->chord_quality]));
    json_object_object_add(*jchord, "interval", json_object_new_int(chord->interval));
}

void chord_free(chord_t* chord) {
    if (chord != NULL) {
        free(chord);
    }
}
