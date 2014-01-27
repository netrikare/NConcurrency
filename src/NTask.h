#ifndef NTASK_HPP_
#define NTASK_HPP_

#include <pthread.h>

namespace NConcurrency{

class NTask{

	int done;
	void *result;

	pthread_mutex_t mutex;
	pthread_cond_t cond;

	void execute();

protected:
	long id;

public:

	NTask();
	NTask(long id);
	virtual ~NTask();

	long getId();
	int isDone();
	void * getResult();


	virtual void *run()=0;

	friend void *executorThreadFunction(void *pNExecutor);
};

}
#endif /* NTASK_HPP_ */
