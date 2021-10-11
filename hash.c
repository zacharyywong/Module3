/* 
 * hash.c -- implements a generic hash table as an indexed set of queues.
 *
 */
#include <stdint.h>

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
  void *data; //could be a queue or any other data
  char *key; 
  
} element_i;

typedef struct hashstruct{
  uint32_t hsize; //size of table as determined by argument from hopen
  uint32_t length; //number of elements in the hash table
  element_i* slots;// hash slots--> this is an array
  
} hashtable_i


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
  hh->slots = calloc(hsize, sizeof(element_i));
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
    if (hh->slots[i].key != NULL){
      printf("deleting: %s",hh->slots[i].key);//for testing purposes
      free((void*)hh->slots[i].key);
    }
  }
  // free entire array of slots
  free(hh->slots);
  free(hh); //free table itself
}

