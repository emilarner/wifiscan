#include "wifiscan.h"

int ap_compare(const void *a, const void *b)
{
    struct AccessPoint *ap1 = *(struct AccessPoint**) a;
    struct AccessPoint *ap2 = *(struct AccessPoint**) b; 

    return (int) (ap2->strength - ap1->strength);
}

struct AccessPoints *linux_scan()
{
#ifdef UNIX
    int sock = iw_sockets_open();
    iwrange range_info;

    if (iw_get_range_info(sock, "wlp2s0", &range_info) < 0)
        return NULL;
    

    wireless_scan_head head;
    wireless_scan *result;

    if (iw_scan(sock, "wlp2s0", range_info.we_version_compiled, &head) < 0)
        return NULL;

    
    struct AccessPoints *aps = access_points_init();

    result = head.result;

    while (result != NULL)
    {
        struct AccessPoint *ap = (struct AccessPoint*) malloc(sizeof(*ap));

        strncpy(ap->ssid, result->b.essid, sizeof(ap->ssid));

        bssid_to_string(ap->bssid, (unsigned char*) result->ap_addr.sa_data);
        access_points_add(aps, ap);

        result = result->next;
    }

    return aps;
#endif
#ifndef UNIX
    return NULL;
#endif
}

struct AccessPoints *windows_scan()
{
#ifdef WINDOWS
    HANDLE clientHandle = NULL;
    DWORD maxClient = 2;
    DWORD curVersion = 0;

    WlanOpenHandle(
        maxClient,
        NULL,
        &curVersion,
        &clientHandle
    );


    PWLAN_INTERFACE_INFO_LIST ilist = NULL;
    WlanEnumInterfaces(clientHandle, NULL, &ilist);

    PWLAN_INTERFACE_INFO wl_info = (WLAN_INTERFACE_INFO *) &ilist->InterfaceInfo[0];

    DWORD res = WlanScan(clientHandle, &wl_info->InterfaceGuid, NULL, NULL, NULL);
    Sleep(4500);

    PWLAN_BSS_LIST list;
    WlanGetNetworkBssList(clientHandle, &wl_info->InterfaceGuid, NULL, dot11_BSS_type_any, false, NULL, &list);

    struct AccessPoints *result = access_points_init();

    for (int i = 0; i < list->dwNumberOfItems; i++)
    {
        struct AccessPoint *ap = (struct AccessPoint*) malloc(sizeof(*ap));

        WLAN_BSS_ENTRY ent = list->wlanBssEntries[i];
        
        DOT11_SSID ssid = ent.dot11Ssid;

        memcpy_s(ap->ssid, sizeof(ap->ssid), ssid.ucSSID, ssid.uSSIDLength);
        ap->ssid[ssid.uSSIDLength] = '\0';
        
        bssid_to_string(ap->bssid, ent.dot11Bssid);
        ap->strength = ent.lRssi;

        access_points_add(result, ap);
    }

    qsort(result->aps, result->length, sizeof(struct AccessPoint*), ap_compare);
    return result;

#endif
#ifndef WINDOWS
    return NULL;
#endif
}

struct AccessPoints *mac_os_scan()
{

#ifndef APPLE
    return NULL;
#endif
}

struct AccessPoints *wifi_scan()
{
#ifdef WINDOWS
    return windows_scan();
#endif

#ifdef UNIX
    return linux_scan();
#endif

#ifdef APPLE
    return mac_os_scan();
#endif
}