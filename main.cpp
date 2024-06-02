#include <iostream>
#include <fstream>

#include "Human.h"
#include "Player.h"
#include "templates.h"
#include "utils.h"

// type aliases sometimes useful to make complex types easier to read
using string = std::string;

#define README_FILE "readme.md"
const string DEFAULT_HUMAN_NAME = "John Doe"; // better global constant
constexpr int DEFAULT_HUMAN_AGE = sum(20, 5); // expression evaluated at compile-time

int main()
{
  print("-- hello world from cpp --\n");

  // memory for this object is allocated on the stack and automatically managed by the compiler, it will be
  // deallocated when the object goes out of the scope of this function
  Human h;
  h.set_name(DEFAULT_HUMAN_NAME);
  string name = h.get_name();
  print(name);
  h.print_sex();

  const auto age = static_cast<uint8_t>(DEFAULT_HUMAN_AGE); // explisit static cast
  h.set_age(age); // otherwise it will be an implicit cast to the type of the function parameter
  h.print_age();

  // read readme.md file content
  std::cout << "readme.md content: ";
  std::ifstream file(README_FILE);
  string line;
  while (getline(file, line)) print(line);
  file.close();

  // * Each memory address holds 1 byte (8 bits) of data. A byte is a group of bits that are operated on as a unit.
  // * Because all data on a computer is just a sequence of bits, we use data type to tell the compiler how to
  // interpret the contents of memory in some meaningful way. The compiler and CPU take care of encoding your value
  // into the appropriate sequence of bits for that data type.
  // * type "int" uses 4 bytes (8*4=32), which is the same as "int32_t".
  // * type "int8_t" uses 1 byte (or 8 bits), it can store 256 unique values in range from -128 to 127 (1 bit for sign).
  // * type "uint8_t" can store 256 unique values in range from 0 to 255.
  int a = -5;
  const int8_t b = 127;
  uint8_t c = 255;
  double d = 5.;
  std::cout << "int: " << sizeof(a) << " bytes" << std::endl;
  std::cout << "int8_t: " << sizeof(b) << " bytes" << std::endl;
  std::cout << "uint8_t: " << sizeof(c) << " bytes" << std::endl;
  std::cout << typeid(c).name() << ": " << sizeof(d) << " bytes" << std::endl;

  // The "char" data type was designed to hold a single character. A character can be a single letter, symbol,
  // or whitespace. The char data type is an integral type, meaning the underlying value is stored as an integer.
  // Similar to how bool value 0 is interpreted as false and non-zero is interpreted as true.
  char ch1 = 'a';
  std::cout << "'" << ch1 << "'" << " (sizeof: " << sizeof(ch1) << " bytes)" << std::endl;

  // - "a_ref" is a reference for "a" (it is like an alias, and not the same as "address of")
  // - We can change the value of "a" through either "a" or reference "a_ref".
  int &a_ref = a;
  a = 1;
  a_ref = 2;
  print(a_ref);

  // we can create const reference to a const value, they can be used to access but not modify the referenced value
  const int &b_ref = b;
  // b_ref = 3 // error
  print(b_ref);

  // const references can also bind to modifiable values, then we can use "aa_ref" to access "a" value, but can not
  // modify it, however we still can modify the value of "a" directly. use it when you need read-only reference
  const int &aa_ref = a;
  print(aa_ref);

  // templates examples
  print(sum<int>(static_cast<int>(d), 10));
  print(mul<5, 5>());

  inc(a); // "a" is passed by reference
  std::cout << "a: " << a << std::endl;

  // Why don't we pass everything by reference?
  // - For objects that are cheap to copy, the cost of copying is similar to the cost of binding, so we favor pass
  // by value, so the code generated will be faster (accessing an object through a reference is slightly slower).
  // - For objects that are expensive to copy, cost of the copy dominates, so we favor pass by reference.
  // - Usually an object is considered "cheap to copy" if it's equal to or smaller than the size of two
  // memory addresses and has no setup costs (like class constructor). But if you're not sure whether an object is
  // cheap or expensive to copy, favor pass by reference (or by const reference if you don't need to modify it).
  // - Usually pass fundamental types by value and other types by reference.
  string food = "pizza";
  print_by_ref(food); // "food" is passed by const reference (no copy, can not be modified)

  // Be careful! the (&) symbol has different meaning depending on context (reference, address-of, bitwise operator).
  // We can use the "address-of" operator (&) to retrieve the address assigned to variable "game". For objects that
  // use more than one byte of memory, it will return the memory address of the first byte used by the object.
  const string game = "Hades 2";
  std::cout << "address: " << &game << std::endl;

  // The "dereference operator" (*) used to access the object at a given memory address
  std::cout << "value: " << *(&game) << std::endl;

  // A "pointer" is an object that holds a memory address as it's value
  int x = 5;
  int *ptr = &x; // pointer types are declared using (*)
  // we can then use the "dereference operator" (*) to acces the value at that address
  std::cout << "x: " << *ptr << std::endl;

  // We can change the value being pointed at (by assigning the "dereferenced" pointer to a new value)
  *ptr = 4;
  std::cout << "x: " << *ptr << std::endl;

  // "pointer to a const value" treats the value being pointed to as constant, regardless of whether the object at
  // that address was initially defined as const or not
  const int *ptr2 = &x;
  // *ptr2 = a; // error: can not change a const value through dereference
  std::cout << "x: " << *ptr2 << std::endl; // but we can use dereference to read the value

  // But the pointer itself is not a constant, so we can assign a new address to it
  const int e = 0;
  ptr2 = &e;
  print(*ptr2);

  // We can also make a pointer itself constant, so we can not change the address that it holding after initialization
  const int *const ptr3 = &e;
  // ptr3 = &e; // error: can not assign a new address to const pointer
  print(*ptr3);

  // The size of a pointer is dependent upon the architecture the executable is compiled for, a 32-bit executable
  // uses 32-bit (4 bytes) memory addresses, with a 64-bit executable a pointer would be 64 bits (8 bytes).
  std::cout << "pointer size is " << sizeof(ptr) << " bytes" << std::endl;

  // A pointer can also hold a "null value" (often shortened to "null", means something has no value)
  int *ptr4; // not holding an address means it is a null pointer ("nullptr"), but we can assing a value to it later

  // - When an object is destroyed, any pointers to the destroyed object will be left "dangling".
  // - Accidentally dereferencing "null" and "dangling" pointers is one of the most common reason that c++ programs
  // crash in practice.
  // - It is your responsibility to detect these cases and ensure those pointers are subsequently set to "nullptr".
  // print(*ptr4); // error: segmentation fault (because we are trying to dereference a null pointer)

  // A pointer should either hold the address of a valid object, or be set to "nullptr". That way we only need to
  // test pointers for null, and can assume any non-null pointer is valid.
  ptr = nullptr; // we can assign a "nullptr" literal to make the pointer a null pointer.

  // - Conditions can only be used to differentiate null pointers from non-null pointers. There is no convenient way
  // to determine whether a non-null pointer is pointing to a valid object or dangling (invalid object).
  // - Favor references over pointers unless additional capabilities provided by pointers are needed.
  if (ptr != nullptr) // ("ptr" also could be implicitly converted to Boolean, but not recommended)
    print("ptr is non-null");
  else
    print("ptr is null");

  // Just like pass by reference, pass by address is fast, and avoids making a copy of the argument object.
  // Prefer pass by reference to pass by address unless you have a specific reason to pass by address.
  print_by_ptr(&food); // the address is copied to function parameter
  std::cout << "food: " << food << std::endl;

  print("\n-- end --");
  return EXIT_SUCCESS;
}
