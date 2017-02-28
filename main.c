#include <stdio.h>
#include <signal.h>
#include <onion/log.h>
#include <onion/onion.h>
#include <onion/block.h>
#include <onion/low.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/shortcuts.h>
#include <onion/version.h>
#include <json/json.h>

#include "music_note.h"
#include "chord.h"

onion_connection_status index(void *p, onion_request *req, onion_response *res) {
    return index_html_template(NULL, req, res);
}

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

onion_connection_status chord(void *p, onion_request *req, onion_response *res) {
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

onion *o = NULL;

void on_exit(int _) {
    ONION_INFO("Exit");
    if (o) {
        onion_listen_stop(o);
    }
}

int main(int argc, char* argv[]) {
	
	signal(SIGINT,on_exit);
	signal(SIGTERM,on_exit);
	
	ONION_VERSION_IS_COMPATIBLE_OR_ABORT();
	
    o = onion_new(O_POOL);
    onion_set_timeout(o, 5000);
	onion_set_hostname(o,"0.0.0.0");
	onion_set_port(o, "9077");

    // urls
    onion_url *urls=onion_root_url(o);
    onion_url_add(urls, "^$", index);
	onion_url_add(urls, "^chord/(.*)", chord);
	onion_url_add(urls, "^notes$", notes);

    onion_listen(o);
    onion_free(o);
    return 0;
}
