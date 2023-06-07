/**
 * @file 191064_uyg5A.c
 * @author Bengisu Şahin (sahin.bengisu00@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

enum body
{
    HEAD,
    UBDY,
    HAND,
    LEG_,
    FOOT
};
#define NUMOFITEMS 13

pthread_t headThread, ubdyThread, handThread, legThread, footThread;
pthread_mutex_t dressItemSyn;
int count = 0;
sem_t footSem, ubdySem, headhandSem, tulumSem, headSem, handSem, legSem;

/**
 * @brief Bu fonksiyon, belirli bir vücut parçasına ait bir giysi öğesini temsil eden bir karakter dizisini atar ve ilgili bilgileri koşullara uygun şekilde (if-else) ekrana yazdırır.
 * 
 * @param part 
 * @param name 
 */

void dressItem(int part, char* name)
{

    static const char* BODY_STRING[] = { "kafa ", "govde", "el   ", "bacak", "ayak " };

    if (count == 0)
    {
        printf("%2d. \t\t\t\t\t--> Saglik calisanlarina sonsuz tesekkurler!..\n", count);
    }
    printf("%2d. (%s) %s ", ++count, BODY_STRING[part], name);
    if (NUMOFITEMS - count == 0 && count >= 7)
    {
        printf("\t--> Goreve hazirim!\n");
    }
    else if (NUMOFITEMS - count != 0 && count >= 7)
    {
        printf("\t--> Kalan oge sayisi: %2d\n", NUMOFITEMS - count );
    }
    else
    {
        printf("\n");
    }
}

/**
 * @brief Bu fonksiyon, "HEAD" vücut parçasına ait giysi öğelerini sırayla giydirirken semaforları kullanarak senkronizasyon sağlar.
 * 
 * @param p 
 */

void funcHEAD(void* p)
{
    sem_wait(&headSem);

    dressItem(HEAD, "YuzDezenfektani          ");

    sem_wait(&headhandSem);

    dressItem(HEAD, "SaglikMaskesi            ");
    dressItem(HEAD, "Bone                     ");

    sem_post(&tulumSem);

    sem_wait(&headSem);

    dressItem(HEAD, "KoruyucuPlastikYuzMaskesi");
}

/**
 * @brief Bu fonksiyon, giysi öğelerinin "UBDY" vücut parçasına uygun sırayla giydirilmesini ve semaforlar aracılığıyla senkronizasyon sağlanarak paralel iş parçacıkları arasında uyumlu bir şekilde çalışılmasını sağlamayı hedefler.
 * 
 * @param p 
 */

void funcUBDY(void* p)
{
    dressItem(UBDY, "Atlet                    ");
    dressItem(UBDY, "Gomlek                   ");

    sem_post(&ubdySem);
    sem_wait(&tulumSem);

    dressItem(UBDY, "Tulum                    ");

    sem_post(&headSem);
    pthread_exit(0);
}

/**
 * @brief Bu fonksiyon, "p" olarak adlandırılan bir işaretçi parametresi alır. İşlevde, semaforları kullanarak senkronizasyon sağlanır ve "HAND" (el) vücut parçasına ait giysi öğeleri sırayla giydirilir.
 * 
 * @param p 
 */

void funcHAND(void* p)
{
    sem_wait(&handSem);

    dressItem(HAND, "ElDezenfektani           ");
    dressItem(HAND, "Eldiven                  ");

    sem_post(&headhandSem);
}

/**
 * @brief Semaforları kullanarak senkronizasyon sağlanır ve "LEG_" (bacak) vücut parçasına ait giysi öğeleri sırayla giydirilir.
 * 
 * @param p 
 */

void funcLEG_(void* p)
{
    sem_wait(&footSem);

    dressItem(LEG_, "Pantolon                 ");
    dressItem(LEG_, "Kemer                    ");

    sem_post(&legSem);
}

/**
 * @brief Semaforları kullanarak senkronizasyon sağlanır ve "FOOT" (ayak) vücut parçasına ait giysi öğeleri sırayla giydirilir.
 * 
 * @param p 
 */

void funcFOOT(void* p)
{
    sem_wait(&ubdySem);

    dressItem(FOOT, "Corap                    ");

    sem_post(&footSem);
    sem_wait(&legSem);

    dressItem(FOOT, "Ayakkabi                 ");

    sem_post(&headSem);
    sem_post(&handSem);
}

/**
 * @brief "main" fonksiyonu giysi giydirmesi sürecini yönetir, iş parçacıklarını oluşturur ve sonlandırır, semaforlar ve mutex ile senkronizasyon sağlar ve sonunda kaynakları temizler.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char* argv[])
{

    sem_init(&footSem, 0, 0);
    sem_init(&ubdySem, 0, 0);
    sem_init(&headhandSem, 0, 0);
    sem_init(&tulumSem, 0, 0);
    sem_init(&headSem, 0, 0);
    sem_init(&legSem, 0, 0);
    sem_init(&handSem, 0, 0);

    pthread_mutex_init(&dressItemSyn, NULL);

    pthread_create(&headThread, NULL, (void*)funcLEG_, NULL);
    pthread_create(&ubdyThread, NULL, (void*)funcHEAD, NULL);
    pthread_create(&handThread, NULL, (void*)funcUBDY, NULL);
    pthread_create(&legThread, NULL, (void*)funcFOOT, NULL);
    pthread_create(&footThread, NULL, (void*)funcHAND, NULL);

    pthread_join(headThread, NULL);
    pthread_join(ubdyThread, NULL);
    pthread_join(handThread, NULL);
    pthread_join(legThread, NULL);
    pthread_join(footThread, NULL);

    pthread_mutex_destroy(&dressItemSyn);

    sem_destroy(&footSem);
    sem_destroy(&ubdySem);
    sem_destroy(&headhandSem);
    sem_destroy(&tulumSem);
    sem_destroy(&headSem);
    sem_destroy(&legSem);
    sem_destroy(&handSem);
}