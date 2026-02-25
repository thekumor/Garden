// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/side_panel.h
//	Desc: Place where buttons to place vegs live.
// 
//	Modified: 2026/02/24 2:33 PM
//	Created: 2026/02/22 11:28 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>

// WinAPI
#include <windows.h>

// Garden
#include <grd/controls.h>
#include <grd/util.h>

namespace grd
{

	// ---------------------------------------------------
	//	Part of screen that acts as vegetable menu.
	// ---------------------------------------------------
	class SidePanel : public Control
	{
	public:
		SidePanel(const Vec2i& size, const Vec2i& position, HWND parent);
		SidePanel() = default;

		static WNDCLASSEXW s_SidePanelClass;

		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);
	};

}