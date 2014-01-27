#ifndef NCOUNTDOWNLATCH_HPP_
#define NCOUNTDOWNLATCH_HPP_

#include <pthread.h>

namespace NConcurrency{

class NCountDownLatch{

	volatile int count;
	pthread_mutex_t mutex;
	pthread_cond_t cond;

public:
	NCountDownLatch(int count);
	~NCountDownLatch();

	void countDown();
	void await();
	int getCount();
};

}

#endif /* NCOUNTDOWNLATCH_HPP_ */
