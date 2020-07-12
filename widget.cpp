#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Line_output_RootCA->setReadOnly(true);
    ui->lineEd_OutPutPath_UserCA->setReadOnly(true);

    if(!ui->Manage_model->checkState()){
        page[2] = ui->tabWidget->widget(4);
        ui->tabWidget->removeTab(4);
        page[1] = ui->tabWidget->widget(3);
        ui->tabWidget->removeTab(3);
        page[0] = ui->tabWidget->widget(2);
        ui->tabWidget->removeTab(2);
    }

    qfsm = new QFileSystemModelImpl();
    qfsm->setRootPath("/");
    ui->treeView_RsaSign_elf->setModel(qfsm);
    ui->treeView_RsaSign_elf->setRootIndex(qfsm->index("/"));
    ui->treeView_RsaSign_elf->setColumnWidth(0,180);
}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_lineEd_RootCountry_editingFinished()
{
    this->ca_inf.setCountry(ui->lineEd_RootCountry->text());
}

void Widget::on_lineEd_RootState_editingFinished()
{
    this->ca_inf.setState(ui->lineEd_RootState->text());
}

void Widget::on_lineEd_RootLocality_editingFinished()
{
    this->ca_inf.setLocal(ui->lineEd_RootLocality->text());
}

void Widget::on_lineEd_RootOrganization_editingFinished()
{
    this->ca_inf.setOrg_name(ui->lineEd_RootOrganization->text());
}

void Widget::on_lineEd_RootCommon_editingFinished()
{
    this->ca_inf.setCommon_name(ui->lineEd_RootCommon->text());
}



void Widget::on_Btn_Inport_clicked()
{
    if(1/*这里调用签名函数*/){
        this->fin = new Finish_Close();
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent();
        fin->exec();

    }else{
        this->fin = new Finish_Close();
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent();
        fin->exec();
    }
}

void Widget::set_Content_LineEdCA()
{
    if(ui->lineEd_CASign_CA->text().isEmpty()){
        ca_inf.setCA_Path(this->dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCA_Path());
    }else{
        ui->lineEd_CASign_CA->selectAll();
        ui->lineEd_CASign_CA->del();
        ca_inf.setCA_Path(this->dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCA_Path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_Btn_CASign_CA_clicked()
{
    this->dialog = new Dialog();
    dialog->setWindowTitle("Choose CA File");
    if(dialog->exec()){
        set_Content_LineEdCA();
    }
}


void Widget::on_lineEd_CASign_CA_editingFinished()
{
    this->ca_inf.setCA_Path(ui->lineEd_CASign_CA->text());
}


void Widget::on_Btn_RsaSign_rsa_clicked()
{
    this->dialog = new Dialog();
    dialog->setWindowTitle("Choose RSA File");
    if(dialog->exec()){
        set_Content_LineEdRSA();
    }
}

void Widget::set_Content_LineEdRSA(){
    if(ui->lineEd_RsaSign_rsa->text().isEmpty()){
        ca_inf.setPublic_Rsa_Path(this->dialog->getChoose_path());
        ui->lineEd_RsaSign_rsa->setText(ca_inf.getPublic_Rsa_Path());
    }else{
        ui->lineEd_RsaSign_rsa->selectAll();
        ui->lineEd_RsaSign_rsa->del();
        ca_inf.setPublic_Rsa_Path(this->dialog->getChoose_path());
        ui->lineEd_RsaSign_rsa->setText(ca_inf.getPublic_Rsa_Path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_Manage_model_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->tabWidget->addTab(page[0],"生成公私钥");
        ui->tabWidget->addTab(page[1],"生成用户证书");
        ui->tabWidget->addTab(page[2],"生成根证书");
    }
    else{
        page[2] = ui->tabWidget->widget(4);
        ui->tabWidget->removeTab(4);
        page[1] = ui->tabWidget->widget(3);
        ui->tabWidget->removeTab(3);
        page[0] = ui->tabWidget->widget(2);
        ui->tabWidget->removeTab(2);
    }
}

void Widget::on_Btn_Rsa_Sign_Cancel_clicked()
{
    this->close();
}

void Widget::on_Btn_Cancel_clicked()
{
    this->close();
}

void Widget::on_Btn_GetRsa_Cancel_clicked()
{
    this->close();
}

void Widget::on_pushButton_clicked()
{
    this->close();
}

void Widget::on_Btn_outClose_RootCA_clicked()
{
    this->close();
}
