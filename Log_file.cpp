#include "Log_file.h"

Log_file::Log_file(const std::string& filename) : output(filename, std::ios::app) {}

void Log_file::write(const std::string& text)
{
	output << text << std::endl;
}

Log_file::~Log_file()
{
	output.close();
}