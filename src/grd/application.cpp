// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/application.cpp
//	Desc: Application class definition.
// 
//	Modified: 2026/02/25 2:41 PM
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

	void RepositionSideMenuElements(SidePanel& pnl, Vec2<float> delta = { 1.0f, 1.0f })
	{
		Vec2i vegetableButtonPos(15, 40);
		const Vec2i margin(static_cast<std::int32_t>(350 * delta.x), static_cast<std::int32_t>(GRD_WINDOW_HEIGHT * delta.y));

		for (auto& k : pnl.GetControls())
		{
			Image* img = dynamic_cast<Image*>(k);
			if (!img) continue;

			img->SetPosition(vegetableButtonPos);

			vegetableButtonPos.x += 100;
			if (vegetableButtonPos.x >= margin.x - 111)
			{
				vegetableButtonPos.x = 15;
				vegetableButtonPos.y += 76;
			}
		}
	}

	int Application::Run()
	{
		Window& window = m_MainWindow;
		HWND windowHandle = window.m_Handle;
		MSG msg = { };
		EventListener listener;
		g_EventDispatcher.PinListener(&listener);

		g_ImageInfo.LoadImage("img/vegetables.png");

		Field field({ GRD_WINDOW_WIDTH - 350, GRD_WINDOW_HEIGHT }, { 0, 0 }, windowHandle);
		SidePanel panel({ 350, GRD_WINDOW_HEIGHT }, { GRD_WINDOW_WIDTH - 350, 0 }, windowHandle);

		//field.GetListener()->AddCallback(EventType::CameraMove, [&field, &window, &panel](const EventData& data)
		//{
		//	Vec2i cameraMove = GRD_EVDATA_CAST(data, Vec2i);

		//	if (field.GetPosition().x + cameraMove.x > 0) return;
		//	if (field.GetPosition().y + cameraMove.y > 0) return;

		//	field.SetPosition(field.GetPosition() + cameraMove);
		//	panel.PushToFront();

		//	window.ForceRedraw();
		//});

		panel.GetListener()->AddCallback(EventType::WindowResize, [&panel](const EventData& data)
		{
			Vec2<float> delta = GRD_EVDATA_CAST(data, Vec2<float>);

			panel.Resize(delta);
			panel.Reposition(delta);

			RepositionSideMenuElements(panel, delta);
		});

		panel.GetListener()->AddCallback(EventType::LanguageChanged, [&panel](const EventData& data)
		{
			WPARAM wp = GRD_EVDATA_CAST(data, WPARAM);
			for (auto& child : panel.GetControls())
			{
				Image* img = dynamic_cast<Image*>(child);
				if (!img) continue;

				switch (wp)
				{
					case ID_LANGUAGE_ENGLISH:
					{
						LuaVariable val = g_Lua.GetTableValue(img->GetTag().c_str(), "lang_en");
						std::wstring vegetableName(val.Value.begin(), val.Value.end());
						img->SetText(vegetableName);
					} break;

					case ID_LANGUAGE_POLSKI:
					{
						LuaVariable val = g_Lua.GetTableValue(img->GetTag().c_str(), "lang_pl");
						std::wstring vegetableName(val.Value.begin(), val.Value.end());
						img->SetText(vegetableName);
					} break;
				}
			}
		});

		g_Lua.DoFile("data/vegetables.lua");
		std::vector<LuaVariable> luaGlobals = g_Lua.GetGlobalVariables();
		std::vector<std::vector<KeyTable>> luaVegetables = { };
		g_Vegetables.reserve(26);

		LuaVariable defaultLanguage = g_Lua.GetVariable("def_lang");

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
				if (l.Key.Value == "lang_" + defaultLanguage.Value)
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

			Image* img = panel.CreateControl<Image>(wVegetableName, { 96, 72 }, { 0, 0 }); // { 0, 0 } for now
			img->SetTag(k.Name);
			img->SetRect(vegetableRect);

			img->GetListener()->AddCallback(EventType::MouseLeft, [img, vegetableCodeName, &panel](const EventData& ev)
			{
				g_CurrentVegetable = GetGlobalVegetableByName(vegetableCodeName);

				if (Image::s_SelectedImg)
					Image::s_SelectedImg->SetBgColors(RGB(64, 64, 64), RGB(0, 0, 0));

				img->SetBgColors(RGB(128, 128, 128), RGB(0, 0, 0));

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

			RepositionSideMenuElements(panel);
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
