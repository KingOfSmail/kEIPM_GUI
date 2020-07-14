#ifndef QFILESYSTEMMODELIMPL_H
#define QFILESYSTEMMODELIMPL_H

#include <QFileSystemModel>
#include <QAbstractItemModel>
#include <QSet>
#include <QtWidgets/QTreeView>

class QFileSystemModelImpl : public QFileSystemModel
{
public:
    QFileSystemModelImpl(QTreeView *treeView);

    QSet<QString> getSelectedFiles() const;

private:
    int columnCount(const QModelIndex &parent) const
    {
        (void)parent;
        return 1;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData( const QModelIndex &index, const QVariant &value, int role);

    mutable QMap<QModelIndex,bool> m_indexMap;
    QTreeView *m_treeView;

};

#endif // QFILESYSTEMMODELIMPL_H
