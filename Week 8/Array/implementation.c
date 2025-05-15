#include "implementation.h"

void initDaftarBuku(daftarBuku arrBuku[], int size) {
	char buffer[256];
	printf("\n\t#=====(Inisialisasi Daftar Buku)=====#\n");
	for (int i = 0; i < size; i++) {
		printf("\n\tMasukkan nama buku ke-%d: ", i + 1);
		fgets(buffer, 256, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		arrBuku[i].namaBuku = strdup(buffer);
		printf("\tMasukkan jumlah stok buku ke-%d: ", i + 1);
		scanf("%d", &arrBuku[i].stok);
		getchar();
		arrBuku[i].pAnggota = (List*)malloc(sizeof(List));
		createList(arrBuku[i].pAnggota);
	}
}

void addBuku(daftarBuku arrBuku[], int size) {
	char buffer[256];
	for (int i = 0; i < size; i++) {
		if (arrBuku[i].namaBuku == NULL) {
			printf("\tMasukkan nama buku ke-%d: ", i + 1);
			fgets(buffer, 256, stdin);
			buffer[strcspn(buffer, "\n")] = '\0';
			arrBuku[i].namaBuku = strdup(buffer);
			printf("\tMasukkan jumlah stok buku ke-%d ", i + 1);
			scanf("%d", &arrBuku[i].stok);
			getchar();
			arrBuku[i].pAnggota = (List*)malloc(sizeof(List));
			createList(arrBuku[i].pAnggota);
			return;
		}
	}
	printf("\tSemua slot kota sudah terisi.\n");
	sleep(1);
}

void delBuku(daftarBuku arrBuku[], int index) {
	if (arrBuku[index - 1].namaBuku == NULL) {
		printf("\tBuku pada indeks %d tidak ada.\n", index);
		return;
	}
	if (arrBuku[index - 1].pAnggota != NULL) {
		deleteList(arrBuku[index-1].pAnggota);
		free(arrBuku[index-1].pAnggota);
	}
	free((void *)arrBuku[index-1].namaBuku);
	arrBuku[index-1].namaBuku = NULL;
	arrBuku[index-1].pAnggota = NULL;
	arrBuku[index-1].stok = 0;
}

void addPeminjam(List* antrean) {
	char strBuffer[256]; 
	int intBuffer;
	printf("\tMasukkan nama anggota: ");
	fgets(strBuffer, 256, stdin);
	strBuffer[strcspn(strBuffer, "\n")] = '\0';
	printf("\tMasukkan prioritas anggota: ");
	scanf("%d", &intBuffer);
	getchar();
	elmtAddress newNode = allocate(strBuffer, intBuffer);
	if (newNode == NULL) {
		printf("Alokasi gagal.\n");
		return;
	}
	if (newNode->prioritas == 1) 
		insRear(antrean, newNode);
	else
		insBetween(antrean, newNode);
}

void batalkanPeminjaman(List* antrean) {
	if (antreanEmpty(*antrean)) {
		printf("\n\tAntrean kosong!\n");
		sleep(1);
		return;
	}
	int pos;
	printf("Masukkan pinjaman yang dibatalkan: ");
	scanf("%d", &pos);
	delManual(antrean, pos);
}

void prosesAntrean(List* antrean, List* peminjaman, string tmpTitle) {
	if (antreanEmpty(*antrean)) {
		printf("\n\tAntrean kosong!\n");
		sleep(1);
		free((void *)tmpTitle);
		return;
	}
	elmtAddress peminjam = antrean->front;
	peminjam->bukuPinjaman = strdup(tmpTitle);
	free((void *)tmpTitle);
	antrean->front = peminjam->next;
	if (antrean->front == NULL) 
		antrean->rear = NULL;
	peminjam->next = NULL;
	insRear(peminjaman, peminjam);
}

void printAntrean(daftarBuku arrBuku[], int size) {
	for (int i = 0; i < size; i++) {
		if (arrBuku[i].namaBuku != NULL) {
			printf("\t[Buku: %s, Stok Tersisa: %d]\n", arrBuku[i].namaBuku, arrBuku[i].stok);
			printList(*(arrBuku[i].pAnggota));
			printf("\n");
		}
	}
}

void pengembalian(daftarBuku arrBuku[], List* peminjaman) {
	if (antreanEmpty(*peminjaman)) {
		printf("\n\tTidak ada buku yang dipinjam!\n");
		sleep(1);
		return;
	}
	printList(*peminjaman);
	int pos;
	scanf("%d", &pos);
	elmtAddress toComp = getElmt(*peminjaman, pos);
	for (int i = 0; i < 5; i++) {
		if (arrBuku[i].namaBuku != NULL && strcmp(arrBuku[i].namaBuku, toComp->bukuPinjaman) == 0) {
			arrBuku[i].stok += 1;
			break;
		}
	}
	delManual(peminjaman, pos);
}
