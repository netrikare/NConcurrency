#include "NTask.h"
#include <stdlib.h>
#include <stdio.h>

namespace NConcurrency{

NTask::NTask() : done(0), result(NULL), id(rand()) {
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
}

NTask::NTask(long id) : done(0), result(NULL), id(id) {
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
}

NTask::~NTask() {
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	//printf("Task %ld ~NTask\n", id);
}

long NTask::getId(){
	return id;
}

int NTask::isDone(){
	return done == 1;
}

void NTask::execute(){
	result = run();
	done = 1;

	pthread_cond_broadcast(&cond);
}

void * NTask::getResult(){

	pthread_mutex_lock(&mutex);
	while(done != 1)
		pthread_cond_wait(&cond, &mutex);

	pthread_mutex_unlock(&mutex);

	return result;
}

}
