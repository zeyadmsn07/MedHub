#pragma once

#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "DataManager.h"
#include <vector>

class HospitalSystem
{
private:

    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
    DataManager DM;

public:

    int getDoctorCount() const;
    int getPatientCount() const;
    int getAppointmentCount() const;

    bool registerPatient(const Patient& p);
    bool bookAppointment(const Appointment& appt);
    bool cancelAppointment(const string& patID, QDate d, QTime t);
    bool checkDailyLimit(const string& patID, QDate d) const;
    bool hasConflict(const string& docID, const string& patID, QDate d, QTime t) const;
    bool isWithinBusinessHours(const QDate& d, const QTime& t) const;
    bool isWithinBookableRange(const QDate& d) const;

    vector<QTime> generate20MinSlots (const string& docID, const QDate& d);
    Patient* findPatientByName(const string& n);
    Doctor* findDoctorByID(const string& id);
    vector<Doctor> getDoctorsByDepartment(const string& dept) const;
    vector<Doctor>& getDoctors() { return doctors; }
    vector<Appointment>& getAppointments() { return appointments; }
    void saveData();
    void loadDocs();


};
