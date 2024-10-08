#include "ConsoleWindow.h"

namespace GUI
{
	HANDLE ConsoleWindow::m_console_handler = NULL;
	uint16_t ConsoleWindow::m_last_text_attributes = 15;

	void ConsoleWindow::init()
	{
		m_console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void ConsoleWindow::set_text_colours(const TextColours& _color)
	{
		m_last_text_attributes &= 0xFFFF0000;
		m_last_text_attributes |= _color.code();

		SetConsoleTextAttribute(m_console_handler, m_last_text_attributes);
	}

	void ConsoleWindow::set_text_borders(const TextBorders& _borders)
	{
		m_last_text_attributes &= ~COMMON_LVB_GRID_HORIZONTAL;
		m_last_text_attributes &= ~COMMON_LVB_GRID_LVERTICAL;
		m_last_text_attributes &= ~COMMON_LVB_GRID_RVERTICAL;
		m_last_text_attributes &= ~COMMON_LVB_UNDERSCORE;
		m_last_text_attributes |= _borders.code();

		SetConsoleTextAttribute(m_console_handler, m_last_text_attributes);
	}

	void ConsoleWindow::set_text_attributes(const TextAttributes& _attributes)
	{
		m_last_text_attributes = _attributes.code();

		SetConsoleTextAttribute(m_console_handler, m_last_text_attributes);
	}

	Size ConsoleWindow::get_console_size()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(m_console_handler, &info);
		Size size {uint16_t(info.srWindow.Bottom - info.srWindow.Top + 1),
				   uint16_t(info.srWindow.Right - info.srWindow.Left + 1)};
		return size;
	}
	
	void ConsoleWindow::set_cursor_visibility(bool visibility)
	{
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(m_console_handler, &info);
		info.bVisible = visibility;
		SetConsoleCursorInfo(m_console_handler, &info);
	}
	
	void ConsoleWindow::set_cursor_position(const ScreenPoint point)
	{
		SetConsoleCursorPosition(m_console_handler, { point.y, point.x });
	}

	void ConsoleWindow::fill_screen(Colours background)
	{
		set_cursor_position({ 0, 0 });
		set_text_colours(TextColours(Colours::WHITE, background));
		std::cout << std::string(10000, ' ');
		set_cursor_position({ 0, 0 });
	}

	void ConsoleWindow::delta_cursor_position(const ScreenPoint delta)
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(m_console_handler, &info);
		ScreenPoint point;
		point.x = info.dwCursorPosition.Y + delta.x;
		point.y = info.dwCursorPosition.X + delta.y;
		set_cursor_position(point);
	}
}
