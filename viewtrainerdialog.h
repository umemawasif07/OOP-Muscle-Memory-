#ifndef VIEWTRAINERDIALOG_H
#define VIEWTRAINERDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui { class ViewTrainerDialog; }

struct TrainerData {
    int id;
    std::string name;
    int age;
    std::string phone;
    std::string specialization;
};

class ViewTrainerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ViewTrainerDialog(QWidget *parent = nullptr);
    ~ViewTrainerDialog();
    void loadTrainers(std::vector<TrainerData> trainers);

signals:
    void deleteTrainerRequested(int id);

private slots:
    void on_btnSave_clicked();
    void on_btnClose_clicked();
    void on_btnDelete_clicked();

private:
    Ui::ViewTrainerDialog *ui;
    std::vector<TrainerData> m_trainers;
};

#endif // VIEWTRAINERDIALOG_H