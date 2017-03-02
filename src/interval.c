#include <stdlib.h>
#include <stdio.h>

#include "interval.h"

char quality_names_short[] = { 'P', 'M', 'm', 'a', 'd' };

int number_mapping[5][7] = {
    {1, 5, 8, 0, 0, 0, 0},
    {2, 3, 6, 7, 0, 0, 0},
    {2, 3, 6, 7, 0, 0, 0},
    {1, 2, 3, 4, 5, 6, 7},
    {2, 3, 4, 5, 6, 7, 8}
};

const char* quality_names[] = { "perf", "maj", "min", "aug", "dim" };

const char* quality_names_long[] = {
    "perfect",
    "major",
    "minor",
    "augmented",
    "diminished"
};

interval_t* interval_new(enum quality quality, unsigned int number) {
    interval_t* interval = NULL;
    
    // check if number is in between 1 and 8
    if (number >= 1 && number <= 8) {
        // check mapping 
        int index = -1;
        for (int i=0; number_mapping[(int)quality][i] != 0 && i<7; i++) {
            if (number_mapping[(int)quality][i] == number) {
                index = i;
                break;
            }
        }       
        if (index > -1) {
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

void interval_to_json_object(interval_t interval, struct json_object** jobj) {
    *jobj = json_object_new_object();
    json_object_object_add(*jobj, "quality", json_object_new_string(quality_names[(int)interval.quality]));
    json_object_object_add(*jobj, "number", json_object_new_int(interval.number));
}

const char* interval_to_string(interval_t interval) {
    return NULL;
}