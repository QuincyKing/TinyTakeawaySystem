#include "bardelegate.h"

BarDelegate::BarDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *BarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);


    QSpinBox *spinBox = new QSpinBox(parent);
    spinBox->setRange( 0, 100 );
    spinBox->installEventFilter( const_cast<BarDelegate*>(this) );
    return spinBox;
}

void BarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data( index, Qt::EditRole ).toInt();
    static_cast<QSpinBox*>( editor )->setValue( value );
}

void BarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData( index, static_cast<QSpinBox*>( editor )->value(), Qt::EditRole);
}

void BarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry( option.rect );
}
