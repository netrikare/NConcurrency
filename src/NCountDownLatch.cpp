#include "NCountDownLatch.h"

namespace NConcurrency{

NCountDownLatch::NCountDownLatch(int count) : count(count){
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
}

NCountDownLatch::~NCountDownLatch(){
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

void NCountDownLatch::countDown(){
	pthread_mutex_lock(&mutex);

	count--;
	if(count == 0)
		pthread_cond_broadcast(&cond);

	pthread_mutex_unlock(&mutex);
}

void NCountDownLatch::await(){
	pthread_mutex_lock(&mutex);

	while(count > 0)
		pthread_cond_wait(&cond, &mutex);

	pthread_mutex_unlock(&mutex);
}

int NCountDownLatch::getCount(){
	return count;
}

}
