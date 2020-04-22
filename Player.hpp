#ifndef PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platform.hpp"
template <typename T>
std::string to_string(const sf::Vector2<T>& vec) {
  std::string str = "(";
  str += std::to_string(vec.x);
  str += ",";
  str += std::to_string(vec.y);
  str += ')';

  return str;
}

enum horizontalMovement{Left,None,Right};
class Player{
private:
  sf::RectangleShape rect{sf::Vector2f(10,10)};
  sf::Vector2f velocity{0,0};
  sf::Vector2f horizontalAcceleration={0.02,0},gravity={0,0.00095},jumpingAcceleration={0,-0.01};
  float maxHorizontalSpeed = 0.5;
  horizontalMovement direction = horizontalMovement::None;
  bool isColliding = false;
  bool isJumping = false;
  bool inBetween = false;
public:
  void moveRight(){
    direction = horizontalMovement::Right;
    velocity += horizontalAcceleration;
    if(velocity.x > maxHorizontalSpeed) velocity.x = maxHorizontalSpeed;
  }
  void moveLeft(){
    direction = horizontalMovement::Left;
    velocity -= horizontalAcceleration;
    if(velocity.x < -maxHorizontalSpeed) velocity.x = -maxHorizontalSpeed;
  }
  void stop(){
    direction = horizontalMovement::None;
    velocity.x = 0;
  }
  void jump(){
    isJumping = true;
  }
  void handleCollision(){
    //move things vertically
    if(isJumping){
      velocity+=jumpingAcceleration;
      if(velocity.y <= -0.35){
        velocity.y = -0.35;
        isJumping = false;
      }
    }
    velocity+=gravity;

    sf::FloatRect newPosition{rect.getPosition() + velocity,rect.getSize()};
    sf::Vector2f platformPosition={};
    sf::FloatRect platformBounds;

    //detect collision finally lol
    for(const auto platform: platforms){
      platformPosition = platform->getPosition();
      platformBounds = platform->getObject().getGlobalBounds();
      //left part of platform
      if(newPosition.intersects(platformBounds)) {
        isColliding = true;
        if(newPosition.top + rect.getGlobalBounds().width > platformPosition.y && newPosition.top + rect.getGlobalBounds().width < platformPosition.y + platformBounds.height && newPosition.left <= platformPosition.x + platformBounds.width / 2) {
          velocity.x = 0;
          inBetween = true;
          rect.setPosition(platformPosition.x - rect.getGlobalBounds().width,rect.getPosition().y);
        }
        else{
          velocity.y=0;
          inBetween = false;
        }
      }
      else isColliding = false;
    }
    rect.move(velocity);

  }
  void update(){
    handleCollision();
  }
  Player(const float x, const float y){
    rect.setPosition(x,y);
  }
  sf::RectangleShape getObject(){
    return rect;
  }
  std::string getDirection(){
    if(direction == horizontalMovement::Left){
      return "Left";
    }
    else if(direction == horizontalMovement::Right){
      return "Right";
    }
    else{
      return "Still";
    }
  }
  std::string debugger(){
    std::string str = "Position: " + to_string(rect.getPosition()) + "\nVelocity: " + to_string(velocity) + "\nHorizontal Direction: " + getDirection() + "\nJumping: " + std::to_string(isJumping) + "\nColliding: " + std::to_string(isColliding) + "\nIn Between: "+std::to_string(inBetween);
    return str;
  }
};
#endif
