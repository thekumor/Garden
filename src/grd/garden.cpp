// WinAPI
#include <windows.h>

// Garden
#include <grd/application.h>

#pragma warning(disable: 28251, justification: "Everything's ok :)")

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	grd::Application app(L"Garden", grd::Vec2<std::int32_t>(640, 480), instance);
	return app.Run();
}