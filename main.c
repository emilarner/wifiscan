#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h>

#include "wifiscan.h"

enum OutputOptions
{
    NormalOutput,
    JSONOutput,
    StructOutput
};

void help()
{
    const char *msg =
    "wifiscan -- cross-platform program/library for scanning WiFi access points.\n"
    "USAGE:\n"
    "wifiscan [options]\n"
    "\nOPTIONS:\n\n"

    "Formatting options:\n\n"
    "none                                   Output scan in human-readable form.\n"
    "-j, --json                             Output scan in JSON form.\n"
    "-s, --struct                           Output scan in packed, binary struct form.\n"

    "\nOther options:\n\n"
    "-c, --current                          Instead of scanning, get the currently connected WiFi access point.\n"
    "-o, --output [filename]                Redirect output to a file.\n"

    "\nHelp/Manual options:\n\n"
    "-h, --help                             Display this menu.\n" 
    "-hj, --help-json                       Explains how the JSON is encoded.\n"
    "-hs, --help-struct                     Explains how the binary format is encoded.\n";

    printf("%s\n", msg);
}

void help_json()
{
    const char *msg =
    "The JSON format is as follows:\n\n"
    "A field called 'aps' will contain an array of access points.\n"
    "If this field is null, then the scan failed and your program should reflect that.\n"
    "Each access point has three fields:\n"
    "   - 'ssid': ssid name,\n"
    "   - 'bssid': the bssid,\n"
    "   - 'strength': the signal strength, as an integer,\n"
    "\n";

    printf("%s\n", msg);
}

void help_struct()
{
    const char *msg =
    "The packed binary structure format is as follows:\n\n"
    "First, a uint8_t (in otherwords, a byte) containing the amount of entries.\n"
    "";
}

int main(int argc, char **argv, char **envp)
{
    bool current = false;

    FILE *output = stdout;
    enum OutputOptions outputm = NormalOutput;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-j") || !strcmp(argv[i], "--json"))
            outputm = JSONOutput;

        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--struct"))
            outputm = StructOutput;

        else if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--current"))
            current = true;

        else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output"))
        {
            if (argv[i + 1] == NULL)
            {
                fprintf(stderr, "Error: -o/--output requires a filename.\n");
                return -1;
            }

            if ((output = fopen(argv[i + 1], "wb")) == NULL)
            {
                fprintf(stderr, "Error opening file: %s\n", strerror(errno));
                return -1;
            }
        }

        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            help();
            return 0;
        }
    }

    if (!current)
    {
        struct AccessPoints *aps = wifi_scan();

        switch (outputm)
        {
            case NormalOutput:
            {
                if (aps == NULL)
                {
                    fprintf(stderr, "Error: cannot scan WiFi... is your WiFi card enabled?\n");
                    return -1;
                }

                print_access_points(output, aps);
                break;
            }

            case JSONOutput:
            {
                if (print_access_points_json(output, aps) == -1)
                    return -1;

                break;
            }

            case StructOutput:
            {
                if (print_access_points_struct(output, aps) == -1)
                    return -1;

                break;
            }
        }

        access_points_free(aps);
    }
    else
    {
        fprintf(stderr, "Current WiFi function not implemented yet... sry xD\n");
        return -1;
    }

    fclose(output);
}