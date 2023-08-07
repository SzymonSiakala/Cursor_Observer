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

    char* get_time();

public:
    Mouse_Observer(Console* console, Log_file* log_file);

    void entry_action();
    void exit_action();
};