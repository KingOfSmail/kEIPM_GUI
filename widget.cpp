#include "widget.h"
#include <QFileDialog>
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    /*
    //构造时remove后三个页面
    if(!ui->Manage_model->checkState()){
        page[2] = ui->tabWidget->widget(4);
        ui->tabWidget->removeTab(4);
        page[1] = ui->tabWidget->widget(3);
        ui->tabWidget->removeTab(3);
        page[0] = ui->tabWidget->widget(2);
        ui->tabWidget->removeTab(2);
    }
    */

    QWidget* page1,*page2;
    page1 = ui->tabWidget->widget(4);
    page2 = ui->tabWidget->widget(3);
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);

    ui->tabWidget->insertTab(3,page1,"生成根证书");
    ui->tabWidget->insertTab(4,page2,"生成用户证书");



    //为前两个签名页treeview设置model
    qfsm_forRsaSign_Page = new QFileSystemModelImpl(ui->treeView_RsaSign_elf);
    qfsm_forRsaSign_Page->setRootPath("/");
    ui->treeView_RsaSign_elf->setModel(qfsm_forRsaSign_Page);
    ui->treeView_RsaSign_elf->setRootIndex(qfsm_forRsaSign_Page->index("/"));
    ui->treeView_RsaSign_elf->setColumnWidth(0,200);

    qfsm_forCASign_Page = new QFileSystemModelImpl(ui->treeView_CASign_elf);
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


/**
 * @brief Widget::newpage_Of_Finished
 * 调用签名API 并显示Rsa、CA签名页的弹出窗口函数
 * @param Total_Elf_Path
 * @param Path
 */
