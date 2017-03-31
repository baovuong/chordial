#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

#include "../src/music_note.h"
#include "../src/interval.h"
#include "../src/chord.h"


int main (int argc, char** argv) {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
   }

    /* add the tests to the suite */
    int check = 0;
    check = check || NULL == CU_add_test(pSuite, "Midi Notes", music_note_to_midi_value_test);
    check = check || NULL == CU_add_test(pSuite, "Interval to semitones", interval_get_semitones_test);
    check = check || NULL == CU_add_test(pSuite, "Interval Constructor", interval_new_test);
    check = check || NULL == CU_add_test(pSuite, "Chord Construction", chord_new_test);
    check = check || NULL == CU_add_test(pSuite, "finding intervals in chords", chord_contains_interval_test);
    check = check || NULL == CU_add_test(pSuite, "generating music notes from chord", chord_get_notes_test);
    check = check || NULL == CU_add_test(pSuite, "chord construction from string", chord_construction_from_string);
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
