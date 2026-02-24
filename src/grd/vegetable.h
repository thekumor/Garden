// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/vegetable.h
//	Desc: 
// 
//	Modified: 2026/02/24 9:26 AM
//	Created: 2026/02/24 9:26 AM
//	Authors: The Kumor
// 
// ================================================

#pragma once

// STL
#include <string>
#include <vector>

// Garden
#include <grd/image.h>
#include <grd/lua.h>

namespace grd
{

	class Vegetable
	{
	public:
		Vegetable(const std::string& name, const std::vector<std::string>& likes, const std::vector<std::string>& hates, const ImageRect& rect);
		Vegetable(const std::string& name, const std::vector<LuaVariable>& likes, const std::vector<LuaVariable>& hates, const ImageRect& rect);
		Vegetable() = default;

		inline ImageRect GetRect() const { return m_ImageRect; }
		inline const std::vector<std::string>& GetHates() const { return m_Hates; }
		inline const std::vector<std::string>& GetLikes() const { return m_Likes; }
		bool DoesLike(const std::string& other);
		bool DoesHate(const std::string& other);
		void SetRect(const ImageRect& rect);

	private:
		std::string m_Name;
		std::vector<std::string> m_Likes, m_Hates;
		ImageRect m_ImageRect;
	};

}