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

#pragma comment(lib, "Version.lib")
#include <Windows.h>

/**
 * GetFileVersionInfoW proxy.
 * 
 * WinVer: Windows 2000
 */
BOOL __stdcall expGetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    // Forward call to Version.dll function..
    return ::GetFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData);
}

/**
 * GetFileVersionInfoSizeW proxy.
 * 
 * WinVer: Windows 2000
 */
DWORD __stdcall expGetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle)
{
    // Forward call to Version.dll function..
    return ::GetFileVersionInfoSizeW(lptstrFilename, lpdwHandle);
}

/**
 * GetFileVersionInfoExW proxy.
 * 
 * WinVer: Windows Vista
 */
BOOL __stdcall expGetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    // Forward call to Version.dll function..
    return ::GetFileVersionInfoExW(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

/**
 * GetFileVersionInfoSizeExW proxy.
 * 
 * WinVer: Windows Vista
 */
DWORD __stdcall expGetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lpwstrFileName, LPDWORD lpdwHandle)
{
    // Forward call to Version.dll function..
    return ::GetFileVersionInfoSizeExW(dwFlags, lpwstrFileName, lpdwHandle);
}

/**
 * VerFindFileW proxy.
 * 
 * WinVer: Windows 2000
 */
DWORD __stdcall expVerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT puCurDirLen, LPWSTR szDestDir, PUINT puDestDirLen)
{
    // Forward call to Version.dll function..
    return ::VerFindFileW(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
}

/**
 * VerQueryValueW proxy.
 * 
 * WinVer: Windows 2000
 */
BOOL __stdcall expVerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
    // Forward call to Version.dll function..
    return ::VerQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen);
}

/**
 * Module entry point.
 * 
 * @param {HINSTANCE} hInstDLL - The module instance handle.
 * @param {DWORD} fdwReason - The reason this entry point was invoked.
 * @param {LPVOID} lpvReserved - System reserved.
 * @return {BOOL} TRUE on success, FALSE otherwise.
 */
BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
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