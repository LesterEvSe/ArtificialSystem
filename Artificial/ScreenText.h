#pragma once
#include "ConsoleWindow.h"
#include "TextAttributes.h"
#include "TextInfo.h"
#include <string>
#include <vector>
#include <map>

namespace GUI 
{
	struct AttributePoint
	{
		size_t symbol_num = 0;
		TextAttributes attribute = 0;
	};

	class ScreenText final
	{
	public:
		ScreenText(Size _size)
			: c_size(_size)
		{}

		void push_text(const std::string& text, TextAttributes attributes);
		void push_text(const std::vector<TextInfo>& info_array);
		void render_text_from(ScreenPoint absolute, size_t line_num);
		size_t get_lines_num();
		void render_text_end(ScreenPoint absolute);

	private:
		const Size c_size;
		std::vector<std::string> m_text;
		std::map<size_t, std::vector<AttributePoint>> m_point_map;
	};
}