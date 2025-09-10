#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <csignal>
#include "game.hpp"
#include "cursor_input.hpp"
#include "utils.hpp"

using namespace std;

void cleanup(int signal) {
    restoreTerminalBlocking();
    showCursor();
    exit(signal);
}

void show_info(const string& arg, const string& programName) {
    if (arg == "-h" || arg == "--help") {
        cout << "Break Brick Game - A simple terminal-based Break Brick implementation\n";
        cout << "Usage: " << programName << " [option]\n\n";
        cout << "Options:\n";
        cout << "  -h, --help    Show this help message\n";
        cout << "  -v, --version Show version information\n";
        cout << "\nControls:\n";
        cout << "  W/S or Up/Down - Move Paddle up/down\n";
        cout << "  A/D or Left/Right - Move Paddle left/right\n";
        cout << "  Q - Quit to menu\n";
        cout << "  R - Restart game\n";
        cout << "  [ / ] - Decrease/Increase ball speed\n";
    } else if (arg == "-v" || arg == "--version") {
        cout << "Break Brick Game v1.0.0\n";
        cout << "A clean, object-oriented implementation of the classic Break Brick game\n";
    } else {
        cout << "Unknown option: " << arg << "\n";
        cout << "Use -h or --help for usage information\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        show_info(argv[1], argv[0]);
        return 0;
    }
    signal(SIGINT, cleanup); // Ctrl+C
    signal(SIGTERM, cleanup); // kill command

    setTerminalNonBlocking();

    const int width = 20;
    const int height = 36;

    Game game(width, height);
    game.run();

    restoreTerminalBlocking();
    
    return 0;
}

