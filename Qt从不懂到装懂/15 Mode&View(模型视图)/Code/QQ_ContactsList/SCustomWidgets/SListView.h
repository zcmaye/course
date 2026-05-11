#ifndef SLISTVIEW_H_
#define SLISTVIEW_H_

#include <QListView>

class QStandardItemModel;
class SListView 
	: public QListView
{
	Q_OBJECT
public:
	explicit SListView(QWidget* parent = nullptr);
protected:
	bool viewportEvent(QEvent* event) override;
signals:
	void hoveredRole(const QModelIndex& index, int role);
	void pressedRole(const QModelIndex& index, int role);
};
#endif // !SLISTVIEW_H_
