#include <SFML/Graphics.hpp>
template <typename T>
std::string to_string(const sf::Vector2<T>& vec) {
  std::string str = "(";
  str += std::to_string(vec.x);
  str += ",";
  str += std::to_string(vec.y);
  str += ')';

  return str;
}
enum horizontalMovement{Left, None, Right};
class PlayerObject{
private:
  sf::RectangleShape rect{sf::Vector2f(10,10)};
  sf::Vector2f velocity{0,0};
  sf::Vector2f acceleration{0,0.05};
  sf::Vector2f horizontalAcceleration{0.5,0};
  horizontalMovement direction = horizontalMovement::None;
  bool jumping = false;
  bool collide = false;
public:
  PlayerObject(unsigned int x, unsigned int y){
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(x,y);
  }

  void update(){
    if(collide){
      acceleration.y = 0;
	  velocity.y = 0;
    }
    else{
      acceleration={0,0.5};
    }
	if(jumping){
      acceleration={0,-0.9};
      collide = false;
    }
    if(velocity.y <= -6.2){
      jumping=false;
    }
	//horizontal movement
	if(direction==horizontalMovement::Right){
		velocity+=horizontalAcceleration;
		if(velocity.x>2)velocity.x=2;
	}
	else if(direction==horizontalMovement::Left){
		velocity-=horizontalAcceleration;
		if(velocity.x<-2)velocity.x=-2;
	}
	else{
		velocity.x = 0;
	}
	velocity += acceleration;
    //change acceleration back to normal

    rect.move(velocity);
  }
  void changeJumpStatus(bool jump){
    if(collide) {
      jumping=jump;
      collide=false;
    }
  }

  void setCollisionStatus(bool colliding){
    collide=colliding;
  }
  bool getJumpStatus(){
    return jumping;
  }
  bool getCollisionStatus(){
    return collide;
  }
  
  void setMovingRight(bool movingRight){
	  if(movingRight){
		  direction=horizontalMovement::Right;
	  }
	  else{
		  direction=horizontalMovement::None;
	  }
  }
  void setMovingLeft(bool movingLeft){
	  if(movingLeft){
		  direction=horizontalMovement::Left;
	  }
	  else{
		  direction=horizontalMovement::None;
	  }
  }
	
  std::string getMovementDirection(){
	switch(this->direction){
		case horizontalMovement::Right:
			return "Right";
		case horizontalMovement::Left:
			return "Left";
		case horizontalMovement::None:
			return "Stationary";
		default:
			return "Right";
	}
  }
	  
  sf::RectangleShape getPlayerSprite(){
    return rect;
  }
  void move(int x, int y){
    rect.move(x,y);
  }
  sf::Vector2f getVelocity(){
    return velocity;
  }
  sf::Vector2f getAcceleration(){
    return acceleration;
  }
  sf::Vector2f getPosition(){
    return rect.getPosition();
  }
  sf::FloatRect getGlobalBounds(){
    return rect.getGlobalBounds();
  }
};
