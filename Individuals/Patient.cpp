#include "Patient.h"

Patient::Patient(string name, QDate bdate, char gender, string mob, string natID)
    : Person(name), birthDate(bdate), gender(gender), mobileNumber(mob), nationalID(natID) {}

QDate Patient::getBirthdate() const { return birthDate; }
char Patient::getGender() const { return gender; }
string Patient::getMobileNumber() const { return mobileNumber; }
string Patient::getNationalID() const { return nationalID; }

void Patient::setMobileNumber(string num)
{
    mobileNumber = num;
}

bool Patient::operator==(const Patient &other) const
{
    return this->nationalID == other.nationalID;
}
