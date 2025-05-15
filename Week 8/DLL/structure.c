#include "structure.h"

elmtAddress allocateAnggota(string namaAnggota, int prioritas) {
    elmtAddress newNode = (elmtAddress)malloc(sizeof(Anggota));
    if (newNode != NULL) {
        newNode->namaAnggota = strdup(namaAnggota);
        newNode->prioritas = prioritas;
        newNode->bukuPinjaman = NULL;
        newNode->next = NULL;
        newNode->prev = NULL;    // Initialize prev pointer to NULL
    }
    return newNode;
}

bukuAddress allocateBuku(string namaBuku, int stok) {
    bukuAddress newNode = (bukuAddress)malloc(sizeof(Buku));
    if (newNode != NULL) {
        newNode->namaBuku = strdup(namaBuku);
        newNode->stok = stok;
        newNode->pAnggota = (List*)malloc(sizeof(List));
        createList(newNode->pAnggota);
        newNode->next = NULL;
        newNode->prev = NULL;    // Initialize prev pointer to NULL
    }
    return newNode;
}

void createList(List* antrean) {
    antrean->front = NULL;
    antrean->rear = NULL;
}

void deallocateAnggota(elmtAddress node) {
    if (node != NULL) {
        free((void *)node->namaAnggota);
        if (node->bukuPinjaman != NULL) {
            free((void *)node->bukuPinjaman);
        }
        free(node);
    }
}

void deallocateBuku(bukuAddress node) {
    if (node != NULL) {
        free((void *)node->namaBuku);
        deleteList(node->pAnggota);
        free(node->pAnggota);
        free(node);
    }
}

void deleteList(List* antrean) {
    elmtAddress current = antrean->front;
    while (current != NULL) {
        elmtAddress next = current->next;
        deallocateAnggota(current);
        current = next;
    }
    antrean->front = NULL;
    antrean->rear = NULL;
}

elmtAddress getElmt(List antrean, int pos) {
    if (pos < 1) return NULL;
    
    elmtAddress current = antrean.front;
    for(int i = 1; i < pos && current != NULL; i++)
        current = current->next;    
    return current;
}

bukuAddress getBuku(bukuAddress node, int pos) {
    if (pos < 1) return NULL;
    
    bukuAddress current = node;
    for(int i = 1; i < pos && current != NULL; i++)
        current = current->next;
    return current;
}

int countBuku(bukuAddress node) {
    int count = 0;
    bukuAddress current = node;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

bool antreanEmpty(List antrean) {
    return antrean.front == NULL;
}

bool bukuExists(bukuAddress node, string namaBuku) {
    bukuAddress current = node;
    while (current != NULL) {
        if (strcmp(current->namaBuku, namaBuku) == 0)
            return true;
        current = current->next;
    }
    return false;
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

void printAllBuku(bukuAddress node) {
    bukuAddress current = node;
    int i = 1;
    while (current != NULL) {
        printf("\t%d. %s (Stok: %d)\n", i, current->namaBuku, current->stok);
        current = current->next;
        i++;
    }
}

void insRear(List* antrean, elmtAddress node) {
    if (antrean->rear == NULL) {
        // List is empty
        antrean->front = node;
        antrean->rear = node;
        node->prev = NULL;
        node->next = NULL;
    } 
    else {
        // Insert at the end
        node->prev = antrean->rear;
        node->next = NULL;
        antrean->rear->next = node;
        antrean->rear = node;
    }
}

void insBetween(List* antrean, elmtAddress node) {
    // Case: Empty list or higher priority than front node
    if (antrean->front == NULL || node->prioritas > antrean->front->prioritas) {
        node->next = antrean->front;
        node->prev = NULL;
        if (antrean->front != NULL) {
            antrean->front->prev = node;
        }
        antrean->front = node;
        if (antrean->rear == NULL) {
            antrean->rear = node;
        }
        return;
    }
    
    // Case: Find position based on priority
    elmtAddress current = antrean->front;
    while (current->next != NULL && current->next->prioritas >= node->prioritas) 
        current = current->next;
    
    // Insert node
    node->next = current->next;
    node->prev = current;
    if (current->next != NULL) {
        current->next->prev = node;
    } else {
        antrean->rear = node;  // New tail if inserting at the end
    }
    current->next = node;
}

void delFront(List* antrean) {
    if (antrean->front == NULL) {
        printf("List kosong!\n");
        return;
    }
    
    elmtAddress temp = antrean->front;
    antrean->front = antrean->front->next;
    
    if (antrean->front == NULL) {
        // List is now empty
        antrean->rear = NULL;
    } else {
        // Update prev pointer of the new front
        antrean->front->prev = NULL;
    }
    
    deallocateAnggota(temp);
}

void delManual(List* antrean, int pos) {
    if (pos < 1) 
        return;
    
    if (pos == 1) {
        delFront(antrean);
        return;
    }
    
    // Find the node to delete
    elmtAddress current = getElmt(*antrean, pos);
    if (current == NULL) 
        return;
    
    // Update the next and prev pointers
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        // If deleting the last node, update rear
        antrean->rear = current->prev;
    }
    
    deallocateAnggota(current);
}

void addBuku(bukuAddress* node, string namaBuku, int stok) {
    bukuAddress newNode = allocateBuku(namaBuku, stok);
    
    if (*node == NULL) {
        // List is empty
        *node = newNode;
    } else {
        // Add to the end of the list
        bukuAddress current = *node;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void removeBuku(bukuAddress* node, string namaBuku) {
    if (*node == NULL) return;
    
    bukuAddress current = *node;
    
    // Check if it's the first node
    if (strcmp(current->namaBuku, namaBuku) == 0) {
        *node = current->next;
        if (*node != NULL) {
            (*node)->prev = NULL;
        }
        deallocateBuku(current);
        return;
    }
    
    // Check the rest of the list
    while (current != NULL && strcmp(current->namaBuku, namaBuku) != 0) {
        current = current->next;
    }
    
    if (current != NULL) {
        // Found the node to remove
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        
        deallocateBuku(current);
    }
}
