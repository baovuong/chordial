#ifndef INTERVAL_H
#define INTERVAL_H

#include <json/json.h>

enum quality {
    PERFECT,
    MAJOR,
    MINOR,
    AUGMENTED,
    DIMINISHED
};

typedef struct interval {
    enum quality quality;
    unsigned int number;
} interval_t;

interval_t* interval_new(enum quality, unsigned int);

const char* interval_to_string(interval_t);
void interval_to_json_object(interval_t, struct json_object**);
int interval_equals(interval_t, interval_t);

unsigned int interval_get_semitones(interval_t);

void interval_free(interval_t*);

#endif
