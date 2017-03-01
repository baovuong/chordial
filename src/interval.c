#include "interval.h"

const char* quality_names_short [] = {
    "perf",
    "maj",
    "min",
    "aug",
    "dim"
};

const char* quality_names_long [] = {
    "perfect",
    "major",
    "minor",
    "augmented",
    "diminished"
};



void interval_to_json_object(interval_t interval, struct json_object* jobj) {
    jobj = json_object_new_object();
    json_object_object_add(jobj, "quality", json_object_new_string(quality_names_short[(int)interval.quality]));
    json_object_object_add(jobj, "number", json_object_new_int(interval.number));
}

const char* interval_to_string(interval_t interval) {
    return NULL;
}