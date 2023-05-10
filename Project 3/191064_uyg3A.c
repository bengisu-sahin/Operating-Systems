/**
 * @file 191064_Uyg3A.c
 * @author Bengisu Şahin (sahin_bengisu00@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @brief global değişkenler
 *
 */
struct stat prop;
struct stat updated_stat;
int isModified;
char *pathRep;

/**
 * @brief pathSub dizinindeki değişiklikleri takip ederek terminale ve bir log dosyasına değişiklikleri yazdırır. Ayrıca, değişen dosyaları pathRep dizinine kopyalar. Terminale de aynı zamanda zaman bilgisini yazdırır.
 *
 * @param p
 * @return void*
 */
void *printTimeAndFileCh(void *p)
{

    char cmd[500];
    char *pathSub = (char *)p;
    char pathLogFile[250] = "191064_uyg3A_repHist.log";

    printf("\nPrinting Time and Changes ->\n");
    printf("pathSub: %s\n", pathSub);
    printf("pathLog: %s\n\n", pathLogFile);

    while (1)
    {
        if (isModified)
        {
            printf("Last modified time: %s\n", ctime(&prop.st_mtime));
            sprintf(cmd, "echo \"Last modified time: %s\" >> %s", ctime(&prop.st_mtime), pathLogFile);
            system(cmd);

            printf("%s: ", pathSub);
            sprintf(cmd, "echo \"%s: \" >> %s", pathSub, pathLogFile);
            system(cmd);

            sprintf(cmd, "ls %s -la", pathSub);
            system(cmd);
            sprintf(cmd, "ls %s -la >> %s", pathSub, pathLogFile);
            system(cmd);

            sprintf(cmd, "echo \"--------------------------------\n\" >> %s", pathLogFile);
            printf("-------------------------------------------------\n");
            system(cmd);

            sprintf(cmd, "cp -r %s* %s", pathSub, pathRep);
            system(cmd);
            sleep(2);
        }
        printf("\r\033[1A%c", system("date"));
        fflush(stdout);
        usleep((int)(100000));
    }
}

/**
 * @brief Bu fonksiyon, pathSub dizinindeki son değişiklik zamanını takip ederek, dosyada değişiklik olduğunda isModified değişkenini günceller. printTimeAndFileCh fonksiyonu, isModified değişkenini kontrol ederek, dosya değişikliği olduğunda ilgili işlemleri gerçekleştirir.
 *
 * @param prm
 * @return void*
 */

void *Checker(void *prm)
{
    char *pathSub = (char *)prm;
    printf("\nChecke ->\n");
    printf("pathChk: %s\n", pathSub);
    for (int i = 0; i < 1;)
    {
        stat(pathSub, &prop);
        sleep(1);
        isModified = 0;
        stat(pathSub, &updated_stat);

        if (prop.st_mtime != updated_stat.st_mtime)
            isModified = 1;
    }
}

/**
 * @brief Bu program, kullanıcı tarafından komut satırında girilen iki dizin yolu (pathRep ve pathSub) için bir izleyici görevi görür. Checker fonksiyonu, pathSub dizinindeki son değişiklik zamanını takip ederek, dosyada değişiklik olduğunda isModified değişkenini günceller. printTimeAndFileCh fonksiyonu, isModified değişkenini kontrol ederek, dosya değişikliği olduğunda ilgili işlemleri gerçekleştirir ve değişiklikleri kaydeder.main fonksiyonu, girilen argüman sayısını kontrol eder ve doğru sayıda argüman girilmediğinde programı sonlandırır. Daha sonra, Checker ve printTimeAndFileCh thread leri oluşturur ve pthread_join fonksiyonu ile bu thread lerin tamamlanmasını bekler.
 *
 * @param argc
 * @param argv
 * @return int
 */

int main(int argc, char *argv[])
{

    if (argc < 3 || argc > 3)
    {
        printf("You have provided an incorrect number of arguments");
        printf("\nThis program requires exactly two additional arguments: pathRep and pathSub. Please ensure that you have provided the correct number of arguments when executing the program '%s'.\n", argv[0]);
        printf("Cancelled automatically\n");
        exit(1);
    }

    pathRep = argv[1];
    isModified = 0;
    pthread_t threadChecker, threadWorker;
    printf("\nMain Function ->\n");
    printf("pathRep: %s\n", argv[1]);
    printf("pathSub: %s\n", argv[2]);

    pthread_create(&threadChecker, NULL, Checker, argv[2]);
    pthread_create(&threadWorker, NULL, printTimeAndFileCh, argv[2]);

    pthread_join(threadChecker, NULL);
    pthread_join(threadWorker, NULL);

    return 0;
}