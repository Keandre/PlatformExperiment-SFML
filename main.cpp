#include <SFML/Window.hpp>
#include "PlayerObject.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    PlayerObject player = PlayerObject(100,100);

    sf::RectangleShape platform(sf::Vector2f(250,50));
    platform.setPosition(0,300);
    platform.setFillColor(sf::Color::Yellow);
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)){
          switch(event.type){
            case sf::Event::Closed:
              window.close();
              break;
            case sf::Event::KeyPressed:
              if(event.key.code == sf::Keyboard::W){
                player.move(1,0);
              }
          }
        }

        //handle collision
        if(player.getPlayerSprite().getGlobalBounds().intersects(platform.getGlobalBounds())){
          player.changeAirStatus(false);
        }

        window.clear(sf::Color::Black);
        player.update();
        window.draw(player.getPlayerSprite());
        window.draw(platform);
        window.display();
    }

    return 0;
}
