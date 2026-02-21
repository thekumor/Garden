// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2026/02/21 8:27 AM
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
		window.SetSize({ GRD_WINDOW_WIDTH, GRD_WINDOW_HEIGHT });
	}

	int Application::Run()
	{
		HWND windowHandle = m_MainWindow.m_Handle;
		MSG msg = { };
		EventListener listener;
		g_EventDispatcher.PinListener(&listener);

		Lua lua;
		lua.DoFile("data/vegetables.lua");
		std::vector<LuaVariable> globals = lua.GetGlobalVariables();

		std::vector<std::vector<KeyTable>> vegs = { };
		for (auto& k : globals)
			if (k.Name.substr(0, 4) == "veg_")
				vegs.push_back(lua.GetTables(k.Name.c_str()));

		Field field({ 120, 120 }, { 0, 0 }, windowHandle);

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