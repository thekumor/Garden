// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/window.h
//	Desc: Window class definition.
// 
//	Modified: 2026/02/23 9:48 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>
#include <vector>

// WinAPI
#include <windows.h>

// Garden
#include <grd/base_class.h>
#include <grd/controls.h>
#include <grd/util.h>
#include <grd/events.h>
#include <grd/resource.h>

namespace grd
{

	// ---------------------------------------------------
	//	Handles displaying elements.
	// ---------------------------------------------------
	class Window : public Control
	{
	public:
		Window(const std::wstring& title, const Vec2i& size);
		Window() = default;
		~Window() = default;

		friend class Application;

		static WNDCLASSEXW s_WindowClass;

		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);

		void ForceRedraw();
	};

	// ---------------------------------------------------
	//	Camera for moving and zooming the view.
	// ---------------------------------------------------
	class Camera : public BaseClass
	{
	public:
		Camera() = default;
		~Camera() = default;

		void Reset();
		void Zoom(float factor);
		void Move(const Vec2<float>& delta);

	private:

	};

}