#include <stdio.h>
#include <signal.h>
#include <onion/log.h>
#include <onion/onion.h>
#include <onion/block.h>
#include <onion/low.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/shortcuts.h>
#include <json/json.h>

#include "chord.h"

onion_connection_status index(void *p, onion_request *req, onion_response *res) {
    return OCS_PROCESSED;
}

onion_connection_status chord(void *p, onion_request *req, onion_response *res) {
    onion_block *jresb = onion_block_new();
    chord_t* chord = NULL;
	struct json_object* json = NULL;
    char* default_message = onion_low_strdup("no chord provided");
    if (onion_request_get_query(req, "1")) {
        chord = chord_new_as_string(onion_request_get_query(req, "1"));
        chord_to_json_object(chord, &json);
    } else {
        json = json_object_new_object();
    }

    // write to response
    onion_response_set_header(res, "Content-Type", "application/json");

    const char* json_string = json_object_to_json_string(json);
    onion_response_write0(res, json_string);

    // cleanup
    onion_block_free(jresb);
    onion_low_free(default_message);
    chord_free(chord);

    return OCS_PROCESSED;
}

onion *o = NULL;

void on_exit(int _) {
    ONION_INFO("Exit");
    if (o) {
        onion_listen_stop(o);
    }
}

int main(int argc, char* argv[]) {
    onion *o = onion_new(O_POOL);
    onion_set_timeout(o, 5000);
	onion_set_hostname(o,"0.0.0.0");

    // urls
    onion_url *urls=onion_root_url(o);
    onion_url_add(urls, "chord", chord);
    onion_url_add(urls, "^(.*)$", chord);


    onion_listen(o);
    onion_free(o);
    return 0;
}
