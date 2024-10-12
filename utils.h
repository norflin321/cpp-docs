#pragma once

#include <iostream>

// A program-defined type is a custom type that we can create for use in our own programs.
// The enumerated types and class types (including structs, classes and unions) allow for
// creation of program-defined types.
template <typename T, typename U=float>
struct Item
{
	std::string name = "item";
	T price;
	U discount;
};
// The compiler can deduce the template types from the types of the object’s initializer,
// (this is called class template argument deduction or CTAD for short).
// We can provide the compiler with a deduction guide, which tells the compiler how to deduce
// the template arguments for a given class template.
template <typename T, typename U>
Item(T, U) -> Item<T, U>;

namespace utils
{

void print(std::string_view value);
void print(int value);
void print(double value);
void print(const Item<int, float> &item);

void print_by_ref(const std::string &value);
void print_by_ptr(std::string *value);
void inc(int &value);

}