#ifndef GAME_H
#define GAME_H

#include<iostream>
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

        //Game logic
        int point;
        bool mouseHold;

        //Enemy variables
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        int maxEnemySize;
        int minEnemySize;

        //Private functions
        void initVariable();
        void initWindow();
        
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