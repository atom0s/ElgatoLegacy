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
#pragma comment(lib, "WtsApi32.lib")
#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "../thirdparty/detours.lib")
#include "../thirdparty/detours.h"

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
 * Detour Prototypes
 */
extern "C"
{
    auto Real_WTSQuerySessionInformationW = static_cast<decltype(::WTSQuerySessionInformationW)*>(::WTSQuerySessionInformationW);
};

/**
 *  wtsapi32!WTSQuerySessionInformationW detour callback.
 *
 * @param {HANDLE} hServer - A handle to an RD Session Host server.
 * @param {DWORD} SessionId - A Remote Desktop Services session identifier.
 * @param {WTS_INFO_CLASS} WTSInfoClass - A value of the WTS_INFO_CLASS enumeration that indicates the type of session information to retrieve in a call to the WTSQuerySessionInformation function.
 * @param {LPWSTR} ppBuffer - A pointer to a variable that receives a pointer to the requested information.
 * @param {DWORD*} pBytesReturned - A pointer to a variable that receives the size, in bytes, of the data returned in ppBuffer.
 * @return {BOOL} Non-zero on success, FALSE otherwise.
 */
BOOL __stdcall Mine_WTSQuerySessionInformationW(HANDLE hServer, DWORD SessionId, WTS_INFO_CLASS WTSInfoClass, LPWSTR* ppBuffer, DWORD* pBytesReturned)
{
    // Allow the actual call to happen..
    const auto ret = Real_WTSQuerySessionInformationW(hServer, SessionId, WTSInfoClass, ppBuffer, pBytesReturned);
    if (!ret)
        return ret;

    // Check for session info lookups..
    if (WTSInfoClass == WTS_INFO_CLASS::WTSSessionInfoEx)
    {
        // Obtain the session information data..
        const auto session = (WTSINFOEXW*)*ppBuffer;

        // Force the unlock state of the session..
        session->Data.WTSInfoExLevel1.SessionFlags = WTS_SESSIONSTATE_UNLOCK;
    }

    return ret;
}

/**
 * Hooks a specific API to fix session lock lookups causing StreamDecks to not function on Windows 7.
 */
void __stdcall ApplySessionPatch(void)
{
    ::DetourTransactionBegin();
    ::DetourUpdateThread(::GetCurrentThread());
    ::DetourAttach(&(PVOID&)Real_WTSQuerySessionInformationW, Mine_WTSQuerySessionInformationW);
    ::DetourTransactionCommit();
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
            ApplySessionPatch();
            return TRUE;
        default:
            break;
    }

    return TRUE;
}