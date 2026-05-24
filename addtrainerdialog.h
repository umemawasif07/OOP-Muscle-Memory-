#ifndef ADDTRAINERDIALOG_H
#define ADDTRAINERDIALOG_H

#include <QDialog>

namespace Ui
{
class AddTrainerDialog;
}

class AddTrainerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainerDialog(QWidget *parent = nullptr);
    ~AddTrainerDialog();

    QString getTrainerName();
    int     getTrainerAge();
    QString getTrainerPhone();
    QString getSpecialization();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddTrainerDialog *ui;
};

#endif // ADDTRAINERDIALOG_H