#ifndef WIFISCAN_H
#define WIFISCAN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "accesspoint.h"
#include "formatting.h"

#ifdef _WIN32
    #pragma comment(lib, "Wlanapi.lib")

    #include <windows.h>
    #include <wlanapi.h>
    
    #define WINDOWS
#endif

#ifdef __unix__
    #include <iwlib.h>
    #define UNIX
#endif

#ifdef __APPLE__
    #define APPLE
#endif

int ap_compare(const void *a, const void *b);

struct AccessPoints *linux_scan();
struct AccessPoints *windows_scan();
struct AccessPoints *mac_os_scan();


struct AccessPoints *wifi_scan(); 

#endif