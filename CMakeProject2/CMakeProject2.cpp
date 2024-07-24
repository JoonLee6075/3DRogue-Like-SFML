#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
  
    // Create a Game object
    Game game;

    // Game loop
    while (game.running())
    {
        // Update game logic
        game.update();

        // Render game
        game.render();
    }

    return 0;
}