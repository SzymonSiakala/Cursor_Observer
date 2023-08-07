#pragma once
#include <string>
#include <fstream>

class Log_file
{
private:
	std::ofstream output;

public:
	Log_file(const std::string& filename);

	void write(const std::string& text);

	~Log_file();
};