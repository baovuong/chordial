#ifndef MUSIC_NOTE_H
#define MUSIC_NOTE_H

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

// Music Note class
struct music_note {
    enum pitch_class pitch_class;
    unsigned int octave;
};
typedef struct music_note music_note_t;

// constructors
music_note_t* music_note_new();
music_note_t* music_note_new1(enum pitch_class);
music_note_t* music_note_new2(enum pitch_class, unsigned int);
music_note_t* music_note_new_from_midi_value(unsigned int);
music_note_t* music_note_new_from_string(const char*);
// destructor
void music_note_free(music_note_t*);

unsigned int music_note_to_midi_value(music_note_t);
const char* music_note_to_string(music_note_t);
void music_note_to_json_object(music_note_t, struct json_object**);
#endif
