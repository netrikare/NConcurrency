#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <stdio.h>
#include <stdlib.h>

volatile static int newCounter = 0;
volatile static int delCounter = 0;

/*
 * Uncomment this to enable global object creation/deletion counting
 */

/*
void* operator new(size_t size) {
	newCounter++;
	void* wsk = malloc(size);
	//printf("COUNTER new %d size %d address %d\n", newCounter, size, wsk);
	return wsk;
}
void operator delete(void* wsk) {
	delCounter++;
	//printf("COUNTER del %d address %d\n", delCounter, wsk);
	free(wsk);
}
void* operator new[](size_t size) {
	newCounter++;
	void* wsk = malloc(size);
	//printf("COUNTER new[] %d size %d address %d\n", newCounter, size, wsk);
	return wsk;
}
void operator delete[](void* wsk) {
	delCounter++;
	//printf("COUNTER del[] %d address %d\n", delCounter, sizeof(wsk));
	free(wsk);
}
*/

int leaksCount(){
	return !(newCounter == delCounter);
}

void printMemoryLeaks(){
	printf("Memory leaks count: %d\n", leaksCount());
}

#endif /* UTIL_HPP_ */
