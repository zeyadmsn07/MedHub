#include "Appointment.h"

Appointment::Appointment(Patient* pat, Doctor* doc, QDate d, QTime start, int dur)
    : patient(pat), doctor(doc), date(d), startTime(start), duration(dur), status(CONFIRMED) {}

Patient* Appointment::getPatient() const { return patient; }
Doctor* Appointment::getDoctor() const { return doctor; }
QDate Appointment::getDate() const { return date; }
QTime Appointment::getStartTime() const { return startTime; }
int Appointment::getDuration() const { return duration; }
AppointmentStatus Appointment::getStatus() const { return status; }

QTime Appointment::getEndTime() const {
    return startTime.addSecs(duration * 60); 
}

void Appointment::setStatus(AppointmentStatus s) {
    status = s;
}

bool Appointment::operator==(const Appointment& other) const
{
    return (this->doctor == other.doctor && 
            this->date == other.date && 
            this->startTime == other.startTime);
}
