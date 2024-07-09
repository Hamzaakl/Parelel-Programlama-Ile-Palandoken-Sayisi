


# Palandöken Sayısı Bulucu

Bu proje, C++ ve MPI kullanarak belirli aralıklardaki palandöken sayılarını bulan bir uygulamadır. Palandöken sayıları, belirli bir kurala göre tanımlanan özel sayı dizileridir. Bu kod, MPI kullanarak paralel hesaplama yapar ve belirli bir aralıktaki palandöken sayılarının sayısını bulur.
---
-Palandöken sayısı:
-Rakamları birbirinden farklı ve değeri bir tek sayı olan dijitlerinin adedi değeri bir çift sayı olan dijitlerinin adedinden fazla olan sayılar Palandöken Sayısı olarak adlandırılmaktadır.
.
Örneğin 751824693 bir Palandöken Sayısıdır çünkü:
751824693 sayısının rakamları birbirinden farklıdır.
Değeri bir tek sayı olan 5 dijit vardır: 7, 5, 1, 9, 3
Değeri bir çift sayı olan 4 dijit vardır: 8, 2, 4, 6
## İçindekiler

- [Kurulum](#kurulum)
- [Kullanım](#kullanım)

## Kurulum

Bu projeyi çalıştırmak için aşağıdaki adımları izleyin:

1. Bu projeyi yerel makinenize klonlayın:

   ```sh
   git clone https://github.com/Hamzaakl/Parelel-Programlama-Ile-Palandoken-Sayisi.git
   cd Parelel-Programlama-Ile-Palandoken-Sayisi
   ```

2. Gerekli bağımlılıkları kurun:

   - MPI Kütüphanesi (OpenMPI veya MPICH gibi)
   - C++ derleyicisi (g++ gibi)

3. Projeyi derleyin:

   ```sh
   mpic++ -o palandoken Parelel-Programlama-Palandoken-Sayisi.cpp
   ```

## Kullanım

Derleme tamamlandıktan sonra, uygulamayı çalıştırmak için aşağıdaki komutu kullanın:

```sh
mpirun -np <proses_sayisi> ./palandoken
alt limit girin <alt_limit>
ust limit girin <ust_limit>
```

- `<proses_sayisi>`: Kullanmak istediğiniz işlemci çekirdeği sayısı.


Örnek kullanım:

```sh
mpirun -np 4 ./palandoken
alt limit girin 1
ust limit girin 1000000
```

Bu komut, 1 ile 1.000.000 arasındaki palandöken sayılarını bulmak için 4 işlemci çekirdeği kullanacaktır.


