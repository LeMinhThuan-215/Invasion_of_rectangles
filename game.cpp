#include "game.h"

Game::Game()
{
    std::srand(time(NULL));
    this->initVariable();
    this->initWindow();
    this->initFont();
    this->initText();
    this->initTime();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Restart function

void Game::gameRestart()
{
    this->initVariable();
    this->initText();
    this->initTime();
    this->initEnemies();
}

//Init functions

void Game::initVariable()
{
    this->health = 100;
    this->getTime = sf::seconds(0.f);
    this->mouseHold = false;
    this->gameOver = false;

    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 1000.f;
    this->maxEnemies = 10;
    this->maxEnemySize = 100;
    this->minEnemySize = 30;
}

void Game::initWindow()
{
    this->window = nullptr;
    this->videoMode.height = 600;
    this->videoMode.width = 1000;
    this->window = new sf::RenderWindow(videoMode, "First game", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
}

void Game::initFont()
{
    if (!this->font.loadFromFile("fonts/Fredoka-Regular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONT::Failed to load font!" << std::endl;
    }
}

void Game::initText()
{
    this->text.setFont(this->font);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(sf::Vector2f(5.f, 5.f));
}

void Game::initTime()
{
    this->clock.restart();
}

void Game::initEnemies()
{
    this->enemies.clear();
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
                else if (this->gameOver == true && this->event.key.code == sf::Keyboard::Space)
                {
                    this->gameOver = false;
                    this->gameRestart();
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

void Game::updateHealth()
{
    //Kill the enemies when it below and decrease health
    if (this->enemies.size() > 0 && this->enemies.front().getPosition().y > this->videoMode.height)
    {
        int damage = this->enemies.front().getSize().y / 10;
        if (this->health > damage)
        {
            this->health -= damage;
        }
        else
        {
            this->gameOver = true;
        }
        this->enemies.erase(this->enemies.begin());
    }
}

void Game::updateTime()
{
    this->getTime = clock.getElapsedTime();

}

void Game::updateText()
{
    int survivalTime = round(this->getTime.asSeconds());
    if (this->gameOver)
    {
        this->text.setString("Game Over!!!\nSurvival time: " + std::to_string(survivalTime) + "\n\nPress Space to restart ...");
    }
    else
    {
        this->text.setString("Your health: " + std::to_string(this->health) + "\n" + "Survival time: " + std::to_string(survivalTime));
    }
}

void Game::renderText()
{
    this->window->draw(text);
}

void Game::update()
{
    this->getEvents();
    this->updateMousePosition();
    this->updateEnemies();
    this->updateHealth();
    this->updateText();
    if (!this->gameOver)
    {
        this->updateTime();
    }
}

void Game::render()
{
    //Clear old frame
    this->window->clear();

    //Draw objects
    if (!this->gameOver)
    { 
        this->renderEnemies();
    }
    this->renderText();

    //Display new frame
    this->window->display();
}