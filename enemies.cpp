#include "game.h"

void Game::randomEnemyColor()
{
    this->color.r = rand() % 250 + 100;
    this->color.g = rand() % 250 + 100;
    this->color.b = rand() % 250 + 100;
}

void Game::addRandomEnemy()
{
    //Random size for enemy
    float enemySize = rand() % (this->maxEnemySize - this->minEnemySize) + this->minEnemySize;
    this->enemy.setSize(sf::Vector2f(enemySize, enemySize));

    //Random position for enemy
    float posX = rand() % static_cast<int>(this->videoMode.width - this->enemy.getSize().x);
    float posY = -this->enemy.getSize().y;
    this->enemy.setPosition(posX, posY);

    //Random color for enemy
    this->randomEnemyColor();
    this->enemy.setFillColor(color);
    
    //Add enemy to vector
    this->enemies.push_back(enemy);

}

void Game::spawnEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer > this->enemySpawnTimerMax)
        {
            this->addRandomEnemy();
            enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 15.f;
        }
    }
}

void Game::moveEnemies()
{
    for (auto &e:this->enemies)
    {
        e.move(0.f, 2.f);
    }
}

void Game::killEnemies()
{
    //Kill the enemies when clicked upon them
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (int i = 0; i < this->enemies.size(); i++)
        {        
            if (this->enemies[i].getGlobalBounds().contains(this->floatMousePosition))
            {
                this->enemies.erase(this->enemies.begin() + i);
            }
        }
    }

    //Kill the enemies when it below and decrease point
    if (this->enemies.size() > 0 && this->enemies.front().getPosition().y > this->videoMode.height)
    {
        this->point -= this->enemies.front().getSize().y / 10;
        std::cout << this->point << std::endl;
        this->enemies.erase(this->enemies.begin());
    }
}

void Game::updateEnemies()
{
    //Spawn the enemies
    this->spawnEnemies();

    //Move the enemies
    this->moveEnemies();

    //Kill the enemies
    this->killEnemies();
}

void Game::renderEnemies()
{
    for (auto &e: this->enemies)
    {
        this->window->draw(e);
    }
}