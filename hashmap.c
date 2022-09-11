#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) { //ya
  Pair *newPair = createPair(key, value); 
  size_t i = hash(key, map->capacity);
  while(true){
    if(map->buckets[i] == NULL){
    map->buckets[i] = newPair;
    map->size++;
    map->current = i;
    }
    i++;
    if ( i== map->capacity){
      i = 0;
    }
  }
}

void enlarge(HashMap * map) { // ya
  enlarge_called = 1; //no borrar (testing purposes)
  Pair ** oldBruckets = map->buckets;
  size_t largo = map->capacity;
  map->capacity = map->capacity * 2; //dublicar la capacidad
  map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair *));
  map->size = 0;
  for (size_t i = 0; i < largo ; i++ ){
    if(oldBruckets[i] != NULL){
      insertMap(map,oldBruckets[i]->key,oldBruckets[i]->value); 
    }
  }
}
 
HashMap * createMap(long capacity) { //ya
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  
    map->buckets = (Pair **)malloc(capacity * sizeof(Pair));
    map->capacity = capacity;
    map->current = -1;
  
    return map;
}

void eraseMap(HashMap * map,  char * key) {    //ya 
  Pair *pairEliminar = searchMap(map, key); 
  if(pairEliminar != NULL){
    pairEliminar->key=NULL;
    map->size --;
  }
}

Pair * searchMap(HashMap * map,  char * key) {   // ya
  size_t i = hash(key, map->capacity);
  while (!is_equal(key, map->buckets[i]->key)){
  I = i ++  % map->capacity;
  if (map->buckets[i] == NULL) return NULL;
  }
  map ->current = i;
  return map-> buckets[i];
}

Pair * firstMap(HashMap * map) {
   
    return NULL;
}

Pair * nextMap(HashMap * map) {
  if (map->size == 0)return NULL;
  for (size_t i = 0; i > map->capacity; i++){
     if (map->buckets[i] != NULL && map->buckets[i]->key !=NULL){
       map->current = i;
       return map->buckets[i];
     }
  }
  return NULL;
}
