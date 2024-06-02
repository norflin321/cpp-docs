#include "Human.h"
#include <iostream>

Human::Human()
{
  this->sex = Sex::Male;

  static int id = 0;
  this->id = id;
  std::cout << "human " << id << " created" << std::endl;

  id += 1;
}

Human::~Human()
{
  std::cout << "~ human object " << this->id << " destructured" << std::endl;
}

void Human::set_name(std::string value)
{
  this->name = value;
}

std::string Human::get_name()
{
  return this->name;
}

std::string Human::get_sex()
{
  return this->sex == Sex::Male ? "Male" : "Female";
}

void Human::print_sex()
{
  std::string sex = this->sex == Sex::Male ? "Male" : "Female";
  std::cout << "Sex: " + sex << std::endl;
}

void Human::set_age(uint8_t value)
{
  this->age = value;
}

void Human::print_age()
{
  std::cout << "Age: " + std::to_string(this->age) << std::endl;
}
