#ifndef CA_INF_H
#define CA_INF_H

#include <QSet>
#include <QString>

struct RootCA_Page{
    QString Root_Common_name;
    QString Root_Org_name;
    QString Root_Local;
    QString Root_State;
    QString Root_Country;
    QString Root_outPut_CA_Path;

};

struct UserCA_Page{
    //save UserCA Page
    QString User_input_RootCA_Path;
    QString User_Common_name;
    QString User_Org_name;
    QString User_Local;
    QString User_State;
    QString User_Country;
    QString User_outPut_CA_Path;
};

struct CreateRsaPage{
    //save CreateRsa Page
    QString CreateRsa_Private_Key_Path;
    QString CreateRsa_Public_Key_Path;

    QString CreateRsa_inport_PrivsteKey_path;


};


struct CASign_Page{
    //save CASign Page
    QString CASign_inport_UserCA_Path;
    QSet<QString> CASign_inport_elf_Path;

};

struct RsaSige_Page{
    //save RsaSign Page
    QString RsaSign_inport_PublicKey_Path;
    QSet<QString> RsaSign_inport_elf_Path;
};


class CA_inf
{
public:
    CA_inf();

    QString getRoot_Common_name() const;
    void setRoot_Common_name(const QString &value);

    QString getRoot_Org_name() const;
    void setRoot_Org_name(const QString &value);

    QString getRoot_Local() const;
    void setRoot_Local(const QString &value);

    QString getRoot_State() const;
    void setRoot_State(const QString &value);

    QString getRoot_Country() const;
    void setRoot_Country(const QString &value);


    QString getUser_input_RootCA_Path() const;
    void setUser_input_RootCA_Path(const QString &value);

    QString getUser_Common_name() const;
    void setUser_Common_name(const QString &value);

    QString getUser_Org_name() const;
    void setUser_Org_name(const QString &value);

    QString getUser_Local() const;
    void setUser_Local(const QString &value);

    QString getUser_State() const;
    void setUser_State(const QString &value);

    QString getUser_Country() const;
    void setUser_Country(const QString &value);

    QString getUser_outPut_CA_Path() const;
    void setUser_outPut_CA_Path(const QString &value);

    QString getCreateRsa_Private_Key_Path() const;
    void setCreateRsa_Private_Key_Path(const QString &value);

    QString getCreateRsa_Public_Key_Path() const;
    void setCreateRsa_Public_Key_Path(const QString &value);

    QString getCASign_inport_UserCA_Path() const;
    void setCASign_inport_UserCA_Path(const QString &value);

    QString getRsaSign_inport_PublicKey_Path() const;
    void setRsaSign_inport_PublicKey_Path(const QString &value);

    void setCASign_inport_elf_Path(const QSet<QString> qs);
    void setRsaSign_inport_elf_Path(const QSet<QString> qs);

    QString getCreateRsa_inport_PrivsteKey_path() const;
    void setCreateRsa_inport_PrivsteKey_path(const QString &value);

    QString getRoot_outPut_CA_Path() const;
    void setRoot_outPut_CA_Path(const QString &value);

    QSet<QString> getRsaSign_inport_elf_Path() const;

    QSet<QString> getCASign_inport_elf_Path() const;

    void reset_ca_inf();

private:
    RootCA_Page rootCA_page;
    UserCA_Page userCA_Page;
    CreateRsaPage createRsa_Page;
    CASign_Page caSign_Page;
    RsaSige_Page rsaSign_Page;

};


#endif // CA_INF_H
