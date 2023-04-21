// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define WINVER 0x0501
#define _WIN32_IE 0x701
#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <wingdi.h>
#include <shlwapi.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "resource.h"

#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"Gdi32.lib")
#pragma comment (lib,"Comdlg32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"Lz32.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "advapi32.lib")
