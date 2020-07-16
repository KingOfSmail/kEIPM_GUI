#ifndef FINISH_CLOSE_H
#define FINISH_CLOSE_H

#include <QDialog>

namespace Ui {
class Finish_Close;
}

class Finish_Close : public QDialog
{
    Q_OBJECT

public:
    explicit Finish_Close(QWidget *parent = nullptr);
    ~Finish_Close();

    void set_textContent(const QString &str_reason);

private slots:

    void on_Btn_Finish_clicked();

    void on_pushButton_clicked();

private:
    Ui::Finish_Close *ui;
    bool flag;
};

#endif // FINISH_CLOSE_H
