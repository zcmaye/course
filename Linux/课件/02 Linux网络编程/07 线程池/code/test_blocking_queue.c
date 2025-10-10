#include "BlockingQueue.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct State{
	BlockingQueue* que;
}State;

void state_init(State* state)
{
	state->que = bque_create(5);
}
void state_destroy(State* state)
{
	pthread_mutex_destroy(&state->mutex);
}

void* thr_fn_producer(void* arg)
{
	State* state = (State*)arg;
	int v = 0;
	while(true) {
		usleep(100 * 1000);

		bque_push(state->que,v);
		printf("producer value is %d\n",v);
		v++;
	}
	return NULL;
}

void* thr_fn_customer(void* arg)
{
	State* state = (State*)arg;
	while(true) {
		usleep(500 * 1000);

		Data v;
		if(bque_pop_front(state->que,&v)){
			printf("customer value is %d\n",(int)v);
		}
	}
	return NULL;
}

int main(){
	State state;
	state_init(&state);

	pthread_t producer,customer;
	pthread_create(&producer,NULL,thr_fn_producer,&state);
	pthread_create(&customer,NULL,thr_fn_customer,&state);
	
	pthread_join(producer,NULL);
	pthread_join(customer,NULL);

	state_destroy(&state);
	return 0;
}
