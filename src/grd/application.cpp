// ================================================
// 
//	Project: Garden
// 
//	File: src/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2025/01/08 2:27 PM
//	Authors: The Kumor
// 
// ================================================

#include "application.h"

namespace grd
{

	Application::Application(const std::wstring& title, const Vec2<std::int32_t>& size, HINSTANCE instance)
		: m_Instance(instance), m_MainWindow(title, size)
	{
	}

	int Application::Run()
	{
		MSG msg = { };

		const std::int32_t c_ButtonSize = 96;

		for (std::int32_t y = 0; y < 10; y++)
			for (std::int32_t x = 0; x < 15; x++)
				m_MainWindow.CreateControl<Button>(L"", { c_ButtonSize, c_ButtonSize }, { c_ButtonSize * x, c_ButtonSize * y });

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

}