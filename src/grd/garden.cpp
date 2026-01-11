// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/garden.cpp
//	Desc: Tool that tells you whether
//	your vegetable garden is valid or not.
// 
//	Modified: 2025/01/08 2:24 PM
//	Authors: The Kumor
// 
// ================================================

// WinAPI
#include <windows.h>

// Garden
#include <grd/application.h>

#define GRD_WINDOW_HEIGHT 900
#define GRD_WINDOW_WIDTH 1280

#pragma warning(disable: 28251)

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	grd::Application app(L"Garden", grd::Vec2<std::int32_t>(GRD_WINDOW_WIDTH, GRD_WINDOW_HEIGHT), instance);
	return app.Run();
}