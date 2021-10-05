
/* 
 * queue.h -- public interface to the queue module
 */

#include <queue.h>                                                             
#include <stdio.h>                                                             
#include <stdlib.h>                                                            
#include <stdbool.h>                                                           
#include <string.h>                                                            
#include <inttypes.h>  



/* the queue representation is hidden from users of the module */
typedef void queue_t;


/*
 * internal representation of queue
 */
typedef struct elementstruct{
	void *data;
	struct elementstruct *next;
}element_i;

typedef struct queuestruct{
	element_i *front;
	element_i *back;

} queue_i;

//static queue_i->front=NULL;
//static queue_i->back=NULL;
// pointers to front and back
//static void *front;
//static void *back;

/* create an empty queue 
 *return the front pointer 
 */
queue_t* qopen(void){
	queue_i* rp;
	rp = (queue_i*)(malloc(sizeof(queue_i)));
	rp->front = NULL;
  rp->back = NULL; 
	return (queue_t*)rp;
}

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp){
	qp = (queue_i*)qp;
	free(qp);
}

/* put element at the end of the queue
 * returns 0 is successful; nonzero otherwise 
 */
int32_t qput(queue_t *qp, void *elementp){
	queue_i* rp;
	rp = (queue_i*) qp;
	elementp = (element_i*) elementp;
	
	//void *front;
	//void *back;

	//make element the front
	if (rp->front == NULL){
	 rp->front = elementp;
	 rp->back = elementp;
	}
	//put the element in the back
	else{
		rp -> back -> next = elementp;
		rp -> back = elementp;
	}
	return 0;

}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp){
	element_i *got;
	queue_i *rp;
	rp = (queue_i*) qp; 

	// store front in temporary pointer to return later 
	got = rp -> front;

	//make the original front equal to the orginal front element next element
	rp -> front = rp -> front -> next;

	// return the original front element through got pointer
	return (void*) got;

}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	element_i *currentElement;
	queue_i *rp;
	rp = (queue_i*) qp; 
	// make current Element equal to the specific queue's front element
	for (currentElement= rp -> front; currentElement!=NULL; currentElement=currentElement->next){
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
	element_i *p;
	bool result;
  queue_i *rp = (queue_i*) qp; 
	// for loop to go through each element in the list
	for (p = rp->front; p != NULL; p=p->next){

		//compare elements in helper function
		result = searchfn(p, skeyp);

		//stop after finding a match
		if (result){
			return (void*)p;
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
	
	element_i *p;
	element_i *prev;
	element_i *got;
  bool result;
	queue_i *rp  = (queue_i*) qp; 

	for (p = rp->front; p != NULL; p=p->next){
		result = searchfn(p, skeyp);

		//remove p if match found
		if (result){
			got=p;
			prev->next = p->next;
			return (void*)got;
		}

		// update back pointer
		prev = p;
	}
	return NULL;
}

/* concatenatenates elements of q2 into q1
 * q2 is dealocated, closed, and unusable upon completion 
 */
void qconcat(queue_t *q1p, queue_t *q2p){
	//link back of q1 to front of q2
	queue_i *r1p = (queue_i*) q1p;
	queue_i *r2p = (queue_i*) q2p; 
	r1p->back->next = r2p -> front;
	free(r2p);

}

