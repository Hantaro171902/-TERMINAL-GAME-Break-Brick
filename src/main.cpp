#include <iostream>
#include "game.hpp"
#include "ultils.hpp"

int main() {
    const int screenWidth = 30;
    const int screenHeight = 20;
    
    Game game(screenWidth, screenHeight);
    
    hideCursor();
    game.setup();
    
    while (game.life > 0) {
        game.render();
        game.layout();
        game.input();
        game.update();
        
        // Add a small delay to control game speed
        sleep_ms(100);
    }
    
    game.gameOver();
    showCursor();
    
    return 0;
}

