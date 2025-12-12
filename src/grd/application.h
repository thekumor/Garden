#pragma once

// STL
#include <string>
#include <cstdlib>

// WinAPI
#include <windows.h>

// Garden
#include <grd/util.h>
#include <grd/base_class.h>
#include <grd/window.h>

namespace grd
{

	class Application : public BaseClass
	{
	public:
		Application(const std::wstring& title, const Vec2<std::int32_t>& size, HINSTANCE instance);
		Application() = default;
		~Application() = default;

		int Run();

	private:
		HINSTANCE m_Instance;
		Window m_MainWindow;
	};

}