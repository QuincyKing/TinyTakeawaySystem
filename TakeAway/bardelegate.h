#ifndef BARDELEGATE
#define BARDELEGATE

#include "prerequisite.h"

class BarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BarDelegate(QObject *parent = 0);

    QWidget *createEditor( QWidget *parent,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index ) const;
    void setEditorData( QWidget *editor,
                                 const QModelIndex &index ) const;
    void setModelData( QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index ) const;
    void updateEditorGeometry( QWidget *editor,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index ) const;

};

#endif // BARDELEGATE

