#include "NQueue.h"
#include "NExecutor.h"
#include "NCountDownLatch.h"
#include "Util.h"

#include <iostream>
#include <unistd.h>

using namespace std;
using namespace NConcurrency;

class MyTask : public NTask{

public:
	MyTask() : NTask(){}
	MyTask(long id) : NTask(id) {}
	~MyTask(){}

	void *run(){
		long id = getId();
		printf("Task %ld run(), sleeping %ld s.\n", id, id);
		sleep(id);
	}
};

void test1(){
	printf("%s\n", "Testing NExecutor");
	NExecutor *ex = new NExecutor(3);
	ex->start();
	printf("%s\n", "Executor started");

	int th1Count = 4;
	int th2Count = 10;
	int i;

	MyTask **th1 = new MyTask*[th1Count];
	for(i=0;i<th1Count;i++){
		MyTask *t = new MyTask(i);
		th1[i] = t;
		ex->submit(t);
	}

	sleep(3);

	MyTask **th2 = new MyTask*[th2Count];
	for(i=0;i<th2Count;i++){
		NTask *t = new MyTask(i);
		th2[i] = (MyTask*)t;
		ex->submit(t);
	}

	printf("%s\n", "Tasks submitted, waiting for them to finish...");
	ex->stop();
	printf("%s\n", "Executor stopped");

	for(i=0;i<th1Count;i++)		delete th1[i];
	delete [] th1;
	for(i=0;i<th2Count;i++)		delete th2[i];
	delete [] th2;

	delete ex;

	//printMemoryLeaks();
}

class MyTask2 : public NTask{
public:
	MyTask2(long id): NTask(id) {}
	~MyTask2(){

	}
	void *run(){
		long id = getId();
		printf("Task %ld run(), sleeping %ld s.\n", id, id);
		sleep(id);
		int *d = new int(3);
		return d;
	}
};

void test2(){
	printf("%s\n", "Testing NExecutor");
	NExecutor *ex = new NExecutor(3);
	ex->start();
	printf("%s\n", "Executor started");
	MyTask2 *t = new MyTask2(2);
	ex->submit(t);

	printf("Task %ld submitted\n", t->getId());
	printf("%s\n", "Waiting for task completion");

	sleep(5);
	printf("Task %ld getting result\n", t->getId());
	int *result = (int*)t->getResult();
	printf("Task %ld result: %d\n", t->getId(), *result);

	ex->stop();

	delete result;
	delete t;
	delete ex;

	//printMemoryLeaks();
}

int main() {

	test1();
	test2();

	pthread_exit(NULL);
	return 0;
}
