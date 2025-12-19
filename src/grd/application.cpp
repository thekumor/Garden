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

		m_MainWindow.CreateControl<Button>(L"Hej!", { 256, 128 }, { 0, 0 });

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

}