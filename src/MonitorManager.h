#pragma once
#include <windows.h>
#include <vector>
#include <string>

class MonitorManager {
public:
    struct MonitorInfo {
        int index;
        std::wstring name;
        RECT rect;
    };

    static std::vector<MonitorInfo> GetAllMonitors();
    static int GetPrimaryMonitorIndex();
};
