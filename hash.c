/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"
#include "hash.h"

/* 
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.
 * 
 * The following (rather complicated) code, has been taken from Paul
 * Hsieh's website under the terms of the BSD license. It's a hash
 * function used all over the place nowadays, including Google Sparse
 * Hash.
 */
#define get16bits(d) (*((const uint16_t *) (d)))

//internal represenation of a hash table:
typedef struct elementstruct{//not too confident about this but think we need it for opening it...
  void *data; //can handle any sort of data
  char *key;
} element_i;

typedef struct hashstruct{
  uint32_t hsize; //size of table as determined by argument from hopen
  uint32_t length; //number of elements in the hash table
  queue_t* slots;// hash slots--> this is an array
  
} hashtable_i;


static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {
  uint32_t hash = len, tmp;
  int rem;
  
  if (len <= 0 || data == NULL)
		return 0;
  rem = len & 3;
  len >>= 2;
  /* Main loop */
  for (;len > 0; len--) {
    hash  += get16bits (data);
    tmp    = (get16bits (data+2) << 11) ^ hash;
    hash   = (hash << 16) ^ tmp;
    data  += 2*sizeof (uint16_t);
    hash  += hash >> 11;
  }
  /* Handle end cases */
  switch (rem) {
  case 3: hash += get16bits (data);
    hash ^= hash << 16;
    hash ^= data[sizeof (uint16_t)] << 18;
    hash += hash >> 11;
    break;
  case 2: hash += get16bits (data);
    hash ^= hash << 11;
    hash += hash >> 17;
    break;
  case 1: hash += *data;
    hash ^= hash << 10;
    hash += hash >> 1;
  }
  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 4;
  hash += hash >> 17;
  hash ^= hash << 25;
  hash += hash >> 6;
  return hash % tablesize;
}

// hopen -- opens a hash table with the initial size hsize

hashtable_t *hopen(uint32_t hsize){
  hashtable_i* hh;
  hh = (hashtable_i*)malloc(hh);// allocate memory for internal represenation of table
  if(hh == NULL){
    free(hh);
    return NULL;
  }
  hh->hsize = hsize; 
  hh->length = 0;

  //allocate memory for the array of entries
  hh->slots = calloc(hsize, sizeof(queue_t));
  if(hh->slots == NULL){
    free(hh);
    return NULL;
  }
  return (hashtable_t*)hh;
}


//hclose -- closes hash table
void hclose(hashtable_t *htp){

  hashtable_i*hh=(hashtable_i*)htp;
  // free any allocated keys
  for(uint32_t i = 0; i < hh->hsize; i++){
    if (hh->slots[i] != NULL){
      printf("deleting: %s",hh->slots[i]);//for testing purposes
      free((void*)hh->slots[i]);
    }
  }
  // free entire array of slots
  free(hh->slots);
  free(hh); //free table itself
}

// hput -- puts an entry into a hash table under designated key
// returns 0 for sucess; nonzero otherwise

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen){
  uint32_t loc;
  queue_t*qp;
  hashtable_i*hh=htp;
  element_i*elep;
  loc = SuperFastHash(key, keylen, hh->hsize);
  if (hh->slots[loc]!=NULL){//in the case that this is the first element at this location in the table
    qp = qopen();
    hh->slots[loc]=qp;
    elep->key = key;
    elep->data = ep;
    qput(qp, elep);
    hh->length+=1;
  }else{//if there is an existing
    qp = hh->slots[loc];//retrieve pointer to existing queue
    elep->key = key;//put key and data into element structure
    elep->data = ep;
    qput(qp, elep);//put completed element structure into exisiting queue
    hh->length+=1;
  }
  if(hh->slots[loc] != qp) return 1; //check that queue in proper part of the table
  if(qsearch(qp, searchfn, elep) == NULL) return 1; //utilize search functionality of queue to check for success
  return 0; //if it makes it thru the above checks --> success
}




