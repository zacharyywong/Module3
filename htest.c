/* htest.c --- 
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
#define HASHSIZE 10
#define MAXCHAR 10
//#include <queue.c>
#include <queue.h>
#include <hash.h>
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

typedef struct element_htest {
	void *data;
	char key[MAXCHAR];
} element_htest;

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
	//printf("%p\n\n", vp);
			if (vp == NULL){
		printf("person not found! \n\n");
		return;
		
		}
	//	printf("made it past if, person exists\n\n");
	person_t* pp1;
	//person_t* pp2;
	pp1=(person_t*) vp;
	//pp2 = pp1 -> data;
	//	strcpy(pp1->name, "zach");
	//pp1 -> age = 3;
	//pp1 -> gradYear = 30;
	
	printf("printing person...\n\n");
	//  printf("name: %s, gradYear = %d, fav = %d, age = %d \n\n", pp->name, pp->gradYear, pp->fav, pp->age);
	printf("name %s, age %d, gradYear %d, fav %d \n\n", pp1->name, pp1->age, pp1->gradYear, pp1 ->fav);
	//printf("test");
}

static bool hsearchfn(void* elementp, const void* keyp){                                                                             
	element_htest *ep = (element_htest *) elementp;
	char *key = (char *)keyp;
	// compare the two elements                                    
	if(ep->key == key)return(true);                                                             
	else return(false);                                                                                      
}

int main(){
	//printf("Made it into main function\n\n");
	person_t*steve = make_person("Steve", 50, 1999, 3);
	person_t*elise = make_person("elise", 80, 1963, 8);
	person_t*mike = make_person("mike", 53, 1963, 15);
	//person_t*pam = make_person("pam", 45, 1980, 30);
	//person_t*tom = make_person("tom", 30, 1990, 25);
  //person_t*jess = make_person("jess", 25, 2000, 17);                                           

  hashtable_t* hash1 = hopen(HASHSIZE);
	//printf("just opened a hastable\n\n");
	//print on empty hashtable
	happly(hash1, print_person);
	//printf("just did happly\n\n");

	hput(hash1, (void*)(steve), steve->name, 5);
	hput(hash1, (void*)(elise), elise->name, 5);
	hput(hash1, (void*)(mike), mike->name, 6);
	
	
	//printf("just hput 1 people\n\n");
	happly(hash1, print_person); 
	//printf("just before hclose\n\n");
	//hclose(hash1);

}
