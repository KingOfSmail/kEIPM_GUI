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

    bool getFlag() const;
    void setFlag(bool value);
    void set_textContent(const char* str_reason);

    bool close_flag;
private slots:

    void on_Btn_Finish_clicked();

private:
    Ui::Finish_Close *ui;
    bool flag;
};

#endif // FINISH_CLOSE_H
