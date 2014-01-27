#ifndef NQueue_HPP_
#define NQueue_HPP_

#include "NTask.h"
#include <iostream>

namespace NConcurrency{

class NNode{

public:
	NNode *prev;
	NNode *next;
	NTask *task;
};

class NQueue{

	pthread_mutex_t lock;
	pthread_cond_t cond;
	int isFinished;
	int size;

public:
	NNode *last;
	NNode *first;

	NQueue();
	~NQueue();
	int isEmpty();
	void add(NTask *task);
	NNode* remove(NTask *task);
	NNode* remove(int index);
	NNode* removeFirst();
	void abortWaiting();

	friend std::ostream & operator<< (std::ostream &out, const NQueue &s);
};

}

#endif /* NQueue_HPP_ */
