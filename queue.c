#pragma once
/* 
 * queue.h -- public interface to the queue module
 */

#include <queue.h>                                                             
#include <stdio.h>                                                             
#include <stdlib.h>                                                            
#include <stdbool.h>                                                           
#include <string.h>                                                            
#include <inttypes.h>  

static void *front=NULL;
static void *back=NULL;
/* the queue representation is hidden from users of the module */
typedef void queue_t{
//int size = 0;
	//pointers to front and back 
   void* front;
   void* back;
}

//struct queue{
//	void *front;
//	void *back;

//} queue_t;
// pointers to front and back
//static void *front;
//static void *back;

/* create an empty queue 
 *return the front pointer 
 */
queue_t* qopen(void){
	front = NULL;
  back = NULL; 
	return front;
}

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp){
	free(qp);
}

/* put element at the end of the queue
 * returns 0 is successful; nonzero otherwise 
 */
int32_t qput(queue_t *qp, void *elementp){

	//void *front;
	//void *back;

	//make element the front
	if (qp == NULL){
	 qp->front = elementp;
	 qp -> back = elementp;
	}
	//put the element in the back
	else{
		qp -> back -> next = elementp;
		qp -> back = elementp;
	}
	return 0;

}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
	void *got;

	// store front in temporary pointer to return later 
	got = qp -> front;

	//make the original front equal to the orginal front element next element
	qp -> front = qp -> front -> next;

	// return the original front element through got pointer
	return *got;

}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	void *currentElement;

	// make current Element equal to the specific queue's front element
	for (currentElement= qp -> front; currentElement!=NULL; currentElement=currentElement->next){
		fn(currentElement);
	}

}

/* search a queue using a supplied boolean function
 * skeyp -- a key to search for
 * searchfn -- a function applied to every element of the queue
 *          -- elementp - a pointer to an element
 *          -- keyp - the key being searched for (i.e. will be 
 *             set to skey at each step of the search
 *          -- returns TRUE or FALSE as defined in bool.h
 * returns a pointer to an element, or NULL if not found
 */
//static bool searchfn(void* elementp, const void* keyp){

	// compare addresses of the two elements 
//	if(elementp == keyp){
//		return(TRUE);
//	}else{
//		return(FALSE);
//	}
//}

void* qsearch(queue_t *qp, 
							bool (*searchfn)(void* elementp,const void* keyp),
							const void* skeyp){
	void *p;
	bool result;

	// for loop to go through each element in the list
	for (p = qp->front; p != NULL; p=p->next){

		//compare elements in helper function
		result = searchfn(p, skeyp);

		//stop after finding a match
		if (result){
			return *p;
		}
	}
	//if no match in the whole list 
	return NULL;

}

/* search a queue using a supplied boolean function (as in qsearch),
 * removes the element from the queue and returns a pointer to it or
 * NULL if not found
 */
void* qremove(queue_t *qp,
							bool (*searchfn)(void* elementp,const void* keyp),
							const void* skeyp){
	
	void *p;
	void *back;
	void *got;
  bool result;

	for (p = qp->front; p != NULL; p=p->next){
		result = searchfn(p, skeyp);

		//remove p if match found
		if (result){
			got=p;
			back->next = p->next;
			return got;
		}

		// update back pointer
		back = p;
	}
	return NULL;
}

/* concatenatenates elements of q2 into q1
 * q2 is dealocated, closed, and unusable upon completion 
 */
void qconcat(queue_t *q1p, queue_t *q2p){
	//link back of q1 to front of q2
	q1p->back->next = q2p -> front;
	free(q2p);

}

