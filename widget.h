#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabBar>

#include "qfilesystemmodelimpl.h"
#include "ca_inf.h"
#include "dialog.h"
#include "finish_close.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_lineEd_RootCountry_editingFinished();

    void on_lineEd_RootState_editingFinished();

    void on_lineEd_RootLocality_editingFinished();

    void on_lineEd_RootOrganization_editingFinished();

    void on_Btn_Inport_clicked();

    void set_Content_LineEdCA();
    void set_Content_LineEdRSA();

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

private:
    Ui::Widget *ui;
    CA_inf ca_inf;
    Dialog *dialog;
    Finish_Close *fin;
    QFileSystemModelImpl *qfsm;
    QWidget *page[3];
};
#endif // WIDGET_H
