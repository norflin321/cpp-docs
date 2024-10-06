#include <cassert>
#include <iostream>

// prefer "std::string_view" over "std::string" when you need a read-only string, especially for function parameters
void print(std::string_view value)
{
  std::cout << value << std::endl;
}

// functions can be overloaded (when they have the same name but different parameters)
void print(int value)
{
  std::cout << value << std::endl;
}

// accept an argument by reference (no copy, can be modified)
void inc(int &value)
{
  value += 1;
}

// accept an argument by const reference (no copy, can not be modified)
void print_by_ref(const std::string &value)
{
  std::cout << value << std::endl;
}

// pass by pointer (no copy, can be modified using dereference)
void print_by_ptr(std::string *ptr)
{
  assert(ptr); // fail the program in debug mode if pointer is null (asserts do not work in production)

  // make sure we got non-null pointer, because if we dereference a null pointer our program will crash
  if (ptr == nullptr)
    return;

  // Prefer "pass by reference" over "pass by address" unless you have a specific reason to "pass by address".
  std::cout << ptr << " -> " << *ptr << std::endl;
  *ptr = "hotdog";
  std::cout << ptr << " -> " << *ptr << std::endl;
}