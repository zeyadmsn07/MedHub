#include "MainWindow.h"
#include "PatientRegistrationDialog.h"
#include "AppointmentBookingDialog.h"
#include "patientlogdialog.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QTableView>
#include <set>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    backend.loadDocs();
    std::set<std::string> departments;
    for (const auto& doc : backend.getDoctors()) {
        departments.insert(doc.getDept());
    }

    ui->comboDepartment->addItem("All Departments");
    for (const auto& dept : departments) {
        ui->comboDepartment->addItem(QString::fromStdString(dept));
    }

    ui->timeTable->populateDoctorList(backend);

    updateDashboardStats();
    connect(ui->timeTable, &TimeTableWidget::appointmentChanged, this, &MainWindow::updateDashboardStats);
}

MainWindow::~MainWindow() {
    backend.saveData();
    delete ui;
}

void MainWindow::updateDashboardStats() {
    QString statsText = QString("Docs: %1 | Patients: %2 | Appts: %3")
    .arg(backend.getDoctorCount())
        .arg(backend.getPatientCount())
        .arg(backend.getAppointmentCount());

    ui->lblStats->setText(statsText);
}

void MainWindow::on_btnRegisterPatient_clicked() {
    PatientRegistrationDialog dialog(backend, this);
    dialog.exec();
    updateDashboardStats();
}

void MainWindow::on_btnBookAppointment_clicked() {
    AppointmentBookingDialog dialog(backend, this);

    if (dialog.exec() == QDialog::Accepted) {
        QModelIndex index = ui->timeTable->findChild<QTableView*>("doctorView")->currentIndex();
        if (index.isValid()) {
            ui->timeTable->on_doctorView_clicked(index);
        }
        updateDashboardStats();
    }
}

void MainWindow::on_comboDepartment_currentTextChanged(const QString &text) {
    if (text == "All Departments") {
        ui->timeTable->populateDoctorList(backend, "");
    } else {
        ui->timeTable->populateDoctorList(backend, text);
    }
}

void MainWindow::on_btnViewPatients_clicked() {
    PatientLogDialog dialog(backend, this);
    dialog.exec();
}
