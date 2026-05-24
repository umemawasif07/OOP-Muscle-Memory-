#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "addmemberdialog.h"
#include "viewmemberdialog.h"
#include "recordpaymentdialog.h"
#include "viewpaymentsdialog.h"
#include "addtrainerdialog.h"
#include "viewtrainerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class Person
{
protected:
    std::string name;
    int age;
    std::string phone;
public:
    Person() { name = ""; age = 0; phone = ""; }
    Person(std::string n, int a, std::string p) { name=n; age=a; phone=p; }
    virtual ~Person() {}
    std::string getName()  { return name;  }
    int         getAge()   { return age;   }
    std::string getPhone() { return phone; }
    virtual void display() {}
};

class Member : public Person {
private:
    int memberID;
    std::string membershipType;
    std::string joinDate;
    std::string expiryDate;
public:
    Member() : Person() { memberID=0; membershipType=""; joinDate=""; expiryDate=""; }
    Member(int id, std::string n, int a, std::string p,
           std::string type, std::string jDate, std::string eDate)
        : Person(n,a,p) {
        memberID=id; membershipType=type; joinDate=jDate; expiryDate=eDate;
    }
    ~Member() {}
    int         getID()             { return memberID;       }
    std::string getMembershipType() { return membershipType; }
    std::string getJoinDate()       { return joinDate;       }
    std::string getExpiryDate()     { return expiryDate;     }
};

class Trainer : public Person {
private:
    int trainerID;
    std::string specialization;
public:
    Trainer() : Person() { trainerID=0; specialization=""; }
    Trainer(int id, std::string n, int a, std::string p, std::string spec)
        : Person(n,a,p) { trainerID=id; specialization=spec; }
    ~Trainer() {}
    int         getID()             { return trainerID;      }
    std::string getSpecialization() { return specialization; }
};

class Payment {
private:
    int paymentID, memberID;
    double amount;
public:
    Payment() { paymentID=0; memberID=0; amount=0.0; }
    Payment(int pid, int mid, double amt) { paymentID=pid; memberID=mid; amount=amt; }
    ~Payment() {}
    int    getPaymentID() { return paymentID; }
    int    getMemberID()  { return memberID;  }
    double getAmount()    { return amount;    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddMember_clicked();
    void on_btnViewMembers_clicked();
    void on_btnRecordPayment_clicked();
    void on_btnViewPayments_clicked();
    void on_btnAddTrainer_clicked();
    void on_btnViewTrainers_clicked();
    void on_btnExit_clicked();
    void deleteMemberById(int id);
    void deleteTrainerById(int id);

private:
    Ui::MainWindow *ui;
    std::vector<Member>  members;
    std::vector<Trainer> trainers;
    std::vector<Payment> payments;

    void saveMembers();
    void loadMembers();
    void savePayments();
    void loadPayments();
    void saveTrainers();
    void loadTrainers();
};

#endif // MAINWINDOW_H