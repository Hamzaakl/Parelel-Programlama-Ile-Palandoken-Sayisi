#include <mpi.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

// Fonksiyon prototipleri
bool PalandokenSayisiMi(long long sayi);
bool BenzersizRakamlar(long long sayi);
int TekRakamSayisi(long long sayi);
int CiftRakamSayisi(long long sayi);

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // MPI ortamýný baþlat

    int sira, toplamSira;
    MPI_Comm_rank(MPI_COMM_WORLD, &sira); // Her bir sürecin sýra numarasýný al
    MPI_Comm_size(MPI_COMM_WORLD, &toplamSira); // Toplam süreç sayýsýný al

    long long altLimit, ustLimit;
    if (sira == 0) {
        // Kullanýcýdan alt ve üst limitleri al
        cout << "Alt limiti giriniz: ";
        cin >> altLimit;
        cout << "Üst limiti giriniz: ";
        cin >> ustLimit;
    }

    // Alt ve üst limitleri tüm süreçlere yay
    MPI_Bcast(&altLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ustLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int yerelSayac = 0;
    // Her süreç kendi aralýðýndaki sayýlarý kontrol eder
    for (long long i = altLimit + sira; i <= ustLimit; i += toplamSira) {
        if (PalandokenSayisiMi(i)) {
            yerelSayac++;
        }
    }

    int genelSayac;
    // Tüm süreçlerin yerel sayaçlarýný toplayarak master sürece ilet
    MPI_Reduce(&yerelSayac, &genelSayac, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Master süreç toplam Palandöken Sayýsýný yazdýrýr
    if (sira == 0) {
        cout << "Alt limit " << altLimit << " ile üst limit " << ustLimit << " arasýnda " << genelSayac << " adet Palandoken Sayisi var." << endl;
    }

    MPI_Finalize(); // MPI ortamýný sonlandýr
    return 0;
}

// Palandoken Sayisi kontrol fonksiyonu
bool PalandokenSayisiMi(long long sayi) {
    if (!BenzersizRakamlar(sayi)) return false;
    int tekRakamSayisi = TekRakamSayisi(sayi);
    int ciftRakamSayisi = CiftRakamSayisi(sayi);
    return (tekRakamSayisi % 2 != 0) && (ciftRakamSayisi % 2 == 0);
}

// Benzersiz rakam kontrol fonksiyonu
bool BenzersizRakamlar(long long sayi) {
    bool rakamlar[10] = {false};
    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakamlar[rakam]) return false;
        rakamlar[rakam] = true;
        sayi /= 10;
    }
    return true;
}

// Tek rakam sayýsý hesaplama fonksiyonu
int TekRakamSayisi(long long sayi) {
    int sayac = 0;
    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakam % 2 != 0) sayac++;
        sayi /= 10;
    }
    return sayac;
}

// Çift rakam sayýsý hesaplama fonksiyonu
int CiftRakamSayisi(long long sayi) {
    int sayac = 0;
    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakam % 2 == 0) sayac++;
        sayi /= 10;
    }
    return sayac;
}
