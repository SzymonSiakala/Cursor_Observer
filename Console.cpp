#include "Console.h"

void Console::set_size(int width, int height)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD new_size;
	new_size.X = width;
	new_size.Y = height;

	SetConsoleScreenBufferSize(console, new_size);

	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = new_size.Y - 1;
	rect.Right = new_size.X - 1;

	SetConsoleWindowInfo(console, TRUE, &rect);
}

void Console::set_text_color(int color)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
}

RECT Console::get_size()
{
	HWND console_window = GetConsoleWindow();
	RECT window_rect;
	GetWindowRect(console_window, &window_rect);
	return window_rect;
}