#ifndef SCONTACTSLISTVIEW_H_
#define SCONTACTSLISTVIEW_H_

#include <QListView>

class ContactsInfo;
class QStandardItemModel;
class SContactsListView :public QListView
{
	Q_OBJECT
public:
	explicit SContactsListView(QWidget* parent = nullptr);
	void init();
protected:
	bool viewportEvent(QEvent* event) override;
private:
	QStandardItemModel* m_model;
	QList<ContactsInfo*> m_infos;
};
#endif // !SCONTACTSLISTVIEW_H_
