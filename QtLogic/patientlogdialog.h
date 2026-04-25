#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include "../Logic/HospitalSystem.h"

namespace Ui {
class PatientLogDialog;
}

class PatientLogDialog : public QDialog {
    Q_OBJECT

public:
    explicit PatientLogDialog(HospitalSystem& sys, QWidget *parent = nullptr);
    ~PatientLogDialog();

private slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    Ui::PatientLogDialog *ui;
    HospitalSystem& backend;
    QStandardItemModel* patientModel;
};
