#include "application.h"

namespace grd
{

	Application::Application(const std::wstring& title, const Vec2<std::int32_t>& size, HINSTANCE instance)
		: m_Instance(instance), m_MainWindow(title, size)
	{
	}

	int Application::Run()
	{
		MessageBoxW(nullptr, L"Hello, Garden!", L"Garden Application", MB_OK | MB_ICONINFORMATION);

		return EXIT_SUCCESS;
	}

}