#include "finish_close.h"
#include "ui_finish_close.h"

Finish_Close::Finish_Close(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finish_Close)
{
    ui->setupUi(this);
}

Finish_Close::~Finish_Close()
{
    delete ui;
}

bool Finish_Close::getFlag() const
{
    return flag;
}

void Finish_Close::setFlag(bool value)
{
    flag = value;
}

void Finish_Close::set_textContent(const QString& str_reason){
    if(this->flag){
        ui->text_remind->insertPlainText(str_reason);
        ui->Btn_Finish->setText("完成");
    }else{
        ui->text_remind->insertPlainText(str_reason);
        ui->Btn_Finish->setText("退出");
    }
}

void Finish_Close::on_Btn_Finish_clicked()
{

    this->close();
}

