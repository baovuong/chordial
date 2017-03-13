#include "music_note.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MIDI_VALUE 127
#define MIN_MIDI_VALUE 0

const char* pitch_class_names[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

music_note_t* music_note_new() {
    return music_note_new1(C);
}

music_note_t* music_note_new1(enum pitch_class pitch_class) {
    return music_note_new2(pitch_class, 4);
}

music_note_t* music_note_new2(enum pitch_class pitch_class, unsigned int octave) {
    music_note_t* music_note = (music_note_t*)malloc(sizeof(music_note_t));
    music_note->pitch_class = pitch_class;
    music_note->octave = octave > 10 ? 10 : octave;

    // check if it's a valid music note, based on
    unsigned int midi_value = music_note_to_midi_value(*music_note);
    return midi_value >= MIN_MIDI_VALUE && midi_value <= MAX_MIDI_VALUE ? music_note : NULL;
}

music_note_t* music_note_new_from_midi_value(unsigned int midi_value) {
    if (midi_value >= MIN_MIDI_VALUE && midi_value <= MAX_MIDI_VALUE) {
        return music_note_new2((enum pitch_class)midi_value % 12, midi_value / 12);
    }
    return NULL;
}

void music_note_free(music_note_t* music_note) {
    if (music_note != NULL) {
        free(music_note);
    }
}

unsigned int music_note_to_midi_value(music_note_t music_note) {
    return music_note.octave * 12 + music_note.pitch_class;
}

const char* music_note_to_string(music_note_t music_note) {
    char* result = (char*)calloc(5, sizeof(char));
    char buffer[3];
    strcpy(result, pitch_class_names[music_note.pitch_class]);
    sprintf(buffer, "%d", music_note.octave);
    strcat(result, buffer);
    return result;
}

void music_note_to_json_object(music_note_t music_note, struct json_object** jobj) {
    *jobj = json_object_new_object();
    json_object_object_add(*jobj, "pitchClass", json_object_new_string(pitch_class_names[music_note.pitch_class]));
    json_object_object_add(*jobj, "octave", json_object_new_int(music_note.octave));
}

int music_note_compare(music_note_t note1, music_note_t note2) {
    return music_note_to_midi_value(note1) - music_note_to_midi_value(note2);
}

int music_note_equals(music_note_t note1, music_note_t note2) {
    return music_note_compare(note1, note2) == 0;
}
