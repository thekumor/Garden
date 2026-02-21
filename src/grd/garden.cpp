// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/garden.cpp
//	Desc: Tool that tells you whether
//	your vegetable garden is valid or not.
// 
//	Modified: 2026/02/21 8:14 AM
//	Authors: The Kumor
// 
// ================================================

#define STB_IMAGE_IMPLEMENTATION

// WinAPI
#include <windows.h>

// STL
#include <unordered_map>
#include <vector>

// Garden
#include <grd/application.h>
#include <grd/events.h>
#include <grd/util.h>

// Global variables
grd::EventDispatcher grd::g_EventDispatcher;
std::unordered_map<HWND, grd::Vec2i> grd::g_WindowSizes;

#pragma warning(disable: 28251)

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	grd::Application app(L"Garden", grd::Vec2i(GRD_WINDOW_WIDTH, GRD_WINDOW_HEIGHT), instance);
	return app.Run();
}