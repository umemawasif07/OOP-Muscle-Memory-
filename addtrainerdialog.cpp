#include "addtrainerdialog.h"
#include "ui_addtrainerdialog.h"
#include <QMessageBox>

AddTrainerDialog::AddTrainerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainerDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add New Trainer");
}

AddTrainerDialog::~AddTrainerDialog()
{
    delete ui;
}

QString AddTrainerDialog::getTrainerName() {
    return ui->lineEditName->text();
}

int AddTrainerDialog::getTrainerAge() {
    return ui->spinBoxAge->value();
}

QString AddTrainerDialog::getTrainerPhone() {
    return ui->lineEditPhone->text();
}

QString AddTrainerDialog::getSpecialization() {
    return ui->lineEditSpec->text();
}

void AddTrainerDialog::on_btnSave_clicked()
{
    QString name  = ui->lineEditName->text().trimmed();
    QString phone = ui->lineEditPhone->text().trimmed();
    QString spec  = ui->lineEditSpec->text().trimmed();

    // Name check
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter trainer name!");
        ui->lineEditName->setFocus();
        return;
    }

    // Name sirf letters
    for (QChar c : name) {
        if (!c.isLetter() && !c.isSpace()) {
            QMessageBox::warning(this, "Error", "Name can only contain letters!");
            ui->lineEditName->setFocus();
            return;
        }
    }

    // Phone check
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter phone number!");
        ui->lineEditPhone->setFocus();
        return;
    }

    // Phone sirf numbers
    for (QChar c : phone) {
        if (!c.isDigit()) {
            QMessageBox::warning(this, "Error", "Phone can only contain numbers!");
            ui->lineEditPhone->setFocus();
            return;
        }
    }

    // Phone 11 digits
    if (phone.length() != 11) {
        QMessageBox::warning(this, "Error", "Phone number must be 11 digits!");
        ui->lineEditPhone->setFocus();
        return;
    }

    // Specialization check
    if (spec.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter specialization!");
        ui->lineEditSpec->setFocus();
        return;
    }

    accept();
}

void AddTrainerDialog::on_btnCancel_clicked()
{
    reject();
}