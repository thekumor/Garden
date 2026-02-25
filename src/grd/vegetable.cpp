// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/vegetable.cpp
//	Desc: 
// 
//	Modified: 2026/02/24 10:11 AM
//	Created: 2026/02/24 9:26 AM
//	Authors: The Kumor
// 
// ================================================

#include "vegetable.h"

namespace grd
{
	
	Vegetable::Vegetable(const std::string& name, const std::vector<std::string>& likes, const std::vector<std::string>& hates, const ImageRect& rect)
		: m_Name(name), m_Likes(likes), m_Hates(hates), m_ImageRect(rect)
	{}

	Vegetable::Vegetable(const std::string& name, const std::vector<LuaVariable>& likes, const std::vector<LuaVariable>& hates, const ImageRect& rect)
		: m_Name(name), m_ImageRect(rect)
	{
		for (auto& k : likes)
			m_Likes.push_back(k.Value);

		for (auto& k : hates)
			m_Hates.push_back(k.Value);
	}

	bool Vegetable::operator==(const Vegetable& other)
	{
		return m_Name == other.m_Name;
	}

	bool Vegetable::DoesLike(const std::string& other)
	{
		for (auto& k : m_Likes)
			if (k == other)
				return true;

		return false;
	}

	bool Vegetable::DoesHate(const std::string& other)
	{
		for (auto& k : m_Hates)
			if (k == other)
				return true;

		return false;
	}

	void Vegetable::SetRect(const ImageRect& rect)
	{
		m_ImageRect = rect;
	}

	Vegetable* GetGlobalVegetableByRect(const ImageRect& rect)
	{
		for (auto& k : g_Vegetables)
			if (k.GetRect() == rect)
				return &k;

		return nullptr;
	}

	Vegetable* GetGlobalVegetableByName(const std::string& name)
	{
		for (auto& k : g_Vegetables)
			if (k.GetName() == name)
				return &k;

		return nullptr;
	}

	Vegetable* GetGlobalVegetable(const Vegetable& veg)
	{
		for (auto& k : g_Vegetables)
			if (k == veg)
				return &k;

		return nullptr;
	}

	VegetableContainer::VegetableContainer(Vegetable* veg)
		: Veg(veg), Status(VegetableStatus::Neutral), IsValid(true)
	{
		
	}

	VegetableContainer::VegetableContainer()
		: Status(VegetableStatus::Neutral), IsValid(true)
	{}

	bool VegetableContainer::operator==(const VegetableContainer& other) const
	{
		return Veg == other.Veg;
	}

}