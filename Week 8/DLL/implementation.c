#include "implementation.h"

void initDaftarBuku(bukuAddress* node) {
    char buffer[256];
    printf("\n\t#=====(Inisialisasi Daftar Buku)=====#\n");
    for (int i = 0; i < 5; i++) {
        printf("\n\tMasukkan nama buku ke-%d: ", i + 1);
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("\tMasukkan jumlah stok buku ke-%d: ", i + 1);
        int stok;
        scanf("%d", &stok);
        getchar();
        addBuku(node, buffer, stok);
    }
}

void addBukuMenu(bukuAddress* node) {
    char buffer[256];
    printf("\tMasukkan nama buku: ");
    fgets(buffer, 256, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("\tMasukkan jumlah stok buku: ");
    int stok;
    scanf("%d", &stok);
    getchar();
    addBuku(node, buffer, stok);
}

void delBukuMenu(bukuAddress* node) {
    printAllBuku(*node);
    printf("\n\tPilih buku untuk dihapus (1-%d): ", countBuku(*node));
    int index;
    scanf("%d", &index);
    getchar();
    bukuAddress toDelete = getBuku(*node, index);
    if (toDelete != NULL) {
        removeBuku(node, toDelete->namaBuku);
    } else {
        printf("\tBuku tidak valid!\n");
        sleep(1);
    }
}

void addPeminjam(bukuAddress node) {
    printAllBuku(node);
    printf("\n\tMasukkan index buku yang ditambahkan peminjam (1-%d): ", countBuku(node));
    int index;
    scanf("%d", &index);
    getchar();
    bukuAddress selected = getBuku(node, index);
    if (selected != NULL) {
        char strBuffer[256];
        int intBuffer;
        printf("\tMasukkan nama anggota: ");
        fgets(strBuffer, 256, stdin);
        strBuffer[strcspn(strBuffer, "\n")] = '\0';
        printf("\tMasukkan prioritas anggota: ");
        scanf("%d", &intBuffer);
        getchar();
        elmtAddress newNode = allocateAnggota(strBuffer, intBuffer);
        if (newNode->prioritas == 1) 
            insRear(selected->pAnggota, newNode);
        else
            insBetween(selected->pAnggota, newNode);
    } else {
        printf("\tBuku tidak valid!\n");
        sleep(1);
    }
}

void batalkanPeminjaman(bukuAddress node) {
    printAllBuku(node);
    printf("\n\tMasukkan index buku (1-%d): ", countBuku(node));
    int index;
    scanf("%d", &index);
    getchar();
    bukuAddress selected = getBuku(node, index);
    if (selected != NULL) {
        if (antreanEmpty(*selected->pAnggota)) {
            printf("\n\tAntrean kosong!\n");
            sleep(1);
            return;
        }
        printf("\tAntrean untuk buku %s:\n", selected->namaBuku);
        printList(*selected->pAnggota);
        printf("Masukkan pinjaman yang dibatalkan: ");
        int pos;
        scanf("%d", &pos);
        delManual(selected->pAnggota, pos);
        selected->stok += 1;
    } else {
        printf("\tBuku tidak valid!\n");
        sleep(1);
    }
}

void prosesAntrean(bukuAddress node, List* peminjaman) {
    printAllBuku(node);
    printf("\n\tMasukkan index buku (1-%d): ", countBuku(node));
    int index;
    scanf("%d", &index);
    getchar();
    bukuAddress selected = getBuku(node, index);
    if (selected != NULL) {
        if (selected->stok == 0) {
            printf("\tStok buku habis!\n");
            sleep(1);
            return;
        }
        if (antreanEmpty(*selected->pAnggota)) {
            printf("\n\tAntrean kosong!\n");
            sleep(1);
            return;
        }
        
        // Get the first person in the queue
        elmtAddress peminjam = selected->pAnggota->front;
        peminjam->bukuPinjaman = strdup(selected->namaBuku);
        
        // Remove from the queue
        selected->pAnggota->front = peminjam->next;
        if (selected->pAnggota->front == NULL) {
            selected->pAnggota->rear = NULL;
        } else {
            selected->pAnggota->front->prev = NULL;
        }
        
        // Add to peminjaman list
        peminjam->next = NULL;
        peminjam->prev = NULL;
        insRear(peminjaman, peminjam);
        
        // Decrease book stock
        selected->stok -= 1;
    } else {
        printf("\tBuku tidak valid!\n");
        sleep(1);
    }
}

void printAntrean(bukuAddress node) {
    bukuAddress current = node;
    while (current != NULL) {
        printf("\t[Buku: %s, Stok Tersisa: %d]\n", current->namaBuku, current->stok);
        printList(*current->pAnggota);
        printf("\n");
        current = current->next;
    }
}

void pengembalian(bukuAddress node, List* peminjaman) {
    if (antreanEmpty(*peminjaman)) {
        printf("\n\tTidak ada buku yang dipinjam!\n");
        sleep(1);
        return;
    }
    printList(*peminjaman);
    printf("\tPilih peminjam yang mengembalikan buku: ");
    int pos;
    scanf("%d", &pos);
    getchar();
    
    elmtAddress toComp = getElmt(*peminjaman, pos);
    if (toComp != NULL) {
        bukuAddress current = node;
        while (current != NULL) {
            if (strcmp(current->namaBuku, toComp->bukuPinjaman) == 0) {
                current->stok += 1;
                break;
            }
            current = current->next;
        }
        delManual(peminjaman, pos);
    } else {
        printf("\tPeminjam tidak valid!\n");
        sleep(1);
    }
}
