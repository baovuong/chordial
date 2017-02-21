#ifndef CHORD_H
#define CHORD_H

#include <json/json.h>

enum music_note {
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
typedef enum music_note music_note_t;

enum chord_quality {
    MAJOR,
    MINOR,
    AUGMENTED,
    DIMINISHED,
    DOMINANT
};
typedef enum chord_quality chord_quality_t;


struct chord {
    music_note_t key;
    chord_quality_t chord_quality;
    unsigned int interval;
};
typedef struct chord chord_t;

chord_t* chord_new(music_note_t key, chord_quality_t chord_quality, unsigned int interval);
chord_t* chord_new_as_string(const char* name);

const char* chord_str(chord_t* chord);
void chord_to_json_object(chord_t* chord, struct json_object** jchord);


unsigned int* chord_notes(chord_t* chord);
unsigned int* chord_notes_with_octave(chord_t* chord, unsigned char octave);


void chord_free(chord_t* chord);
#endif
