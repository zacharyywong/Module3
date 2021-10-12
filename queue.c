
/* 
 * queue.c -- create a reusable queue module //
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
	void *data; // an elementstruct 
	//	void *data2;
	//void *data3;
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

	
 	element_i* elementp_i;
	element_i* elementp_t;
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
	//fillDataArr(elementp_i, elementp_t

	
	// need to allocate memory for the actual element object that is going into the queue

	//elementp_i = (element_i*) elementp;


	
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
	elementp_i->data = elementp_t;
	elementp_i->next = NULL;
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
	 if (rp->front == NULL){
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
	
	return got->data;

}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	//	if (qp==NULL){
	//	printf("queue is NULL");
	//	return;
	//}
	element_i* currentElement;
	void* currentElementV; 
	queue_i *rp;
	rp = (queue_i*) qp;
	printf("outside of for loop of qapply\n\n");
	// make current Element equal to the specific queue's front element
	if(rp->front == NULL) printf("rp -> front is NULL\n\n");
	currentElement= rp -> front;
	while (currentElement!=NULL){
		//printf("currentElement %s = \n\n",currentElement->data);
		currentElementV = currentElement->data;
		if (currentElementV == NULL){
			//			printf("element in queue supposed to be null %s", currentElement);
			printf("warning: entered for loop but element is NULL! \n\n");
		}
		printf("element being applied to function... \n\n");
		fn(currentElementV);
		currentElement=currentElement->next;
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
/*
static bool searchfn(void* elementp, const void* keyp){
	element_i* elementp_i = NULL;
	element_i* elementp_t = NULL;
	element_i* elementp_i1 = NULL;
	element_i* elementp_k = NULL;

	// put the element and key into two different element structs and fill in the element struct's data accordingly
	elementp_t = (element_i*) elementp;
	elementp_i1 = (element_i*)keyp;
	
	elementp_i->data = elementp_t;
	elementp_k->data = elementp_i1;
	
	
  // compare addresses of the two elements                                                
  if(elementp_i -> data  == elementp_k -> data){                                                           
    return(true);                                                                       
  }else{                                                                                
    return(false);                                                                      
  }                                                                                      
} 
*/
/*static bool searchfn(void* elementp, const void* keyp){                        
                                                                                
// compare the two elements                                                     
   if(elementp == keyp){                                                        
     return(true);                                                              
     }else{                                                                                                                                               
    return(false);                                                              
   }                                                                            
	 } */  
void* qsearch(queue_t *qp, 
							bool (*searchfn)(void* elementp,const void* keyp),
							const void* skeyp){
	element_i *p;
	//	element_i *p_i;
	bool result;
  queue_i *rp = (queue_i*) qp; 
	// for loop to go through each element in the list
	for (p = rp->front; p != NULL; p=p->next){
		//put in the data of the current element, skeyp should only be the data already
		//p_i->data = p->data;
		//compare elements in helper function
		result = searchfn(p->data, skeyp);

		//stop after finding a match
		if (result){
			return (void*)p->data;
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
		result = searchfn(p->data, skeyp);

		//remove p if match found
		if (result){
			got=p;
			//check if p is front 
			if (p == rp->front){	
			rp ->front = p->next;
			}
			else{
				prev ->next = p ->next;
			}
			return (void*)got->data;
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

