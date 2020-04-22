#ifndef PLATFORM_HPP
#include <SFML/Graphics.hpp>
#include <vector>
enum Behavior{Regular,Moving,Bouncing};
class Platform{
private:
  Behavior type;
  sf::RectangleShape object{sf::Vector2f(0,0)};
public:
  Platform(const sf::Vector2f size, const sf::Vector2f location,const sf::Color color,const Behavior behave=Behavior::Regular){
    object.setSize(size);
    object.setPosition(location);
    object.setFillColor(color);
    type = behave;
  }
  //update
  void update(){
    if(type != Behavior::Regular){
      //determine behavior
    }
  }
  sf::Vector2f getPosition(){
    return object.getPosition();
  }
  sf::RectangleShape getObject(){
    return object;
  }
};

Platform platform = Platform(sf::Vector2f(250,50),sf::Vector2f(100,300),sf::Color::Red);
Platform platformTwo = Platform(sf::Vector2f(350,25),sf::Vector2f(90,500),sf::Color::Blue);

std::vector<Platform*> platforms{&platform,&platformTwo};


#endif
