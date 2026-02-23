// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/lua.cpp
//	Desc: Lua bindings for Garden.
// 
//	Modified: 2026/02/23 8:55 AM
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

	LuaType Lua::CheckVariable(LuaVariable& variable, std::int32_t offset)
	{
		std::int32_t type = lua_type(m_State, offset);

		switch (type)
		{
			case LUA_TSTRING:
			{
				variable.Value = lua_tostring(m_State, offset);
				variable.Type = LuaType::String;
			} break;
			case LUA_TNUMBER:
			{
				variable.Value = std::to_string(lua_tonumber(m_State, offset));
				variable.Type = LuaType::Number;
			} break;
			case LUA_TBOOLEAN:
			{
				variable.Value = lua_toboolean(m_State, offset) ? "true" : "false";
				variable.Type = LuaType::Boolean;
			} break;
			case LUA_TFUNCTION:
			{
				variable.Value = "<function>";
				variable.Type = LuaType::Function;
			} break;
			case LUA_TTABLE:
			{
				variable.Value = "<table>";
				variable.Type = LuaType::Table;
			} break;
			default:
			{
				variable.Value = "<non-string/number/boolean value>";
				variable.Type = LuaType::None;
			} break;
		}

		return variable.Type;
	}

	LuaVariable Lua::GetVariable(const char* name)
	{
		LuaVariable variable;
		variable.Name = name;

		lua_getglobal(m_State, name);
		CheckVariable(variable);
		lua_pop(m_State, 1);

#if GRD_LUA_ENABLE_CACHE
		m_CachedVariables[name] = variable;
#endif
		return variable;
	}

	std::vector<LuaVariable> Lua::GetTable(const char* name)
	{
		std::vector<LuaVariable> variables;

		lua_getglobal(m_State, name);
		if (!lua_istable(m_State, -1)) return {};

		lua_pushnil(m_State);
		std::int32_t i = 1;
		while (lua_next(m_State, -2) != 0)
		{
			LuaVariable var;

			CheckVariable(var, -1);

			if (lua_type(m_State, -2) == LUA_TSTRING)
				var.Name = lua_tostring(m_State, -2);
			else
			{
				var.Name = std::to_string(i);
				i++;
			}

			variables.push_back(var);

			lua_pop(m_State, 1);
		}

		lua_pop(m_State, 1);

#if GRD_LUA_ENABLE_CACHE
		m_CachedTables[name] = variables;
#endif
		return variables;
	}

	std::vector<KeyTable> Lua::GetTables(const char* name)
	{
		std::vector<KeyTable> keyTables;

		lua_getglobal(m_State, name);
		if (!lua_istable(m_State, -1)) return {};

		lua_pushnil(m_State);

		while (lua_next(m_State, -2) != 0)
		{
			KeyTable keyTab;
			CheckVariable(keyTab.Key, -2);
			keyTab.Value = [&]()
				{
					LuaVariable var;
					CheckVariable(var, -1);
					if (var.Type != LuaType::Table) return std::vector<LuaVariable>{var};

					std::vector<LuaVariable> tab;
					lua_pushnil(m_State);

					std::int32_t i = 1;
					while (lua_next(m_State, -2) != 0)
					{
						LuaVariable var;

						CheckVariable(var, -1);

						if (lua_type(m_State, -2) == LUA_TSTRING)
							var.Name = lua_tostring(m_State, -2);
						else
						{
							var.Name = std::to_string(i);
							i++;
						}

						tab.push_back(var);

						lua_pop(m_State, 1);
					}

					return tab;
				}();

			keyTables.push_back(keyTab);

			lua_pop(m_State, 1);
		}

#if GRD_LUA_ENABLE_CACHE
		m_CachedComplexTables[name] = keyTables;
#endif
		return keyTables;
	}

#if GRD_LUA_ENABLE_CACHE
	const std::vector<grd::LuaVariable>* Lua::GetCachedTable(const std::string& name) const
	{
		std::unordered_map<std::string, std::vector<LuaVariable>>::const_iterator it = m_CachedTables.find(name);
		if (it == m_CachedTables.end())
			return nullptr;

		return &m_CachedTables.at(name);
	}

	const std::vector<grd::KeyTable>* Lua::GetCachedComplexTable(const std::string& name) const
	{
		std::unordered_map<std::string, std::vector<KeyTable>>::const_iterator it = m_CachedComplexTables.find(name);
		if (it == m_CachedComplexTables.end())
			return nullptr;

		return &m_CachedComplexTables.at(name);
	}

	const grd::LuaVariable* Lua::GetCachedVariable(const std::string& name) const
	{
		std::unordered_map<std::string, LuaVariable>::const_iterator it = m_CachedVariables.find(name);
		if (it == m_CachedVariables.end())
			return nullptr;

		return &m_CachedVariables.at(name);
	}
#endif

	std::vector<LuaVariable> Lua::GetGlobalVariables()
	{
		return GetTable("_G");
	}

	void Lua::DoFile(const char* path)
	{
		if (m_State)
			luaL_dofile(m_State, path);
	}

	void Lua::DoString(const char* str)
	{
		if (m_State)
			luaL_dostring(m_State, str);
	}

}