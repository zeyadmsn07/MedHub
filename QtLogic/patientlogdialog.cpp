#include "patientlogdialog.h"
#include "ui_patientlogdialog.h"
#include <QHeaderView>

PatientLogDialog::PatientLogDialog(HospitalSystem& sys, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientLogDialog),
    backend(sys)
{
    ui->setupUi(this);
    patientModel = new QStandardItemModel(this);
    patientModel->setHorizontalHeaderLabels({"National ID", "Name", "Birthdate", "Gender", "Mobile Number"});

    ui->patientTableView->setModel(patientModel);
    ui->patientTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto& patients = backend.getPatients();
    for (int i = 0; i < patients.size(); ++i) {
        QStandardItem* itemID = new QStandardItem(QString::fromStdString(patients[i].getNationalID()));
        itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);
        
        QStandardItem* itemName = new QStandardItem(QString::fromStdString(patients[i].getName()));
        itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
        
        QStandardItem* itemDate = new QStandardItem(patients[i].getBirthdate().toString("yyyy-MM-dd"));
        itemDate->setFlags(itemDate->flags() & ~Qt::ItemIsEditable);
        
        QStandardItem* itemGender = new QStandardItem(QString(patients[i].getGender()));
        itemGender->setFlags(itemGender->flags() & ~Qt::ItemIsEditable);
        
        QStandardItem* itemMobile = new QStandardItem(QString::fromStdString(patients[i].getMobileNumber()));
        
        patientModel->setItem(i, 0, itemID);
        patientModel->setItem(i, 1, itemName);
        patientModel->setItem(i, 2, itemDate);
        patientModel->setItem(i, 3, itemGender);
        patientModel->setItem(i, 4, itemMobile);
    }
    connect(patientModel, &QStandardItemModel::dataChanged, this, &PatientLogDialog::onDataChanged);
}

PatientLogDialog::~PatientLogDialog() {
    delete ui;
}

void PatientLogDialog::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    if (topLeft.column() == 4) {
        QString newMobile = patientModel->data(topLeft).toString();
        QString natID = patientModel->data(patientModel->index(topLeft.row(), 0)).toString();

        auto& patients = backend.getPatients();
        for (int i = 0; i < patients.size(); ++i) {
            if (patients[i].getNationalID() == natID.toStdString()) {
                patients[i].setMobileNumber(newMobile.toStdString());
                backend.saveData();
                break;
            }
        }
    }
}
