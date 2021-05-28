/*
   Created by IcarusCoding on 27.05.2021.
   Copyright (c) IcarusCoding All rights reserved.
*/

#ifndef THEFOREST_HACK_CLR_CLR_BOOTSTRAP_H_
#define THEFOREST_HACK_CLR_CLR_BOOTSTRAP_H_

#include "Windows.h"
//#include "MSCorEE.h"
#include <metahost.h>
#include <string>
#pragma comment(lib, "mscoree.lib")

VOID StartRuntime(const std::wstring& modulePath);

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved);

DWORD WINAPI ThreadCallback(LPVOID lpParameter);

std::wstring RetrieveModulePath(const std::wstring& name);

#endif //THEFOREST_HACK_CLR_CLR_BOOTSTRAP_H_
