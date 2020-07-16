#include "qfilesystemmodelimpl.h"

QFileSystemModelImpl::QFileSystemModelImpl(QTreeView *treeView)
    : QFileSystemModel(),
      m_treeView(treeView)
{
}

Qt::ItemFlags QFileSystemModelImpl::flags(const QModelIndex &index) const
{
    return Qt::ItemIsUserCheckable|QFileSystemModel::flags(index);
}

QVariant QFileSystemModelImpl::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if (index.column() == 0 && role == Qt::CheckStateRole)
        {
            if (m_indexMap.contains(index))
            {
                return m_indexMap[index] ? Qt::Checked : Qt::Unchecked;
            }
            else
            {
                int iChecked = Qt::Unchecked;
                QModelIndex _parentIndex = index.parent();

                //check if this node's parent is checked
                while(_parentIndex.isValid())
                {
                    if (m_indexMap[_parentIndex])
                    {
                        iChecked = Qt::Checked;
                        break;
                    }
                    else
                    {
                        _parentIndex = _parentIndex.parent();
                    }
                }

                if (iChecked == Qt::Checked)
                {
                    m_indexMap[index] = true;
                    m_pathMap[filePath((index))] = true;
                    if(hasChildren(index) && rowCount(index) == 0){
                        m_treeView->expand(index);
                    }
                }
                else
                {
                    m_indexMap[index] = false;
                    m_pathMap[filePath((index))] = false;
                }

                return iChecked;
            }
        }

        return QFileSystemModel::data(index, role);

}

bool QFileSystemModelImpl::setData( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/ )
{
    if(hasChildren(index) && rowCount(index) == 0){
        m_treeView->expand(index);
    }
    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        if (value == Qt::Unchecked)
        {
            m_indexMap[index] = false;
            m_pathMap[filePath((index))] = false;
            //refresh it's child node
            emit dataChanged(index, index);
        }
        else if (value == Qt::Checked)
        {
            m_indexMap[index] = true;
            m_pathMap[filePath((index))] = true;
            //refresh it's child node
            emit dataChanged(index, index);
        }

        if (hasChildren(index))
        {
            QString strFilePath = filePath(index);

            int iChildCount = rowCount(index);

            if (iChildCount > 0)
            {
                for (int i = 0; i < iChildCount; i++)
                {
                    QModelIndex _child = this->index(i, 0, index);
                    setData(_child, value,Qt::CheckStateRole);
                }
            }
        }
    }

    return QFileSystemModel::setData(index, value, role);
}

QSet<QString> QFileSystemModelImpl::getSelectedFiles() const
{
    QSet<QString> ret;
    QMap<QString,bool>::const_iterator it = m_pathMap.constBegin();
    for(;it!=m_pathMap.constEnd(); ++it) {
        if (it.value()) {
            ret.insert(it.key());
        }
    }
    return ret;
}
