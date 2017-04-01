#include <CUnit/CUnit.h>

#include "test_note.h"

#include "../src/music_note.h"

// music note
void music_note_to_midi_value_test(void) {
    music_note_t concert_a = {A, 4};
    CU_ASSERT_EQUAL(57, music_note_to_midi_value(concert_a));
}