// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/image.cpp
//	Desc: Defines the way images are stored.
// 
//	Modified: 2026/02/23 10:50 AM
//	Created: 2026/02/23 10:50 AM
//	Authors: The Kumor
// 
// ================================================

#include "image.h"

namespace grd
{

	ImageInfo::ImageInfo(const std::string& path)
	{
		LoadImage(path);
	}

	ImageInfo::~ImageInfo()
	{
		if (ImageData != nullptr)
			stbi_image_free(ImageData);
	}

	bool ImageInfo::LoadImage(const std::string& path)
	{
		Path = path;

		ImageData = stbi_load(path.c_str(), &ImageWidth, &ImageHeight, &ImageChannels, 4);
		if (!ImageData)
		{
			MessageBoxW(nullptr, L"Failed to load field image", L"File load error", IDOK);
			return false;
		}

		// Switch to BGRA
		for (std::int32_t i = 0; i < ImageWidth * ImageHeight; i++)
		{
			unsigned char* pixel = ImageData + i * 4;

			unsigned char r = pixel[0];
			unsigned char g = pixel[1];
			unsigned char b = pixel[2];
			unsigned char a = pixel[3];

			pixel[0] = (b * a) / 255;
			pixel[1] = (g * a) / 255;
			pixel[2] = (r * a) / 255;
		}

		return true;
	}

	WNDCLASSEXW Image::s_ImageClass = { 0 };
	std::unordered_map<HWND, ImageRect> Image::s_ImageRects;

	Image::Image(const std::wstring& text, const Vec2i& size, const Vec2i& position, HWND parent)
		: Control(L"", size, position)
	{
		static const wchar_t* className = L"Garden Image";
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

		if (!s_ImageClass.hInstance)
		{
			s_ImageClass = { 0 };
			s_ImageClass.cbClsExtra = 0;
			s_ImageClass.cbSize = sizeof(WNDCLASSEXW);
			s_ImageClass.hInstance = instance;
			s_ImageClass.lpszClassName = className;
			s_ImageClass.lpszMenuName = nullptr;
			s_ImageClass.hCursor = LoadCursorW(nullptr, IDC_HAND);
			s_ImageClass.lpfnWndProc = Image::s_WindowProcedure;

			RegisterClassEx(&s_ImageClass);
			CheckErrors(L"Image.Image.RegisterClassEx");
		}

		m_Handle = CreateWindow(
			className,
			text.c_str(),
			WS_VISIBLE | WS_CHILD,
			position.x,
			position.y,
			size.x,
			size.y,
			parent,
			nullptr,
			instance,
			0
		);
		CheckErrors(L"Image.Image.CreateWindow");

		m_Listener->SetQualifier(m_Handle);
	}

	void Image::SetRect(const ImageRect& rect)
	{
		m_Rect = rect;
	}

	LRESULT Image::s_WindowProcedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				BITMAPINFO bmi = { 0 };
				bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				bmi.bmiHeader.biWidth = g_ImageInfo.ImageWidth;
				bmi.bmiHeader.biHeight = -g_ImageInfo.ImageHeight;
				bmi.bmiHeader.biPlanes = 1;
				bmi.bmiHeader.biBitCount = 32;
				bmi.bmiHeader.biCompression = BI_RGB;

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(handle, &ps);

				RECT rc;
				GetClientRect(handle, &rc);
				
				// Some background
				static HBRUSH brush = CreateSolidBrush(RGB(64, 64, 64));
				FillRect(hdc, &rc, brush);

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

				std::unordered_map<HWND, ImageRect>::const_iterator it = Image::s_ImageRects.find(handle);
				if (it == Image::s_ImageRects.end())
					MessageBoxW(nullptr, L"Unable to find image rect", L"Image.s_WindowProcedure", IDOK);

				ImageRect imageRect = Image::s_ImageRects[handle];

				AlphaBlend(
					hdc,
					0, 0, rc.right - rc.left, rc.bottom - rc.top,
					memDC,
					imageRect.Pos.x, imageRect.Pos.y, imageRect.Size.x, imageRect.Size.y,
					bf
				);

				wchar_t text[32];
				std::int32_t length = GetWindowTextLengthW(handle);

				if (length != 0)
				{
					GetWindowTextW(handle, text, length + 1);
					DrawTextW(hdc, text, -1, &rc, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
				}

				SelectObject(memDC, old);
				DeleteObject(dib);
				DeleteDC(memDC);

				EndPaint(handle, &ps);
			} break;
		}

		return DefWindowProcW(handle, msg, wp, lp);
	}

	ImageRect::ImageRect(const Vec2i& pos, const Vec2i& size)
		: Pos(pos), Size(size)
	{}

}
