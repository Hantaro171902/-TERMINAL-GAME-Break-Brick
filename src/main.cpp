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
        game.layout();
        game.render();
        game.input();
        game.update();
        
        // Smaller delay for smoother movement (~60 FPS)
        sleep_ms(16);
    }
    
    game.gameOver();
    showCursor();
    
    return 0;
}

