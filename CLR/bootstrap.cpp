/*
   Created by IcarusCoding on 27.05.2021.
   Copyright (c) IcarusCoding All rights reserved.
*/

#include "bootstrap.h"
#include <iostream>
#include <string>

using std::cout;
using std::wcout;
using std::wstring;

VOID StartRuntime(const std::wstring& modulePath) {
    ICLRMetaHost *clrHost = nullptr;
    if(CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (PVOID*) &clrHost) != S_OK) {
        cout << "Error: Cannot create CLR instance!\n";
        return;
    }
    IEnumUnknown *runtimes = nullptr;
    if(clrHost->EnumerateInstalledRuntimes(&runtimes) != S_OK) {
        cout << "Error: Could not retrieve installed CLR runtimes!\n";
        return;
    }
    auto runtimeVersion = reinterpret_cast<LPWSTR>(LocalAlloc(LPTR, 1024));
    if(runtimeVersion == nullptr) {
        cout << "Error: Could not allocate buffer memory!\n";
        return;
    }
    IUnknown *runtime = nullptr;
    ICLRRuntimeInfo *runtimeInfo = nullptr;
    DWORD bufBytes = 1024;
    while(runtimes->Next(1, &runtime, nullptr) == S_OK) {
        if(runtime->QueryInterface<ICLRRuntimeInfo>(&runtimeInfo) == S_OK && runtimeInfo != nullptr) {
            runtimeInfo->GetVersionString(runtimeVersion, &bufBytes);
            wcout << L"Supported CLR version found: " << runtimeVersion << "\n";
        }
    }
    if(runtimeInfo == nullptr) {
        cout << "Error: Could not find a valid CLR version!\n";
        return;
    }
    wcout << L"Selecting CLR version " << runtimeVersion << ".\n";
    ICLRRuntimeHost *runtimeHost = nullptr;
    if(runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*) &runtimeHost) != S_OK) {
        cout << L"Error: Could not retrieve CLR host for version " << runtimeVersion << "!\n";
        return;
    }
    runtimeHost->Start();
    wcout << L"Successfully started CLR host with version " << runtimeVersion << ".\n";
    cout << "Executing .NET Code...\n";
    DWORD result = -1;
    if(runtimeHost->ExecuteInDefaultAppDomain(modulePath.c_str(), L"TheForestHack.TestClass", L"TestMethod", L"TestParameter", &result) != S_OK) {
        cout << "Error: Failed to execute .NET code: " << GetLastError() << "!\n";
        return;
    }
    //TODO close CLR host
}

DWORD WINAPI ThreadCallback(LPVOID lpParameter) {
    MessageBoxA(nullptr, "Injection successful", "Injection", MB_OK);
    wstring modulePath = RetrieveModulePath(L"TheForest_Hack_CLR_Shared.dll");
    MessageBoxW(nullptr, modulePath.c_str(), L"Injection", MB_OK);
    StartRuntime(modulePath + L"\\TheForestHack.dll");
    return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved) {
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, ThreadCallback, hInstance, 0, nullptr);
            break;
        default:
            break;
    }
    return TRUE;
}

wstring RetrieveModulePath(const wstring& name) {
    const HMODULE dllModule = GetModuleHandleW(name.c_str());
    auto buf = (LPWSTR) malloc(MAX_PATH * sizeof(LPWSTR));
    GetModuleFileNameW(dllModule, buf, 2048);
    wstring tmpBuf(buf);
    const size_t index = tmpBuf.find_last_of(L"/\\");
    return tmpBuf.substr(0, index);
}

int main() {
    ThreadCallback(nullptr);
}