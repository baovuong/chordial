#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

#include "../src/music_note.h"
#include "../src/interval.h"
#include "../src/chord.h"

// music note
void music_note_to_midi_value_test(void) {
    music_note_t concert_a = {A, 4};
    CU_ASSERT_EQUAL(57, music_note_to_midi_value(concert_a));
}

// interval 
void interval_get_semitones_test(void) {
    interval_t M3 = {MAJOR, 3};
    interval_t m3 = {MINOR, 3};
    interval_t d3 = {DIMINISHED, 3};
    interval_t A3 = {AUGMENTED, 3};
    

    CU_ASSERT_EQUAL(4, interval_get_semitones(M3));
    CU_ASSERT_EQUAL(3, interval_get_semitones(m3));
    CU_ASSERT_EQUAL(2, interval_get_semitones(d3));
    CU_ASSERT_EQUAL(5, interval_get_semitones(A3));
}

void interval_new_test(void) {
    interval_t* M3 = interval_new(MAJOR, 3);
    interval_t* P3 = interval_new(PERFECT, 3);
    
    CU_ASSERT_PTR_NOT_NULL(M3);
    CU_ASSERT_PTR_NULL(P3);
    
    interval_free(M3);
    
}

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
