#include "MonitorManager.h"
#include <windows.h>
#include <vector>

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC, LPRECT lprcMonitor, LPARAM dwData) {
    std::vector<MonitorManager::MonitorInfo>* monitors = reinterpret_cast<std::vector<MonitorManager::MonitorInfo>*>(dwData);
    MONITORINFOEX mi;
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfo(hMonitor, &mi)) {
        MonitorManager::MonitorInfo info;
        info.index = (int)monitors->size();
        info.name = mi.szDevice;
        info.rect = mi.rcMonitor;
        monitors->push_back(info);
    }
    return TRUE;
}

std::vector<MonitorManager::MonitorInfo> MonitorManager::GetAllMonitors() {
    std::vector<MonitorInfo> monitors;
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&monitors);
    return monitors;
}

int MonitorManager::GetPrimaryMonitorIndex() {
    auto monitors = GetAllMonitors();
    for (size_t i = 0; i < monitors.size(); ++i) {
        if (monitors[i].rect.left == 0 && monitors[i].rect.top == 0)
            return (int)i;
    }
    return 0;
}
