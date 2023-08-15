#include<QApplication>
#include"SContactsListView.h"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	SContactsListView w;
	w.show();



	return a.exec();
}