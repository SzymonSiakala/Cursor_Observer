#pragma once

class Observer
{
private:
    Console* console;
    Log_file* log_file;

    char* get_time();

public:
    Observer(Console* console, Log_file* log_file);

    void entry_action();
    void exit_action();
};