#include "accesspoint.hpp"

WifiScan::AccessPointPP::AccessPointPP(struct AccessPoint *ap)
{
    bssid = std::string(ap->bssid);
    ssid = std::string(ap->ssid);
}



WifiScan::AccessPointsPP::~AccessPointsPP()
{
    for (int i = 0; i < aps.size(); i++)
        delete aps[i];
}