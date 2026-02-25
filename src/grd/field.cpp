// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/24 7:08 PM
//	Created: 2026/02/20 10:42 AM
//	Authors: The Kumor
// 
// ================================================

#include "field.h"

namespace grd
{

	static void PaintField(HWND handle, HDC hdc)
	{
		static HBRUSH s_LikesBackground = CreateSolidBrush(RGB(0, 255, 0));
		static HBRUSH s_HatesBackground = CreateSolidBrush(RGB(255, 0, 0));
		static HBRUSH s_NeutralBackground = CreateSolidBrush(RGB(0, 120, 0));

		for (auto& plantedVeg : Field::s_PlantedVegetables)
		{
			Vec2i position = plantedVeg.first;
			VegetableContainer vegetable = plantedVeg.second;

			HBRUSH* chosenBrush = &s_NeutralBackground;

			if (vegetable.Status == VegetableStatus::Bad)
				chosenBrush = &s_HatesBackground;
			else if (vegetable.Status == VegetableStatus::Good)
				chosenBrush = &s_LikesBackground;

			ImageRect imageRect = vegetable.Veg->GetRect();

			BITMAPINFO bmi = { 0 };
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = g_ImageInfo.ImageWidth;
			bmi.bmiHeader.biHeight = -g_ImageInfo.ImageHeight;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			RECT rc;
			rc.left = position.x;
			rc.top = position.y;
			rc.right = rc.left + 64;
			rc.bottom = rc.top + 64;

			// Some background
			FillRect(hdc, &rc, *chosenBrush);

			HDC memDC = CreateCompatibleDC(hdc);
			void* bits = nullptr;

			HBITMAP dib = CreateDIBSection(
				hdc,
				&bmi,
				DIB_RGB_COLORS,
				&bits,
				nullptr,
				0
			);

			memcpy(bits, g_ImageInfo.ImageData, g_ImageInfo.ImageWidth * g_ImageInfo.ImageHeight * 4);
			HBITMAP old = reinterpret_cast<HBITMAP>(SelectObject(memDC, dib));

			BLENDFUNCTION bf = {
				AC_SRC_OVER,
				0,
				255,
				AC_SRC_ALPHA
			};

			AlphaBlend(
				hdc,
				rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
				memDC,
				imageRect.Pos.x, imageRect.Pos.y, imageRect.Size.x, imageRect.Size.y,
				bf
			);

			SelectObject(memDC, old);
			DeleteObject(dib);
			DeleteDC(memDC);
		}
	}

	std::unordered_map<Vec2i, VegetableContainer> Field::s_PlantedVegetables = {};
	WNDCLASSEXW Field::s_FieldClass = { 0 };

	static void CheckVegetableStatus(const Vec2i& pos, std::int32_t distance = 3)
	{
		if (distance <= 0) return;

		VegetableContainer& container = Field::s_PlantedVegetables[pos];

		const Vec2i offsets[] = {
			{-64, -64}, {0, -64}, {64, -64},
			{-64, 0}, {64, 0},
			{-64, 64}, {0, 64}, {64, 64},

			{0, -128}, {0, 128}, {128, 0}, {-128, 0},
			{-128, 64}, {-64, 128}, {64, 128}, {128, 64},
			{128, -64}, {64, -128}, {-128, -64}, {-64, -128}
		};

		auto it = Field::s_PlantedVegetables.find(pos);
		if (it == Field::s_PlantedVegetables.end())
			return;

		VegetableContainer& itself = it->second;
		Vegetable* veg = itself.Veg;

		bool seenGood = false;
		bool seenBad = false;

		for (const Vec2i& offset : offsets)
		{
			Vec2i neighborPos = pos + offset;
			auto nit = Field::s_PlantedVegetables.find(neighborPos);
			if (nit == Field::s_PlantedVegetables.end())
				continue;

			Vegetable* neighbor = nit->second.Veg;

			if (nit->second.IsValid && it->second.IsValid)
			{
				if (veg->DoesHate(neighbor->GetName()) || neighbor->DoesHate(veg->GetName()))
				{
					seenBad = true;
				}
				else if (veg->DoesLike(neighbor->GetName()) || neighbor->DoesLike(veg->GetName()))
				{
					seenGood = true;
				}
			}

			double len = neighborPos.Length(pos);
			CheckVegetableStatus(neighborPos, distance - static_cast<std::int32_t>(len / 64));
		}

		if (seenBad)
			itself.Status = VegetableStatus::Bad;
		else if (seenGood)
			itself.Status = VegetableStatus::Good;
		else
			itself.Status = VegetableStatus::Neutral;
	}

