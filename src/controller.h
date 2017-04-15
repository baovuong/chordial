#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <onion/request.h>
#include <onion/response.h>

onion_connection_status notes(void *p, onion_request *req, onion_response *res);
onion_connection_status api_notes(void *p, onion_request *req, onion_response *res);
onion_connection_status api_intervals(void *p, onion_request *req, onion_response *res);
onion_connection_status chord(void *p, onion_request *req, onion_response *res);
onion_connection_status api_chordprogression_notes(void *p, onion_request *req, onion_response *res);
onion_connection_status arg_test(void *p, onion_request *req, onion_response *res);

void controller_setup(onion_url *urls);


#endif
