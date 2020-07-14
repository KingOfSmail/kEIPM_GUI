#include "ca_inf.h"

CA_inf::CA_inf()
{

}

QString CA_inf::getRoot_Common_name() const
{
    return rootCA_page.Root_Common_name;
}

void CA_inf::setRoot_Common_name(const QString &value)
{
    rootCA_page.Root_Common_name = value;
}

QString CA_inf::getRoot_Org_name() const
{
    return rootCA_page.Root_Org_name;
}

void CA_inf::setRoot_Org_name(const QString &value)
{
    rootCA_page.Root_Org_name = value;
}

QString CA_inf::getRoot_Local() const
{
    return rootCA_page.Root_Local;
}

void CA_inf::setRoot_Local(const QString &value)
{
    rootCA_page.Root_Local = value;
}

QString CA_inf::getRoot_State() const
{
    return rootCA_page.Root_State;
}

void CA_inf::setRoot_State(const QString &value)
{
    rootCA_page.Root_State = value;
}

QString CA_inf::getRoot_Country() const
{
    return rootCA_page.Root_Country;
}

void CA_inf::setRoot_Country(const QString &value)
{
    rootCA_page.Root_Country = value;
}

QString CA_inf::getUser_input_RootCA_Path() const
{
    return userCA_Page.User_input_RootCA_Path;
}

void CA_inf::setUser_input_RootCA_Path(const QString &value)
{
    userCA_Page.User_input_RootCA_Path = value;
}

QString CA_inf::getUser_Common_name() const
{
    return userCA_Page.User_Common_name;
}

void CA_inf::setUser_Common_name(const QString &value)
{
    userCA_Page.User_Common_name = value;
}

QString CA_inf::getUser_Org_name() const
{
    return userCA_Page.User_Org_name;
}

void CA_inf::setUser_Org_name(const QString &value)
{
    userCA_Page.User_Org_name = value;
}

QString CA_inf::getUser_Local() const
{
    return userCA_Page.User_Local;
}

void CA_inf::setUser_Local(const QString &value)
{
    userCA_Page.User_Local = value;
}

QString CA_inf::getUser_State() const
{
    return userCA_Page.User_State;
}

void CA_inf::setUser_State(const QString &value)
{
    userCA_Page.User_State = value;
}

QString CA_inf::getUser_Country() const
{
    return userCA_Page.User_Country;
}

void CA_inf::setUser_Country(const QString &value)
{
    userCA_Page.User_Country = value;
}

QString CA_inf::getUser_outPut_CA_Path() const
{
    return userCA_Page.User_outPut_CA_Path;
}

void CA_inf::setUser_outPut_CA_Path(const QString &value)
{
    userCA_Page.User_outPut_CA_Path = value;
}

QString CA_inf::getCreateRsa_Private_Key_Path() const
{
    return createRsa_Page.CreateRsa_Private_Key_Path;
}

void CA_inf::setCreateRsa_Private_Key_Path(const QString &value)
{
    createRsa_Page.CreateRsa_Private_Key_Path = value;
}

QString CA_inf::getCreateRsa_Public_Key_Path() const
{
    return createRsa_Page.CreateRsa_Public_Key_Path;
}

void CA_inf::setCreateRsa_Public_Key_Path(const QString &value)
{
    createRsa_Page.CreateRsa_Public_Key_Path = value;
}

QString CA_inf::getCASign_inport_UserCA_Path() const
{
    return caSign_Page.CASign_inport_UserCA_Path;
}

void CA_inf::setCASign_inport_UserCA_Path(const QString &value)
{
    caSign_Page.CASign_inport_UserCA_Path = value;
}

QString CA_inf::getRsaSign_inport_PublicKey_Path() const
{
    return rsaSign_Page.RsaSign_inport_PublicKey_Path;
}

void CA_inf::setRsaSign_inport_PublicKey_Path(const QString &value)
{
    rsaSign_Page.RsaSign_inport_PublicKey_Path = value;
}

void CA_inf::setCASign_inport_elf_Path(const QSet<QString> qs)
{
    QString temp;
    QSetIterator<QString> it(qs);
    while(it.hasNext()){
        temp = it.next();
        this->caSign_Page.CASign_inport_elf_Path.insert(temp);
    }
}

void CA_inf::setRsaSign_inport_elf_Path(const QSet<QString> qs)
{
    QString temp;
    QSetIterator<QString> it(qs);
    while(it.hasNext()){
        temp = it.next();
        this->rsaSign_Page.RsaSign_inport_elf_Path.insert(temp);
    }
}


QSet<QString> CA_inf::getRsaSign_inport_elf_Path() const
{
    return rsaSign_Page.RsaSign_inport_elf_Path;
}

QSet<QString> CA_inf::getCASign_inport_elf_Path() const
{
    return caSign_Page.CASign_inport_elf_Path;
}

void CA_inf::reset_ca_inf()
{
    rootCA_page.Root_Local.clear();
    rootCA_page.Root_State.clear();
    rootCA_page.Root_Country.clear();
    rootCA_page.Root_Org_name.clear();
    rootCA_page.Root_Common_name.clear();
    rootCA_page.Root_outPut_CA_Path.clear();

    userCA_Page.User_Local.clear();
    userCA_Page.User_State .clear();
    userCA_Page.User_Country.clear();
    userCA_Page.User_Org_name.clear();
    userCA_Page.User_outPut_CA_Path .clear();
    userCA_Page.User_input_RootCA_Path.clear();

    createRsa_Page.CreateRsa_Private_Key_Path.clear();
    createRsa_Page.CreateRsa_Public_Key_Path.clear();

    caSign_Page.CASign_inport_elf_Path.clear();
    caSign_Page.CASign_inport_UserCA_Path.clear();

    rsaSign_Page.RsaSign_inport_elf_Path.clear();
    rsaSign_Page.RsaSign_inport_PublicKey_Path.clear();
}



QString CA_inf::getCreateRsa_inport_PrivsteKey_path() const
{
    return createRsa_Page.CreateRsa_inport_PrivsteKey_path;
}

void CA_inf::setCreateRsa_inport_PrivsteKey_path(const QString &value)
{
    createRsa_Page.CreateRsa_inport_PrivsteKey_path = value;
}

QString CA_inf::getRoot_outPut_CA_Path() const
{
    return rootCA_page.Root_outPut_CA_Path;
}

void CA_inf::setRoot_outPut_CA_Path(const QString &value)
{
    rootCA_page.Root_outPut_CA_Path = value;
}
