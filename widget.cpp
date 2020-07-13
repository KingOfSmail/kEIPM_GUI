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

    qfsm_forRsaSign_Page = new QFileSystemModelImpl();
    qfsm_forRsaSign_Page->setRootPath("/");
    ui->treeView_RsaSign_elf->setModel(qfsm_forRsaSign_Page);
    ui->treeView_RsaSign_elf->setRootIndex(qfsm_forRsaSign_Page->index("/"));
    ui->treeView_RsaSign_elf->setColumnWidth(0,200);

    qfsm_forCASign_Page = new QFileSystemModelImpl();
    qfsm_forCASign_Page->setRootPath("/");
    ui->treeView_CASign_elf->setModel(qfsm_forCASign_Page);
    ui->treeView_CASign_elf->setRootIndex(qfsm_forCASign_Page->index("/"));
    ui->treeView_CASign_elf->setColumnWidth(0,200);
}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_lineEd_RootCountry_editingFinished()
{
    this->ca_inf.setRoot_Country(ui->lineEd_RootCountry->text());
}

void Widget::on_lineEd_RootState_editingFinished()
{
    this->ca_inf.setRoot_State(ui->lineEd_RootState->text());
}

void Widget::on_lineEd_RootLocality_editingFinished()
{
    this->ca_inf.setRoot_Local(ui->lineEd_RootLocality->text());
}

void Widget::on_lineEd_RootOrganization_editingFinished()
{
    this->ca_inf.setRoot_Org_name(ui->lineEd_RootOrganization->text());
}

void Widget::on_lineEd_RootCommon_editingFinished()
{
    this->ca_inf.setRoot_Common_name(ui->lineEd_RootCommon->text());
}



void Widget::on_Btn_Inport_clicked()
{
    this->ca_inf.setCASign_inport_elf_Path(qfsm_forCASign_Page->elf_Path);

    error = keipm_gen_key_pair();
    if(!error.errno){
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

void Widget::set_Content_lineEd_CASign_CA()
{
    if(ui->lineEd_CASign_CA->text().isEmpty()){
        ca_inf.setCASign_inport_UserCA_Path(this->dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCASign_inport_UserCA_Path());
    }else{
        ui->lineEd_CASign_CA->selectAll();
        ui->lineEd_CASign_CA->del();
        ca_inf.setCASign_inport_UserCA_Path(this->dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCASign_inport_UserCA_Path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_Btn_CASign_CA_clicked()
{
    this->dialog = new Dialog();
    dialog->setWindowTitle("Choose CA File");
    if(dialog->exec()){
        set_Content_lineEd_CASign_CA();
    }
}


void Widget::on_lineEd_CASign_CA_editingFinished()
{
    this->ca_inf.setCASign_inport_UserCA_Path(ui->lineEd_CASign_CA->text());
}


void Widget::on_Btn_RsaSign_rsa_clicked()
{
    this->dialog = new Dialog();
    dialog->setWindowTitle("Choose RSA File");
    if(dialog->exec()){
        set_Content_lineEd_RsaSign_rsa();
    }
}

void Widget::set_Content_lineEd_RsaSign_rsa(){
    if(ui->lineEd_RsaSign_rsa->text().isEmpty()){
        ca_inf.setRsaSign_inport_PublicKey_Path(this->dialog->getChoose_path());
        ui->lineEd_RsaSign_rsa->setText(ca_inf.getRsaSign_inport_PublicKey_Path());
    }else{
        ui->lineEd_RsaSign_rsa->selectAll();
        ui->lineEd_RsaSign_rsa->del();
        ca_inf.setRsaSign_inport_PublicKey_Path(this->dialog->getChoose_path());
        ui->lineEd_RsaSign_rsa->setText(ca_inf.getRsaSign_inport_PublicKey_Path());
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

void Widget::on_Btn_User_Visit_RootCA_clicked()
{
    this->dialog = new Dialog();
    dialog->setWindowTitle("Choose RSA File");
    if(dialog->exec()){
        set_Content_lineEd_User_InputPath_RootCA();
    }
}

void Widget::set_Content_lineEd_User_InputPath_RootCA(){
    if(ui->lineEd_User_InputPath_RootCA->text().isEmpty()){
        ca_inf.setUser_input_RootCA_Path(this->dialog->getChoose_path());
        ui->lineEd_User_InputPath_RootCA->setText(ca_inf.getUser_input_RootCA_Path());
    }else{
        ui->lineEd_User_InputPath_RootCA->selectAll();
        ui->lineEd_User_InputPath_RootCA->del();
        ca_inf.setUser_input_RootCA_Path(this->dialog->getChoose_path());
        ui->lineEd_User_InputPath_RootCA->setText(ca_inf.getUser_input_RootCA_Path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_lineEd_UserCountry_editingFinished()
{
    this->ca_inf.setUser_Country(ui->lineEd_UserCountry->text());
}

void Widget::on_lineEd_UserState_editingFinished()
{
    this->ca_inf.setUser_State(ui->lineEd_UserState->text());
}

void Widget::on_lineEd_UserLocality_editingFinished()
{
    this->ca_inf.setUser_Local(ui->lineEd_UserLocality->text());
}

void Widget::on_lineEd_UserOrganization_editingFinished()
{
    this->ca_inf.setUser_Org_name(ui->lineEd_UserOrganization->text());
}

void Widget::on_lineEd_UserCommon_editingFinished()
{
    this->ca_inf.setUser_Common_name(ui->lineEd_UserCommon->text());
}

void Widget::on_Btn_RsaSign_Inport_clicked()
{
    this->ca_inf.setRsaSign_inport_elf_Path(qfsm_forRsaSign_Page->elf_Path);
}

void Widget::on_lineEd_RsaSign_rsa_editingFinished()
{
    this->ca_inf.setRsaSign_inport_PublicKey_Path(ui->lineEd_RsaSign_rsa->text());
}
