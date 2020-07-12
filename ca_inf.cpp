#include "ca_inf.h"

CA_inf::CA_inf()
{

}

QString CA_inf::getCommon_name() const
{
    return Common_name;
}

void CA_inf::setCommon_name(const QString &value)
{
    Common_name = value;
}

QString CA_inf::getOrg_name() const
{
    return Org_name;
}

void CA_inf::setOrg_name(const QString &value)
{
    Org_name = value;
}

QString CA_inf::getLocal() const
{
    return Local;
}

void CA_inf::setLocal(const QString &value)
{
    Local = value;
}

QString CA_inf::getState() const
{
    return State;
}

void CA_inf::setState(const QString &value)
{
    State = value;
}

QString CA_inf::getCountry() const
{
    return Country;
}

void CA_inf::setCountry(const QString &value)
{
    Country = value;
}

QString CA_inf::getCA_Path() const
{
    return CA_Path;
}

void CA_inf::setCA_Path(const QString &value)
{
    CA_Path = value;
}

QString CA_inf::getElf_Path() const
{
    return elf_Path;
}

void CA_inf::setElf_Path(const QString &value)
{
    elf_Path = value;
}

QString CA_inf::getPublic_Rsa_Path() const
{
    return Public_Rsa_Path;
}

void CA_inf::setPublic_Rsa_Path(const QString &value)
{
    Public_Rsa_Path = value;
}
