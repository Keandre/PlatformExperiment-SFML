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
  sf::Vector2f gravity{0,0.08};
  sf::Vector2f acceleration{0,0.08};
  sf::Vector2f horizontalAcceleration{0.5,0};
  horizontalMovement direction = horizontalMovement::None;
  bool jumping = false;
  bool collide = false;
  bool onPlatform = false;
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
    else acceleration=gravity;
	if(jumping){
      acceleration={0,-0.7};
      collide = false;
    }
    if(velocity.y <= -3.0){
      jumping=false;
      acceleration=gravity;
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
  if(onPlatform){
    if(!jumping){
      velocity.y=0;
      acceleration.y=0;
    }
    else{
      velocity.y=-1.5;
      acceleration.y=-0.7;
    }
    rect.move(velocity);
  }
	velocity += acceleration;
    //change acceleration back to normal

    if(!onPlatform)rect.move(velocity);
    if(rect.getPosition().y>600)rect.setPosition(0,0);
  }
  void changeJumpStatus(bool jump){
    if(collide||onPlatform) {
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
  void setPosition(float a, float b){
    rect.setPosition(a,b);
  }
  void setOnPlatformStatus(bool plat){
    onPlatform=plat;
  }
  bool getOnPlatformStatus(){
    return onPlatform;
  }
};
