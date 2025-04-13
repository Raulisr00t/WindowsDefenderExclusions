# Microsoft Defender Exclusions Viewer

This project is a C program that allows you to view the path exclusions set in **Windows Defender** using the Windows Registry API. It checks the system for any excluded files or directories from being scanned by Microsoft Defender.

## Features
- Scans the **Windows Registry** for path exclusions.
- Outputs excluded files and directories, including their data type and size.
- Supports both 32-bit and 64-bit versions of Windows.

## Prerequisites
- Windows operating system.
- A C compiler (e.g., MinGW, Visual Studio) to compile the code.

## How It Works
The program reads the **Windows Registry** at the key:
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows Defender\Exclusions\Paths

It then enumerates the values under this registry key and outputs any **path exclusions** related to Microsoft Defender.
The exclusions will be listed in the following format:
- **Value Name**: Path or filename excluded
- **Data Type**: `REG_SZ` (string) or `REG_DWORD` (DWORD)
- **Data Size**: The size of the data (in bytes)

## Compilation Instructions

### Using Visual Studio:
1. Open **Visual Studio**.
2. Create a new **Console Application** project in C.
3. Copy and paste the code into the main file (e.g., `main.c`).
4. Compile the project.
5. Run the resulting executable as Administrator to check for exclusions.

### Using MinGW:
1. Install **MinGW** (Minimalist GNU for Windows).
2. Open **Command Prompt** or **PowerShell**.
3. Navigate to the directory containing the source code.
4. Run the following command to compile:
5.Run the program as Administrator

```powershell
gcc -o MicrosoftDefenderExclusions MicrosoftDefenderExclusions.c
.\MicrosoftDefenderExclusions.exe
```

## Running the Program
Run as Administrator: Since accessing the registry key requires elevated permissions, you must run the program with Administrator privileges.
Example output:
```yaml
[+] Running as 64-bit process.
[+] Defender Path Exclusions (values):
    [+] Value Name: C:\Windows\AAct_Tools\AAct_files, Type: 4, Data Size: 4
    [+] Value Name: C:\Windows\System32\SppExtComObjPatcher.exe, Type: 4, Data Size: 4
    [+] Value Name: C:\Windows\System32\SppExtComObjHook.dll, Type: 4, Data Size: 4
    [+] Value Name: C:\Windows\AAct_Tools\AAct_files\KMSSS.exe, Type: 4, Data Size: 4
    [+] Value Name: C:\Windows\AAct_Tools, Type: 4, Data Size: 4
    [+] Value Name: C:\Windows\AAct_Tools\AAct.exe, Type: 4, Data Size: 4
```
## Output Explanation
Value Name: The path or filename that has been excluded from Windows Defender scanning.
Type: This indicates the type of data stored in the registry (usually REG_SZ for strings and REG_DWORD for DWORD values).
Data Size: The size of the data associated with the excluded path (in bytes).

### Example:
For the excluded path C:\Windows\AAct_Tools\AAct_files, the data type is REG_DWORD with a data size of 4 bytes.

# License
This project is licensed under the MIT License - see the LICENSE file for details.
