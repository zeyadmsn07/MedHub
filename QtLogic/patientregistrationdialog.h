#pragma once

#include <QDialog>
#include "../Logic/HospitalSystem.h"
namespace Ui {
class PatientRegistrationDialog;
}

class PatientRegistrationDialog : public QDialog {
    Q_OBJECT

public:
    explicit PatientRegistrationDialog(HospitalSystem& sys, QWidget *parent = nullptr);
    ~PatientRegistrationDialog();

private slots:
    void accept() override;

private:
    Ui::PatientRegistrationDialog *ui;
    HospitalSystem& backend;
};
