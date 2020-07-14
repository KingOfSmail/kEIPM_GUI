#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置对应输入框为只读
    ui->Line_output_RootCA->setReadOnly(true);
    ui->lineEd_OutPutPath_UserCA->setReadOnly(true);

    ui->lineEd_GetRsa_Greate_privateKey->setReadOnly(true);
    ui->lineEd_GetRsa_public_Path->setReadOnly(true);
    ui->lineEd_GetRsa_privaPath->setReadOnly(true);
    ui->lineEd_GetRsa_publicPath->setReadOnly(true);

    //构造时remove后三个页面
    if(!ui->Manage_model->checkState()){
        page[2] = ui->tabWidget->widget(4);
        ui->tabWidget->removeTab(4);
        page[1] = ui->tabWidget->widget(3);
        ui->tabWidget->removeTab(3);
        page[0] = ui->tabWidget->widget(2);
        ui->tabWidget->removeTab(2);
    }


    //为前两个签名页treeview设置model
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

// Wigdet Page

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

//End of Widget Page

//Rsa、CA签名页的弹出窗口函数

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
        QByteArray ba_it = it.toUtf8();
        const char* tempElfPath = ba_it.data();
        QByteArray ba_Path = Path.toUtf8();
        const char* tempUserCA = ba_Path.data();

        //
        e = Sign_elf_(tempUserCA,tempElfPath);
        //

        if(e.errno){
            fin->setWindowTitle("Defeat");
            fin->setFlag(false);
            fin->set_textContent("已完成");

            QString s = QString::number(count, 10);
            QByteArray ba_temp1 = s.toUtf8();
            const char* count_char = ba_temp1.data();
            fin->set_textContent(count_char);
            fin->set_textContent("个文件,");
            int Fail_count = 0;
            Fail_count = Total_Elf_Path.size()-count;
            s = QString::number(Fail_count,10);
            fin->set_textContent("未完成");
            QByteArray ba_temp2 = s.toUtf8();
            const char* Fail_f = ba_temp2.data();
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


    if(temp_TotalPath.isEmpty()){
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent(e.reason);
        fin->exec();

        ca_inf.reset_ca_inf();
        fin->deleteLater();
        fin = nullptr;
        return;
    }

Page_error:
    fin->set_textContent("\n错误提示：\n");
    fin->set_textContent(e.reason);
    fin->set_textContent("\n未成功签名文件：\n");
    for(QString it : temp_TotalPath){
        QByteArray ba_it_t = it.toUtf8();
        fin->set_textContent(ba_it_t.data());
        fin->set_textContent("\n");
    }
    fin->exec();

    ca_inf.reset_ca_inf();
    fin->deleteLater();
    fin = nullptr;

eo:
    return;
}


//CASign Page

void Widget::on_Btn_Inport_clicked()
{
    this->ca_inf.setCASign_inport_elf_Path(qfsm_forCASign_Page->elf_Path);
    Finish_Close *fin = new  Finish_Close(this);

    QSet<QString> Total_Elf_Path = ca_inf.getCASign_inport_elf_Path();
    QString UserCA_Path=ca_inf.getCASign_inport_UserCA_Path();

    newpage_Of_Finished(fin,Total_Elf_Path,UserCA_Path,keipm_set_UserCA);
}

