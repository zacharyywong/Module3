/* qtest.c --- 
 * 
 * 
 * Author: Zachary J. Wong
 * Created: Mon Oct  4 22:10:36 2021 (-0400)
 * Version: 
 * 
 * Description: A test of queue.c 
 * qtest 
 */

#define MAXREG 10

//#include <queue.c>
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
	int fav;
	//int age;
} person_t;


person_t* make_person(char* name, int age, int gradYear, int fav){
	person_t* pp=NULL;

	pp=(person_t*)malloc(sizeof(person_t));
	// fail case
	if (pp == NULL){

		//print to stderr file
		fprintf(stderr, "[Error: malloc failed allocating person]\n");
		return NULL;
	}
	//fill in data
	strcpy(pp->name, name);
	//strcpy(pp->gradYear, gradYear);
	//	strcpy(pp->fav, fav); 
	pp->age = age;
	pp->gradYear = gradYear;
	pp -> fav = fav;
	//	printf("testing print name %s, gradYear %d, fav %d, age %d \n\n", pp->name, pp->gradYear, pp->fav, pp->age);
	//printf("make person name %s, age %d \n\n", pp->name, pp->age); 
	return pp;

}

/*
 * print the data of the person type
 * return if successful
 */

void print_person(void *vp){
	if (vp == NULL){
		printf("person not found \n\n");
		return;
		
	}
	person_t* pp1;
	//person_t* pp2;
	pp1=(person_t*) vp;
	//pp2 = pp1 -> data;
	//	strcpy(pp1->name, "zach");
	//pp1 -> age = 3;
	//pp1 -> gradYear = 30;
	
	
	//  printf("name: %s, gradYear = %d, fav = %d, age = %d \n\n", pp->name, pp->gradYear, pp->fav, pp->age);
	printf("name %s, age %d, gradYear %d, fav %d \n\n", pp1->name, pp1->age, pp1->gradYear, pp1 ->fav);
 
}

static bool searchfn(void* elementp, const void* keyp){                                                                             
// compare the two elements                                    
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

	person_t *zach = make_person("zach", 20, 2023, 500);
	person_t *foster = make_person("foster", 22, 2022, 501); 
	 //	person_t *zach = make_person("zach", 2023, 100, 20);
	 //	person_t *foster = make_person("foster", 2022, 101, 22);
	person_t *mikaela = make_person("mikaela", 23, 2021, 502);
	person_t *cam = make_person("cam", 22, 2050, 503);
	person_t *sarah = make_person("sarah", 21, 2019, 504);
	person_t *billie = make_person("billie", 18, 2026, 505);

	// open/apply/put functions
	queue1 = qopen();
	//qapply(queue1,print_person); //print on empty list
	//printf("print before putting in queue \n");                                                                                                                                                
	// print_person((void*)zach);
	qput(queue1, (void*)zach);
	//printf("print first queue \n"); 
	//print_person((void*)zach);
 	qput(queue1, (void*)foster);
	qput(queue1, (void*)mikaela);
	qput(queue1, (void*)cam);
	//qput(queue1, (void*)sarah);
	//qput(queue1, (void*)billie); 
	printf("print first queue \n");
	qapply(queue1, print_person); //print on 3 person list
	//qclose(queue1);
	
	//put function
	queue2 = qopen();
	qput(queue2, (void*) cam);                                                         
	qput(queue2, (void*)sarah);                                                       
	qput(queue2, (void*)billie);
	printf("print second queue \n");
	qapply(queue2, print_person); //print on another 3 person list
	
	// get function
	blank1 = (person_t*)qget(queue1);
	blank2 = (person_t*)qget(queue2);
	printf("print queue1 after using qget()\n");
	qapply(queue1, print_person);
	printf("print queue2 after using qget()\n");
	qapply(queue2, print_person);
		
	// search for foster (present)
	blank1 = (person_t*)qsearch(queue1, searchfn, (void*)foster);
	printf("Person found after searching for foster\n");
	//print_person(blank1);
	print_person((void*)(blank1));
		
	//search for sarah (present);
	blank2 = (person_t*)qsearch(queue2, searchfn, sarah);
	printf("Person found after searching for sarah\n");
	//print_person(blank2);
	print_person((void*)(blank2));
	
	//search for mikaela (not present in queue2);
	blank3 = (person_t*)qsearch(queue2, searchfn, mikaela);
	printf("Person found after searching for mikaela\n\n");
	//print_person(blank3);
	print_person((void*)(blank3));
	
	//remove
	blank1 = (person_t*)qremove(queue1, searchfn, mikaela);
	printf("print queue1 after removing mikaela\n");
	qapply(queue1, print_person);
	
	blank2 = (person_t*)qremove(queue2, searchfn, sarah);
	printf("print queue2 after removing sarah\n");
	qapply(queue2, print_person);
	
	// remove billie from queue 2
	blank2 = (person_t*)qremove(queue2, searchfn, billie);                      
  printf("print queue2 after removing billie\n");                              
  qapply(queue2, print_person); 
  
	//concat
	qconcat(queue1, queue2);
	printf("print concatenated queue\n");
	qapply(queue1, print_person);
	
	//close 
	qclose(queue1);
	free(foster);
	free(cam);
	free(zach);
	free(mikaela);
	free(sarah);
	free(billie);
}
