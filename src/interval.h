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

struct interval {
    enum quality quality;
    unsigned int number;
};
typedef struct interval interval_t;


void interval_to_json_object(interval_t, struct json_object*);
#endif