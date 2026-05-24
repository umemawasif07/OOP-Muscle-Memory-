#include "addmemberdialog.h"
#include "ui_addmemberdialog.h"
#include <QMessageBox>
#include <QDate>  // automatic date ke liye

AddMemberDialog::AddMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add New Member");
}

AddMemberDialog::~AddMemberDialog()
{
    delete ui;
}

QString AddMemberDialog::getMemberName() {
    return ui->lineEditName->text();
}

int AddMemberDialog::getMemberAge() {
    return ui->spinBoxAge->value();
}

QString AddMemberDialog::getMemberPhone() {
    return ui->lineEditPhone->text();
}

QString AddMemberDialog::getMembershipType() {
    return ui->comboBoxMembership->currentText();
}

// Aaj ki date automatically
QString AddMemberDialog::getJoinDate() {
    return QDate::currentDate().toString("dd-MM-yyyy");
}

// Membership type ke hisaab se expiry automatic
QString AddMemberDialog::getExpiryDate() {
    QDate joinDate = QDate::currentDate();
    QString type = ui->comboBoxMembership->currentText();

    if (type == "Monthly") {
        return joinDate.addMonths(1).toString("dd-MM-yyyy");
    } else {
        return joinDate.addYears(1).toString("dd-MM-yyyy");
    }
}

void AddMemberDialog::on_btnSave_clicked()
{
    QString name  = ui->lineEditName->text().trimmed();
    QString phone = ui->lineEditPhone->text().trimmed();
    int age       = ui->spinBoxAge->value();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter member name!");
        ui->lineEditName->setFocus();
        return;
    }

    for (QChar c : name) {
        if (!c.isLetter() && !c.isSpace()) {
            QMessageBox::warning(this, "Error", "Name can only contain letters!");
            ui->lineEditName->setFocus();
            return;
        }
    }

    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter phone number!");
        ui->lineEditPhone->setFocus();
        return;
    }

    for (QChar c : phone) {
        if (!c.isDigit()) {
            QMessageBox::warning(this, "Error", "Phone can only contain numbers!");
            ui->lineEditPhone->setFocus();
            return;
        }
    }

    if (phone.length() != 11) {
        QMessageBox::warning(this, "Error", "Phone number must be 11 digits!");
        ui->lineEditPhone->setFocus();
        return;
    }

    if (age < 16 || age > 80) {
        QMessageBox::warning(this, "Error", "Age must be between 16 and 80!");
        ui->spinBoxAge->setFocus();
        return;
    }

    accept();
}

void AddMemberDialog::on_btnCancel_clicked()
{
    reject();
}