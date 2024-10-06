#pragma once
// templates that are needed in multiple files should be defined in a header file, and then #included wherever needed.
// use function templates to write generic code that can work with wide variety of types.

// function template is used to generate (at compile-time) one or more
// overloaded functions, each with a different set of actual types.
// template types are sometimes called generic types
template <typename T>
constexpr T sum(T a, T b)
{
  return a + b;
}

// non-type template parameter. they are primarily used when we need to pass constexpr values to function or class.
template <int a, int b>
int mul()
{
  return a * b;
}