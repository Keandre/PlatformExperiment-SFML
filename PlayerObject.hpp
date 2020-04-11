#include <SFML/Graphics.hpp>

class PlayerObject{
private:
  sf::RectangleShape rect{sf::Vector2f(10,10)};
  sf::Vector2f velocity{0,0};
  sf::Vector2f acceleration{0,0.00001};
  bool inAir = true;
public:
  PlayerObject(unsigned int x, unsigned int y){
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(x,y);
  }

  void update(){
    if(inAir){
        rect.move(velocity);
        velocity += acceleration;
    }
  }

  void changeAirStatus(bool status){
    inAir=status;
  }

  sf::RectangleShape getPlayerSprite(){
    return rect;
  }

  void move(int x, int y){
    rect.move(x,y);
  }
};
