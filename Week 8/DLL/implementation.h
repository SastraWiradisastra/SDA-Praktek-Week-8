#ifndef IMPLEMENTATION_H 
#define IMPLEMENTATION_H

#include "structure.h"

void initDaftarBuku(bukuAddress* node);
void addBukuMenu(bukuAddress* node);
void delBukuMenu(bukuAddress* node);
void addPeminjam(bukuAddress node);
void batalkanPeminjaman(bukuAddress node);
void prosesAntrean(bukuAddress node, List* peminjaman);
void printAntrean(bukuAddress node);
void pengembalian(bukuAddress node, List* peminjaman);

#endif
