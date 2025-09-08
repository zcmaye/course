#include <stdbool.h>

typedef void* Data;
typedef struct Queue Queue;

//初始化队列
Queue* que_create(int capacity);
bool que_init(Queue* que,int capacity);
//销毁队列
void que_destroy(Queue* que);
//队列队列容量
int que_capacity(Queue* que);
//队列元素数量
int que_size(Queue* que);
//队列是否为空
bool que_isEmpty(Queue*que);
//队列是否已满
bool que_isFull(Queue*que);
//入队
bool que_push(Queue*que,Data value);
//出队
bool que_pop(Queue*que);
//队头元素
Data* que_front(Queue*que);
