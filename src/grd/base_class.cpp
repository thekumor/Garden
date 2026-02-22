// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/base_class.cpp
//	Desc: Pins the listener to the global
//	dispatcher.
// 
//	Modified: 2026/02/22 10:43 AM
//	Created: 2026/02/22 10:39 AM
//	Authors: The Kumor
// 
// ================================================

#include "base_class.h"

namespace grd
{

	BaseClass::BaseClass()
	{
		m_Listener = new EventListener;
		g_EventDispatcher.PinListener(m_Listener);
	}

	BaseClass::~BaseClass()
	{
		auto* listener = g_EventDispatcher.GetListenerHandle(m_Listener);

		if (listener)
			listener->SetInvalid();

		delete m_Listener;
	}

}
