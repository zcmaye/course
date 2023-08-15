#include "SeqList.h"
/*
	用数组的时候：很多时候，是使用的时候自己处理越界啊..等等问题
	c++ STL  
*/
bool inc(SeqList* list)
{
	Data *ptmp = realloc(list->base, sizeof(Data) * (list->capacity+INC_SIZE));
	//assert(ptmp != NULL);
	if (ptmp == NULL)
	{
		return false;
	}
	list->base = ptmp;
	list->capacity += INC_SIZE;
	return true;
}
void initList(SeqList* list)
{
	list->capacity = INIT_SEQLIST_SIZE;
	list->size = 0;
	list->base = calloc(list->capacity, sizeof(Data));
	assert(list->base != NULL);	//断言，如果分配失败，直接中断即可
}

void push_back(SeqList* list, Data data)
{
	//此时的满，是说元素存到了容量的上限，而不是内存的上线
	//真正的满：元素到达上限，并且扩容失败
	if (list->size >= list->capacity && !inc(list))
	{
		return;
	}
	list->base[list->size] = data;	//插入数据
	list->size++;//size++
}

void push_front(SeqList* list, Data data)
{
	if (list->size >= list->capacity && !inc(list))
	{
		return;
	}
	//首先移动元素
	for (int i = list->size; i > 0; i--)
	{
		list->base[i] = list->base[i - 1];
	}
	list->base[0] = data;
	list->size++;
}

void insert(SeqList* list, int index, Data data)
{
	if (index < 0 || index >= list->capacity)
	{
		return;
	}
	if (index > list->size && index < list->capacity)
	{
		index = list->size;
	}
	for (int i = list->size; i >index; i--)
	{
		list->base[i] = list->base[i - 1];
	}
	list->base[index] = data;
	list->size++;
}

void show_list(SeqList* list)
{
	for (int i = 0; i < list->size; i++)
	{
		printf("%d ", list->base[i]);
	}
	printf("\n");
}
#if 0
void show_harem(SeqList* list)
{
	for (int i = 0; i < list->size; i++)
	{
		printf("%d %s\n", list->base[i].id, list->base[i].name);
	}
	printf("\n");
}
#endif // 0


void pop_back(SeqList* list)
{
	if (!empty(list))
	{
		list->size--;
	}	
}
void pop_front(SeqList* list)
{
	if (empty(list))
		return;
	for (int i = 0; i < list->size-1; i++)
	{
		list->base[i] = list->base[i + 1];
	}
	list->size--;
}
void erase_pos(SeqList* list, int pos)
{
	if (empty(list))
		return;
	for (int i = pos; i < list->size-1; i++)
	{
		list->base[i] = list->base[i + 1];
	}
	list->size--;
}

void erase_val(SeqList* list, Data val)
{
	if (empty(list))
		return;
	int ret = find(list, val);
	if (ret != -1)
	{
		for (int i = ret; i < list->size-1; i++)
		{
			list->base[i] = list->base[i + 1];
		}
		list->size--;
	}
}
int size(SeqList* list)
{
	return list->size;
}
bool empty(SeqList* list)
{
	return list->size==0;
}
int find(SeqList* list, Data val)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->base[i] == val)
		{
			return i;
		}
	}
	return -1;
}
void sort(SeqList* list)
{
	for (int i = 0; i < list->size-1; i++)
	{
		for (int k = 0; k < list->size-i-1; k++)
		{
			if (list->base[k] > list->base[k + 1])
			{
				Data t = list->base[k];
				list->base[k] = list->base[k + 1];
				list->base[k + 1] = t;
			}
		}
	}
}
void reverse(SeqList* list)
{
	for (int i = 0; i < list->size/2; i++)
	{
		Data t = list->base[i];
		list->base[i] = list->base[list->size -i - 1];
		list->base[list->size - i - 1] = t;
	}
}
void clear(SeqList* list)
{
	list->size = 0;
	free(list->base);
	list->base = NULL;
}