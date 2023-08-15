#include"SeqList.h"
int main()
{
	SeqList list;
	initList(&list);

	for (int i = 0; i < 5; i++)
	{
		Harem maye = { 1001+i,"Å¥îÜÂ»ÊÏ¡¤maye" };
		push_back(&list, maye);
	}

	show_harem(&list);


	return 0;
}