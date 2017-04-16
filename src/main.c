#include <stdio.h>
#include <signal.h>

#include <onion/onion.h>
#include <onion/block.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/version.h>

#include <onion/static.h>
#include <onion/opack.h>

#include "../assets.h"

#include "controller.h"

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
    onion_url_add(urls, "^static/", opack_static);
    controller_setup(urls);



    // start
    onion_listen(o);
    onion_free(o);
    return 0;
}
