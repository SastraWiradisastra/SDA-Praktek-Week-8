#include "structure.h"

elmtAddress allocate(string namaAnggota, int prioritas) {
	elmtAddress newNode = (elmtAddress)malloc(sizeof(Anggota));
	if (newNode != NULL) {
		newNode->namaAnggota = strdup(namaAnggota);
		newNode->prioritas = prioritas;
		newNode->bukuPinjaman = NULL;
		newNode->next = NULL;
	}
	return newNode;
}

void createList(List* antrean) {
	antrean->front = NULL;
	antrean->rear = NULL;
}

void deallocate(elmtAddress node) {
	if (node != NULL) {
		free((void *)node->namaAnggota);
		free((void *)node->bukuPinjaman);
		free(node);
	}
}

void deleteList(List* antrean) {
	elmtAddress current = antrean->front;
	while (current != NULL) {
		elmtAddress next = current->next;
		deallocate(current);
		current = next;
	}
	antrean->front = NULL;
	antrean->rear = NULL;
}

elmtAddress getElmt(List antrean, int pos)
{
	elmtAddress current = antrean.front;
	for(int i = 1; i != pos; i++)
		current = current->next;	
	return current;
}

bool antreanEmpty(List antrean) {
	return antrean.front == NULL;
}

void printElmt(elmtAddress node) {
	if (node != NULL) {
		int prioritasNum = node->prioritas;
		char prioritasString[8];
		switch (prioritasNum) {
			case 1: strcpy(prioritasString, "Umum"); break;
			case 2: strcpy(prioritasString, "Anggota"); break;
			case 3: strcpy(prioritasString, "Dosen"); break;
		}
		printf("%s (%s)\n", node->namaAnggota, prioritasString);
	}
}

void printList(List antrean) {
	elmtAddress current = antrean.front;
	if (current == NULL) {
		printf("\tList kosong!\n");
		return;
	}
	int i = 1;
	while (current != NULL) {
		printf("\t%d. ", i);
		printElmt(current);
		current = current->next;
		i++;
	}
	printf("\t--- End of queue ---\n");
}

void insRear(List* antrean, elmtAddress node) {
	if (antrean->rear == NULL) {
		antrean->front = node;
        	antrean->rear = node;
	} 
	else {
        	antrean->rear->next = node;
        	antrean->rear = node;
    	}
}

void insBetween(List* antrean, elmtAddress node) {
	if (antrean->front == NULL || node->prioritas > antrean->front->prioritas) {
		node->next = antrean->front;
		antrean->front = node;
		if (antrean->rear == NULL)
			antrean->rear = node;
		return;
	}
	elmtAddress current = antrean->front;
	while (current->next != NULL && current->next->prioritas >= node->prioritas) 
		current = current->next;
	node->next = current->next;
	current->next = node;
	if (node->next == NULL) 
		antrean->rear = node;
}

void delFront(List* antrean) {
	if (antrean->front == NULL) {
		printf("List kosong!\n");
		return;
	}
	else {
		elmtAddress temp = antrean->front;
		antrean->front = antrean->front->next;
		deallocate(temp);
	}
}

void delManual(List* antrean, int pos) {
	if (pos < 1) 
		return;
	if (pos == 1) {
		delFront(antrean);
		return;
	}
	elmtAddress current = antrean->front;
	elmtAddress prev = NULL;
	for (int i = 1; current != NULL && i < pos; i++) {
		prev = current;
		current = current->next;
	}
	if(current == NULL) 
		return;
	prev->next = current->next;
	deallocate(current);
}
