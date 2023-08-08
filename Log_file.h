#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

class Log_file
{
private:
	std::ofstream output;

public:
	// Opens the log file with the given filename.
	Log_file(const std::string& filename);

	// Writes the given text to the log file.
	void write(const std::string& text);

	// Closes the log file.
	~Log_file();
};