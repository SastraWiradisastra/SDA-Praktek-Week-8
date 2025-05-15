#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>	// I/O control 
#include <stdlib.h>	// Memory allocation and macros
#include <stdbool.h>	// Implementing bool type
#include <string.h>	// String operations
#include <unistd.h>	// Additional system utilities (e.g. sleep(), etc.)

// Singular data type definition
typedef const char* string;
typedef struct Anggota* elmtAddress;

// Node and list structure
typedef struct Anggota {
	string namaAnggota;
	int prioritas;
	string bukuPinjaman;
	elmtAddress next;
} Anggota;

typedef struct List {
	elmtAddress front;
	elmtAddress rear;	
} List;

/* Constructors */
elmtAddress allocate(string namaAnggota, int prioritas);
void createList(List* antrean);

/* Destructors */
void deallocate(elmtAddress node);
void deleteList(List* antrean);

/* Getter */
elmtAddress getElmt(List antrean, int pos);

/* Verification */
bool antreanEmpty(List antrean);

/* List processing*/
// Printing
void printAnggota(elmtAddress node);
void printList(List antrean);

// Search
elmtAddress searchList(List antrean, string query);

/* List I/O */
// Insertions
void insRear(List* antrean, elmtAddress node);
void insBetween(List* antrean, elmtAddress node);	

// Deletions
void delFront(List* antrean);
void delManual(List* antrean, int pos);	

#endif
