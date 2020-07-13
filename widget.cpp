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

const char *Widget::QstrToChar(QString str)
{
    QByteArray ba = str.toUtf8();
    return ba.data();
}

void Widget::newpage_Of_Finished(Finish_Close *fin,QSet<QString> Total_Elf_Path,QString Path,keipm_err_t (*Sign_elf_)(const char*,const char*)){
    QSet<QString> temp_TotalPath = Total_Elf_Path;

    QSet<QString> Success_SignElf;
    keipm_err_t e;
    int count = 0;
    if(Total_Elf_Path.isEmpty()){
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent("错误提示：\n未选择文件.");
        fin->exec();

        fin->deleteLater();
        fin = nullptr;
        goto eo;
    }
    for(QString it :Total_Elf_Path){
        const char* tempElfPath = QstrToChar(it);
        const char* tempUserCA = QstrToChar(Path);

        //
        e = Sign_elf_(tempUserCA,tempElfPath);
        //

        if(e.errno){
            fin->setWindowTitle("Defeat");
            fin->setFlag(false);
            fin->set_textContent("已完成");

            QString s = QString::number(count, 10);
            const char* count_char = QstrToChar(s);
            fin->set_textContent(count_char);
            fin->set_textContent("个文件,");
            int Fail_count = 0;
            Fail_count = Total_Elf_Path.size()-count;
            s = QString::number(Fail_count,10);
            fin->set_textContent("未完成");
            const char* Fail_f = QstrToChar(s);
            fin->set_textContent(Fail_f);
            fin->set_textContent("个文件。\n");
            goto Page_error;
        }
        const char* t = tempElfPath;
        Success_SignElf.insert(t);
        temp_TotalPath -= t;
        count++;
        tempUserCA = nullptr;
        tempElfPath = nullptr;
    }


    if(!temp_TotalPath.isEmpty()){
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent(e.reason);
        fin->exec();

        fin->deleteLater();
        fin = nullptr;
    }

Page_error:
    fin->set_textContent("\n错误提示：\n");
    fin->set_textContent(e.reason);
    fin->set_textContent("\n未成功签名文件：\n");
    for(QString it : temp_TotalPath){
        fin->set_textContent(QstrToChar(it));
        fin->set_textContent("\n");
    }
    fin->exec();
    fin->deleteLater();
    fin = nullptr;

eo:
    return;
}



void Widget::on_Btn_Inport_clicked()
{
    this->ca_inf.setCASign_inport_elf_Path(qfsm_forCASign_Page->elf_Path);
    Finish_Close *fin = new  Finish_Close(this);

    QSet<QString> Total_Elf_Path = ca_inf.getCASign_inport_elf_Path();
    QString UserCA_Path=ca_inf.getCASign_inport_UserCA_Path();

    newpage_Of_Finished(fin,Total_Elf_Path,UserCA_Path,keipm_set_UserCA);
}

void Widget::on_Btn_RsaSign_Inport_clicked()
{
    this->ca_inf.setRsaSign_inport_elf_Path(qfsm_forRsaSign_Page->elf_Path);

    Finish_Close *fin = new  Finish_Close(this);
    QSet<QString> Total_Elf_Path = ca_inf.getRsaSign_inport_elf_Path();
    QString Public_Key = ca_inf.getRsaSign_inport_PublicKey_Path();

    newpage_Of_Finished(fin,Total_Elf_Path,Public_Key,keipm_set_Key);

}

void Widget::set_Content_lineEd_CASign_CA(Dialog *dialog)
{
    if(ui->lineEd_CASign_CA->text().isEmpty()){
        ca_inf.setCASign_inport_UserCA_Path(dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCASign_inport_UserCA_Path());
    }else{
        ui->lineEd_CASign_CA->selectAll();
        ui->lineEd_CASign_CA->del();
        ca_inf.setCASign_inport_UserCA_Path(dialog->getChoose_path());
        ui->lineEd_CASign_CA->setText(ca_inf.getCASign_inport_UserCA_Path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_Btn_CASign_CA_clicked()
{
    Dialog *dialog = new Dialog(this);
    dialog->setWindowTitle("Choose CA File");
    if(dialog->exec()){
        set_Content_lineEd_CASign_CA(dialog);
    }
}


void Widget::on_lineEd_CASign_CA_editingFinished()
{
    this->ca_inf.setCASign_inport_UserCA_Path(ui->lineEd_CASign_CA->text());
}


void Widget::on_Btn_RsaSign_rsa_clicked()
{
    Dialog* dialog = new Dialog(this);
    dialog->setWindowTitle("Choose RSA File");
    if(dialog->exec()){
        set_Content_lineEd_RsaSign_rsa(dialog);
    }
}

void Widget::set_Content_lineEd_RsaSign_rsa(Dialog* dialog){
    if(ui->lineEd_RsaSign_rsa->text().isEmpty()){
        ca_inf.setRsaSign_inport_PublicKey_Path(dialog->getChoose_path());
        ui->lineEd_RsaSign_rsa->setText(ca_inf.getRsaSign_inport_PublicKey_Path());
    }else{
        ui->lineEd_RsaSign_rsa->selectAll();
        ui->lineEd_RsaSign_rsa->del();
        ca_inf.setRsaSign_inport_PublicKey_Path(dialog->getChoose_path());
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
    Dialog* dialog = new Dialog(this);
    dialog->setWindowTitle("Choose RSA File");
    if(dialog->exec()){
        set_Content_lineEd_User_InputPath_RootCA(dialog);
    }
}

void Widget::set_Content_lineEd_User_InputPath_RootCA(Dialog* dialog){
    if(ui->lineEd_User_InputPath_RootCA->text().isEmpty()){
        ca_inf.setUser_input_RootCA_Path(dialog->getChoose_path());
        ui->lineEd_User_InputPath_RootCA->setText(ca_inf.getUser_input_RootCA_Path());
    }else{
        ui->lineEd_User_InputPath_RootCA->selectAll();
        ui->lineEd_User_InputPath_RootCA->del();
        ca_inf.setUser_input_RootCA_Path(dialog->getChoose_path());
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



void Widget::on_lineEd_RsaSign_rsa_editingFinished()
{
    this->ca_inf.setRsaSign_inport_PublicKey_Path(ui->lineEd_RsaSign_rsa->text());
}
