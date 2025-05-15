#include "implementation.h"
#include "tui.h"

int main() {
    bukuAddress daftarBuku = NULL;
    system("clear");
    initDaftarBuku(&daftarBuku);
    
    List peminjaman;
    createList(&peminjaman);

    int choice;
    for (;;) {
        printMainMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printTambahBukuMenu();
                addBukuMenu(&daftarBuku);
                break;
            case 2:
                printDeleteBukuMenu();
                delBukuMenu(&daftarBuku);
                break;
            case 3:
                printTambahPeminjamanMenu();
                addPeminjam(daftarBuku);
                break;
            case 4:
                printBatalPeminjamanMenu();
                batalkanPeminjaman(daftarBuku);
                break;
            case 5:
                printProsesPeminjamanMenu();
                prosesAntrean(daftarBuku, &peminjaman);
                break;
            case 6:
                fflush(stdin);
                do {
                    printAntreanMenu();
                    printAntrean(daftarBuku);
                    printf("\tInput 'q' untuk kembali ke menu: ");
                } while (getchar() != 'q');
                break;
            case 7:
                printPengembalianMenu();
                pengembalian(daftarBuku, &peminjaman);
                break;
            case 8: 
                // Clean memory before exit
                bukuAddress current = daftarBuku;
                while (current != NULL) {
                    bukuAddress next = current->next;
                    deleteList(current->pAnggota);
                    free(current->pAnggota);
                    free((void *)current->namaBuku);
                    free(current);
                    current = next;
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
