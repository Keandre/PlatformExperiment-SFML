#include <SFML/Graphics.hpp>
#include "Player.hpp"
#ifndef GAME_HPP
struct Game{
  void run()
  {
    sf::RenderWindow window{sf::VideoMode(800,600),"My window"};

    Player player = Player(100,100);
    sf::Font font;
    if(!font.loadFromFile("LucidaBrightRegular.ttf")){}
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
        if(event.type == sf::Event::KeyPressed){
          if(event.key.code == sf::Keyboard::D){
            player.moveRight();
          }
          if(event.key.code == sf::Keyboard::A){
            player.moveLeft();
          }
          if(event.key.code == sf::Keyboard::W){
            player.jump();
          }
        }
        if(event.type == sf::Event::KeyReleased){
          if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D){
            player.stop();
          }
        }
      }

      window.clear(sf::Color::Black);

      player.update();
      text.setString(player.debugger() + "\nPlatform Position: "+ to_string(platforms[0]->getPosition()));
      //draw platforms
      for(const auto platform: platforms){
        window.draw(platform->getObject());
      }
      window.draw(player.getObject());
      window.draw(text);
      window.display();
    }
  }
};
#endif
