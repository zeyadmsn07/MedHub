#pragma once

#include "Person.h"
#include <QDate>
#include <string>

using namespace std;

class Patient : public Person {
private:

    QDate birthDate;
    
    char gender;

    string nationalID;
    
    string mobileNumber;

public:

    Patient(string name, QDate bdate, char gender, string mob, string natID);

    QDate getBirthdate() const;

    char getGender() const;

    string getMobileNumber() const;

    string getNationalID() const;

    void setMobileNumber(string num);

    bool operator==(const Patient& other) const;
};
