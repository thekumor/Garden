// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/field.h
//	Desc: Field and the way it behaves.
// 
//	Modified: 2026/02/24 2:33 PM
//	Created: 2026/02/20 10:35 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <unordered_map>

// WinAPI
#include <windows.h>

// Garden
#include <grd/controls.h>
#include <grd/util.h>
#include <grd/events.h>
#include <grd/base_class.h>
#include <grd/image.h>
#include <grd/vegetable.h>

namespace grd
{

	// ---------------------------------------------------
	//	Part of screen where user can plant vegetables.
	// ---------------------------------------------------
	class Field : public Control
	{
	public:
		Field(const Vec2i& size, const Vec2i& position, HWND parent = nullptr);
		Field() = default;
		~Field() = default;

		static std::unordered_map<Vec2i, VegetableContainer> s_PlantedVegetables;
		static WNDCLASSEXW s_FieldClass;

		static LRESULT s_WindowProcedure(HWND, UINT, WPARAM, LPARAM);
	};

}