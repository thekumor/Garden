// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/lua.cpp
//	Desc: Lua bindings for Garden.
// 
//	Modified: 2026/02/10 6:31 PM
//	Created: 2026/02/10 6:31 PM
//	Authors: The Kumor
// 
// ================================================

#include "lua.h"

namespace grd
{
	Lua::Lua()
	{
		m_State = luaL_newstate();
		luaL_openlibs(m_State);
	}

	Lua::~Lua()
	{
		lua_close(m_State);
	}

}