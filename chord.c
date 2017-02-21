#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>

#include "chord.h"

// using this for reference:
// https://en.wikipedia.org/wiki/List_of_chords

char* note_values[] = {
    "C",
    "C#",
    "D",
    "D#",
    "E",
    "F",
    "F#",
    "G",
    "G#",
    "A",
    "A#",
    "B"
};

char* chord_quality_values[] = {
    "maj",
    "min",
    "aug",
    "dim",
    "dom"
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

//

chord_t* chord_new(music_note_t key, chord_quality_t chord_quality, unsigned int interval) {
    chord_t* chord = (chord_t*)malloc(sizeof(chord_t));
    chord->key = key;
    chord->chord_quality = chord_quality;
    chord->interval = interval % 14;
    return chord;
}

chord_t* chord_new_as_string(const char* name) {
    char* valid_note = "ABCDEFG#";
    char* valid_quality = "adgijmni";
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

    return chord_new(
        find_string(12, note_values, note_str),
        find_string(5, chord_quality_values, quality_str),
        interval);
}

const char* chord_str(chord_t* chord) {
    char* result = (char*)calloc(sizeof(char), 8);
    strcat(result, note_values[(int)chord->key]);
    strcat(result, chord_quality_values[(int)chord->chord_quality]);

    char interval_string[3];
    sprintf(interval_string, "%d", chord->interval);

    strcat(result, interval_string);
    return result;
}

unsigned int* chord_notes(chord_t* chord) {
    return NULL;
}

unsigned int* chord_notes_with_octave(chord_t* chord, unsigned char octave) {
    return NULL;
}


void chord_to_json_object(chord_t* chord, struct json_object** jchord) {
    *jchord = json_object_new_object();
    json_object_object_add(*jchord, "key", json_object_new_int((int)chord->key));
    json_object_object_add(*jchord, "quality", json_object_new_int((int)chord->chord_quality));
    json_object_object_add(*jchord, "interval", json_object_new_int(chord->interval));
}

void chord_free(chord_t* chord) {
    if (chord != NULL) {
        free(chord);
    }
}
