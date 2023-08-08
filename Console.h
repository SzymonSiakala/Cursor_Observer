#pragma once
#include <Windows.h>
#include <stdexcept>

class Console
{
public:
	// Sets the console size to the specified dimensions.
	void set_size(int width, int height);

	// Sets the text color of the console.
	void set_text_color(int color);

	// Returns the dimensions of the console window.
	RECT get_size();

};