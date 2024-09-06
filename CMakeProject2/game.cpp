#include "game.h"
#include "FileManager.h"
char Game::map[25][31] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'#','.','#','#','#','.','#','.','#','#','#','#','#','.','#','#','#','.','.','.','.','#','#','#','.','#','#','#','.','.','#'},
    {'#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.','#','.','.','.','#','.','.','#'},
    {'#','.','#','.','#','#','#','#','#','.','#','#','#','#','#','.','#','#','#','#','.','#','.','#','.','#','.','#','.','.','#'},
    {'#','.','.','.','#','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','.','#','.','#','#','#','#','#','.','#','.','.','.','.','#','#','#','#','#','.','#','#','#','#','#','.','.','#'},
    {'#','.','.','.','#','.','.','.','.','.','#','.','#','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','.','#','#','#','.','#','.','#','.','.','.','.','.','#','#','#','.','#','#','#','.','#','#','#','#','#'},
    {'#','.','.','.','.','.','#','.','.','.','#','.','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','#','#'},
    {'#','.','#','#','#','#','#','.','#','.','#','.','.','.','.','.','#','.','#','#','#','#','#','.','#','#','#','#','.','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','.','#','#','#','#','#','.','.','.','.','.','#','.','#','#','#','.','#','.','#','#','#','.','#','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','#','.','#','#','#','.','#','.','.','.','.','.','#','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','.','#','.','#','.','.','.','.','.','#','#','#','#','#','.','#','.','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','#','.','#','.','#','.','#','#','#','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','.','#','.','#','.','.','.','.','.','.','.','#','.','#','#','#','#','#','.','#','#','#','.','#','.','#'},
    {'#','.','.','.','.','.','#','.','#','.','#','#','#','#','#','.','#','.','.','.','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','#','#','#','#','.','.','.','#','.','.','.','.','.','.','.','#','.','#','#','#','.','#','#','#','#','#','.','#','.','#'},
    {'#','.','.','.','.','.','#','.','#','#','#','#','#','.','#','#','#','.','.','.','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','.','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','.','#','#','#','.','#','.','#'},
    {'#','.','.','.','.','.','#','.','#','#','#','#','#','.','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','#','#'},
    {'#','.','#','#','#','.','#','.','.','.','.','.','.','.','.','.','#','.','#','#','#','.','#','.','#','#','#','.','#','#','#'},
    {'#','.','.','.','.','.','#','.','#','#','#','#','#','.','#','.','#','.','.','.','.','.','#','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','.','.','.','.','.','.','.','#','.','#','#','#','#','#','.','#','.','#','#','#','#','#','.','#'},
};
Game::Game()
{
    
    initVariables();
    initWindow();
}
Game::~Game()
{
    delete window;
}

void Game::initWindow()

{
    this->videoMode.height = 800;
    this->videoMode.width = 1200;

    this->window = new sf::RenderWindow(this->videoMode, "Fake 3D Ascii Roguelike", sf::Style::Titlebar | sf::Style::Close);
    this->window->setKeyRepeatEnabled(false);

    this->window->setFramerateLimit(140);
}

