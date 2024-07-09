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
    MPI_Init(&argc, &argv); // MPI ortam�n� ba�lat

    int sira, toplamSira;
    MPI_Comm_rank(MPI_COMM_WORLD, &sira); // Her bir s�recin s�ra numaras�n� al
    MPI_Comm_size(MPI_COMM_WORLD, &toplamSira); // Toplam s�re� say�s�n� al

    long long altLimit, ustLimit;
    if (sira == 0) {
        // Kullan�c�dan alt ve �st limitleri al
        cout << "Alt limiti giriniz: ";
        cin >> altLimit;
        cout << "�st limiti giriniz: ";
        cin >> ustLimit;
    }

    // Alt ve �st limitleri t�m s�re�lere yay
    MPI_Bcast(&altLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ustLimit, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int yerelSayac = 0;
    // Her s�re� kendi aral���ndaki say�lar� kontrol eder
    for (long long i = altLimit + sira; i <= ustLimit; i += toplamSira) {
        if (PalandokenSayisiMi(i)) {
            yerelSayac++;
        }
    }

    int genelSayac;
    // T�m s�re�lerin yerel saya�lar�n� toplayarak master s�rece ilet
    MPI_Reduce(&yerelSayac, &genelSayac, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Master s�re� toplam Paland�ken Say�s�n� yazd�r�r
    if (sira == 0) {
        cout << "Alt limit " << altLimit << " ile �st limit " << ustLimit << " aras�nda " << genelSayac << " adet Palandoken Sayisi var." << endl;
    }

    MPI_Finalize(); // MPI ortam�n� sonland�r
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

// Tek rakam say�s� hesaplama fonksiyonu
int TekRakamSayisi(long long sayi) {
    int sayac = 0;
    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakam % 2 != 0) sayac++;
        sayi /= 10;
    }
    return sayac;
}

// �ift rakam say�s� hesaplama fonksiyonu
int CiftRakamSayisi(long long sayi) {
    int sayac = 0;
    while (sayi > 0) {
        int rakam = sayi % 10;
        if (rakam % 2 == 0) sayac++;
        sayi /= 10;
    }
    return sayac;
}
