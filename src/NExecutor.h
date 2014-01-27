#ifndef NEXECUTOR_HPP_
#define NEXECUTOR_HPP_

#include "NQueue.h"
#include "NTask.h"

namespace NConcurrency{

class NExecutor{

	pthread_t *thId;
	int threadCount;
	NQueue *q;

public:
	NExecutor(int threadCount);
	~NExecutor();

	void start();
	void stop();
	void submit(NTask *task);

	friend void *executorThreadFunction(void *pNExecutor);
};

}

#endif /* NEXECUTOR_HPP_ */