void Game::initVariables()
{
    this->endGame = false;
    this->window = nullptr;

    FileManager fileManager;
    if (!font.loadFromFile("resources/SpaceMono-Regular.ttf"))
    {
        std::cout << "where the fuck is my font";
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text2.setFont(font);
    p = player(0, 0);
    map[14][15] = 'o';
    //x,y 변경 주의
    p.setPosition(15,14);

}

bool Game::running() const
{
    return true;
}

bool Game::getEndGame() const
{
    return false;
}

void Game::update()
{
    pollEvents();

    if (moving && repeatCounter > 0)
    {
        mapPos[0] += mapDisp[0];
        mapPos[1] += mapDisp[1];

        repeatCounter--;
    }
    else if (repeatCounter > 0)
    {
        repeatCounter--;
        if (repeatCounter <= 0)
        {
            moving = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && repeatCounter == 0 && map[(int)p.getPosition().y-1][(int)p.getPosition().x] != '#')
    {
        moving = true;
        repeatCounter = 30;
        std::pair<int, int> curr = std::make_pair((int)p.getPosition().x, (int)p.getPosition().y);
        map[curr.second][curr.first] = behindPlayer;

        p.setPosition(curr.first , curr.second-1);

        behindPlayer = map[curr.second][curr.first];

        map[curr.second - 1][ curr.first] = 'o';

        //28
        mapDisp[1] = (14.f/ 15.f);
        mapDisp[0] = 0;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && repeatCounter == 0 && map[(int)p.getPosition().y][(int)p.getPosition().x-1] != '#')
    {
        moving = true;
        repeatCounter = 30;
        std::pair<int, int> curr = std::make_pair((int)p.getPosition().x, (int)p.getPosition().y);
        map[curr.second][curr.first] = behindPlayer;

        p.setPosition(curr.first-1, curr.second);

        behindPlayer - map[curr.second][curr.first];

        map[curr.second][curr.first-1] = 'o';

        mapDisp[0] = (12.f / 15.f);
        mapDisp[1] = 0;

        //p.setPosition(curr.first,curr.second-)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && repeatCounter == 0 && map[(int)p.getPosition().y + 1][(int)p.getPosition().x] != '#')
    {
        moving = true;
        repeatCounter = 30;
        std::pair<int, int> curr = std::make_pair((int)p.getPosition().x, (int)p.getPosition().y);
        map[curr.second][curr.first] = behindPlayer;

        p.setPosition(curr.first, curr.second + 1);

        behindPlayer = map[curr.second][curr.first];

        map[curr.second + 1][curr.first] = 'o';

        mapDisp[1] = -(14.f / 15.f);
        mapDisp[0] = 0;

        //p.setPosition(curr.first,curr.second-)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && repeatCounter == 0 && map[(int)p.getPosition().y][(int)p.getPosition().x + 1] != '#')
    {
        moving = true;
        repeatCounter = 30;
        std::pair<int, int> curr = std::make_pair((int)p.getPosition().x, (int)p.getPosition().y);
        map[curr.second][curr.first] = behindPlayer;

        p.setPosition(curr.first + 1, curr.second );

        behindPlayer - map[curr.second][curr.first];

        map[curr.second][curr.first + 1] = 'o';

        mapDisp[0] = -(12.f / 15.f);
        mapDisp[1] = 0;

        //p.setPosition(curr.first,curr.second-)
    }
    

    // Gradually return to center
    //viewOffsetX *= 0.9f;
    //viewOffsetY *= 0.9f;
}


void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
            this->window->close();
            break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                {
                    this->window->close();
                }
           
        }
    }
}

void Game::render()
{
    this->window->clear(sf::Color::Black);

    float displaceMultiplier = 0;
    //per layer
    float previousLocation[2] = { 0,0 };
    //where did we come from
    for (int j = 0; j <= 14; j += 2)
    {
        // 8 layer player gonna be on layer 4
        
        //600 - 360 = 240
        //400 - 360 = 40
        text.setPosition(mapPos[0] - (12.f * 30.f) , mapPos[1]-(320.f));
        
        // where to put our top left corner of our map
        text.setFillColor(sf::Color(255, 255, 255, (15 - j) * (15 - j)));

        for (int x = 0; x < 31; x++)
        {
            for (int y = 0; y < 25; y++)
            {
                text.setString(map[y][x]);
                previousLocation[0] = text.getPosition().x;
                previousLocation[1] = text.getPosition().y;

               
                text.setPosition(text.getPosition().x + ((videoMode.width / 2 - text.getPosition().x) * displaceMultiplier), text.getPosition().y + ((videoMode.height / 2 - text.getPosition().y) * displaceMultiplier));

                if (text.getString() != "o" && text.getString() != ".")
                {
                    this->window->draw(text);
                }
                else
                {
                    if (j == 6)
                    {
                        sf::Color temp = text.getFillColor();

                        if (text.getString() == 'o')
                        {
                            text.setFillColor(sf::Color::Green);
                        }
                        if (text.getString() == '.')
                        {
                            text.setFillColor(sf::Color(255, 255, 255, 190));
                        }
                        this->window->draw(text);

                        text.setFillColor(temp);
                    }


                }

                text.setPosition(sf::Vector2f(previousLocation[0] , previousLocation[1]));
                text.setPosition(text.getPosition().x, text.getPosition().y + 28.f);
                
            }
            text.setPosition(text.getPosition().x + 24.f, mapPos[1] - (320.f));

            
        }
        displaceMultiplier += 0.018;
    }

    this->window->display();



}
/*
void Game::render()
{
    this->window->clear(sf::Color::Black);

    float mapWidth = 30 * 24.f;
    float mapHeight = 30 * 28.f;

    float startX = (videoMode.width - mapWidth) / 2 + mapDisp[0];
    float startY = (videoMode.height - mapHeight) / 2 + mapDisp[1];

    float displacementMultiplier = 0;
    sf::Vector2f previousLocation;

    for (int j = 0; j <= 14; j += 2)
    {
        float layerOffset = viewOffsetY * (j / 14.0f); // Changed from (1 - (j / 14.0f))
        float sideOffset = viewOffsetX * (j / 14.0f); // Changed from (1 - (j / 14.0f))
        text.setPosition(startX + sideOffset, startY + layerOffset);
        text.setFillColor(sf::Color(255, 255, 255, (15 - j) * (15 - j)));

        for (int y = 0; y < 30; y++)
        {
            for (int x = 0; x < 30; x++)
            {
                text.setString(map[y][x]);
                previousLocation = text.getPosition();

                float displaceX = (videoMode.width / 2 - previousLocation.x) * displacementMultiplier;
                float displaceY = (videoMode.height / 2 - previousLocation.y) * displacementMultiplier;
                text.setPosition(previousLocation.x + displaceX, previousLocation.y + displaceY);

                if (text.getString() != "o" && text.getString() != ".")
                {
                    this->window->draw(text);
                }
                else
                {
                    if (j == 6)
                    {
                        this->window->draw(text);
                    }

                   
                }

                text.setPosition(previousLocation);
                text.move(24.f, 0);
            }
            text.setPosition(startX + sideOffset, text.getPosition().y + 28.f);
        }
        displacementMultiplier += 0.018;
    }

    this->window->display();
}
*/