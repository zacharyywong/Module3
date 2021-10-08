
/* 
 * queue.c -- public interface to the queue module
 */

#include <queue.h>                                                             
#include <stdio.h>                                                             
#include <stdlib.h>                                                            
#include <stdbool.h>                                                           
#include <string.h>                                                            
#include <inttypes.h>  

//#define DEBUG
/* the queue representation is hidden from users of the module */
typedef void queue_t;

//#define COUNT 3

/*
 * internal representation of queue
 */
typedef struct elementstruct{
	void *data1;
	void *data2;
	void *data3;
	//void *arr[COUNT];
	//for (int i = 0; i < COUNT; i++){
	//	*arr[i] = data;
	//}
	struct elementstruct* next;
} element_i;

typedef struct queuestruct{
	element_i *front;
	element_i *back;

} queue_i;



/* create an empty queue 
 *return the front pointer 
 */
queue_t* qopen(void){
	queue_i *rp;
	rp = (queue_i*)(malloc(sizeof(queue_i)));
	rp->front = NULL;
  rp->back = NULL;
	return (queue_t*)rp;
}

#ifdef DEBUG
typedef struct person{
	char name[10];
	int age;
	int gradYear;
  printf("print person in queue.c: name %s, age %d, gradyear %d", name, age, gradYear);
} person_t;
#endif
	

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp){
	qp = (queue_i*)qp;
	free(qp);
}

/*
static void fillDataArr(element_i *elementp_i, element_i *elementp_t){
	for (int i = 0; i < COUNT; i++){
		elementp_i -> arr[i] = elementp_t -> arr[i];
	}
}
*/
/* put element at the end of the queue
 * returns 0 is successful; nonzero otherwise 
 */
int32_t qput(queue_t *qp, void *elementp){
  queue_i* rp;
	rp = (queue_i*) qp;
<<<<<<< HEAD

 	element_i* elementp_i;
	element_i* elementp_t=NULL;
	//	element_i *elementp_t; 
	//	element_i *elementp_t;
	//	elementp = 0;
	//elementp = NULL;
	//	elementp_i = (element_i*) elementp;
	//elementp_i  = (element_i*)elementp;
	//adjustStruct(elementp)
	elementp_i = (element_i*)malloc(sizeof(element_i));
	elementp_t = (element_i*)elementp;
	
	// fill in data
	//fillDataArr(elementp_i, elementp_t);
=======
	element_i* elementp_i;
	
	// need to allocate memory for the actual element object that is going into the queue
	elementp_i = (element_i*)(malloc(sizeof(elementp)));
	//elementp_i = (element_i*) elementp;
	elementp_i = elementp;
>>>>>>> 458c85372ccf74983db43fb9a59e6d2565ad26bf
	
	/*
	//copy array into new array of size 2 times greater, free old array, nd 
	while (elementp_t->arr[COUNT+1] !=NULL){
		COUNT = COUNT * 2;
		elementp_i = (element_i*)malloc(sizeof(element_i));
		elementp_t = (element_i*)elementp;
		fillDataArr(elementp_i, elementp_t);
	}
	*/
	//	elementp_i ->arr[i] = elementp_t ->arr[i];
	elementp_i ->data1 = elementp_t ->data1;
	elementp_i ->data2 = elementp_t ->data2;
	elementp_i ->data3 = elementp_t ->data3;
	elementp_i ->next = NULL;
	//elementp_t = elementp_i;
	
	//elementp_t ->data = elementp_i->data;
	//elementp_t ->next = NULL;
	//elementp_i ->next = NULL;
	//elementp_t = elementp_i;
	//	elementp_i = (element_i*)malloc(sizeof(element_i));
	//	elementp_i ->next = NULL;
	//void *front;
	//void *back;

	//make element the front
	 if (rp->front == NULL && rp ->back ==NULL){
			//elementp_i ->next = NULL;
	//printf("front of list \n");
	  	rp->front = elementp_i;
		 rp->back = elementp_i;
		//		elementp_t ->data = elementp_i->data;
 		//elementp_t ->next = elementp_i->next;  
		//rp->back->next = NULL;
		//rp -> front -> next = NULL;
	 	}
	//put the element in the back
	
	else{
		//printf("back of list \n");
		//rp -> back = (element_i*)malloc(sizeof(element_i));
		rp -> back -> next = elementp_i;
		rp -> back = elementp_i;
		//		rp ->back ->data = elementp_i ->data;
		
		//rp -> back = elementp_i ->next;
		//		rp -> back -> next= NULL;
	}
	//	printf("testing in qput, %
	//free(elementp_i);
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
	element_i* currentElement;
	queue_i *rp;
	rp = (queue_i*) qp;
	// make current Element equal to the specific queue's front element
	for (currentElement= rp -> front; currentElement!=NULL; currentElement=currentElement->next){
		fn((void*)currentElement);
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

