// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2026/02/06 2:35 PM
//	Authors: The Kumor
// 
// ================================================

#include "application.h"

namespace grd
{

	Application::Application(const std::wstring& title, const Vec2i& size, HINSTANCE instance)
		: m_Instance(instance), m_MainWindow(title, size)
	{}

	int Application::Run()
	{
		const Vec2i buttonSize(32, 32);
		for (std::int32_t y = 0; y < GRD_WINDOW_HEIGHT / buttonSize.y; y++)
			for (std::int32_t x = 0; x < GRD_WINDOW_WIDTH / buttonSize.x; x++)
				m_MainWindow.CreateControl<Button>(L"", { buttonSize.x, buttonSize.y }, { buttonSize.x * x, buttonSize.y * y });

		EventListener listener;
		listener.Subscribe(&g_EventDispatcher);
		MSG msg = { };
		Vec2i gridSize(64, 64);

		listener.AddCallback(EventType::GridSizeChanged, [&](EventData data)
			{
				std::int32_t size = GRD_EVDATA_CAST(data, std::int32_t);
				switch (size)
				{
					case ID_SIZE_32X32:
					{
						gridSize = Vec2i(32, 32);
					} break;
					case ID_SIZE_48X48:
					{
						gridSize = Vec2i(48, 48);
					} break;
					case ID_SIZE_64X64:
					{
						gridSize = Vec2i(64, 64);
					} break;
					case ID_SIZE_96X96:
					{
						gridSize = Vec2i(96, 96);
					} break;
				}
			}
		);

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return EXIT_SUCCESS;
	}

}