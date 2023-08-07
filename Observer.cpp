// Apriorit Poland Summer 2023 Internship Program
// Observer
// Szymon Siąkała

#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

class Console
{
public:
    void set_size(int width, int height)
    {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD new_size;
        new_size.X = width;
        new_size.Y = height;

		SetConsoleScreenBufferSize(console, new_size);

		SMALL_RECT rect;
		rect.Top = 0;
		rect.Left = 0;
		rect.Bottom = new_size.Y - 1;
		rect.Right = new_size.X - 1;

		SetConsoleWindowInfo(console, TRUE, &rect);
	}

    void set_text_color(int color)
    {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, color);
	}

    RECT get_size()
    {
        HWND console_window = GetConsoleWindow();
        RECT window_rect;
        GetWindowRect(console_window, &window_rect);
        return window_rect;
    }
};

class Log_file
{
private:
    std::ofstream output;

public:
    Log_file(const std::string& filename) : output(filename, std::ios::app) {}

    void write(const std::string& text)
    {
        output << text << std::endl;
    }

    ~Log_file()
    {
		output.close();
	}
};

class Observer
{
private:
    Console* console;
    Log_file* log_file;

    char* get_time()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm timeinfo;
        localtime_s(&timeinfo, &time);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        return buffer;
    }

public:
    Observer(Console* console, Log_file* log_file): console(console), log_file(log_file) {}

    void entry_action()
    {
        console->set_text_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::string message= this->get_time();
        message += " -> ENTER";
        log_file->write(message);
    }

    void exit_action() {
        console->set_text_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::string message = this->get_time();
        message += " -> LEAVE";
        log_file->write(message);
    }
};

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
    Observer observer(&console, &log_file);

    console.set_size(75, 20);
    console.set_text_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    print_name();

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

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
                observer.entry_action();
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
                observer.exit_action();
                is_inside = false;

                system("cls");
                print_name();
                print_closed_eye();
            }
        }
    }

    return 0;
}