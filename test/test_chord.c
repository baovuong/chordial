#include <CUnit/CUnit.h>
#include "test_chord.h"
#include "../src/music_note.h"
#include "../src/interval.h"
#include "../src/chord.h"

// chord construction
void chord_new_test(void) {
    interval_t minor_third_interval = {MINOR, 3};
    interval_t major_third_interval = {MAJOR, 3};
    interval_t perfect_fifth_interval = {PERFECT, 5};
    interval_t minor_seventh_interval = {MINOR, 7};

    music_note_t c1 = {C, 1};
    music_note_t d4 = {D, 4};

    // major third triad
    chord_t* c_major_triad = chord_new1(c1);
    CU_ASSERT_EQUAL(c_major_triad->intervalc, 2);
    CU_ASSERT_TRUE(interval_equals(c_major_triad->intervals[0], major_third_interval));
    CU_ASSERT_TRUE(interval_equals(c_major_triad->intervals[1], perfect_fifth_interval));

    // minor seventh
    chord_t* d_minor_seventh = chord_new2(d4, MINOR_SEVENTH);
    CU_ASSERT_EQUAL(d_minor_seventh->intervalc, 3);

    chord_free(c_major_triad);
    chord_free(d_minor_seventh);
}

void chord_contains_interval_test(void) {
    interval_t major_third_interval = {MAJOR, 3};
    interval_t perfect_fifth_interval = {PERFECT, 5};
    interval_t minor_seventh_interval = {MINOR, 7};
    interval_t minor_third_interval = {MINOR, 3};
    music_note_t e5 = {E, 5};

    chord_t* e_dominant_seventh = chord_new2(e5, DOMINANT_SEVENTH);
    CU_ASSERT_TRUE(chord_contains_interval(e_dominant_seventh, major_third_interval));
    CU_ASSERT_TRUE(chord_contains_interval(e_dominant_seventh, perfect_fifth_interval));
    CU_ASSERT_TRUE(chord_contains_interval(e_dominant_seventh, minor_seventh_interval));
    CU_ASSERT_FALSE(chord_contains_interval(e_dominant_seventh, minor_third_interval));

    chord_free(e_dominant_seventh);
}

void chord_get_notes_test(void) {
    music_note_t c4 = {C, 4};
    music_note_t e4 = {E, 4};
    music_note_t g4 = {G, 4};
    chord_t* cmajor = chord_new();

    music_note_t* notes = chord_notes(cmajor);
    CU_ASSERT_PTR_NOT_NULL_FATAL(notes);

    int count = cmajor->intervalc+1;

    CU_ASSERT_TRUE(music_note_equals(c4, notes[0]));
    CU_ASSERT_TRUE(music_note_equals(e4, notes[1]));
    CU_ASSERT_TRUE(music_note_equals(g4, notes[2]));

    free(notes);
    chord_free(cmajor);
}

void chord_construction_from_string(void) {
    music_note_t c4 = {C, 4};
    music_note_t e4 = {E, 4};
    music_note_t g4 = {G, 4};
    music_note_t b4 = {B, 4};
    
    chord_t* Cmaj7 = chord_new_as_string("Cmaj7");
    CU_ASSERT_PTR_NOT_NULL_FATAL(Cmaj7);
    
    music_note_t* notes = chord_notes(Cmaj7);
    CU_ASSERT_PTR_NOT_NULL_FATAL(notes);
    
    CU_ASSERT_TRUE(music_note_equals(c4, notes[0]));
    CU_ASSERT_TRUE(music_note_equals(e4, notes[1])); 
    CU_ASSERT_TRUE(music_note_equals(g4, notes[2]));
    CU_ASSERT_TRUE(music_note_equals(b4, notes[3]));
    free(notes);
    chord_free(Cmaj7);
}