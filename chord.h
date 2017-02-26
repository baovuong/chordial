#ifndef CHORD_H
#define CHORD_H

#include <json/json.h>

enum pitch_class {
    C,
    C_SHARP,
    D,
    D_SHARP,
    E,
    F,
    F_SHARP,
    G,
    G_SHARP,
    A,
    A_SHARP,
    B
};

enum quality {
    PERFECT,
    MAJOR,
    MINOR,
    AUGMENTED,
    DIMINISHED
};

// Music Note class
struct music_note {
    enum pitch_class pitch_class;
    unsigned int octave;
};
typedef struct music_note_t;

// constructors
music_note_t* music_note_new();
music_note_t* music_note_new1(enum pitch_class pitch_class);
music_note_t* music_note_new2(enum pitch_class pitch_class, unsigned int octave);

unsigned int music_note_to_midi_value(music_note_t);

// Interval class
struct interval {
    enum quality quality;
    unsigned int number;
};
typedef struct interval interval_t;


// Chord class
struct chord {
    music_note_t root_note;
    interval_t* intervals;
    int intervalc;
};
typedef struct chord chord_t;

// constructors
chord_t* chord_new();
chord_t* chord_new1(music_note_t root);
chord_t* chord_new2(music_note_t root, interval_t interval);
chord_t* chord_new_as_string(const char* name);

void chord_add_interval(interval_t interval);

// to string
const char* chord_str(chord_t* chord);

// to json object
void chord_to_json_object(chord_t* chord, struct json_object** jchord);

unsigned int* chord_notes(chord_t* chord);
unsigned int* chord_notes1(chord_t* chord, unsigned char octave);

// destructor
void chord_free(chord_t* chord);
#endif
