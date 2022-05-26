#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <stdlib.h>
#include <stdint.h>

struct AccessPoint
{
    char bssid[32];
    char ssid[64];
    long strength;
};

struct AccessPoints
{
    struct AccessPoint **aps;
    size_t capacity;
    size_t length;
};

struct AccessPoints *access_points_init();
size_t access_points_add(struct AccessPoints *p, struct AccessPoint *ap);
struct AccessPoint *access_points_get(struct AccessPoints *p, size_t index);
void access_points_free(struct AccessPoints *p);


#endif