#pragma once

#include <string>
#include <vector>

#include "../accesspoint.h"

namespace WifiScan
{
    class AccessPointPP
    {
    public:
        std::string ssid;
        std::string bssid;

        AccessPointPP(struct AccessPoint *ap);
    };

    class AccessPointsPP
    {
    public:
        std::vector<AccessPointPP*> aps;
        ~AccessPointsPP();
    };
}
