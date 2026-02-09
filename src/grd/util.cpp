// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/util.cpp
//	Desc: Utility functions and structures.
// 
//	Modified: 2026/02/09 11:44 AM
//	Authors: The Kumor
// 
// ================================================

#include "util.h"

namespace grd
{

	DWORD CheckErrors(const std::wstring& info)
	{
		DWORD errorCode = GetLastError();

		LPWSTR msg = nullptr;

		size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&msg), 0, nullptr);

		if (errorCode)
			MessageBox(nullptr, msg, info.c_str(), MB_ICONERROR | MB_OK);
#if GRD_WINAPI_DEBUG_INFO
		else
			MessageBox(nullptr, msg, info.c_str(), MB_ICONINFORMATION | MB_OK);
#endif

		return errorCode;
	}

}