#include "Console.h"

void Console::set_size(const int width, const int height)
{
	const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rect = { 0, 0, 0, 0 };
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	if (!SetConsoleWindowInfo(console, TRUE, &rect))
	{
		throw std::runtime_error("Unable to resize console window.");
	}
}

void Console::set_text_color(const int color)
{
	const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetConsoleTextAttribute(console, color))
	{
		throw std::runtime_error("Unable to set console text color.");
	}
}

RECT Console::get_size()
{
	const HWND console_window = GetConsoleWindow();
	RECT rect = { 0, 0, 0, 0 };
	if (!GetWindowRect(console_window, &rect))
	{
		throw std::runtime_error("Unable to get console window size.");
	}

	return rect;
}