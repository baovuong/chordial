#include "music_note.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return midi_value >= 0 && midi_valud <= 127 ? music_note : NULL;
}

void music_note_free(music_note_t* music_note) {
    if (music_note != NULL) {
        free(music_note);
    }
}

unsigned int music_note_to_midi_value(music_note_t music_note) {
    return music_note.octave * 12 + (int)music_note.pitch_class;
}

char* music_note_to_string(music_note_t music_note) {
    char* result = (char*)calloc(5, sizeof(char));
    char buffer[3];
    strcpy(result, pitch_class_names[(int)music_note.pitch_class]);
    sprintf(buffer, "%d", music_note.octave);
    strcat(result, buffer);
    return result;
}

void music_note_to_json_object(music_note_t music_note, struct json_object* jobj) {
    jobj = json_object_new_object();
}
