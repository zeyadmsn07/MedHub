#pragma once

#include "Patient.h"
#include "Doctor.h"
#include <QDate>
#include <QTime>

using namespace std;
enum AppointmentStatus
{
    CONFIRMED,
    CANCELLED,
    COMPLETED
};

class Appointment {
private:
    Patient* patient;
    Doctor* doctor;
    
    QDate date;
    
    QTime startTime;
    
    int duration;
    AppointmentStatus status;

public:
    Appointment(Patient* pat, Doctor* doc, QDate d, QTime start, int dur = 20);

    Patient* getPatient() const;
    Doctor* getDoctor() const;
    QDate getDate() const;
    QTime getStartTime() const;
    QTime getEndTime() const; 
    int getDuration() const;
    AppointmentStatus getStatus() const;

    void setStatus(AppointmentStatus s);

    bool operator==(const Appointment& other) const;
};
