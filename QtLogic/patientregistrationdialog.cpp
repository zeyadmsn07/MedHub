#include "PatientRegistrationDialog.h"
#include "ui_patientregistrationdialog.h"
#include <QMessageBox>

using namespace std;

PatientRegistrationDialog::PatientRegistrationDialog(HospitalSystem& sys, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientRegistrationDialog),
    backend(sys)
{
    ui->setupUi(this);

    ui->comboGender->addItems({"Male", "Female"});
}

PatientRegistrationDialog::~PatientRegistrationDialog() {
    delete ui;
}

void PatientRegistrationDialog::accept() {
    string name = ui->txtName->text().toStdString();
    QDate dob = ui->dateBirth->date();
    char gender = ui->comboGender->currentText() == "Male" ? 'M' : 'F';
    string mobile = ui->txtMobile->text().toStdString();
    string natID = ui->txtNationalID->text().toStdString();

    if (name.empty() || mobile.empty() || natID.empty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return;
    }

    Patient newPatient(name, dob, gender, mobile, natID);

    if (backend.registerPatient(newPatient)) {
        QMessageBox::information(this, "Success", "Patient registered successfully!");
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "Error", "A patient with this National ID already exists.");
    }
}