void Widget::newpage_Of_Finished(const QSet<QString> &Total_Elf_Path,bool is_prikey,const QString &Path,keipm_err_t (*Sign_elf_)(const char*,const char*)){
    Finish_Close *fin = new Finish_Close(this);

    QSet<QString> temp_TotalPath = Total_Elf_Path;

    QSet<QString> Success_SignElf;
    keipm_err_t e;
    int count = 0;
    if(Path.isEmpty()) {
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent(QString("错误提示：\n未选择%1文件.").arg(is_prikey ? "私钥" : "证书"));
        fin->exec();

        fin->deleteLater();
        fin = nullptr;
        goto eo;
    }
    if(Total_Elf_Path.isEmpty()){
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent("错误提示：\n未选择待签名ELF文件.");
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

    fin->deleteLater();
    fin = nullptr;

eo:
    return;
}


//CASign Page

/**
 * @brief 证书签名按钮
 */
void Widget::on_Btn_Inport_clicked()
{
    const QSet<QString> &Total_Elf_Path = qfsm_forCASign_Page->getSelectedFiles();

    QString CA_path = ui->lineEd_CASign_CA->text();
    newpage_Of_Finished(Total_Elf_Path,false,CA_path,keipm_set_UserCA);
}

void Widget::on_Btn_CASign_CA_clicked()
{
    QString userCert_pathname = QFileDialog::getOpenFileName(this,
                                                               tr("打开证书"),
                                                               "user.der",
                                                               tr("DER编码证书(*der)"));
    if (userCert_pathname.length()) {
        ui->lineEd_CASign_CA->setText(userCert_pathname);
    }
}

void Widget::on_Btn_Cancel_clicked()
{
    this->close();
}

/**
 * @brief RSA签名按钮
 */
void Widget::on_Btn_RsaSign_Inport_clicked()
{
    const QSet<QString> &Total_Elf_Path = qfsm_forRsaSign_Page->getSelectedFiles();

    QString Public_Key = ui->lineEd_RsaSign_rsa->text();
    newpage_Of_Finished(Total_Elf_Path,true,Public_Key,keipm_set_Key);
}

// End of CASign Page


//Rsa Sign Page

void Widget::on_Btn_RsaSign_rsa_clicked()
{
    QString prikey_pathname = QFileDialog::getOpenFileName(this,
                                                           tr("打开RSA私钥"),
                                                           "private_pkcs1.pem",
                                                           tr("PEM私钥(*pem)"));
    if (prikey_pathname.length()) {
        ui->lineEd_RsaSign_rsa->setText(prikey_pathname);
    }
}

void Widget::on_Btn_Rsa_Sign_Cancel_clicked()
{
    this->close();
}

// End of Rsa Sign Page


//Creat Rsa Page

void Widget::on_Btn_GetRsa_publicKey_clicked()
{
    QString pubkey_path = QFileDialog::getOpenFileName(this,
                                                       tr("打开公钥"),
                                                       "public_pkcs1.pem",
                                                       tr("PEM公钥(*pem)"));
    if (pubkey_path.length()) {
        ui->lineEd_GetRsa_inport_public_privateKey->setText(pubkey_path);
    }
}

void Widget::on_Btn_GetRsa_Create_privateKey_clicked()
{
    keipm_err_t error;
    QString str_private_path = QFileDialog::getSaveFileName(this,
                                                             tr("选择私钥保存位置"),
                                                             "private_pkcs1.pem",
                                                             tr("PEM私钥(*pem)"));
    if (str_private_path.isEmpty()) {
        return;
    }
    QByteArray bv_str_private_path = str_private_path.toUtf8();

    error = keipm_create_PrivateKey(bv_str_private_path.data());

    if(!error.errno){
        copy_privateKey_To_CreatePublicKey(str_private_path);
    }else{
        copy_privateKey_To_CreatePublicKey("");
    }

    remindPage(error);
}

/**
 * @brief 导入私钥以生成公钥按钮
 */
void Widget::on_Btn_GetRsa_Create_publicKey_clicked()
{
    keipm_err_t error;
    QByteArray ba = ui->lineEd_GetRsa_inport_public_privateKey->text().toUtf8();
    const char *private_key_path = ba.data();

    if (ba.isEmpty()) {
        remindPage(ERROR(kEIPM_ERR_INVALID, "未选择私钥文件"));
        return;
    }

    QString str_public_path = QFileDialog::getSaveFileName(this,
                                                           tr("选择公钥保存位置"),
                                                           "public_pkcs1.pem",
                                                           tr("PEM公钥(*pem)"));
    // If user has pushed cancel button
    if (str_public_path.isEmpty()) {
        return;
    }

    QByteArray ba_str_public_path = str_public_path.toUtf8();    
    const char *public_key_path = ba_str_public_path.data();

    error = keipm_create_PublicKey(public_key_path, private_key_path);
    remindPage(error);
}

void Widget::on_Btn_GetRsa_Create_clicked()
{
    keipm_err_t error;
    QString private_path = QFileDialog::getSaveFileName(this,
                                                        tr("选择私钥保存位置"),
                                                        "private_pkcs1.pem",
                                                        tr("PEM私钥(*pem)"));
    // If user has pushed cancel button
    if (private_path.isEmpty()) {
        return;
    }
    QByteArray ba_private_path = private_path.toUtf8();
    const char* privateKey_path = ba_private_path.data();

    error = keipm_create_PrivateKey(privateKey_path);

    if(!error.errno){
        copy_privateKey_To_CreatePublicKey(private_path);
    }else{
        remindPage(error);
        // It makes no sense to continue
        return;
    }

    QString public_path = QFileDialog::getSaveFileName(this,
                                                       tr("选择公钥保存位置"),
                                                       "private_pkcs1.pem",
                                                       tr("PEM公钥(*pem)"));
    // If user has pushed cancel button
    if (public_path.isEmpty()) {
        return;
    }
    QByteArray ba_public_path = public_path.toUtf8();
    const char *publicKey_path = ba_public_path.data();

    error = keipm_create_PublicKey(publicKey_path, privateKey_path);

    remindPage(error);
}

void Widget::on_Btn_GetRsa_Cancel_clicked()
{
    this->close();
}

void Widget::copy_privateKey_To_CreatePublicKey(const QString &privateKey_path)
{
    ui->lineEd_GetRsa_inport_public_privateKey->setText(privateKey_path);
}

//End of Creat Rsa Page


//Create_UserCA Page
void Widget::on_Btn_User_Visit_RootCA_clicked()
{
    QString rootCA_pathname = QFileDialog::getOpenFileName(this,
                                                           tr("打开CA根证书"),
                                                           "root_ca.der",
                                                           tr("DER编码证书(*der)"));

    if (rootCA_pathname.length()) {
        ui->lineEd_User_InputPath_RootCA->setText(rootCA_pathname);
    }
}

static keipm_err_t checkCertInfo(
        const QString &User_Local,
        const QString &User_State,
        const QString &User_Country,
        const QString &User_Org_name,
        const QString &User_Common_name)
{
    if (User_Local.isEmpty() || User_State.isEmpty() || User_Country.isEmpty()
            || User_Org_name.isEmpty() || User_Common_name.isEmpty()) {
        return ERROR(kEIPM_ERR_INVALID, "证书有字段为空，请检查");
    }
    if (User_Country.length() != 2) {
        return ERROR(kEIPM_ERR_INVALID, "“所在国家 C”字段必须为2个字节");
    }
    return ERROR(kEIPM_OK, NULL);
}

void Widget::on_pushButton_2_clicked()
{
    keipm_err_t error;
    UserCa userca;

    QByteArray ba = ui->lineEd_UserLocality->text().toUtf8();
    userca.User_Local = ba.data();

    QByteArray ba1 = ui->lineEd_UserState->text().toUtf8();
    userca.User_State = ba1.data();

    QByteArray ba2 = ui->lineEd_UserCountry->text().toUtf8();
    userca.User_Country = ba2.data();

    QByteArray ba3 = ui->lineEd_UserOrganization->text().toUtf8();
    userca.User_Org_name = ba3.data();

    QByteArray ba4 = ui->lineEd_UserCommon->text().toUtf8();
    userca.User_Common_name = ba4.data();

    QByteArray ba5 = ui->lineEd_User_InputPath_RootCA->text().toUtf8();
    userca.User_input_RootCA_Path = ba5.data();

    if (ba5.isEmpty()) {
        remindPage(ERROR(kEIPM_ERR_INVALID, "未选择根证书文件"));
        return;
    }

    error = checkCertInfo(userca.User_Local, userca.User_State, userca.User_Country,
                          userca.User_Org_name, userca.User_Common_name);
    if (error.errno != kEIPM_OK) {
        remindPage(error);
        return;
    }

    QString userCert_pathname = QFileDialog::getSaveFileName(this,
                                                           tr("保存用户证书"),
                                                           "user.der",
                                                           tr("DER编码证书(*der)"));
    if (userCert_pathname.isEmpty()) {
        return;
    }
    QByteArray ba6 = userCert_pathname.toUtf8();

    error = keipm_create_userCA(ba6.data(), &userca);

    remindPage(error);

}

void Widget::on_pushButton_clicked()
{
    this->close();
}

//End Of Create UserCA Page


//Create_RootCA Page

void Widget::on_Btn_output_RootCA_clicked()
{
    keipm_err_t error;
    rootCa_inf Root_CA;

    QByteArray ba = ui->lineEd_RootLocality->text().toUtf8();
    Root_CA.Root_Local = ba.data();

    QByteArray ba1 = ui->lineEd_RootState->text().toUtf8();
    Root_CA.Root_State = ba1.data();

    QByteArray ba2 = ui->lineEd_RootCountry->text().toUtf8();
    Root_CA.Root_Country = ba2.data();

    QByteArray ba3 = ui->lineEd_RootOrganization->text().toUtf8();
    Root_CA.Root_Org_name = ba3.data();

    QByteArray ba4 = ui->lineEd_RootCommon->text().toUtf8();
    Root_CA.Root_Common_name = ba.data();

    error = checkCertInfo(Root_CA.Root_Local, Root_CA.Root_State, Root_CA.Root_Country,
                          Root_CA.Root_Org_name, Root_CA.Root_Common_name);
    if (error.errno != kEIPM_OK) {
        remindPage(error);
        return;
    }

    QString rootCA_pathname = QFileDialog::getSaveFileName(this,
                                                           tr("保存CA根证书"),
                                                           "root_ca.der",
                                                           tr("DER编码证书(*der)"));
    if (rootCA_pathname.isEmpty()) {
        return;
    }

    QByteArray ba5 = rootCA_pathname.toUtf8();

    error = keipm_create_rootCA(ba5.data(), &Root_CA);
    remindPage(error);
}

void Widget::on_Btn_outClose_RootCA_clicked()
{
    this->close();
}

//End of Create RootCA Page




//点击导入后的弹窗窗口，重载函数为一键导入的弹窗

void Widget::remindPage(keipm_err_t error)
{
    Finish_Close* fin = new Finish_Close(this);
    if(error.errno){
        fin->setWindowTitle("Defeat");
        fin->setFlag(false);
        fin->set_textContent("错误提示：\n");
        fin->set_textContent(error.reason);
        fin->exec();

        fin->deleteLater();
        fin = nullptr;
    }else{
        fin->setWindowTitle("Finish");
        fin->setFlag(true);
        fin->set_textContent(error.reason);
        fin->exec();

        fin->deleteLater();
        fin = nullptr;
    }
}

//End of finished_close Page
