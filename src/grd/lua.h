// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/lua.h
//	Desc: Lua bindings for Garden.
// 
//	Modified: 2026/02/22 11:03 AM
//	Created: 2026/02/10 6:29 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <vector>
#include <string>

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

	enum class LuaType
	{
		None = -1,
		Nil = 0,
		Boolean = 1,
		LightUserData = 2,
		Number = 3,
		String = 4,
		Table = 5,
		Function = 6,
		UserData = 7
	};

	// ---------------------------------------------------
	//	Represents a Lua variable with its name and value.
	// ---------------------------------------------------
	struct LuaVariable
	{
		std::string Name;
		std::string Value;
		LuaType Type = LuaType::None;
	};
	
	// ---------------------------------------------------
	//	Represents a key-value pair in a Lua table, where
	//	value is another table.
	// ---------------------------------------------------
	struct KeyTable
	{
		//std::string Key;
		LuaVariable Key;
		std::vector<LuaVariable> Value;
	};

	// ---------------------------------------------------
	//	Lua state wrapper class. Provides methods to
	//	interact with Lua scripts and variables.
	// ---------------------------------------------------
	class Lua : public BaseClass
	{
	public:
		Lua();
		~Lua();

		LuaVariable GetVariable(const char* name);
		std::vector<LuaVariable> GetTable(const char* name);
		std::vector<LuaVariable> GetGlobalVariables();
		std::vector<KeyTable> GetTables(const char* name);
		void DoFile(const char* path);
		void DoString(const char* str);

	private:
		LuaType CheckVariable(LuaVariable& variable, std::int32_t offset = -1);
		lua_State* m_State;
	};

}