#pragma once

#include <QMainWindow>
#include "../Logic/HospitalSystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRegisterPatient_clicked();
    void on_btnBookAppointment_clicked();
    void updateDashboardStats();
    void on_btnViewPatients_clicked();
    void on_comboDepartment_currentTextChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    HospitalSystem backend;
};
