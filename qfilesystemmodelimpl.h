#ifndef QFILESYSTEMMODELIMPL_H
#define QFILESYSTEMMODELIMPL_H

#include <QFileSystemModel>
#include <QSet>
#include <QAbstractItemModel>

class QFileSystemModelImpl : public QFileSystemModel
{
public:
    QFileSystemModelImpl();


    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role);
    bool setData( const QModelIndex &index, const QVariant &value, int role);

    void setFileCheckState(QString filePath,QVariant value);

    mutable QMap<QModelIndex,bool> m_indexMap;
    QSet<QString> m_checkedFileList;
};

#endif // QFILESYSTEMMODELIMPL_H