void Widget::on_Btn_CASign_CA_clicked()
{
    Dialog *dialog = new Dialog(this);
    dialog->setWindowTitle("Choose CA File");
    if(dialog->exec()){
        set_Content_lineEd_CASign_CA(dialog);
    }
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

void Widget::on_Btn_Cancel_clicked()
{
    this->close();
}

void Widget::on_lineEd_CASign_CA_editingFinished()
{
    this->ca_inf.setCASign_inport_UserCA_Path(ui->lineEd_CASign_CA->text());
}

void Widget::on_Btn_RsaSign_Inport_clicked()
{
    this->ca_inf.setRsaSign_inport_elf_Path(qfsm_forRsaSign_Page->elf_Path);

    Finish_Close *fin = new  Finish_Close(this);
    QSet<QString> Total_Elf_Path = ca_inf.getRsaSign_inport_elf_Path();
    QString Public_Key = ca_inf.getRsaSign_inport_PublicKey_Path();

    newpage_Of_Finished(fin,Total_Elf_Path,Public_Key,keipm_set_Key);

}

// End of CASign Page


//Rsa Sign Page

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

void Widget::on_lineEd_RsaSign_rsa_editingFinished()
{
    this->ca_inf.setRsaSign_inport_PublicKey_Path(ui->lineEd_RsaSign_rsa->text());
}

void Widget::on_Btn_Rsa_Sign_Cancel_clicked()
{
    this->close();
}

// End of Rsa Sign Page


//Creat Rsa Page

void Widget::on_Btn_GetRsa_publicKey_clicked()
{
    Dialog* dialog = new Dialog(this);
    dialog->setWindowTitle("Choose RSA PrivateKey");
    if(dialog->exec()){
        set_Content_lineEd_GetRsa_inport_public_privateKey(dialog);

    }
}

void Widget::set_Content_lineEd_GetRsa_inport_public_privateKey(Dialog* dialog){
    if(ui->lineEd_GetRsa_inport_public_privateKey->text().isEmpty()){
        ca_inf.setCreateRsa_inport_PrivsteKey_path(dialog->getChoose_path());
        ui->lineEd_GetRsa_inport_public_privateKey->setText(ca_inf.getCreateRsa_inport_PrivsteKey_path());
    }else{
        ui->lineEd_GetRsa_inport_public_privateKey->selectAll();
        ui->lineEd_GetRsa_inport_public_privateKey->del();
        ca_inf.setCreateRsa_inport_PrivsteKey_path(dialog->getChoose_path());
        ui->lineEd_GetRsa_inport_public_privateKey->setText(ca_inf.getCreateRsa_inport_PrivsteKey_path());
    }
    dialog->deleteLater();
    dialog = nullptr;
}

void Widget::on_Btn_GetRsa_Create_privateKey_clicked()
{
    keipm_err_t error;
    QString str_private_path = QString(keipm_create_PrivateKey(&error));
    Finish_Close* fin = new Finish_Close(this);
    ca_inf.setCreateRsa_Private_Key_Path(str_private_path);
    if(!error.errno){

        if(ui->lineEd_GetRsa_Greate_privateKey->text().isEmpty()){
            ui->lineEd_GetRsa_Greate_privateKey->setText(ca_inf.getCreateRsa_Private_Key_Path());
        }else{
            ui->lineEd_GetRsa_Greate_privateKey->selectAll();
            ui->lineEd_GetRsa_Greate_privateKey->del();
            ui->lineEd_GetRsa_Greate_privateKey->setText(ca_inf.getCreateRsa_Private_Key_Path());
        }

        ca_inf.setCreateRsa_Private_Key_Path(str_private_path);
        copy_privateKey_To_CreatePublicKey(str_private_path);
    }else{
        if(!ui->lineEd_GetRsa_Greate_privateKey->text().isEmpty()){
            ui->lineEd_GetRsa_Greate_privateKey->selectAll();
            ui->lineEd_GetRsa_Greate_privateKey->del();
            QString s = QString("");
            copy_privateKey_To_CreatePublicKey(s);
        }
    }

    remindPage(fin,error);
}

void Widget::on_Btn_GetRsa_Create_publicKey_clicked()
{
    keipm_err_t error;
    QByteArray ba = ca_inf.getCreateRsa_Private_Key_Path().toUtf8();
    const char* private_key_path = ba.data();
    QString str_public_path = QString(keipm_create_PublicKey(&error,private_key_path));
    Finish_Close* fin = new Finish_Close(this);
    ca_inf.setCreateRsa_Public_Key_Path(str_public_path);
    if(!error.errno){

        if(ui->lineEd_GetRsa_public_Path->text().isEmpty()){
            ui->lineEd_GetRsa_public_Path->setText(ca_inf.getCreateRsa_Public_Key_Path());
        }else{
            ui->lineEd_GetRsa_public_Path->selectAll();
            ui->lineEd_GetRsa_public_Path->del();
            ui->lineEd_GetRsa_public_Path->setText(ca_inf.getCreateRsa_Public_Key_Path());
        }

    }else{
        if(!ui->lineEd_GetRsa_public_Path->text().isEmpty()){
            ui->lineEd_GetRsa_public_Path->selectAll();
            ui->lineEd_GetRsa_public_Path->del();
        }
    }

    remindPage(fin,error);
}

void Widget::on_Btn_GetRsa_Create_clicked()
{
    keipm_err_t error_private,error_public;
    QString private_path = QString(keipm_create_PrivateKey(&error_private));
    QByteArray ba = private_path.toUtf8();
    const char* privateKey_path = ba.data();
    QString public_path = QString(keipm_create_PublicKey(&error_public,privateKey_path));
    Finish_Close *fin = new Finish_Close(this);
    ca_inf.setCreateRsa_Private_Key_Path(private_path);
    ca_inf.setCreateRsa_Public_Key_Path(public_path);

    if(!error_private.errno){
      if(ui->lineEd_GetRsa_privaPath->text().isEmpty()){
          ui->lineEd_GetRsa_privaPath->setText(ca_inf.getCreateRsa_Private_Key_Path());
      }else{
          ui->lineEd_GetRsa_privaPath->selectAll();
          ui->lineEd_GetRsa_privaPath->del();
          ui->lineEd_GetRsa_privaPath->setText(ca_inf.getCreateRsa_Private_Key_Path());
      }
    }else{
        if(!ui->lineEd_GetRsa_privaPath->text().isEmpty()){
            ui->lineEd_GetRsa_privaPath->selectAll();
            ui->lineEd_GetRsa_privaPath->del();
        }
    }
    if(!error_public.errno){
        if(ui->lineEd_GetRsa_publicPath->text().isEmpty()){
            ui->lineEd_GetRsa_publicPath->setText(ca_inf.getCreateRsa_Public_Key_Path());
        }else{
            ui->lineEd_GetRsa_publicPath->selectAll();
            ui->lineEd_GetRsa_publicPath->del();
            ui->lineEd_GetRsa_publicPath->setText(ca_inf.getCreateRsa_Public_Key_Path());
        }
    }else{
        if(!ui->lineEd_GetRsa_publicPath->text().isEmpty()){
            ui->lineEd_GetRsa_publicPath->selectAll();
            ui->lineEd_GetRsa_publicPath->del();
        }
    }
    remindPage(fin,error_private,error_public);
}

void Widget::on_Btn_GetRsa_Cancel_clicked()
{
    this->close();
}

void Widget::copy_privateKey_To_CreatePublicKey(QString privateKey_path)
{
    ca_inf.setCreateRsa_inport_PrivsteKey_path(privateKey_path);

    if(ui->lineEd_GetRsa_inport_public_privateKey->text().isEmpty()){
        ui->lineEd_GetRsa_inport_public_privateKey->setText(ca_inf.getCreateRsa_inport_PrivsteKey_path());
    }else{
        ui->lineEd_GetRsa_inport_public_privateKey->selectAll();
        ui->lineEd_GetRsa_inport_public_privateKey->del();
        ui->lineEd_GetRsa_inport_public_privateKey->setText(ca_inf.getCreateRsa_inport_PrivsteKey_path());
    }

}

//End of Creat Rsa Page


//Create_UserCA Page
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

void Widget::on_pushButton_2_clicked()
{
    const char* User_output_CA_path;
    keipm_err_t error;
    UserCa userca;
    Finish_Close *fin = new Finish_Close(this);

    QByteArray ba = ca_inf.getUser_Local().toUtf8();
    userca.User_Local = ba.data();

    QByteArray ba1 = ca_inf.getUser_State().toUtf8();
    userca.User_State = ba1.data();

    QByteArray ba2 = ca_inf.getUser_Country().toUtf8();
    userca.User_Country = ba2.data();

    QByteArray ba3 = ca_inf.getUser_Org_name().toUtf8();
    userca.User_Org_name = ba3.data();

    QByteArray ba4 = ca_inf.getUser_Common_name().toUtf8();
    userca.User_Common_name = ba4.data();

    QByteArray ba5 = ca_inf.getUser_input_RootCA_Path().toUtf8();
    userca.User_input_RootCA_Path = ba5.data();

    User_output_CA_path = keipm_create_userCA(&error,userca);

    if(!error.errno){
        ui->lineEd_OutPutPath_UserCA->setText(User_output_CA_path);
        QString s = QString(User_output_CA_path);
        ca_inf.setRoot_outPut_CA_Path(s);
    }else{
        ui->lineEd_OutPutPath_UserCA->selectAll();
        ui->lineEd_OutPutPath_UserCA->del();
    }
    remindPage(fin,error);

}

void Widget::on_pushButton_clicked()
{
    this->close();
}

//End Of Create UserCA Page


//Create_RootCA Page

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

void Widget::on_Btn_output_RootCA_clicked()
{
    const char* Root_outPut_CA_Path;
    keipm_err_t error;
    rootCa_inf Root_CA;
    Finish_Close* fin =new Finish_Close(this);

    QByteArray ba = ca_inf.getRoot_Local().toUtf8();
    Root_CA.Root_Local = ba.data();

    QByteArray ba1 = ca_inf.getRoot_State().toUtf8();
    Root_CA.Root_State = ba1.data();

    QByteArray ba2 = ca_inf.getRoot_Country().toUtf8();
    Root_CA.Root_Country = ba2.data();

    QByteArray ba3 = ca_inf.getRoot_Org_name().toUtf8();
    Root_CA.Root_Org_name = ba3.data();

    QByteArray ba4 = ca_inf.getRoot_Common_name().toUtf8();
    Root_CA.Root_Common_name = ba.data();

    Root_outPut_CA_Path = keipm_create_rootCA(&error,Root_CA);


    if(!error.errno){
        ui->Line_output_RootCA->setText(Root_outPut_CA_Path);
        QString s = QString(Root_outPut_CA_Path);
        ca_inf.setRoot_outPut_CA_Path(s);
    }else{
        ui->Line_output_RootCA->selectAll();
        ui->Line_output_RootCA->del();
    }
    remindPage(fin,error);
}

void Widget::on_Btn_outClose_RootCA_clicked()
{
    this->close();
}

//End of Create RootCA Page




//点击导入后的弹窗窗口，重载函数为一键导入的弹窗

void Widget::remindPage(Finish_Close *fin, keipm_err_t error)
{
    if(error.errno){
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent("错误提示：\n");
        fin->set_textContent(error.reason);
        fin->exec();



        ca_inf.reset_ca_inf();
        fin->deleteLater();
        fin = nullptr;
    }else{
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent(error.reason);
        fin->exec();



        ca_inf.reset_ca_inf();
        fin->deleteLater();
        fin = nullptr;
    }
}

void Widget::remindPage(Finish_Close *fin, keipm_err_t error_priv, keipm_err_t error_pub)
{
    if((!error_priv.errno)&&(!error_pub.errno)){
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent(error_priv.reason);
        fin->set_textContent("\n");
        fin->set_textContent(error_pub.reason);
        fin->exec();

        ca_inf.reset_ca_inf();
        fin->deleteLater();
        fin = nullptr;
    }else{
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent(error_priv.reason);
        fin->set_textContent("\n");
        fin->set_textContent(error_pub.reason);
        fin->exec();

        ca_inf.reset_ca_inf();
        fin->deleteLater();
        fin = nullptr;
    }
}

//End of finished_close Page
