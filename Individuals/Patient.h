#pragma once

#include "Person.h"
#include <QDate>
#include <string>

using namespace std;

class Patient : public Person {
private:
    // QDate makes it incredibly easy to hook up to Qt's calendar UI widgets later.
    QDate birthDate;
    
    char gender;
    string nationalID;
    
    string mobileNumber;

public:
    // Constructor
    Patient(string name, QDate bdate, char gender, string mob, string natID);

    // Getters
    QDate getBirthdate() const;
    char getGender() const;
    string getMobileNumber() const;
    string getNationalID() const;

    // Setter
    void setMobileNumber(string num);

    // Overloaded equality operator to check for duplicates
    bool operator==(const Patient& other) const;
};