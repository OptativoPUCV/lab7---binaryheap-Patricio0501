#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if(pq->size == 0){
    return NULL;
  }
  return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority){
  if(pq->size == pq->capac){
    pq->capac = pq->capac * 2 + 1;
    pq->heapArray = (heapElem*)realloc(pq->heapArray, sizeof(heapElem) * pq->capac);
    if(pq->heapArray == NULL){
      perror("Error al aumentar la capacidad del arreglo Heap");
      exit(EXIT_FAILURE);
    }
  }

  int capacidad = pq->size;
  pq->heapArray[capacidad].priority = priority;
  pq->heapArray[capacidad].data = data;
  pq->size++;
  
  while(capacidad > 0 && pq->heapArray[capacidad].priority > pq->heapArray[(capacidad - 1) / 2].priority){
    heapElem temp = pq->heapArray[capacidad];
    pq->heapArray[capacidad] = pq->heapArray[(capacidad - 1) / 2];
    pq->heapArray[(capacidad - 1) / 2] = temp;

    capacidad = (capacidad - 1) / 2;
  }
  
}

void heap_pop(Heap* pq){
  if(pq->size == 0){
    return;
  }

  pq->heapArray[0] = pq->heapArray[pq->size - 1];
  pq->size--;

  int index = 0;
  while(1){
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if(leftChild < pq->size && pq->heapArray[leftChild].priority > pq->heapArray[largest].priority){
      largest = leftChild;
    }

    if(rightChild < pq->size && pq->heapArray[rightChild].priority > pq->heapArray[largest].priority){
      largest = rightChild;
    }

    if(largest == index){
      break;
    }

    heapElem temp = pq->heapArray[index];
    pq->heapArray[index] = pq->heapArray[largest];
    pq->heapArray[largest] = temp;

    index = largest;
  }
}


Heap* createHeap(){
  Heap* reserva = (Heap*)malloc(sizeof(Heap));

  if(reserva == NULL){
    perror("Error al reservar memoria en el Heap");
    exit(EXIT_FAILURE);
  }

  reserva->size = 0;
  reserva->capac = 3;


  reserva->heapArray = (heapElem*)malloc(sizeof(heapElem) * 3);

  if(reserva->heapArray == NULL){
    perror("Error al reservar la memoria en el arreglo heapArray");
    exit(EXIT_FAILURE);
  }

  return reserva;
}
