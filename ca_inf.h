#ifndef CA_INF_H
#define CA_INF_H

#include <QString>

class CA_inf
{
public:
    CA_inf();

    QString getCommon_name() const;
    void setCommon_name(const QString &value);

    QString getOrg_name() const;
    void setOrg_name(const QString &value);

    QString getLocal() const;
    void setLocal(const QString &value);

    QString getState() const;
    void setState(const QString &value);

    QString getCountry() const;
    void setCountry(const QString &value);

    QString getCA_Path() const;
    void setCA_Path(const QString &value);

    QString getElf_Path() const;
    void setElf_Path(const QString &value);

    QString getPublic_Rsa_Path() const;
    void setPublic_Rsa_Path(const QString &value);

private:
    QString Common_name;
    QString Org_name;
    QString Local;
    QString State;
    QString Country;

    QString Public_Rsa_Path;
    QString CA_Path;
    QString elf_Path;
};

#endif // CA_INF_H
