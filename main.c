#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "utilities.h"

char *program_name;

/**
 * Inform the user about the correct usage of this program
 * 
*/
static void usage(const char *msg) 
{
    printf("Error: %s: %s\n", program_name, msg);
    //printf("Usage: %s [OPTION]... URL\n", program_name);
    printf("For more information please use the '-h' or '--help' option\n");
    exit(EXIT_FAILURE);
}


/**
 * Exit the programm with a proper status code and inform the user about the error.
*/
static void error_exit(const char *msg)
{
    fprintf(stderr, "[ERROR]: %s: %s: %s\n", program_name, msg, strerror(errno));
    exit(EXIT_FAILURE);
}

/**
 * Provide detailed information about the accepted options.
*/
static void help_menu(void)
{
    printf("Usage: %s [OPTION]... URL\n\n", program_name);
    printf("\t-h, --help \t\t Print the help menu\n");
    printf("\t-p, --port \t\t Specify a port number, default is 80\n");
    printf("\t-v, --verbose \t\t Verbose, prints out more useful output\n");
    exit(EXIT_FAILURE);
}


const struct option longoptions[] = {
    {"port", required_argument, NULL, 'p'},
    {"help", no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'}
};


int main(int argc, char **argv) 
{
    program_name = argv[0];


    int c;
    int *longindex = NULL;

    char *port = "80";
    unsigned int is_verbose = 0;
    unsigned int count_p = 0;
    unsigned int count_v = 0;


    while ((c = getopt_long(argc, argv, "p:hv", longoptions, longindex)) != -1) {
        switch(c) {
            case 'p':
                if (count_p)
                    usage("Option p must occur at most once");

                const char *invalid_port_msg = "Port must be a positive integer between 1 and 65535";

                if (*optarg == '\0')
                    usage(invalid_port_msg);

                char *endptr;
                long result = strtol(optarg, &endptr, 10);

                if(*endptr != '\0' || result < 0 || result > 65535) {
                    usage(invalid_port_msg);
                }

                port = strdup(optarg);

                break;
            case 'h':
                help_menu();
            case 'v':
                if(count_v)
                    usage("Option '-v', '--verbose' must occur at most once");
                
                is_verbose = 1;
                break;
            case '?':
                exit(EXIT_FAILURE); //get opts prints its own error -> can be disabled and we can print custom error msg
            default:
                error_exit("Unknown error parsing the options");
  
        }
    }


    if (argc - optind != 1)
        usage("The URL is required as positional argument");


    char *url = argv[optind];

    

    return EXIT_SUCCESS;

}