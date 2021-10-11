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
  person_t*steve = make_person("Steve", 50, 1999, 3);
  hashtable_t*hash = hopen();

  

}
