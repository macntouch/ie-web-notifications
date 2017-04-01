// IE Web Notifications
// Copyright (C) 2015-2016, Sergei Zabolotskikh. All rights reserved.
//
// This file is a part of IE Web Notifications project.
// The use and distribution terms for this software are covered by the
// BSD 3-Clause License (https://opensource.org/licenses/BSD-3-Clause)
// which can be found in the file LICENSE at the root of this distribution.
// By using this software in any fashion, you are agreeing to be bound by
// the terms of this license. You must not remove this notice, or
// any other, from this software.

#include "stdafx.h"
#include "resource.h"
#include "ie_web_notifications_i.h"

namespace {
  class CNikoModule : public ATL::CAtlDllModuleT<CNikoModule>
  {
  public:
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_REGISTRY_SCRIPT, "{F40350AA-C458-4AB4-920B-4F6E91BE606E}")
  };
}

CNikoModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE /*hInstance*/, DWORD dwReason, LPVOID lpReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH) {
  }
  return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE.
STDAPI DllCanUnloadNow(void) {
  return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type.
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv) {
  return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void) {
  // registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer(FALSE);
  return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void) {
  HRESULT hr = _AtlModule.DllUnregisterServer(FALSE);
  return hr;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine) {
  HRESULT hr = E_FAIL;
  static const wchar_t szUserSwitch[] = L"user";

  if (nullptr != pszCmdLine) {
    if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0) {
      ATL::AtlSetPerUserRegistration(true);
    }
  }

  if (bInstall) {
    hr = DllRegisterServer();
    if (FAILED(hr)) {
      DllUnregisterServer();
    }
  } else {
    hr = DllUnregisterServer();
  }

  return hr;
}