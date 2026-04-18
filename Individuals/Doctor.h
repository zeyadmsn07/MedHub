#pragma once
#include "Person.h"
#include "AvailabilitySlot.h"
#include <string>
#include <vector>

class Doctor: public Person
{
private:
    const std::string doctorId;
    const std::string department;
    std::vector<AvailabilitySlot> availability;

public:
    Doctor(const std::string& docId,const std::string& dept, const std::string& docName);

    const std::string& getId() const;

    const std::string& getDept() const;

    const std::vector<AvailabilitySlot>& getAvailable() const;

    void addAvailabilitySlot(const AvailabilitySlot& slot);

    bool operator==(const Doctor& doc2) const;
};
