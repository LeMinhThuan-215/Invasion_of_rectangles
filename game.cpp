#include "game.h"

Game::Game()
{
    std::srand(time(NULL));
    this->initVariable();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

//Init functions

void Game::initVariable()
{
    this->window = nullptr;

    this->point = 100;
    this->mouseHold = false;

    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 1000.f;
    this->maxEnemies = 10;
    this->maxEnemySize = 100;
    this->minEnemySize = 30;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 1000;
    this->window = new sf::RenderWindow(videoMode, "First game", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
}

//Game functions

bool Game::running()
{
    return this->window->isOpen();
}

void Game::getEvents()
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
                break;
        }
    }
}

void Game::updateMousePosition()
{
    this->intMousePosition = sf::Mouse::getPosition(*this->window);
    this->floatMousePosition = this->window->mapPixelToCoords(this->intMousePosition);
}


void Game::update()
{
    this->getEvents();
    this->updateMousePosition();
    this->updateEnemies();
}

void Game::render()
{
    //Clear old frame
    this->window->clear();

    //Draw objects
    this->renderEnemies();

    //Display new frame
    this->window->display();
}