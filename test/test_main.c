#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

#include "test_note.h"
#include "test_interval.h"
#include "test_chord.h"


int main (int argc, char** argv) {
    CU_pSuite music_note_suite = NULL;
    CU_pSuite interval_suite = NULL;
    CU_pSuite chord_suite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    music_note_suite = CU_add_suite("Music Note Test Suite", NULL, NULL);
    interval_suite = CU_add_suite("Interval Test Suite", NULL, NULL);
    chord_suite = CU_add_suite("Chord Test Suite", NULL, NULL);
    if (NULL == music_note_suite || NULL == interval_suite || NULL == chord_suite) {
        CU_cleanup_registry();
        return CU_get_error();
   }

    /* add the tests to the suite */
    int check = 0;
    check = check || NULL == CU_add_test(music_note_suite, "Midi Notes", music_note_to_midi_value_test);
    
    check = check || NULL == CU_add_test(interval_suite, "Interval to semitones", interval_get_semitones_test);
    check = check || NULL == CU_add_test(interval_suite, "Interval Constructor", interval_new_test);
    
    check = check || NULL == CU_add_test(chord_suite, "Chord Construction", chord_new_test);
    check = check || NULL == CU_add_test(chord_suite, "finding intervals in chords", chord_contains_interval_test);
    check = check || NULL == CU_add_test(chord_suite, "generating music notes from chord", chord_get_notes_test);
    check = check || NULL == CU_add_test(chord_suite, "chord construction from string", chord_construction_from_string);
    if (check) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
