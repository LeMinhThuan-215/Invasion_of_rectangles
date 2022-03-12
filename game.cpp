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
    
    this->killCount = 0;

    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 1200.f;
    this->maxEnemies = 10;
    this->maxEnemySize = 100;
    this->minEnemySize = 30;
    this->enemyVeclocity = 1.5f;
}

void Game::initWindow()
{
    this->window = nullptr;
    this->videoMode.height = 600;
    this->videoMode.width = 1000;
    this->window = new sf::RenderWindow(videoMode, "Invasion of Rectangles", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->setIcon();
}

void Game::setIcon()
{
    if (!this->icon.loadFromFile("icon.jpg"))
    {
        std::cout << "ERROR::GAME::SETICON::Failed to load icon!" << std::endl;
    }
    else
    {
        this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, icon.getPixelsPtr());
    }
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

void Game::updateDifficult()
{
    if (this->killCount >= 20 && this->enemyVeclocity < 2.5f)
    {
        this->enemyVeclocity += 0.001f;
        this->enemySpawnTimerMax -= 0.2f;
    }
    if (this->killCount >= 50 && this->enemyVeclocity < 3.5f)
    {
        this->enemyVeclocity += 0.001f;
        this->enemySpawnTimerMax -= 0.3f;

    }
    if (this->killCount >= 100 && this->enemyVeclocity < 5.f)
    {
        this->enemyVeclocity += 0.002f;
        this->enemySpawnTimerMax -= 0.4f;
    } 
}


void Game::updateText()
{
    std::stringstream ss;
    int survivalTime = round(this->getTime.asSeconds());
    if (this->gameOver)
    {
        ss << "Game Over!!!";
        ss << "\nSurvival time: " << survivalTime;
        ss << "\nYou have killed: " << this->killCount << " enemies";
        ss << "\n\nPress Space to restart ...";
        this->text.setString(ss.str());
    }
    else
    {

        ss << "Your health: " << this->health;
        ss << "\nSurvival time: " << survivalTime;
        ss << "\nKill: " << this->killCount;
    }
    this->text.setString(ss.str());
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
    this->updateDifficult();

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