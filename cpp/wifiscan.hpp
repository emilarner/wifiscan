#pragma once

#include <string>
#include <vector>

#include "../wifiscan.h"
#include "accesspoint.hpp"

namespace WifiScan
{
    class WifiScan
    {
    public:
        static std::vector<AccessPointPP> wifi_scan();
        
    };
}