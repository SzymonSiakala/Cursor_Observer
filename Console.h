#pragma once
#include <Windows.h>

class Console
{
public:
	void set_size(int width, int height);
	void set_text_color(int color);
	RECT get_size();
};