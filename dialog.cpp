#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    model = new QDirModel();
    ui->File_treeView->setModel(model);
    ui->File_treeView->setRootIndex(model->index("/"));
    ui->File_treeView->setColumnWidth(0,180);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_Btn_Cancel_Sub_clicked()
{
    this->reject();
}


void Dialog::on_File_treeView_doubleClicked(const QModelIndex &index)
{
    choose_path = model->filePath(index);
}

QString Dialog::getChoose_path() const
{
    return choose_path;
}

void Dialog::on_Btn_submit_clicked()
{
    choose_path = model->filePath(ui->File_treeView->currentIndex());
    this->accept();
}
