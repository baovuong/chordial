#ifndef CHORD_H
#define CHORD_H

#include <json/json.h>

#include "music_note.h"
#include "interval.h"

#define INTERVAL_MAX 10


enum chord_quality {
    MAJOR_TRIAD,
    MINOR_TRIAD,
    AUGMENTED_TRIAD,
    DIMINISHED_TRIAD,
    MAJOR_SIXTH,
    MINOR_SIXTH,
    DOMINANT_SEVENTH,
    MAJOR_SEVENTH,
    MINOR_SEVENTH
};



// Chord class
typedef struct chord {
    music_note_t root;
    interval_t intervals[INTERVAL_MAX];
    int intervalc;
} chord_t;

// constructors
chord_t* chord_new();
chord_t* chord_new1(music_note_t root);
chord_t* chord_new2(music_note_t root, enum chord_quality chord_quality);
chord_t* chord_new_as_string(const char* name);
chord_t* chord_new_as_string1(const char* name, int octave);

void chord_add_interval(chord_t* chord, interval_t interval);
void chord_remove_interval(chord_t* chord, interval_t interval);
int chord_contains_interval(chord_t* chord, interval_t interval);

// to string
const char* chord_to_string(chord_t* chord);

// to json object
void chord_to_json_object(chord_t* chord, struct json_object* jchord);

music_note_t* chord_notes(chord_t* chord);

// destructor
void chord_free(chord_t* chord);
#endif
