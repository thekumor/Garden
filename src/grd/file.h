// ================================================
// 
//	Project: Garden
// 
//	File: src/grd/file.h
//	Desc: 
// 
//	Modified: 2026/02/25 10:59 AM
//	Created: 2026/02/15 10:13 AM
//	Authors: The Kumor
// 
// ================================================

// STL
#include <fstream>
#include <string>
#include <cstdint>
#include <sstream>
#include <unordered_map>

// WinAPI
#include <windows.h>

// Garden
#include <grd/util.h>
#include <grd/vegetable.h>

namespace grd
{

	enum FileMode
	{
		Invalid = 0,
		Write = std::ios::out,
		Open = std::ios::in,
		Binary = std::ios::binary,
	};

	class File
	{
	public:
		File(const std::wstring& path, int mode);
		File();
		~File();

		inline char* GetBinary() const { return m_BinaryContent; }
		inline std::string GetString() const { return m_StringContent; }
		void Open();
		void Write(const std::string& what);
		void Write(char* what, size_t size);
		void WriteMap(std::unordered_map<Vec2i, VegetableContainer>& map);
		void ReadMap(std::unordered_map<Vec2i, VegetableContainer>* where);
		void Close();

	private:
		int m_Mode;
		std::wstring m_Path;
		std::string m_StringContent;
		std::fstream m_Handle;
		char* m_BinaryContent;
	};

}