#include <windows.h>
#include <stdio.h>
#include <winreg.h>

#define EXCLUSIONS_KEY L"SOFTWARE\\Microsoft\\Windows Defender\\Exclusions\\Paths"

void CheckDefenderPathExclusions() {
    HKEY hKey;
    DWORD retCode;

#ifdef _WIN64
    wprintf(L"[+] Running as 64-bit process.\n");
#else
    wprintf(L"[!] Running as 32-bit process (WOW64).\n");
#endif

    retCode = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        EXCLUSIONS_KEY,
        0,
        KEY_READ | KEY_WOW64_64KEY,  
        &hKey
    );

    if (retCode != ERROR_SUCCESS) {
        wprintf(L"[-] Failed to open registry key. Error: %lu\n", retCode);
        return;
    }

    DWORD index = 0;
    WCHAR valueName[1024];
    DWORD valueNameSize;
    DWORD type;
    BYTE data[1024];
    DWORD dataSize;

    DWORD count = 0;

    wprintf(L"[+] Defender Path Exclusions (values):\n");

    while (TRUE) {
        valueNameSize = sizeof(valueName) / sizeof(WCHAR);
        dataSize = sizeof(data);

        retCode = RegEnumValueW(
            hKey,
            index,
            valueName,
            &valueNameSize,
            NULL,
            &type,
            data,
            &dataSize
        );

        if (retCode == ERROR_NO_MORE_ITEMS) break;

        if (retCode != ERROR_SUCCESS) {
            wprintf(L"[-] RegEnumValueW failed. Error: %lu\n", retCode);
            break;
        }

        wprintf(L"              [+] Value Name: %s, Type: %lu, Data Size: %lu\n", valueName, type, dataSize);

        if (type == REG_SZ) {
            wprintf(L"    • %s\n", valueName); 
        }

        else if (type == REG_DWORD) {
            DWORD dwData = *((DWORD*)data);  
            wprintf(L"• %s (REG_DWORD) Data: %lu\n", valueName, dwData); 
        }

        else {
            wprintf(L"[!] Skipping non-string or non-DWORD value (type: %lu).\n", type);
        }

        index++;
        count++;
    }

    if (count == 0) {
        wprintf(L"[!] No path exclusions found.\n");
    }

    RegCloseKey(hKey);
}

int main() {
    CheckDefenderPathExclusions();
    return 0;
}
