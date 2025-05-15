#include "tui.h"

void printMainMenu() {
	system("clear");
	printf("\n\t#===========================#\n");
	printf("\t|  Program Peminjaman Buku  |\n");
	printf("\t#===========================#\n");
	printf("\t|  1. Tambah Buku           |\n");
	printf("\t|  2. Hapus Buku            |\n");
	printf("\t|  3. Tambah Peminjam       |\n");
	printf("\t|  4. Batalkan Peminjaman   |\n");
	printf("\t|  5. Proses Antrean        |\n");
	printf("\t|  6. Print Antrean         |\n");
	printf("\t|  7. Kembalikan Buku       |\n");
	printf("\t|  8. Keluar                |\n");
	printf("\t#===========================#\n");
	printf("\n\tMasukkan pilihan anda: ");
}

void printTambahBukuMenu() {
	system("clear");
	printf("\n\t#===================#\n");
	printf("\t|  Penambahan Buku  |\n");
	printf("\t#===================#\n\n");
}

void printDeleteBukuMenu() {
	system("clear");
	printf("\n\t#====================#\n");
	printf("\t|  Penghapusan Buku  |\n");
	printf("\t#====================#\n");
	printf("\n\tPilih buku untuk dihapus (1-5): ");
}

void printTambahPeminjamanMenu() {
	system("clear");
	printf("\n\t#=========================#\n");
	printf("\t|  Penambahan Peminjaman  |\n");
	printf("\t#=========================#\n");
	printf("\n\tMasukkan index buku yang ditambahkan peminjam (1-5): ");
}

void printBatalPeminjamanMenu() {
	system("clear");
	printf("\n\t#=========================#\n");
	printf("\t|  Pembatalan Peminjaman  |\n");
	printf("\t#=========================#\n");
}

void printProsesPeminjamanMenu() {
	system("clear");
	printf("\n\t#=========================#\n");
	printf("\t|  Pemrosesan Peminjaman  |\n");
	printf("\t#=========================#\n");
	printf("\n\tMasukkan index antrean buku yang akan diproses (1-5): ");
}

void printPengembalianMenu() {
	system("clear");
	printf("\n\t#=====================#\n");
	printf("\t|  Pengembalian Buku  |\n");
	printf("\t#=====================#\n");
	printf("\n\tMasukkan index pinjaman yang dikembalikan: ");
}

void printAntreanMenu() {
	system("clear");
	printf("\n\t#================#\n");
	printf("\t|  Antrean Buku  |\n");
	printf("\t#================#\n\n");
}