	LRESULT Field::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				static HBRUSH s_Background = CreateSolidBrush(RGB(0, 100, 0));
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);

				HDC hdc = BeginPaint(handle, &ps);
				FillRect(hdc, &rc, s_Background);
				PaintField(handle, hdc);
				EndPaint(handle, &ps);
			} break;

			case WM_LBUTTONDOWN:
			{
				if (!g_CurrentVegetable) break;

				RECT rc;
				POINT cursorPos;
				GetCursorPos(&cursorPos);
				GetWindowRect(handle, &rc);

				cursorPos.x -= rc.left;
				cursorPos.y -= rc.top;

				cursorPos.x -= cursorPos.x % 64;
				cursorPos.y -= cursorPos.y % 64;

				RECT paintRegion;
				paintRegion.left = cursorPos.x - 128;
				paintRegion.top = cursorPos.y - 128;
				paintRegion.right = paintRegion.left + 320;
				paintRegion.bottom = paintRegion.top + 320;

				Vec2i cursorVec(cursorPos.x, cursorPos.y);

				Field::s_PlantedVegetables[cursorVec] = VegetableContainer(g_CurrentVegetable);

				CheckVegetableStatus(cursorVec);

				InvalidateRect(handle, &paintRegion, TRUE);
			} break;

			case WM_RBUTTONDOWN:
			{
				RECT rc;
				POINT cursorPos;
				GetCursorPos(&cursorPos);
				GetWindowRect(handle, &rc);

				cursorPos.x -= rc.left;
				cursorPos.y -= rc.top;

				cursorPos.x -= cursorPos.x % 64;
				cursorPos.y -= cursorPos.y % 64;

				RECT paintRegion;
				paintRegion.left = cursorPos.x - 128;
				paintRegion.top = cursorPos.y - 128;
				paintRegion.right = paintRegion.left + 320;
				paintRegion.bottom = paintRegion.top + 320;

				Vec2i cursorVec(cursorPos.x, cursorPos.y);

				std::unordered_map<Vec2i, VegetableContainer>::iterator it = Field::s_PlantedVegetables.find(cursorVec);
				if (it == Field::s_PlantedVegetables.end()) break;

				Field::s_PlantedVegetables[cursorVec].IsValid = false;
				CheckVegetableStatus(cursorVec);
				Field::s_PlantedVegetables.erase(cursorVec);

				InvalidateRect(handle, &paintRegion, TRUE);
			} break;
		}

		return Control::s_WindowProcedure(handle, msg, wp, lp);
	}

	Field::Field(const Vec2i& size, const Vec2i& position, HWND parent)
		: Control(L"", size, position)
	{
		const wchar_t* className = L"Garden Field";
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		if (!s_FieldClass.hInstance)
		{
			s_FieldClass.cbSize = sizeof(WNDCLASSEXW);
			s_FieldClass.hInstance = instance;
			s_FieldClass.lpszClassName = className;
			s_FieldClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			s_FieldClass.lpfnWndProc = Field::s_WindowProcedure;

			RegisterClassExW(&s_FieldClass);
			CheckErrors(L"Field.Field.RegisterClassExW");
		}

		m_Handle = CreateWindowW(
			className,
			L"",
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			instance,
			0
		);
		CheckErrors(L"Field.Field.CreateWindowW");

		ShowWindow(m_Handle, SW_SHOW);

		m_Listener->AddCallback(EventType::WindowResize, [this](EventData ev)
			{
				Vec2<float> delta = GRD_EVDATA_CAST(ev, Vec2<float>);

				Resize(delta);
				Reposition(delta);
			}
		);

		m_Listener->SetQualifier(m_Handle);
	}

}