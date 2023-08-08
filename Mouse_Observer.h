#pragma once
#include <chrono>
#include <ctime>

#include "Console.h"
#include "Log_file.h"

class Mouse_Observer
{
private:
    Console* console;
    Log_file* log_file;

    // Returns the current time as a formatted string.
    char* get_time();

public:
    // Initializes the observer with the given console and log_file instances.
    Mouse_Observer(Console* console, Log_file* log_file);

    // Performs an entry action and logs the time.
    void entry_action();

    // Performs an exit action and logs the time.
    void exit_action();

};