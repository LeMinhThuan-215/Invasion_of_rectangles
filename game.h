#ifndef GAME_H
#define GAME_H

#define _WIN32_WINNT 0x0500
#include <windows.h>

#include<iostream>
#include <cmath>
#include<vector>
#include<ctime>
#include<string>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Game
{
    private:
        //Private variables
        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        sf::Event event;
        sf::Vector2i intMousePosition;
        sf::Vector2f floatMousePosition;
        sf::Color color;

        //Font and text
        sf::Font font;
        sf::Text text;

        //Game logic
        int health;
        sf::Time getTime;
        sf::Clock clock;
        bool mouseHold;
        bool gameOver;

        //Enemy variables
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        int maxEnemySize;
        int minEnemySize;

        //Private functions
        void gameRestart();
        void initVariable();
        void initWindow();
        void initFont();
        void initText();
        void initTime();
        void initEnemies();
        
        //Game objects
        sf::RectangleShape enemy;
        std::vector<sf::RectangleShape> enemies;

    public:
        //Constructors, Destructors
        Game();
        ~Game();

        //Game functions
        bool running();
        void getEvents();
        void updateMousePosition();
        void updateHealth();
        void updateTime();
        
        void updateText();
        void renderText();

        void update();
        void render();

        //Enemy functions
        void randomEnemyColor();
        void addRandomEnemy();
        void spawnEnemies();
        void moveEnemies();
        void killEnemies();
        void updateEnemies();
        void renderEnemies();

};


#endif