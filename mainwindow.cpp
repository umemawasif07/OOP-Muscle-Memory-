#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmemberdialog.h"
#include "viewmemberdialog.h"
#include "recordpaymentdialog.h"
#include "viewpaymentsdialog.h"
#include "addtrainerdialog.h"
#include "viewtrainerdialog.h"
#include <QMessageBox>
#include <fstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gym Management System");
    loadMembers();
    loadPayments();
    loadTrainers();
}

MainWindow::~MainWindow()
{
    saveMembers();
    savePayments();
    saveTrainers();
    delete ui;
}

// ── Add Member ────────────────────────────────────────────────────────────────

void MainWindow::on_btnAddMember_clicked()
{
    AddMemberDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        std::string name     = dialog.getMemberName().toStdString();
        int         age      = dialog.getMemberAge();
        std::string phone    = dialog.getMemberPhone().toStdString();
        std::string type     = dialog.getMembershipType().toStdString();
        std::string joinDate = dialog.getJoinDate().toStdString();
        std::string expDate  = dialog.getExpiryDate().toStdString();

        int id = 1001 + members.size();
        Member m(id, name, age, phone, type, joinDate, expDate);
        members.push_back(m);
        saveMembers();

        QMessageBox::information(this, "Success",
                                 "Member added!\nMember ID: " + QString::number(id));
    }
}

// ── View Members ──────────────────────────────────────────────────────────────

void MainWindow::on_btnViewMembers_clicked()
{
    ViewMemberDialog dialog(this);

    connect(&dialog, &ViewMemberDialog::deleteMemberRequested,
            this,    &MainWindow::deleteMemberById);

    std::vector<MemberData> data;
    for (size_t i = 0; i < members.size(); i++) {
        MemberData md;
        md.id             = members[i].getID();
        md.name           = members[i].getName();
        md.age            = members[i].getAge();
        md.phone          = members[i].getPhone();
        md.membershipType = members[i].getMembershipType();
        md.joinDate       = members[i].getJoinDate();
        md.expiryDate     = members[i].getExpiryDate();
        data.push_back(md);
    }
    dialog.loadMembers(data);
    dialog.exec();
}

void MainWindow::deleteMemberById(int id)
{
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].getID() == id) {
            members.erase(members.begin() + i);
            saveMembers();
            return;
        }
    }
}

// ── Record Payment ────────────────────────────────────────────────────────────

void MainWindow::on_btnRecordPayment_clicked()
{
    if (members.empty()) {
        QMessageBox::warning(this, "Error", "No members found! Add a member first.");
        return;
    }

    RecordPaymentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        int    memberID = dialog.getMemberID();
        double amount   = dialog.getAmount();

        bool found = false;
        for (size_t i = 0; i < members.size(); i++) {
            if (members[i].getID() == memberID) { found = true; break; }
        }

        if (!found) {
            QMessageBox::warning(this, "Error",
                                 "Member ID " + QString::number(memberID) + " not found!");
            return;
        }

        int pid = 5001 + payments.size();
        Payment p(pid, memberID, amount);
        payments.push_back(p);
        savePayments();

        QMessageBox::information(this, "Success",
                                 "Payment recorded!\nPayment ID: " + QString::number(pid) +
                                     "\nAmount: Rs " + QString::number(amount));
    }
}

// ── View Payments ─────────────────────────────────────────────────────────────

void MainWindow::on_btnViewPayments_clicked()
{
    ViewPaymentsDialog dialog(this);
    std::vector<PaymentData> data;
    for (size_t i = 0; i < payments.size(); i++) {
        PaymentData pd;
        pd.paymentID = payments[i].getPaymentID();
        pd.memberID  = payments[i].getMemberID();
        pd.amount    = payments[i].getAmount();
        data.push_back(pd);
    }
    dialog.loadPayments(data);
    dialog.exec();
}

// ── Add Trainer ───────────────────────────────────────────────────────────────

