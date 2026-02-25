// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.h
//	Desc: Application class definition.
// 
//	Modified: 2026/02/24 9:36 AM
//	Authors: The Kumor
// 
// ================================================

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
#include <grd/controls.h>
#include <grd/field.h>
#include <grd/image.h>
#include <grd/lua.h>
#include <grd/side_panel.h>
#include <grd/vegetable.h>

namespace grd
{

	// ---------------------------------------------------
	//	Handles application lifecycle.
	// ---------------------------------------------------
	class Application : public BaseClass
	{
	public:
		Application(const std::wstring& title, const Vec2i& size, HINSTANCE instance);
		Application() = default;
		~Application() = default;

		int Run();

	private:
		HINSTANCE m_Instance;
		Window m_MainWindow;
	};

}