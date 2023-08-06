// Apriorit Poland Summer 2023 Internship Program
// Observer
// Szymon Siąkała

#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

class MouseObserver {
public:
    virtual void OnEnter() = 0;
    virtual void OnLeave() = 0;
};

class Console {
public:
    void Print(const string& text) {
        cout << text << endl;
    }

    void SetTextColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    int GetWindowWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Bottom;
    }

    int GetWindowHeight() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right;
    }
};

class LogFile {
public:
    LogFile() {
        ofstream ofs("log.txt");
        ofs.close();
    }

    void Write(const string& text) {
        ofstream ofs("log.txt", ios::app);
        ofs << text << endl;
        ofs.close();
    }
};

class MouseWatcher : public MouseObserver {
private:
    Console* console;
    LogFile* logFile;

public:
    MouseWatcher(Console* console, LogFile* logFile) {
        this->console = console;
        this->logFile = logFile;
    }

    void OnEnter() {
        console->SetTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        logFile->Write("Enter");
    }

    void OnLeave() {
        console->SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        logFile->Write("Leave");
    }

};




int main() {
    Console console;
    LogFile logFile;
    MouseWatcher mouseWatcher(&console, &logFile);

    console.Print("hello world");
    std::cout << console.GetWindowWidth() << std::endl;
    std::cout << console.GetWindowHeight() << std::endl;

    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }

        HWND consoleWindow = GetConsoleWindow();

        RECT windowRect;
        GetWindowRect(consoleWindow, &windowRect);

        RECT clientRect;
        GetClientRect(consoleWindow, &clientRect);

        std::cout << "Console Window Coordinates:\n";
        std::cout << "Screen Coordinates:\n";
        std::cout << "Left: " << windowRect.left << "\n";
        std::cout << "Top: " << windowRect.top << "\n";
        std::cout << "Right: " << windowRect.right << "\n";
        std::cout << "Bottom: " << windowRect.bottom << "\n\n";

        std::cout << "Client Coordinates:\n";
        std::cout << "Left: " << clientRect.left << "\n";
        std::cout << "Top: " << clientRect.top << "\n";
        std::cout << "Right: " << clientRect.right << "\n";
        std::cout << "Bottom: " << clientRect.bottom << "\n";

        std::cout << console.GetWindowWidth() << " " << console.GetWindowHeight() << std::endl;

        if (GetCursorPos(&msg.pt)) {
            if (msg.pt.x >= 0 && msg.pt.x < console.GetWindowWidth() &&
                msg.pt.y >= 0 && msg.pt.y < console.GetWindowHeight()) {
                mouseWatcher.OnEnter();
                std::cout << "XXX " << msg.pt.x << " " << msg.pt.y << std::endl;
            }
            else {
                mouseWatcher.OnLeave();
                std::cout << "YYY " << msg.pt.x << " " << msg.pt.y << std::endl;

            }
        }
        Sleep(1000);
    }

    return 0;
}
