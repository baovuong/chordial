#include "test_interval.h"


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