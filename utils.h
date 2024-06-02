#pragma once

#include <iostream>

void print(std::string_view value);
void print(int value);
void print_by_ref(const std::string &value);
void print_by_ptr(std::string *value);
void inc(int &value);
