#ifndef QFILESYSTEMMODELIMPL_H
#define QFILESYSTEMMODELIMPL_H

#include <QFileSystemModel>
#include <QAbstractItemModel>
#include <QSet>

class QFileSystemModelImpl : public QFileSystemModel
{
public:
    QFileSystemModelImpl();

    const QSet<QString> &getSelectedFiles();

private:
    int columnCount(const QModelIndex &parent) const
    {
        (void)parent;
        return 1;
    }


    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData( const QModelIndex &index, const QVariant &value, int role);

    void setFileCheckState(QString filePath,QVariant value);

    mutable QMap<QModelIndex,bool> m_indexMap;
    QSet<QString> elf_Path;
    QSet<QString> getElf_Path() const;
};

#endif // QFILESYSTEMMODELIMPL_H
