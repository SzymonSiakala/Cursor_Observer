// Apriorit Poland Summer 2023 Internship Program
// Observer
// Szymon Siąkała

#include <iostream>

#include "Mouse_Observer.h"

void print_name()
{
    std::string text =
        " _______  ______   _______  _______  _______           _______  _______ \n"
        "(  ___  )(  ___ \\ (  ____ \\(  ____ \\(  ____ )|\\     /|(  ____ \\(  ____ )\n"
        "| (   ) || (   ) )| (    \\/| (    \\/| (    )|| )   ( || (    \\/| (    )|\n"
        "| |   | || (__/ / | (_____ | (__    | (____)|| |   | || (__    | (____)|\n"
        "| |   | ||  __ (  (_____  )|  __)   |     __)( (   ) )|  __)   |     __)\n"
        "| |   | || (  \\ \\       ) || (      | (\\ (    \\ \\_/ / | (      | (\\ (   \n"
        "| (___) || )___) )/\\____) || (____/\\| ) \\ \\__  \\   /  | (____/\\| ) \\ \\__\n"
        "(_______)|/ \\___/ \\_______)(_______/|/   \\__/   \\_/   (_______/|/   \\__/\n";
    std::cout << text << std::endl;
}

void print_open_eye()
{
    std::string open_eye =
        "                              ################       \n"
        "                          #######################    \n"
        "                         #####      ###       #####  \n"
        "                       ####        #####         ####\n"
        "                         ####       ###        ####  \n"
        "                          ####               ####    \n"
        "                              ################       \n";
    std::cout << open_eye;
}

void print_closed_eye()
{
    std::string closed_eye =
        "                              ################       \n"
        "                          #######################    \n"
        "                         #####                #####  \n"
        "                       ####                      ####\n"
        "                         ##########################  \n"
        "                          ####               ####    \n"
        "                              ################       \n";
    std::cout << closed_eye;
}

int main()
{
    bool is_inside = false;
    const std::string filename = "log.txt";

    Console console;
    Log_file log_file(filename);
    Mouse_Observer mouse_observer(&console, &log_file);

    console.set_size(75, 20);
    console.set_text_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    print_name();

    MSG msg;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        GetCursorPos(&msg.pt);
        RECT window_rect = console.get_size();
        if (msg.pt.x >= window_rect.left && msg.pt.x <= window_rect.right &&
            msg.pt.y >= window_rect.top && msg.pt.y <= window_rect.bottom)
        {
            if (!is_inside)
            {
                mouse_observer.entry_action();
                is_inside = true;

                system("cls");
                print_name();
                print_open_eye();
            }
        }
        else
        {
            if (is_inside)
            {
                mouse_observer.exit_action();
                is_inside = false;

                system("cls");
                print_name();
                print_closed_eye();
            }
        }
    }

    return 0;
}