#include "accesspoint.h"

struct AccessPoints *access_points_init()
{
    struct AccessPoints *aps = (struct AccessPoints*) malloc(sizeof(struct AccessPoints));

    aps->capacity = 6;
    aps->length = 0;
    aps->aps = (struct AccessPoint**) malloc(aps->capacity * sizeof(struct AccessPoint*));

    return aps;
}

size_t access_points_add(struct AccessPoints *p, struct AccessPoint *ap)
{
    if (p->length == p->capacity)
    {
        p->capacity *= 2;
        p->aps = (struct AccessPoint**) realloc(p->aps, sizeof(struct AccessPoint*) * p->capacity);
    }

    p->aps[p->length] = ap;
    p->length++;
    return p->length - 1;
}

struct AccessPoint *access_points_get(struct AccessPoints *p, size_t index)
{
    if (index < 0)
        return NULL;

    if (index > (p->length - 1))
        return NULL;

    return p->aps[index];
}

void access_points_free(struct AccessPoints *p)
{
    for (size_t i = 0; i < p->length; i++)
        free(p->aps[i]);

    free(p->aps);
    free(p);
}