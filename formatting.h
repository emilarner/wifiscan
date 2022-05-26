#ifndef FORMATTING_H
#define FORMATTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "accesspoint.h"

char *bssid_to_string(char *mut, unsigned char *bssid);
void print_access_points(FILE *fp, struct AccessPoints *aps);
int print_access_points_json(FILE *fp, struct AccessPoints *aps);
int print_access_points_struct(FILE *fp, struct AccessPoints *aps);

#endif