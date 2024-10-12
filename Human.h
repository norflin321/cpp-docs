#pragma once

#include <string>

// favor scoped enumerations over unscoped enumerations
enum class Sex { Male, Female };

class Human
{
  private:
    int id;
    Sex sex;
    int8_t age;

  protected:
    std::string name;

  public:
    Human();
    ~Human();
    std::string get_name();
    void set_name(std::string value);
    std::string get_sex();
    void print_sex();
    void set_age(uint8_t value=20); // best practice is to specify the default arguments in header files
    void print_age();
};