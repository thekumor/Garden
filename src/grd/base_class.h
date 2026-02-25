// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/base_class.h
//	Desc: Base class definition.
// 
//	Modified: 2026/02/24 8:59 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// Garden
#include <grd/events.h>

namespace grd
{

	// ---------------------------------------------------
	//	Empty base class for inheritance.
	// ---------------------------------------------------
	class BaseClass
	{
	public:
		BaseClass();
		~BaseClass();

		inline EventListener* GetListener() { return m_Listener; }

	protected:
		EventListener* m_Listener;
	};

}