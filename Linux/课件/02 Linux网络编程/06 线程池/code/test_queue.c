#include "Queue.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct State{
	pthread_mutex_t mutex;
	pthread_cond_t not_empty;
	pthread_cond_t not_full;
	Queue* que;
}State;

void state_init(State* state)
{
	pthread_mutex_init(&state->mutex,NULL);
	pthread_cond_init(&state->not_empty,NULL);
	pthread_cond_init(&state->not_full,NULL);
	state->que = que_create(5);
}
void state_destroy(State* state)
{
	que_destroy(state->que);
	pthread_mutex_destroy(&state->mutex);
	pthread_cond_destroy(&state->not_empty);
	pthread_cond_destroy(&state->not_full);
}

void* thr_fn_producer(void* arg)
{
	State* state = (State*)arg;
	int v = 0;
	while(true) {
		usleep(100 * 1000);
		pthread_mutex_lock(&state->mutex);
		while(que_isFull(state->que)) {
			printf("producer wait~\n");
			pthread_cond_wait(&state->not_full,&state->mutex);	
		}

		
		que_push(state->que,v);
		printf("producer value is %d\n",v);
		v++;

		pthread_cond_signal(&state->not_empty);
		pthread_mutex_unlock(&state->mutex);
	}
	return NULL;
}

void* thr_fn_customer(void* arg)
{
	State* state = (State*)arg;
	while(true) {
		usleep(500 * 1000);
		pthread_mutex_lock(&state->mutex);
		while(que_isEmpty(state->que)) {
			printf("customer wait~\n");
			pthread_cond_wait(&state->not_empty,&state->mutex);	
		}
		int*v =  que_front(state->que);
		if(v) {
			printf("customer value is %d\n",*v);
			que_pop(state->que);
		}

		pthread_cond_signal(&state->not_full);
		pthread_mutex_unlock(&state->mutex);
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
