// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/file.cpp
//	Desc: 
// 
//	Modified: 2026/02/25 11:29 AM
//	Created: 2026/02/15 10:13 AM
//	Authors: The Kumor
// 
// ================================================

#include "file.h"

namespace grd
{

	File::File(const std::wstring& path, int mode)
		: m_Path(path), m_Mode(mode)
	{
		m_Handle.open(path, mode);

		if (!m_Handle.is_open())
		{
			MessageBoxW(nullptr, L"Unable to open file", L"File.File.m_Handle.open", IDOK);
			return;
		}
	}

	File::File()
		: m_Path(L""), m_Mode(FileMode::Invalid)
	{}

	File::~File()
	{
		Close();
	}

	void File::Open()
	{
		if ((m_Mode & FileMode::Binary) != 0)
		{
			m_Handle.seekg(0, std::ios::end);
			size_t contentSize = m_Handle.tellg();
			m_Handle.seekg(0, std::ios::beg);

			m_BinaryContent = new char[contentSize];
			m_Handle.read(m_BinaryContent, contentSize);
		}
		else
		{
			std::stringstream ss;
			ss << m_Handle.rdbuf();
			m_StringContent = ss.str();
		}
	}

	void File::Write(const std::string& what)
	{
		if (m_Handle.is_open())
		{
			m_Handle.write(what.c_str(), what.size() * sizeof(char));
		}
	}

	void File::Write(char* what, size_t size)
	{
		if (m_Handle.is_open())
			m_Handle.write(what, size);
	}

	void File::WriteMap(std::unordered_map<Vec2i, VegetableContainer>& map)
	{
		for (auto& [pos, vegContainer] : map)
			Write(std::to_string(pos.x) + "," + std::to_string(pos.y) + "," + vegContainer.Veg->GetName() + "\n");
	}

	void File::ReadMap(std::unordered_map<Vec2i, VegetableContainer>* where)
	{
		where->clear();

		std::string str;
		while (std::getline(m_Handle, str))
		{
			size_t firstComma = str.find(',');
			size_t secondComma = str.find(',', firstComma + 1);

			if (firstComma == std::string::npos || secondComma == std::string::npos)
				continue;

			std::int32_t x = std::stoi(str.substr(0, firstComma));
			std::int32_t y = std::stoi(str.substr(firstComma + 1, secondComma - 1));
			std::string name = str.substr(secondComma + 1);

			Vec2i pos(x, y);
			Vegetable* vegetable = GetGlobalVegetableByName(name);
			
			(*where)[pos] = VegetableContainer(vegetable);
		}
	}

	void File::Close()
	{
		if ((m_Mode & FileMode::Binary) != 0 && m_BinaryContent)
		{
			delete[] m_BinaryContent;
			m_BinaryContent = nullptr;
		}

		if (m_Handle.is_open())
			m_Handle.close();
	}

}