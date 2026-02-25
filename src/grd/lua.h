// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/lua.h
//	Desc: Lua bindings for Garden.
// 
//	Modified: 2026/02/25 9:30 AM
//	Created: 2026/02/10 6:29 PM
//	Authors: The Kumor
// 
// ================================================

#pragma once

#define GRD_LUA_ENABLE_CACHE 0

// STL
#include <vector>
#include <string>
#include <unordered_map>

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
		LuaVariable GetTableValue(const char* name, const char* key);
		LuaVariable GetNil();
#if GRD_LUA_ENABLE_CACHE
		const std::vector<KeyTable>* GetCachedComplexTable(const std::string& name) const;
		const std::vector<LuaVariable>* GetCachedTable(const std::string& name) const;
		const LuaVariable* GetCachedVariable(const std::string& name) const;
#endif
		void DoFile(const char* path);
		void DoString(const char* str);

	private:
		LuaType CheckVariable(LuaVariable& variable, std::int32_t offset = -1);
		lua_State* m_State;
#if GRD_LUA_ENABLE_CACHE
		std::unordered_map<std::string, std::vector<KeyTable>> m_CachedComplexTables;
		std::unordered_map<std::string, std::vector<LuaVariable>> m_CachedTables;
		std::unordered_map<std::string, LuaVariable> m_CachedVariables;
#endif
	};

	extern Lua g_Lua;

}