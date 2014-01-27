#include "NQueue.h"
#include "NExecutor.h"
#include "NCountDownLatch.h"
#include "Util.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace NConcurrency;

NCountDownLatch *ncdl;

void *thFun(void *p){
	long id = (long)p;
	sleep(id);
	printf("Task %ld countDown(), getCount=%d\n", id, ncdl->getCount());

	ncdl->countDown();
	//ncdl->await();
	printf("Task %ld end\n", id);
	pthread_exit(NULL);
}

void test(){
	printf("%s\n","Testing NCountdownLatch");
	int count=5;

	ncdl = new NCountDownLatch(count);
	pthread_t th[count];
	for(int i=0;i<count;i++)
		pthread_create(&th[i], NULL, &thFun, (void *)(long)i);

	printf("%s\n","Main awaiting...");
	ncdl->await();
	printf("%s\n","Main joining...");

	for(int i=0;i<count;i++)
		pthread_join(th[i], NULL);

	delete ncdl;
}

int main() {

	test();

	pthread_exit(NULL);
	return 0;
}
