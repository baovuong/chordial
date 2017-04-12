#include <stdio.h>
#include <signal.h>

#include <onion/log.h>
#include <onion/onion.h>
#include <onion/block.h>
#include <onion/low.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/shortcuts.h>
#include <onion/types.h>
#include <onion/version.h>

#include <onion/static.h>
#include <onion/opack.h>


#include <json/json.h>

#include "../assets.h"

#include "music_note.h"
#include "chord.h"

onion_connection_status notes(void *p, onion_request *req, onion_response *res) {
    for (int i=0; i<11; i++) {
        for (int j=0; j<11; j++) {
            music_note_t note = {(enum pitch_class)j, i};
            onion_response_write0(res, music_note_to_string(note));
            onion_response_write0(res, ", ");
        }
        onion_response_write0(res, "<br/>");
    }
    return OCS_PROCESSED;
}

onion_connection_status api_notes(void *p, onion_request *req, onion_response *res) {
    struct json_object* notes = json_object_new_array();
    music_note_t* note;
    struct json_object* note_json;
    for (unsigned int i=0; i<128; i++) {
        note = music_note_new_from_midi_value(i);
        if (note != NULL) {
            music_note_to_json_object(*note, &note_json);
            json_object_array_add(notes, note_json);
        }
    }
    onion_response_set_header(res, "Content-Type", "application/json");
    onion_response_write0(res, json_object_to_json_string(notes));

    // cleanup
    free(notes);
    music_note_free(note);
    free(note_json);
    return OCS_PROCESSED;
}

onion_connection_status api_intervals(void *p, onion_request *req, onion_response *res) {
    struct json_object* interval_checks = json_object_new_array();
    interval_t* interval;
    struct json_object* interval_json;
    for (int i=0; i<5; i++) {
        for (unsigned int j=1; j<=8; j++) {
            interval = interval_new((enum quality)i, j);
            if (interval != NULL) {
                interval_to_json_object(*interval, &interval_json);
                json_object_array_add(interval_checks, interval_json);
            }

        }
    }

    onion_response_set_header(res, "Content-Type", "application/json");
    onion_response_write0(res, json_object_to_json_string(interval_checks));

    free(interval_checks);
    interval_free(interval);
    free(interval_json);
    return OCS_PROCESSED;
}

onion_connection_status chord(void *p, onion_request *req, onion_response *res) {
    if (OR_GET != (OR_METHODS & onion_request_get_flags(req))) {
        onion_response_set_code(res, HTTP_METHOD_NOT_ALLOWED);
        return OCS_PROCESSED;
    }
    chord_t* chord = NULL;
    struct json_object* json = NULL;
    if (onion_request_get_query(req, "1")) {
        chord = chord_new_as_string(onion_request_get_query(req, "1"));
        if (chord == NULL) {
            json = json_object_new_object();
            json_object_object_add(json, "message", json_object_new_string("malformed chord"));
        } else {
            chord_to_json_object(chord, json);
        }

    } else {
        json = json_object_new_object();
        json_object_object_add(json, "message", json_object_new_string("no chord provided"));
    }

    // write to response
    onion_response_set_header(res, "Content-Type", "application/json");

    const char* json_string = json_object_to_json_string(json);
    onion_response_write0(res, json_string);

    // cleanup
    chord_free(chord);

    return OCS_PROCESSED;
}

onion_connection_status api_chordprogression_notes(void *p, onion_request *req, onion_response *res) {
    if (OR_POST != (OR_METHODS & onion_request_get_flags(req))) {
        onion_response_set_code(res, HTTP_METHOD_NOT_ALLOWED);
        return OCS_PROCESSED;
    }

    // get array of chords, should be in json format
    const onion_block* data = onion_request_get_data(req);
    if (data != NULL) {
        int success = 1;
        const char* content = onion_block_data(data);

        struct json_object* obj = json_tokener_parse(content);
        struct array_list* chord_names = json_object_get_array(obj);
        if (chord_names != NULL) {
            // iterate through chords
            chord_t* chords[chord_names->length];
            for (int i=0; i<chord_names->length; i++) {
                // make sure it's a string
                if (json_object_get_type(chord_names->array[i]) != json_type_string) {
                    // not good
                    onion_response_set_code(res,  HTTP_BAD_REQUEST);
                    success = 0;
                    break;
                }
                chords[i] = chord_new_as_string(json_object_get_string(chord_names->array[i]));
                if (chords[i] == NULL) {
                    onion_response_set_code(res,  HTTP_BAD_REQUEST);
                    success = 0;
                    for (int j=i; j >= 0; j--)
                        chord_free(chords[j]);
                    break;
                }
            }

            if (success) {
                struct json_object* chord_progression_json = json_object_new_array();
                struct json_object* chord_json;
                for (int i=0; i<chord_names->length; i++) {
                    chord_json = json_object_new_array();
                    music_note_t* notes = chord_notes(chords[i]);
                    for (int j=0; j<chords[i]->intervalc+1; j++) {
                        json_object_array_add(chord_json, json_object_new_string(music_note_to_string(notes[j])));
                        printf("%s ", music_note_to_string(notes[j]));
                    }
                    printf("\n");
                    json_object_array_add(chord_progression_json, chord_json);
                    music_note_free(notes);
                    chord_free(chords[i]);
                }

                onion_response_set_header(res, "Content-Type", "application/json");
                const char* json_string = json_object_to_json_string(chord_progression_json);
                onion_response_write0(res, json_string);


                free(chord_json);
                free(chord_progression_json);
            }
        }

        free(chord_names);
        free(obj);
    }

    return OCS_PROCESSED;
}

onion_connection_status arg_test(void *p, onion_request *req, onion_response *res) {
    if ((OR_METHODS & onion_request_get_flags(req)) == OR_GET) {
        onion_response_set_code(res, HTTP_OK);
    } else {
        onion_response_set_code(res, HTTP_METHOD_NOT_ALLOWED);
    }
    return OCS_PROCESSED;
}

onion *o = NULL;

void on_exit(int _) {
    ONION_INFO("Exit");
    if (o) {
        onion_listen_stop(o);
    }
}

// views
int index_html_template(void *, onion_request *req, onion_response *res);

int main(int argc, char* argv[]) {

    // triggers
    signal(SIGINT,on_exit);
    signal(SIGTERM,on_exit);

    ONION_VERSION_IS_COMPATIBLE_OR_ABORT();

    // setup
    o = onion_new(O_POOL | O_SYSTEMD);
    onion_set_timeout(o, 5000);
    onion_set_hostname(o,"0.0.0.0");
    onion_set_port(o, "9077");

    // urls
    onion_url *urls=onion_root_url(o);
    onion_url_add(urls, "", (void*)index_html_template);
    onion_url_add(urls, "^chord/(.*)", chord);
    onion_url_add(urls, "^notes$", notes);
    onion_url_add(urls, "^static/", opack_static);
    onion_url_add(urls, "^arg-test$", arg_test);

    onion_url_add(urls, "^api/notes$", api_notes);
    onion_url_add(urls, "^api/intervals$", api_intervals);
    onion_url_add(urls, "^api/chordprogression/notes$", api_chordprogression_notes);


    // start
    onion_listen(o);
    onion_free(o);
    return 0;
}
