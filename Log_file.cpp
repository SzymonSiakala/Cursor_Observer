#include "Log_file.h"

Log_file::Log_file(const std::string& filename) : output(filename, std::ios::app)
{
	if (!output.is_open())
	{
		throw std::runtime_error("Unable to open the log file.");
	}
}

void Log_file::write(const std::string& text)
{
	if (!output.is_open())
	{
		throw std::runtime_error("Unable to write to the log file.");
	}
	output << text << std::endl;
}

Log_file::~Log_file()
{
	if (output.is_open())
	{
		output.close();
	}
}