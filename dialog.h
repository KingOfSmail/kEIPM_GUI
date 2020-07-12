#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDirModel>
#include <QModelIndex>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QString getChoose_path() const;
private slots:



    void on_Btn_Cancel_Sub_clicked();

    void on_File_treeView_doubleClicked(const QModelIndex &index);


    void on_Btn_submit_clicked();

private:
    Ui::Dialog *ui;
    QDirModel *model;
    QString choose_path;
};

#endif // DIALOG_H
