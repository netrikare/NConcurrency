#include "NQueue.h"
#include <string.h>

namespace NConcurrency{

NQueue::NQueue() : isFinished(0), size(0){

	first = last = NULL;
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
}

NQueue::~NQueue(){

	pthread_mutex_lock(&lock);

	NNode *n = first;
	while(n!=NULL){
		first = first->next;
		delete n;
	}

	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
}

int NQueue::isEmpty(){
	return size == 0;
}

void NQueue::add(NTask *task){

	pthread_mutex_lock(&lock);

	NNode *n = new NNode();
	n->task = task;

	if(first == NULL){
		first = last = n;
	}else{
		n->prev = last;
		last->next = n;
		last = n;
	}
	size++;

	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}

NNode* NQueue::remove(NTask *task){

	pthread_mutex_lock(&lock);

	while(isEmpty() && !isFinished)
		pthread_cond_wait(&cond, &lock);

	NNode *n = first;
	for(; n != last; n = n->next){
		if(n->task == task)	{
			n->next->prev = n->prev;
			n->prev->next = n->next;
			break;
		}
	}
	size--;

	pthread_mutex_unlock(&lock);
	return n;
}

NNode* NQueue::remove(int index){

	pthread_mutex_lock(&lock);

	while(isEmpty() && !isFinished)
		pthread_cond_wait(&cond, &lock);

	NNode *n = first;
	for(int i=0;i<index;i++)
		n = n->next;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	size--;

	pthread_mutex_unlock(&lock);
	return n;
}

NNode* NQueue::removeFirst(){

	pthread_mutex_lock(&lock);

	while(isEmpty() && !isFinished)
		pthread_cond_wait(&cond, &lock);

	//FIFO
	NNode *n = first;
	if(first != NULL){
		first = first->next;
		size--;
	}

	pthread_mutex_unlock(&lock);
	return n;
}

void NQueue::abortWaiting(){
	isFinished = 1;
	pthread_cond_broadcast(&cond);
}

std::ostream & operator<< (std::ostream &out, const NQueue &q){

	for(NNode *n = q.first; n!= q.last && n!= NULL; n=n->next)
		out << "ID: " << n->task->getId() ;

	return out;
}

}
