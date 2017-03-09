#include <stdlib.h>
#include <stdio.h>

#include "interval.h"

char quality_names_short[] = { 'P', 'M', 'm', 'a', 'd' };
const char* quality_names[] = { "perf", "maj", "min", "aug", "dim" };
const char* quality_names_long[] = {
    "perfect",
    "major",
    "minor",
    "augmented",
    "diminished"
};

int quality_steps[] = {0,0,-1,1,-1};
char quality_flags[] = {153, 102, 102, 254, 127};
int default_number_values[] = {0, 2, 4, 5, 7, 9, 11, 12};


// methods

interval_t* interval_new(enum quality quality, unsigned int number) {
    interval_t* interval = NULL;

    // check if number is in between 1 and 8
    if (number >= 1 && number <= 8) {
        // check mapping
        int index = -1;
        if (quality_flags[quality] & (1 << (number-1))) {
            // valid
            interval = (interval_t*)malloc(sizeof(interval_t));
            interval->quality = quality;
            interval->number = number;
        }
    }
    return interval;
}

void interval_free(interval_t* interval) {
    if (interval != NULL) {
        free(interval);
    }
}

unsigned int interval_get_semitones(interval_t interval) {
    return default_number_values[interval.number-1] + 
        (quality_steps[interval.quality] - 
         (interval.quality == DIMINISHED && 
          quality_flags[MAJOR] & (1 << (interval.number-1))));
}

void interval_to_json_object(interval_t interval, struct json_object** jobj) {
    *jobj = json_object_new_object();
    json_object_object_add(*jobj, "quality", json_object_new_string(quality_names[interval.quality]));
    json_object_object_add(*jobj, "number", json_object_new_int(interval.number));
}

const char* interval_to_string(interval_t interval) {
    char* result = (char*)calloc(3, sizeof(char));
    *result = quality_names_short[interval.quality];
    *(result+1) = (char)('0' + interval.number);
    *(result+2) = '\0';
    return result;
}

// helper functions