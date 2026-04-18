#include "Doctor.h"

Doctor::Doctor(
    const std::string& docId,
    const std::string& dept,
    const std::string& docName)
        : Person(docName), doctorId(docId), department(dept) {}

const std::string& Doctor::getId() const
{
    return doctorId;
}

const std::string& Doctor::getDept() const
{
    return department;
}

const std::vector<AvailabilitySlot>& Doctor::getAvailable() const
{
    return availability;
}

void Doctor::addAvailabilitySlot(const AvailabilitySlot& slot)
{
    availability.push_back(slot);
}

bool Doctor::operator==(const Doctor& doc2) const
{
    return doctorId == doc2.doctorId;
}
