#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

#include "../src/music_note.h"
#include "../src/interval.h"

// music note
void music_note_to_midi_value_test(void) {
    music_note_t concert_a = {A, 4};
    CU_ASSERT_EQUAL(57, music_note_to_midi_value(concert_a));
}

void interval_get_semitones_test(void) {
    interval_t interval1 = {MAJOR, 3};
    interval_t interval2 = {MINOR, 3};

    CU_ASSERT_EQUAL(4, interval_get_semitones(interval1));
    CU_ASSERT_EQUAL(3, interval_get_semitones(interval2));
}


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
   if (NULL == CU_add_test(pSuite, "Midi Notes", music_note_to_midi_value_test) ||
       NULL == CU_add_test(pSuite, "Interval to semitones", interval_get_semitones_test)) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
