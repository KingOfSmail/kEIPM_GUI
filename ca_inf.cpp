#include "ca_inf.h"

CA_inf::CA_inf()
{

}

QString CA_inf::getRoot_Common_name() const
{
    return Root_Common_name;
}

void CA_inf::setRoot_Common_name(const QString &value)
{
    Root_Common_name = value;
}

QString CA_inf::getRoot_Org_name() const
{
    return Root_Org_name;
}

void CA_inf::setRoot_Org_name(const QString &value)
{
    Root_Org_name = value;
}

QString CA_inf::getRoot_Local() const
{
    return Root_Local;
}

void CA_inf::setRoot_Local(const QString &value)
{
    Root_Local = value;
}

QString CA_inf::getRoot_State() const
{
    return Root_State;
}

void CA_inf::setRoot_State(const QString &value)
{
    Root_State = value;
}

QString CA_inf::getRoot_Country() const
{
    return Root_Country;
}

void CA_inf::setRoot_Country(const QString &value)
{
    Root_Country = value;
}

QString CA_inf::getUser_input_RootCA_Path() const
{
    return User_input_RootCA_Path;
}

void CA_inf::setUser_input_RootCA_Path(const QString &value)
{
    User_input_RootCA_Path = value;
}

QString CA_inf::getUser_Common_name() const
{
    return User_Common_name;
}

void CA_inf::setUser_Common_name(const QString &value)
{
    User_Common_name = value;
}

QString CA_inf::getUser_Org_name() const
{
    return User_Org_name;
}

void CA_inf::setUser_Org_name(const QString &value)
{
    User_Org_name = value;
}

QString CA_inf::getUser_Local() const
{
    return User_Local;
}

void CA_inf::setUser_Local(const QString &value)
{
    User_Local = value;
}

QString CA_inf::getUser_State() const
{
    return User_State;
}

void CA_inf::setUser_State(const QString &value)
{
    User_State = value;
}

QString CA_inf::getUser_Country() const
{
    return User_Country;
}

void CA_inf::setUser_Country(const QString &value)
{
    User_Country = value;
}

QString CA_inf::getUser_outPut_CA_Path() const
{
    return User_outPut_CA_Path;
}

void CA_inf::setUser_outPut_CA_Path(const QString &value)
{
    User_outPut_CA_Path = value;
}

QString CA_inf::getCreateRsa_Public_Key() const
{
    return CreateRsa_Public_Key;
}

void CA_inf::setCreateRsa_Public_Key(const QString &value)
{
    CreateRsa_Public_Key = value;
}

QString CA_inf::getCreateRsa_Public_Key_Path() const
{
    return CreateRsa_Public_Key_Path;
}

void CA_inf::setCreateRsa_Public_Key_Path(const QString &value)
{
    CreateRsa_Public_Key_Path = value;
}

QString CA_inf::getCASign_inport_UserCA_Path() const
{
    return CASign_inport_UserCA_Path;
}

void CA_inf::setCASign_inport_UserCA_Path(const QString &value)
{
    CASign_inport_UserCA_Path = value;
}

QString CA_inf::getRsaSign_inport_PublicKey_Path() const
{
    return RsaSign_inport_PublicKey_Path;
}

void CA_inf::setRsaSign_inport_PublicKey_Path(const QString &value)
{
    RsaSign_inport_PublicKey_Path = value;
}

void CA_inf::setCASign_inport_elf_Path(const QSet<QString> qs)
{
    QString temp;
    QSetIterator<QString> it(qs);
    while(it.hasNext()){
        temp = it.next();
        this->CASign_inport_elf_Path.insert(temp);
    }
}

void CA_inf::setRsaSign_inport_elf_Path(const QSet<QString> qs)
{
    QString temp;
    QSetIterator<QString> it(qs);
    while(it.hasNext()){
        temp = it.next();
        this->RsaSign_inport_elf_Path.insert(temp);
    }
}


