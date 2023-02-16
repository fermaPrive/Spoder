#include "utilities.h"



/**
 * Check whether the protocol in the url is valid.
 * Accepted protocols are:
 *      http
 *      https
*/
int check_url_protocol(const char *url)
{

    if(!(strncmp(url, "http://", strlen("http://")) == 0 || strncmp(url, "https://", strlen("https://")) == 0)) {
        return -1;
    }

    return 1;
}



//methods for linked list