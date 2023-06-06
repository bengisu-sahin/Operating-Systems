/**
 * @file 191064_uyg4A.c
 * @author Bengisu Şahin (bngsshn@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-14
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
#include <signal.h>

/**
 * @brief global variables
 *
 */

time_t last_modified;
int is_modified = 23;
struct stat attr;

/**
 * @brief ListenChanges() fonksiyonu, belirli bir dosyanın değişiklik zamanını saniye başına kontrol eder. Değişiklik zamanı değişirse, dosyanın değiştirildiğini belirtmek için bir işaret koyar.
 *
 * @param arg
 * @return void*
 */

void *listenChanges(void *arg)
{
    char *inp_path = (char *)arg;
    stat(inp_path, &attr);
    last_modified = attr.st_mtime;
    printf("\t-> Listening  changes:\n");
    sleep(1);
    while (1)
    {
        stat(inp_path, &attr);
        if (last_modified != attr.st_mtime)
        {
            last_modified = attr.st_mtime;
            is_modified = 1;
        }
        sleep(1);
    }
}

/**
 * @brief Bu fonksiyon, bir argüman olarak aldığı input dosyasını okuyarak içindeki bir öğrenci numarasını alır. Daha sonra, öğrenci numarasının ilk iki basamağını fakülte numarası olarak, son iki basamağını bölüm numarası olarak ve son altı basamağını ise kayıt yılı olarak ayırır. Ardından, fakülte ve bölüm numaralarına göre 4 farklı senaryodan birine göre işlem yapar. İşlem sonunda ise program sonlandırılır.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char **argv)
{
    /**
     * @brief Burada doğru sayıda argumanın kullanıcı tarafından girilip girilmediğinin kontrolü yapılmaktadır.
     * 
     */
    if (argc < 2)
    {
        printf("\n%s must be executed with exactly one additional argument (pathInputFile)!\n", argv[0]);
        printf("Typed count is %d\n", argc);
        printf("Aborted automatically\n");
        return 0;
    }

    else if (argc > 2)
    {
        printf("\nToo many arguments!%s must be executed with exactly one additional argument  (pathInputFile)!\n", argv[0]);
        printf("Aborted automatically...\n");
        return 0;
    }

    char *pathInp, number[32];
    long long mesaj;
    int pfd[2], child, child_status;
    pthread_t listenChange;

    pathInp = argv[1];
    pipe(pfd);
    printf("Pipe was created successfully...\n");
    child = fork(); 

    /**
     * @brief Dosyanın değiştirilip değiştirilmediği takip edilir ve dosyanın değiştirilmesi durumunda dosyadaki girdi okunur.
    önce bir child process oluşturulur ve child process değişiklikleri dinlemek için thread oluşturur. Ardından, bir döngü oluşturur ve dosyanın değiştirilip değiştirilmediğini kontrol eder. Dosya değiştirildiğinde, dosyadaki sayıyı okur ve sayının doğru formatta olup olmadığını kontrol eder. Sayı doğru formatta değilse, döngü devam eder ve dosya tekrar değiştirilene kadar bekler. Sayı doğru formatta ise, child, sayıyı parent a gönderir ve sonrasında 4 saniye bekler (sleep).Parent, child tarafından gönderilen sayıyı alır ve fakülte, bölüm ve yıl bilgilerini çıkarır. Burdan hareket le ilgili case lere göre davranıs sergilenir. (Case A,B,C ve D olmak üzere 4 case vardır.)
    
        -Fakülte 15 ve bölüm 21 ise (CASE A), ebeveyn süreç, çocuk sürecinin tamamlanmasını bekler ve sonra programdan çıkar.
        -Yıl 2017'den büyükse (CASE B), ebeveyn süreç, 4 saniye uyur ve sonra programdan çıkar.
        -Fakülte 15 değilse (CASE C), ebeveyn süreç, 6 saniye uyur ve sonra programdan çıkar.
        -Yukarıdaki koşullardan hiçbiri geçerli değilse (CASE D), ebeveyn süreç programdan çıkar.
     * 
     */

    if (child == 0)
    {
        printf("Child\t-> My PID is %d, PPID is %d\n", getpid(), getppid());
        pthread_create(&listenChange, NULL, listenChanges, argv[1]);
        while (1)
        {
            if (is_modified == 1 || is_modified == 23)
            {
                printf("\t-->Last updated\n");

                FILE *fp;
                fp = fopen(pathInp, "r");
                fscanf(fp, "%lli", &mesaj);

                sprintf(number, "%lli", mesaj);
                printf("\t\t%s: %lli\n", pathInp, mesaj);
                if (strlen(number) < 12)
                {
                    printf("\t\t-- wrong input! few digits...");
                    is_modified = 0;
                }
                else if (strlen(number) > 12)
                {
                    printf("\t\t-- number of digits overflowed..");
                    is_modified = 0;
                }
                else
                {
                    printf("Child\t -> Parsing and printing Student ID\n");
                    break;
                }
            }
        }
        close(pfd[0]);
        write(pfd[1], &mesaj, sizeof(mesaj));
        close(pfd[1]);
        printf("Child\t->Slept 4 seconds\n");
        sleep(4);
        exit(1);
    }
    else
    {
        printf("Parent\t-> My PID is %d, PPID is %d\n", getpid(), getppid());
        sleep(1);
        long long alinan;

        close(pfd[1]);
        read(pfd[0], &alinan, sizeof(alinan));
        close(pfd[0]);
        printf("Incoming message from child is %lli\n", alinan);

        long long fakulte = alinan;
        long long bolum = alinan;
        long long yil = alinan;

        while (fakulte >= 100)
            fakulte /= 10;

        while (bolum >= 10000)
            bolum /= 10;

        while (yil >= 100000000)
            yil /= 10;

        bolum = bolum - fakulte * 100;
        yil = yil - (fakulte * 1000000 + bolum * 10000);
        printf("fakulte:%lli, bolum:%lli, yil:%lli\n", fakulte, bolum, yil);
        if (fakulte == 15 && bolum == 21)
        { // CASE A
            printf("CASE A\n");
            wait(&child_status);
            return 0;
        }
        else if (yil >= 2017)
        { // CASE B
            printf("CASE B\n");
            printf("sleep clock for 4 sec\n");
            sleep(4);
            return 0;
        }
        else if (fakulte != 15)
        { // CASE C
            printf("CASE C\n");
            sleep(6);
            return 0;
        }
        else
        { // CASE D
            printf("CASE D\n");
            return 0;
        }
    }
}