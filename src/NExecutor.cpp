#include "NExecutor.h"

namespace NConcurrency{

NExecutor::NExecutor(int threadCount) : threadCount(threadCount){
	thId = new pthread_t[threadCount];
	q = new NQueue();
}

NExecutor::~NExecutor(){
	delete q;
	delete [] thId;
}

void *executorThreadFunction(void *pNExecutor);
void NExecutor::start(){

	for(int i=0;i<threadCount;i++)
		pthread_create(&thId[i], NULL, &executorThreadFunction, this);
}

void NExecutor::stop(){
	q->abortWaiting();

	for(int i=0;i<threadCount;i++)
		pthread_join(thId[i], NULL);

}

void NExecutor::submit(NTask *task){
	q->add(task);
}

void *executorThreadFunction(void *pNExecutor){
	NExecutor *ex = (NExecutor *)pNExecutor;

	NNode *n = ex->q->removeFirst();
	while(n!=NULL){
			NTask *t = (NTask *)n->task;
			if(t != NULL) //task could be deleted in between addition to queue and execution, so check here
				t->execute();
			delete n;
			n = ex->q->removeFirst();
	}

	return NULL;
}

}
