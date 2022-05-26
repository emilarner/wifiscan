#include "formatting.h"

char *bssid_to_string(char *mut, unsigned char *bssid)
{
    memset(mut, 0, 32);
    snprintf(mut, 32, "%02x:%02x:%02x:%02x:%02x:%02x",
        bssid[0],
        bssid[1],
        bssid[2],
        bssid[3],
        bssid[4],
        bssid[5]
    );


    return mut;
}

void print_access_points(FILE *fp, struct AccessPoints *aps)
{
    fprintf(fp, "Wifi Scan Completed:\n\n");

    for (int i = 0; i < aps->length; i++)
    {
        struct AccessPoint *ap = aps->aps[i];
        fprintf(fp, "SSID: %s\n", ap->ssid);
        fprintf(fp, "    BSSID: %s\n", ap->bssid);
        fprintf(fp, "    Strength: %ld\n", ap->strength);

        fprintf(fp, "\n");
    }
}

int print_access_points_json(FILE *fp, struct AccessPoints *aps)
{
    if (aps == NULL)
    {
        fprintf(fp, "{\"aps\": null}");
        return -1;
    }

    fprintf(fp, "{\n");
    fprintf(fp, "\"aps\": [\n");

    for (int i = 0; i < aps->length; i++)
    {
        struct AccessPoint *ap = aps->aps[i];

        fprintf(fp, "    {\n");
        fprintf(fp, "        \"ssid\": \"%s\",\n", ap->ssid);
        fprintf(fp, "        \"bssid\": \"%s\",\n", ap->bssid);
        fprintf(fp, "        \"strength\": %ld\n", ap->strength);
        fprintf(fp, "    }");

        if (i != (aps->length - 1))
            fprintf(fp, ",");

        fprintf(fp, "\n");
    }

    fprintf(fp, "]\n");
    fprintf(fp, "}\n");

    return 0;
}

int print_access_points_struct(FILE *fp, struct AccessPoints *aps)
{
    if (aps == NULL)
    {
        uint8_t error = -1;
        fwrite(&error, 1, 1, fp);
        return -1;
    }

    fwrite((uint8_t*) &aps->length, 1, 1, fp);

    for (int i = 0; i < aps->length; i++)
    {
        struct AccessPoint *ap = aps->aps[i];
        fwrite(ap, 1, sizeof(*ap), fp);
    }

    return 0;
}