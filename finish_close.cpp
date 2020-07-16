#include "finish_close.h"
#include "ui_finish_close.h"

Finish_Close::Finish_Close(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finish_Close)
{
    ui->setupUi(this);
    ui->text_remind->setReadOnly(true);
}

Finish_Close::~Finish_Close()
{
    delete ui;
}

void Finish_Close::set_textContent(const QString& str_reason){
    ui->text_remind->insertPlainText(str_reason);
}

void Finish_Close::on_Btn_Finish_clicked()
{

    this->accept();
}


void Finish_Close::on_pushButton_clicked()
{
    this->reject();
}
