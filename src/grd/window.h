#pragma once

// STL
#include <string>

// Garden
#include <grd/base_class.h>
#include <grd/util.h>

namespace grd
{

	class Window : public BaseClass
	{
	public:
		Window(const std::wstring& title, const Vec2<std::int32_t>& size);
		Window() = default;
		~Window() = default;

	private:
		std::wstring m_Title;
		Vec2<std::int32_t> m_Size;
	};

}