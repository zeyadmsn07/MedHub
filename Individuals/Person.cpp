#include "Person.h"
#include <string>

Person::Person(const std::string& n): name(n) {}

std::string Person::getName() const
{
    return name;
}

Person::~Person() = default;
