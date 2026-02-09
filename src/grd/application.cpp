// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2026/02/09 2:22 PM
//	Authors: The Kumor
// 
// ================================================

#include "application.h"

namespace grd
{

	Application::Application(const std::wstring& title, const Vec2i& size, HINSTANCE instance)
		: m_Instance(instance), m_MainWindow(title, size)
	{}

	void RebuildGrid(Window& window, Vec2i buttonSize = Vec2i(64, 64))
	{
		window.SetSize({GRD_WINDOW_WIDTH, GRD_WINDOW_HEIGHT});

		window.ClearControls();

		for (std::int32_t y = 0; y < GRD_WINDOW_HEIGHT / buttonSize.y; y++)
			for (std::int32_t x = 0; x < GRD_WINDOW_WIDTH / buttonSize.x; x++)
				window.CreateControl<Button>(L"", { buttonSize.x, buttonSize.y }, { buttonSize.x * x, buttonSize.y * y });
	}

	int Application::Run()
	{
		MSG msg = { };
		EventListener listener;
		g_EventDispatcher.PinListener(&listener);

		listener.AddCallback(EventType::GridSizeChanged, [&](EventData data)
			{
				std::int32_t size = GRD_EVDATA_CAST(data, std::int32_t);
				switch (size)
				{
					case ID_SIZE_32X32:
					{
						RebuildGrid(m_MainWindow, Vec2i(32, 32));
					} break;
					case ID_SIZE_48X48:
					{
						RebuildGrid(m_MainWindow, Vec2i(48, 48));
					} break;
					case ID_SIZE_64X64:
					{
						RebuildGrid(m_MainWindow, Vec2i(64, 64));
					} break;
					case ID_SIZE_96X96:
					{
						RebuildGrid(m_MainWindow, Vec2i(96, 96));
					} break;
				}
			}
		);

		RebuildGrid(m_MainWindow, Vec2i(64, 64));

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			g_EventDispatcher.UnpinInvalidListeners();
			g_EventDispatcher.PinWaitingListeners();
		}

		return EXIT_SUCCESS;
	}

}