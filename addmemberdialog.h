#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui
{
class AddMemberDialog;
}

class AddMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberDialog(QWidget *parent = nullptr);
    ~AddMemberDialog();

    QString getMemberName();
    int     getMemberAge();
    QString getMemberPhone();
    QString getMembershipType();
    QString getJoinDate();
    QString getExpiryDate();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddMemberDialog *ui;
};

#endif // ADDMEMBERDIALOG_H