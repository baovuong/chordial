#ifndef CHORD_H
#define CHORD_H

#include <json/json.h>

#include "music_note.h"
#include "interval.h"

// Chord class
struct chord {
    music_note_t root;
    interval_t intervals[10];
    int intervalc;
};
typedef struct chord chord_t;

// constructors
chord_t* chord_new();
chord_t* chord_new1(music_note_t root);
//chord_t* chord_new2(music_note_t root, interval_t interval);
chord_t* chord_new_as_string(const char* name);

void chord_add_interval(interval_t interval);

// to string
const char* chord_to_string(chord_t* chord);

// to json object
void chord_to_json_object(chord_t* chord, struct json_object* jchord);

unsigned int* chord_notes(chord_t* chord);
unsigned int* chord_notes1(chord_t* chord, unsigned char octave);

// destructor
void chord_free(chord_t* chord);
#endif
