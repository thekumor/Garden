// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2026/02/24 10:08 AM
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
		window.ForceRedraw();
	}

	int Application::Run()
	{
		HWND windowHandle = m_MainWindow.m_Handle;
		MSG msg = { };
		EventListener listener;
		g_EventDispatcher.PinListener(&listener);

		g_ImageInfo.LoadImage("img/vegetables.png");

		Field field({ GRD_WINDOW_WIDTH - 300, GRD_WINDOW_HEIGHT }, { 0, 0 }, windowHandle);
		SidePanel panel({ 300, GRD_WINDOW_HEIGHT }, { GRD_WINDOW_WIDTH - 300, 0 }, windowHandle);

		g_Lua.DoFile("data/vegetables.lua");
		std::vector<LuaVariable> luaGlobals = g_Lua.GetGlobalVariables();
		std::vector<std::vector<KeyTable>> luaVegetables = { };
		g_Vegetables.reserve(26);
		
		Vec2i vegetableButtonPos(4, 40);
		for (auto& k : luaGlobals)
		{
			if (k.Name.substr(0, 4) != "veg_") continue;

			std::string vegetableCodeName = k.Name.substr(4, vegetableCodeName.size() - 4);

			std::vector<KeyTable>& veg = luaVegetables.emplace_back(g_Lua.GetTables(k.Name.c_str()));

			std::string vegetableName = "null";
			std::vector<LuaVariable> vegetableLikes, vegetableHates;
			Vec2i vegetablePos(0, 0);

			for (auto& l : veg)
			{
				if (l.Key.Value == "lang_pl")
					vegetableName = l.Value[0].Value;
				else if (l.Key.Value == "pos")
					vegetablePos = Vec2i(atoi(l.Value[0].Value.c_str()), atoi(l.Value[1].Value.c_str()));
				else if (l.Key.Value == "likes")
					vegetableLikes = l.Value;
				else if (l.Key.Value == "hates")
					vegetableHates = l.Value;
			}

			ImageRect vegetableRect(vegetablePos * Vec2i(200, 200), Vec2i(200, 200));

			Vegetable newVegetable(vegetableCodeName, vegetableLikes, vegetableHates, vegetableRect);
			g_Vegetables.push_back(newVegetable);

			std::wstring wVegetableName(vegetableName.begin(), vegetableName.end());

			Image* img = panel.CreateControl<Image>(wVegetableName, { 96, 64 }, vegetableButtonPos);
			img->SetRect(vegetableRect);

			img->GetListener()->AddCallback(EventType::MousePressed, [img, vegetableCodeName, &panel](const EventData& ev)
				{
					g_CurrentVegetable = GetGlobalVegetableByName(vegetableCodeName);

					if (Image::s_SelectedImg)
						Image::s_SelectedImg->SetBgColors(RGB(64, 64, 64), RGB(0, 0, 0));

					img->SetBgColors(RGB(128, 128, 128), RGB(0, 0, 0));

					OutputDebugStringA(g_CurrentVegetable->GetName().c_str());

					Image::s_SelectedImg = img;

					std::vector<Control*> panelControls = panel.GetControls();

					for (auto& l : panelControls)
					{
						Image* im = dynamic_cast<Image*>(l);
						if (!im || im == img) continue;

						Vegetable* relatedVegetable = GetGlobalVegetableByRect(im->GetRect());
						if (!relatedVegetable) continue;

						if (relatedVegetable->DoesHate(vegetableCodeName) || g_CurrentVegetable->DoesHate(relatedVegetable->GetName()))
							im->SetBgColors(RGB(255, 0, 0), RGB(0, 0, 0));
						else if (relatedVegetable->DoesLike(vegetableCodeName) || g_CurrentVegetable->DoesLike(relatedVegetable->GetName()))
							im->SetBgColors(RGB(0, 255, 0), RGB(0, 0, 0));
						else
							im->SetBgColors(RGB(64, 64, 64), RGB(0, 0, 0));
					}
				});

			vegetableButtonPos.x += 100;
			if (vegetableButtonPos.x > 300)
			{
				vegetableButtonPos.x = 4;
				vegetableButtonPos.y += 68;
			}
		}

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
