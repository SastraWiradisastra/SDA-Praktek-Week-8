#ifndef	IMPLEMENTATION_H 
#define IMPLEMENTATION_H

#include "structure.h"

typedef struct {
    string namaBuku;
    int stok;
    List* pAnggota;
} daftarBuku;

void initDaftarBuku(daftarBuku arrBuku[], int size);
void addBuku(daftarBuku arrBuku[], int size);
void delBuku(daftarBuku arrBuku[], int index);
void addPeminjam(List* antrean);
void batalkanPeminjaman(List* antrean);
void prosesAntrean(List* antrean, List* peminjaman, string tmpTitle);
void printAntrean(daftarBuku arrBuku[], int size);
void pengembalian(daftarBuku arrBuku[], List* peminjaman);

#endif
