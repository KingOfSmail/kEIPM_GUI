#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabBar>
#include<QTextCodec>

#include "qfilesystemmodelimpl.h"
#include "ca_inf.h"
#include "dialog.h"
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

    void newpage_Of_Finished(Finish_Close*,QSet<QString>,QString,keipm_err_t (*Sign_elf_)(const char*,const char*));

private slots:
    void on_lineEd_RootCountry_editingFinished();

    void on_lineEd_RootState_editingFinished();

    void on_lineEd_RootLocality_editingFinished();

    void on_lineEd_RootOrganization_editingFinished();

    void on_Btn_Inport_clicked();

    void set_Content_lineEd_CASign_CA(Dialog* dialog);
    void set_Content_lineEd_RsaSign_rsa(Dialog* dialog);

    void on_Btn_CASign_CA_clicked();

    void on_lineEd_CASign_CA_editingFinished();

    void on_lineEd_RootCommon_editingFinished();

    void on_Btn_RsaSign_rsa_clicked();

    void on_Manage_model_stateChanged(int arg1);

    void on_Btn_Rsa_Sign_Cancel_clicked();

    void on_Btn_Cancel_clicked();

    void on_Btn_GetRsa_Cancel_clicked();

    void on_pushButton_clicked();

    void on_Btn_outClose_RootCA_clicked();

    void on_Btn_User_Visit_RootCA_clicked();

    void set_Content_lineEd_User_InputPath_RootCA(Dialog* dialog);

    void on_lineEd_UserCountry_editingFinished();

    void on_lineEd_UserState_editingFinished();

    void on_lineEd_UserLocality_editingFinished();

    void on_lineEd_UserOrganization_editingFinished();

    void on_lineEd_UserCommon_editingFinished();

    void on_Btn_RsaSign_Inport_clicked();

    void on_lineEd_RsaSign_rsa_editingFinished();

    const char *QstrToChar(QString str);



private:
    Ui::Widget *ui;
    CA_inf ca_inf;
    QFileSystemModelImpl *qfsm_forRsaSign_Page,*qfsm_forCASign_Page;
    QWidget *page[3];

    keipm_err_t error;
};
#endif // WIDGET_H
