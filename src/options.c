/*  SATISY, a solver of the satisfiability problem of formulae in the
 *  propositional calculus.
 *  Copyright (C) 2017-present Paul Griffiths.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; If not, see <https://www.gnu.org/licenses/>.
 */

/* Functions and global variables for processing command line options */

#include "internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include "options.h"

#define PROGRAM_NAME "satisfy"

/* Static function declarations */
static void process_cmdline(int, char **);
static void output_help(void);

/* Static options flags */
static int help_flag;
static int version_flag;

/* Processes command line options */
void
process_options(int argc, char ** argv) {
#ifndef HAVE_GETOPT_H
    return;
#else
    process_cmdline(argc, argv);

    if ( version_flag ) {
        puts(PACKAGE_STRING);
        exit(EXIT_SUCCESS);
    } else if ( help_flag ) {
        output_help();
        exit(EXIT_SUCCESS);
    }
#endif
}

#ifdef HAVE_GETOPT_H
#ifdef HAVE_GETOPT_LONG

/* Processing with getopt_long */
static void
process_cmdline(int argc, char ** argv) {
    while ( 1 ) {
        struct option long_options[] = {
            {"help", no_argument, &help_flag, 1},
            {"version", no_argument, &version_flag, 1},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        int c = getopt_long(argc, argv, "hV", long_options, &option_index);
        if ( c == -1 ) {
            break;
        }

        switch ( c ) {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0) {
                    break;
                }

                break;

            case 'h':
                help_flag = 1;
                break;

            case 'V':
                version_flag = 1;
                break;

            case '?':
                /* getopt_long already printed an error message. */
                exit(EXIT_FAILURE);

            default:
                fprintf(stderr, "unhandled option: %d", c);
                exit(EXIT_FAILURE);
        }
    }
}

static void
output_help(void) {
    printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
    printf("A solver of the satisfiability problem of formulae in the\n");
    printf("propositional calculus.\n");

    printf("\nMiscellaneous:\n");
    printf("  -h, --help              produce this help message\n");
    printf("  -V, --version           report version\n");
}

#else

/* Processing without getopt_long */
static void
process_cmdline(int argc, char ** argv) {
    int c;
    opterr = 0;

    while ( (c = getopt(argc, argv, "hV")) != -1 ) {
        switch ( c ) {
            case 'h':
                help_flag = 1;
                break;

            case 'V':
                version_flag = 1;
                break;

            case '?':
                if ( optopt == 's' ) {
                   fprintf (stderr,
                            "Option -%c requires an argument.\n", optopt);
                } else if ( isprint (optopt) ) {
                   fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                } else {
                   fprintf (stderr,
                            "Unknown option character `\\x%x'.\n", optopt);
                }
                exit(EXIT_FAILURE); 

            default:
                fprintf(stderr, "unhandled option: %d", c);
                exit(EXIT_FAILURE);
        }
    }
}

static void
output_help(void) {
    printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
    printf("A solver of the satisfiability problem of formulae in the\n");
    printf("propositional calculus.\n");

    printf("\nMiscellaneous:\n");
    printf("  -h              produce this help message\n");
    printf("  -V              report version\n");
}

#endif  /* HAVE_GETOPT_LONG */
#endif  /* HAVE_GETOPT_H */
