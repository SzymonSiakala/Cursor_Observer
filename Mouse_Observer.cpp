#include "Mouse_Observer.h"

Mouse_Observer::Mouse_Observer(Console* console, Log_file* log_file) : console(console), log_file(log_file) {}

char* Mouse_Observer::get_time()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo = {};
    if (localtime_s(&timeinfo, &time))
    {
        throw std::runtime_error("Unable to get the local time.");
    }
    char buffer[25] = {};
    if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo) == 0)
    {
		throw std::runtime_error("Unable to format the time.");
	}

    return buffer;
}

void Mouse_Observer::entry_action()
{
    console->set_text_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::string message = this->get_time();
    message += " -> ENTER";
    log_file->write(message);
}

void Mouse_Observer::exit_action()
{
    console->set_text_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::string message = this->get_time();
    message += " -> LEAVE";
    log_file->write(message);
}