void MainWindow::on_btnAddTrainer_clicked()
{
    AddTrainerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        std::string name  = dialog.getTrainerName().toStdString();
        int         age   = dialog.getTrainerAge();
        std::string phone = dialog.getTrainerPhone().toStdString();
        std::string spec  = dialog.getSpecialization().toStdString();

        int id = 2001 + trainers.size();
        Trainer t(id, name, age, phone, spec);
        trainers.push_back(t);
        saveTrainers();

        QMessageBox::information(this, "Success",
                                 "Trainer added!\nTrainer ID: " + QString::number(id));
    }
}

// ── View Trainers ─────────────────────────────────────────────────────────────

void MainWindow::on_btnViewTrainers_clicked()
{
    ViewTrainerDialog dialog(this);

    connect(&dialog, &ViewTrainerDialog::deleteTrainerRequested,
            this,    &MainWindow::deleteTrainerById);

    std::vector<TrainerData> data;
    for (size_t i = 0; i < trainers.size(); i++) {
        TrainerData td;
        td.id             = trainers[i].getID();
        td.name           = trainers[i].getName();
        td.age            = trainers[i].getAge();
        td.phone          = trainers[i].getPhone();
        td.specialization = trainers[i].getSpecialization();
        data.push_back(td);
    }
    dialog.loadTrainers(data);
    dialog.exec();
}

void MainWindow::deleteTrainerById(int id)
{
    for (size_t i = 0; i < trainers.size(); i++) {
        if (trainers[i].getID() == id) {
            trainers.erase(trainers.begin() + i);
            saveTrainers();
            return;
        }
    }
}

// ── Exit ──────────────────────────────────────────────────────────────────────

void MainWindow::on_btnExit_clicked()
{
    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) close();
}

// ── File I/O ──────────────────────────────────────────────────────────────────

void MainWindow::saveMembers()
{
    std::ofstream file("members.txt");
    for (size_t i = 0; i < members.size(); i++) {
        file << members[i].getID()             << "\n"
             << members[i].getName()           << "\n"
             << members[i].getAge()            << "\n"
             << members[i].getPhone()          << "\n"
             << members[i].getMembershipType() << "\n"
             << members[i].getJoinDate()       << "\n"
             << members[i].getExpiryDate()     << "\n";
    }
    file.close();
}

void MainWindow::loadMembers()
{
    std::ifstream file("members.txt");
    if (!file) return;

    int id, age;
    std::string name, phone, type, joinDate, expiryDate;

    while (file >> id) {
        file.ignore();
        std::getline(file, name);
        file >> age;
        file.ignore();
        std::getline(file, phone);
        std::getline(file, type);
        std::getline(file, joinDate);
        std::getline(file, expiryDate);
        Member m(id, name, age, phone, type, joinDate, expiryDate);
        members.push_back(m);
    }
    file.close();
}

void MainWindow::savePayments()
{
    std::ofstream file("payments.txt");
    for (size_t i = 0; i < payments.size(); i++) {
        file << payments[i].getPaymentID() << "\n"
             << payments[i].getMemberID()  << "\n"
             << payments[i].getAmount()    << "\n";
    }
    file.close();
}

void MainWindow::loadPayments()
{
    std::ifstream file("payments.txt");
    if (!file) return;
    int pid, mid; double amt;
    while (file >> pid >> mid >> amt) {
        payments.push_back(Payment(pid, mid, amt));
    }
    file.close();
}

void MainWindow::saveTrainers()
{
    std::ofstream file("trainers.txt");
    for (size_t i = 0; i < trainers.size(); i++) {
        file << trainers[i].getID()             << "\n"
             << trainers[i].getName()           << "\n"
             << trainers[i].getAge()            << "\n"
             << trainers[i].getPhone()          << "\n"
             << trainers[i].getSpecialization() << "\n";
    }
    file.close();
}

void MainWindow::loadTrainers()
{
    std::ifstream file("trainers.txt");
    if (!file) return;
    int id, age; std::string name, phone, spec;
    while (file >> id) {
        file.ignore();
        std::getline(file, name);
        file >> age; file.ignore();
        std::getline(file, phone);
        std::getline(file, spec);
        trainers.push_back(Trainer(id, name, age, phone, spec));
    }
    file.close();
}