#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef const char* string;
typedef struct Anggota* elmtAddress;
typedef struct Buku* bukuAddress;

// Forward declaration for List
typedef struct List List;

// Anggota structure with doubly linked list pointers
typedef struct Anggota {
    string namaAnggota;
    int prioritas;
    string bukuPinjaman;
    elmtAddress next;
    elmtAddress prev;    // Added for doubly linked list
} Anggota;

// Buku structure with doubly linked list pointers
typedef struct Buku {
    string namaBuku;
    int stok;
    List* pAnggota;
    bukuAddress next;
    bukuAddress prev;    // Added for doubly linked list
} Buku;

// List structure with head and tail pointers
typedef struct List {
    elmtAddress front;   // Head of the list
    elmtAddress rear;    // Tail of the list
} List;

/* Constructors */
elmtAddress allocateAnggota(string namaAnggota, int prioritas);
bukuAddress allocateBuku(string namaBuku, int stok);
void createList(List* antrean);

/* Destructors */
void deallocateAnggota(elmtAddress node);
void deallocateBuku(bukuAddress node);
void deleteList(List* antrean);

/* Getter */
elmtAddress getElmt(List antrean, int pos);
bukuAddress getBuku(bukuAddress node, int pos);
int countBuku(bukuAddress node);

/* Verification */
bool antreanEmpty(List antrean);
bool bukuExists(bukuAddress node, string namaBuku);

/* List processing */
void printElmt(elmtAddress node);
void printList(List antrean);
void printAllBuku(bukuAddress node);

/* List I/O */
void insRear(List* antrean, elmtAddress node);
void insBetween(List* antrean, elmtAddress node);    
void delFront(List* antrean);
void delManual(List* antrean, int pos);
void addBuku(bukuAddress* node, string namaBuku, int stok);
void removeBuku(bukuAddress* node, string namaBuku);

#endif
