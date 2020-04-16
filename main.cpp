#include <SFML/Window.hpp>
#include "PlayerObject.hpp"
#include <array>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);
    PlayerObject player = PlayerObject(100,100);

    sf::RectangleShape platform(sf::Vector2f(250,50));
    platform.setPosition(0,300);
    platform.setFillColor(sf::Color::Yellow);

    sf::RectangleShape platform2(sf::Vector2f(250,50));
    platform2.setPosition(251,280);
    platform2.setFillColor(sf::Color::Yellow);
	
	sf::RectangleShape movingPlatform(sf::Vector2f(250,25));
	movingPlatform.setPosition(510,260);
	movingPlatform.setFillColor(sf::Color::Green);
	double increment=0;


    sf::Font font;
    if(!font.loadFromFile("Roboto-Regular.ttf")){}
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)){
          if(event.type == sf::Event::KeyPressed){
			  if(event.key.code == sf::Keyboard::W){
				  player.changeJumpStatus(true);
			  }
			  if(event.key.code == sf::Keyboard::D){
				  player.setMovingRight(true);
			  }
			  if(event.key.code == sf::Keyboard::A){
				  player.setMovingLeft(true);
			  } 
			}
			if(event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::D){
				  player.setMovingRight(false);
				}
				if(event.key.code == sf::Keyboard::A){
				  player.setMovingLeft(false);
				}
			}
			if(event.type == sf::Event::Closed){
				window.close();
			}
		}

        //handle collision
        if(player.getGlobalBounds().intersects(platform.getGlobalBounds()) || player.getGlobalBounds().intersects(platform2.getGlobalBounds()) || player.getGlobalBounds().intersects(movingPlatform.getGlobalBounds())){
          player.setFreeFallStatus(false);
        }
		else{
			player.setFreeFallStatus(true);
		}
        window.clear(sf::Color::Black);
        player.update();
		//update movingPlatform
		movingPlatform.setPosition(510,150*std::cos(increment)+350);
		increment+=0.01;
        text.setString("Position: "+to_string(player.getPosition())+"\nVelocity: "+to_string(player.getVelocity())+"\nAcceleration: "+to_string(player.getAcceleration()) + "\nJumping: "+std::to_string(player.getJumpStatus())+"\nColliding: "+std::to_string(player.getCollisionStatus()) + "\nMovement Direction: "+player.getMovementDirection() + "\nFree Fall Status: "+std::to_string(player.getFreeFallStatus()));
        window.draw(player.getPlayerSprite());
        window.draw(platform);
        window.draw(platform2);
		window.draw(movingPlatform);
        window.draw(text);
        window.display();
    }
    return 0;
}


