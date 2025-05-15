#include "implementation.h"
#include "tui.h"

#define SIZE 5

int main() {
	daftarBuku arrBuku[SIZE];
	for (int i = 0; i < SIZE; i++) {
		arrBuku[i].namaBuku = NULL;
		arrBuku[i].pAnggota = (List*)malloc(sizeof(List));
		createList(arrBuku[i].pAnggota);
	}
	system("clear");
	initDaftarBuku(arrBuku, SIZE);
	
	List peminjaman;
	createList(&peminjaman);

	int choice, index;
	for (;;) {
		printMainMenu();
		scanf("%d", &choice);
		getchar();

		switch (choice) {
			case 1:
				printTambahBukuMenu();
				addBuku(arrBuku, SIZE);
				break;
			case 2:
				printDeleteBukuMenu();
				scanf("%d", &index);
				getchar();
				if (index < 1 || index > SIZE || arrBuku[index-1].namaBuku == NULL) {
					printf("\tBuku tidak valid! Silahkan coba lagi.");
					sleep(1);
					break;
				}
				delBuku(arrBuku, index);
				break;
			case 3:
				printTambahPeminjamanMenu();
				scanf("%d", &index);
				getchar();
				if (index < 1 || index > SIZE || arrBuku[index-1].namaBuku == NULL) {
					printf("\tBuku tidak valid! Silahkan coba lagi.");
					sleep(1);
					break;
				}
				addPeminjam(arrBuku[index - 1].pAnggota);
				break;
			case 4:
				printBatalPeminjamanMenu();
				scanf("%d", &index);
				getchar();
				if (index < 1 || index > SIZE || arrBuku[index-1].namaBuku == NULL) {
					printf("\tBuku tidak valid! Silahkan coba lagi.");
					sleep(1);
					break;
				}
				arrBuku[index - 1].stok += 1;
				batalkanPeminjaman(arrBuku[index - 1].pAnggota);
				break;
			case 5:
				printProsesPeminjamanMenu();
				scanf("%d", &index);
				getchar();
				if (index < 1 || index > SIZE || arrBuku[index-1].namaBuku == NULL) {
					printf("\tBuku tidak valid! Silahkan coba lagi.\n");
					sleep(1);
					break;
				}
				if (arrBuku[index - 1].stok == 0) {
					printf("\tStok buku habis!\n");
					sleep(1);
					break;
				}
				string titleToPass = strdup(arrBuku[index - 1].namaBuku);
				prosesAntrean(arrBuku[index - 1].pAnggota, &peminjaman, titleToPass);
				arrBuku[index - 1].stok -= 1;
				break;
			case 6:
				fflush(stdin);
				do {
					printAntreanMenu();
					printAntrean(arrBuku, SIZE);
					printf("\tInput 'q' untuk kembali ke menu: ");
				} while (getchar() != 'q');
				break;
			case 7:
				printPengembalianMenu();
				pengembalian(arrBuku, &peminjaman);
				break;
			case 8: 
				for (int i = 0; i < SIZE; i++) {
					if (arrBuku[i].namaBuku != NULL) {
						deleteList(arrBuku[i].pAnggota);
						free((void *)arrBuku[i].namaBuku);
					}
					free(arrBuku[i].pAnggota);
				}
				deleteList(&peminjaman);
				system("clear");
				exit(0);
			default:
				printf("\tPilihan tidak valid.\n");
				sleep(1);
		}
	}
	return 0;
}
