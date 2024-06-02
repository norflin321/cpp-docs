#include "Player.h"
#include <iostream>

Player::Player()
{
  this->set_name("Anton");
}

void Player::print_info()
{
  std::string name = this->get_name();
  std::cout << "Player info: " << "name \"" << name << "\" (address: " << &name << ")";
  std::cout << ", " << this->get_sex() << std::endl;
}
