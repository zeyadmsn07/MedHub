#include "AppointmentBookingDialog.h"
#include "ui_appointmentbookingdialog.h"
#include <QMessageBox>

using namespace std;

AppointmentBookingDialog::AppointmentBookingDialog(HospitalSystem& sys, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppointmentBookingDialog),
    backend(sys)
{
    ui->setupUi(this);
    this->setWindowTitle("Book Appointment");
    ui->dateAppt->setDate(QDate::currentDate());
}

AppointmentBookingDialog::~AppointmentBookingDialog() {
    delete ui;
}

void AppointmentBookingDialog::prefill(const QString& docID, const QDate& date, const QTime& time) {
    ui->txtDoctorID->setText(docID);
    ui->dateAppt->setDate(date);
    ui->timeAppt->setTime(time);
}

void AppointmentBookingDialog::accept() {
    string pName = ui->txtPatientName->text().toStdString();
    string dID = ui->txtDoctorID->text().toStdString();
    QDate date = ui->dateAppt->date();
    QTime time = ui->timeAppt->time();

    Patient* pat = backend.findPatientByName(pName);
    Doctor* doc = backend.findDoctorByID(dID);

    if (!pat) {
        QMessageBox::warning(this, "Error", "Patient not found. Please register them first.");
        return;
    }
    if (!doc) {
        QMessageBox::warning(this, "Error", "Doctor ID not found.");
        return;
    }

    Appointment appt(pat, doc, date, time);

    if (backend.bookAppointment(appt)) {
        QMessageBox::information(this, "Success", "Appointment successfully booked!");
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "Error", "Booking failed! Check daily limits, schedule conflicts, or business hours.");
    }
}

