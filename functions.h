#ifndef HEAP_H
#define HEAP_H

struct paciente;

struct paciente *InicHeap ();
int InsereHeap ();
int RemoveHeap ();
void Heapfy ();
int ChecaHeap ();
void ImprimeHeap ();
void HeapSort ();
void AlteraHeap ();
void SacodeHeap ();
void ImprimeMenu ();

#endif