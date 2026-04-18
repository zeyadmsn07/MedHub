#pragma once
#include <string>

class Person
{
protected:
    const std::string name;

public:
    Person(const std::string& n);

    virtual ~Person();

    std::string getName() const;
};
