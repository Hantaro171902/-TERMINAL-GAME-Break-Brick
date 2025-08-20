// main.cpp
#include "headers/game.hpp"

int main() {
    console_size(80, 30);
    Game game(30, 20);
    game.setup();

    while (game.life > 0) {
        game.layout();
        game.render();
        game.input();
        game.update();
        sleep_ms(10);
    }

    game.gameOver();
}

