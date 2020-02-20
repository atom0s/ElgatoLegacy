/**
 * ElgatoLegacy - Copyright (c) 2020 atom0s
 * Contact: https://atom0s.com
 *
 * This file is part of ElgatoLegacy.
 *
 * ElgatoLegacy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ElgatoLegacy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ElgatoLegacy.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Windows.h>

/**
 * Device Scale Factor Enumeration
 */
enum DEVICE_SCALE_FACTOR
{
    DEVICE_SCALE_FACTOR_INVALID,
    SCALE_100_PERCENT,
    SCALE_120_PERCENT,
    SCALE_125_PERCENT,
    SCALE_140_PERCENT,
    SCALE_150_PERCENT,
    SCALE_160_PERCENT,
    SCALE_175_PERCENT,
    SCALE_180_PERCENT,
    SCALE_200_PERCENT,
    SCALE_225_PERCENT,
    SCALE_250_PERCENT,
    SCALE_300_PERCENT,
    SCALE_350_PERCENT,
    SCALE_400_PERCENT,
    SCALE_450_PERCENT,
    SCALE_500_PERCENT
};

/**
 * Display Device Type Enumeration
 */
enum DISPLAY_DEVICE_TYPE
{
    DEVICE_PRIMARY,
    DEVICE_IMMERSIVE
};

/**
 * Monitor DPI Type Enumeration
 */
enum MONITOR_DPI_TYPE
{
    MDT_EFFECTIVE_DPI,
    MDT_ANGULAR_DPI,
    MDT_RAW_DPI,
    MDT_DEFAULT
};

/**
 * Process DPI Awareness Enumeration
 */
enum PROCESS_DPI_AWARENESS
{
    PROCESS_DPI_UNAWARE,
    PROCESS_SYSTEM_DPI_AWARE,
    PROCESS_PER_MONITOR_DPI_AWARE
};

/**
 * GetDpiForMonitor proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT expGetDpiForMonitor(HMONITOR hmonitor, MONITOR_DPI_TYPE dpiType, UINT* dpiX, UINT* dpiY)
{
    UNREFERENCED_PARAMETER(hmonitor);

    // Return known valid values.. (3440 x 1440)
    switch (dpiType)
    {
        case MDT_ANGULAR_DPI:
            *dpiX = 108;
            *dpiY = 108;
            break;
        case MDT_RAW_DPI:
            *dpiX = 109;
            *dpiY = 109;
            break;
        case MDT_EFFECTIVE_DPI:
        case MDT_DEFAULT:
            *dpiX = 96;
            *dpiY = 96;
            break;
    }

    return S_OK;
}

/**
 * GetProcessDpiAwareness proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT expGetProcessDpiAwareness(HANDLE hprocess, PROCESS_DPI_AWARENESS* value)
{
    UNREFERENCED_PARAMETER(hprocess);

    // Assume process is DPI unaware..
    *value = PROCESS_DPI_UNAWARE;

    return S_OK;
}

/**
 * GetScaleFactorForDevice proxy.
 * 
 * WinVer: Windows 8
 */
DEVICE_SCALE_FACTOR expGetScaleFactorForDevice(DISPLAY_DEVICE_TYPE deviceType)
{
    UNREFERENCED_PARAMETER(deviceType);

    // Use the default scale factor as the return..
    return SCALE_100_PERCENT;
}

/**
 * GetScaleFactorForMonitor proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT expGetScaleFactorForMonitor(HMONITOR hMon, DEVICE_SCALE_FACTOR* pScale)
{
    UNREFERENCED_PARAMETER(hMon);

    // Use the default scale factor as the return..
    *pScale = SCALE_100_PERCENT;

    return S_OK;
}

/**
 * RegisterScaleChangeEvent proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT expRegisterScaleChangeEvent(HANDLE hEvent, DWORD_PTR* pdwCookie)
{
    UNREFERENCED_PARAMETER(hEvent);
    UNREFERENCED_PARAMETER(pdwCookie);

    return S_OK;
}

/**
 * RegisterScaleChangeNotifications proxy.
 * 
 * WinVer: Windows 8
 */
HRESULT expRegisterScaleChangeNotifications(DISPLAY_DEVICE_TYPE displayDevice, HWND hwndNotify, UINT uMsgNotify, DWORD* pdwCookie)
{
    UNREFERENCED_PARAMETER(displayDevice);
    UNREFERENCED_PARAMETER(hwndNotify);
    UNREFERENCED_PARAMETER(uMsgNotify);
    UNREFERENCED_PARAMETER(pdwCookie);

    return S_OK;
}

/**
 * RevokeScaleChangeNotifications proxy.
 * 
 * WinVer: Windows 8
 */
HRESULT expRevokeScaleChangeNotifications(DISPLAY_DEVICE_TYPE displayDevice, DWORD dwCookie)
{
    UNREFERENCED_PARAMETER(displayDevice);
    UNREFERENCED_PARAMETER(dwCookie);

    return S_OK;
}

/**
 * SetProcessDpiAwareness proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT __stdcall expSetProcessDpiAwareness(PROCESS_DPI_AWARENESS value)
{
    UNREFERENCED_PARAMETER(value);

    return S_OK;
}

/**
 * UnregisterScaleChangeEvent proxy.
 * 
 * WinVer: Windows 8.1
 */
HRESULT expUnregisterScaleChangeEvent(DWORD_PTR dwCookie)
{
    UNREFERENCED_PARAMETER(dwCookie);

    return S_OK;
}

/**
 * Module entry point.
 * 
 * @param {HINSTANCE} hInstDLL - The module instance handle.
 * @param {DWORD} fdwReason - The reason this entry point was invoked.
 * @param {LPVOID} lpvReserved - System reserved.
 * @return {BOOL} TRUE on success, FALSE otherwise.
 */
BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    UNREFERENCED_PARAMETER(lpvReserved);

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hInstDLL);
            return TRUE;
        default:
            break;
    }

    return TRUE;
}