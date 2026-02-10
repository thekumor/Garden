// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/lua.h
//	Desc: Lua bindings for Garden.
// 
//	Modified: 2026/02/10 6:33 PM
//	Created: 2026/02/10 6:29 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// LuaJIT
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

// Garden
#include <grd/base_class.h>

namespace grd
{

	class Lua : public BaseClass
	{
	public:
		Lua();
		~Lua();

	private:
		lua_State* m_State;
	};

}