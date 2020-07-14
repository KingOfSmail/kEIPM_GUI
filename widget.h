#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabBar>
#include <QTextCodec>

#include "qfilesystemmodelimpl.h"
#include "finish_close.h"
#include "api.h"
#include "errors.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void newpage_Of_Finished(const QSet<QString> &,bool,const QString &,keipm_err_t (*Sign_elf_)(const char*,const char*));

private slots:

    void on_Btn_Inport_clicked();

    void on_Btn_CASign_CA_clicked();

    void on_Btn_RsaSign_rsa_clicked();

    void on_Manage_model_stateChanged(int arg1);

    void on_Btn_Rsa_Sign_Cancel_clicked();

    void on_Btn_Cancel_clicked();

    void on_Btn_GetRsa_Cancel_clicked();

    void on_pushButton_clicked();

    void on_Btn_outClose_RootCA_clicked();

    void on_Btn_User_Visit_RootCA_clicked();

    void on_Btn_RsaSign_Inport_clicked();

    void on_Btn_GetRsa_publicKey_clicked();

    void copy_privateKey_To_CreatePublicKey(const QString &);

    void on_Btn_GetRsa_Create_privateKey_clicked();

    void on_Btn_GetRsa_Create_publicKey_clicked();

    void on_Btn_GetRsa_Create_clicked();

    void on_Btn_output_RootCA_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QFileSystemModelImpl *qfsm_forRsaSign_Page,*qfsm_forCASign_Page;
    QWidget *page[3];

    void remindPage(keipm_err_t error);
    void QstrToChar(QByteArray* ba,QString str,const char* char_str);
};
#endif // WIDGET_H
