/**
 * @file 191064_Uyg2A.c
 * @author Bengisu Sahin (bngsshn@gmail.com)
 * @brief Proses ağacını oluşturma
 * @version 0.1
 * @date 2023-04-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int opt1 = 0;
    int opt2 = 0;
    int cmd;
    int depth = 0, controlInput = 0, numCont = 0, temp = 0;
    char pstreeCmd[250];
    char pstreeLogCmd[250];
    char command[250];
    int pid = getpid();
    int ppid = getppid();
    sprintf(pstreeCmd, "pstree -p %d", pid);
    sprintf(pstreeLogCmd, "pstree -p %d >> logs/logAll.log", pid);
    /**
     * @brief Kullanıcının girdiği komutlar okunur, option kontrolü ve isim yazdırma için flaglar set edilir.
     * depth değişkeni alınır ve atio ile int e cevirilir. 
     */
    while ((cmd = getopt(argc, argv, "id")) != -1)
    {
        controlInput = 1;
        if(cmd=='i'){
            opt1 = 1;
        }
         if(cmd=='d'){
            opt2 = 2;
        }
        for (int i = 2; i < argc; i++)
        {
            numCont = 1;
            depth = atoi(argv[i]);
            break;
        }
    }

   /**
    * @brief Options kontrolleri
    * 
    */
    if (controlInput == 0)
    {
        if (argc <= 1 || argc > 2)
        {
            printf("Cancelled automatically...\n");
        }

    }
    else
    {
        if (opt1 == 1 && opt2 == 1)
        {
            printf("152120191064 @bengisusahin wrote this. \n");
            if (numCont == 0)
            {
                printf("Cancelled automatically...\n");
            }
            else if (numCont == 1)
            {
                if (depth < 1)
                {
               
                    printf("Cancelled automatically...\n");
                }
                else
                {
                    depth *= 2;
                }
            }
        }
        else if (opt1 == 1)
        {
            printf("152120191064 @bengisusahin wrote this. \n");
            if (numCont == 0)
            {
                printf("Cancelled automatically...\n");
            }
            else
            {
                if (depth < 2)
                {
                    printf("Cancelled automatically...\n");
                }
            }
        }
        else if (opt2 == 1)
        {
            if (depth > 0)
            {
                depth *= 2;
            }
            else
            {
                printf("Cancelled automatically...\n");
            }
        }

        else if (numCont == 1)
        {
            if (depth < 2)
            {
                printf("Cancelled automatically...\n");
            }
        }
        else
        {
            printf("Cancelled automatically...\n");
        }
    }
/**
 * @brief agacı tamamlama ve log dosyasına yazma 
 * 
 */
    for (int i = 0; i <= depth; i++)
    {
        pid = fork();
        if (pid == 0) // first child
        {
            printf("\nPID: %d, PPID: %d \n", getpid(), getppid());
        }
        else if (pid > 0)
        {
            if (i == 0) // first parent
            {
                system("mkdir -p logs");                             // Create log folder
                sprintf(command, "echo $(date) >> logs/logAll.log"); //Log date
                system(command);
                sprintf(command, "echo PID: %d, depth: %d >> logs/logAll.log", getpid(), depth);
                system(command);
                sprintf(command, "pstree %d -p >> logs/logAll.log", getpid()); // Log ps tree
                system(command);
                printf("----------------logs/logAll.log--------------------\n");
                sprintf(command, "cat logs/logAll.log");
                system(command);
                printf("--------------------------------------------------\n");
                system(pstreeCmd);
            }

            wait(NULL); // wait child
            printf("\nPID: %d, PPID: %d : terminated\n", getpid(), getppid());
            break;
        }
    }
    sleep(1);
}