#pragma once
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include <vector>

class DataManager
{
private:
    Qt::DayOfWeek parseDayOfWeek(QString dayText);

public:
    void loadStaticData(std::vector<Doctor>&);

    void saveLocalData(const std::vector<Patient>& patients, const std::vector<Appointment>& appointments);
    void loadLocalData(std::vector<Patient>& patients, std::vector<Appointment>& appointments, std::vector<Doctor>& doctors);
};
