/*头文件*/
#ifndef CHECKBOXITEMDELEGATE_H
#define CHECKBOXITEMDELEGATE_H

#include <QObject>
#include <QCheckBox>
#include <QStyledItemDelegate>

class SItemCheckDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SItemCheckDelegate(QWidget* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
signals:
    void signalClicked(const QModelIndex& index);
};

#endif // CHECKBOXITEMDELEGATE_H

