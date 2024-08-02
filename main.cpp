#include <iostream>
#include <cmath>
#include <vector>

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <Audio.hpp>
#include <Network.hpp>

class Bullet
{
public:
    sf::CircleShape shape;
    sf::Vector2f currVelocity;
    float maxSpeed;

    Bullet(float radius = 5.f)
        : currVelocity(0.f, 0.f), maxSpeed(15.f)
    {
        this->shape.setRadius(radius);
        this->shape.setFillColor(sf::Color::Red);
    };
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Works!", sf::Style::Default);
    window.setFramerateLimit(120);

    // Player
    sf::CircleShape player(30.f);
    player.setFillColor(sf::Color::White);

    // Bullets
    Bullet b1;
    std::vector<Bullet> bullets;
    // bullets.push_back(Bullet(b1));

    // Enemy


    // Vectors
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Update

        // Vectors
        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
        mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        aimDirNorm = aimDir / static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
        // std::cout << "X: "<< aimDirNorm.x << ", Y: "<< aimDirNorm.y << std::endl;

        // Player
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0.f,-6.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0.f,6.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-6.f,0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(6.f,0.f);

        // Shooting
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            b1.shape.setPosition(playerCenter.x - b1.shape.getRadius(), playerCenter.y - b1.shape.getRadius());
            b1.currVelocity = aimDirNorm * b1.maxSpeed;

            bullets.push_back(Bullet(b1));
        }

        for(size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].shape.move(bullets[i].currVelocity);

            if(
                bullets[i].shape.getPosition().x > 1920 || // Right side
                bullets[i].shape.getPosition().x + bullets[i].shape.getRadius()*2 < 0 || // Left side
                bullets[i].shape.getPosition().y + bullets[i].shape.getRadius()*2 < 0 || // Upper side
                bullets[i].shape.getPosition().y > 1080  // Lower side
                ) { bullets.erase(bullets.begin() + i); } // Delete the bullet if out of bounds

        }

        // Draw
        window.clear();


        for(size_t i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i].shape);
        }

        window.draw(player);

        window.display();
    }

    return 0;
}

