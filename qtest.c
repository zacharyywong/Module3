/* qtest.c --- 
 * 
 * 
 * Author: Zachary J. Wong
 * Created: Mon Oct  4 22:10:36 2021 (-0400)
 * Version: 
 * 
 * Description: A test of queue.c 
 * 
 */

#define MAXREG 10

#include <queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>


typedef struct person {                                                       
  char name[MAXREG];                                                   
  int age;                                                               
  int gradYear;                                                                   
} person_t;


person_t* make_person(char* name, int age, int gradYear){
	person_t* pp;

	pp=(person_t*)malloc(sizeof(person_t));
	// fail case
	if (pp == NULL){

		//print to stderr file
		fprintf(stderr, "[Error: malloc failed allocating person]\n");
		return NULL;
	}
	//fill in data
	
	strcpy(pp->name, name);
	pp->age = age;
	pp->gradYear = gradYear;
	printf("testing print name %s, age %d, gradYear %d \n\n", pp->name, pp->age, pp->gradYear);
	return pp;

}

/*
 * print the data of the person type
 * return if successful
 */
void print_person(void *vp){
	person_t* pp;
	pp=(person_t*) vp;
  printf("name: %s, age = %d, gradyear = %d \n\n", pp->name, pp->age, pp->gradYear);
  return;
}

/*
 * print the specific elements in the queue
 * return 0 if successful
 */
/*int print_queue (char* name_pointer, queue_t *qp){
	person_t *p;
	printf("queue name: %s \n", name_pointer);
	for (p = qp; p!=NULL; p=p->next){
		print_person(p);
	}
	return 0;
	}*/

static bool searchfn(void* elementp, const void* keyp){                        
                                                                             
  // compare addresses of the two elements                                    
  if(elementp == keyp){                                                       
    return(true);                                                             
  }else{                                                                      
    return(false);                                                            
  }                                                                           
}  

int main(){
	queue_t *queue1; 
	queue_t *queue2;

	person_t *blank1;
	person_t *blank2;
	person_t *blank3;
	
	person_t *zach = make_person("zach", 20, 2023);
	person_t *foster = make_person("foster", 22, 2022);
	person_t *mikaela = make_person("mikaela", 23, 2021);
	person_t *cam = make_person("cam", 50, 2024);
	person_t *sarah = make_person("sarah", 23, 2021);
	person_t *billie = make_person("billie", 19, 2026);

	// open/apply/put functions
	queue1 = qopen();
	qapply(queue1,print_person); //print on empty list
	qput(queue1, zach);
	qput(queue1, foster);
	qput(queue1, mikaela);
	qapply(queue1,print_person); //print on 3 person list

	//put function
	queue2 = qopen();
	qput(queue2, cam);                                                         
	qput(queue2, sarah);                                                       
	qput(queue2, billie);
	qapply(queue2, print_person); //print on another 3 person list

	// get function
	blank1 = (person_t*)qget(queue1);
	blank2 = (person_t*)qget(queue2);
	//print_queue("queue1", queue1);
	//print_queue("queue2", queue2);
	
	// search for foster (present)
	blank1 = (person_t*)qsearch(queue1, searchfn, foster);
	print_person(blank1);
		
	//search for sarah (not present);
	blank2 = (person_t*)qsearch(queue1, searchfn, sarah);
	print_person(blank2);

	// search for sarah (present);
	blank3 = (person_t*)qsearch(queue2, searchfn, billie);
	print_person(blank3);

	//remove
	blank1 = (person_t*)qremove(queue1, searchfn, mikaela);
	//print_queue("queue1", queue1);
	
	blank2 = (person_t*)qremove(queue2, searchfn, sarah);
	//print_queue("queue2", queue2);

	//concat

	qconcat(queue1, queue2);
	//print_queue("queue1", queue1);
	//print_queue("queue2", queue2);

	//close 
	qclose(queue1);
	
}
