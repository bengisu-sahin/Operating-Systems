/**
 * @file 191064_uyg6A.c
 * @author Bengisu Şahin (sahin.bengisu00@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

/**
 * @brief Fonksiyon Tanımlamaları
 *
 */

void dummyFunc();
void testAddress(char *);
void handler(int, siginfo_t *, void *);

/**
 * @brief Değişkenler
 *
 */

extern int etext, edata, __executable_start;
int globlVar = 1;
jmp_buf temp;

/**
 * @brief Bu main() fonksiyonu, birkaç değişkenin değerlerini ve adreslerini ekrana yazdırır, işlev prototiplerini ve adreslerini ekrana yazdırır, programın farklı bellek bölgelerinin adreslerini ekrana yazdırır ve SIGSEGV sinyalini işlemek için bir işleyici atanır.
 *
 * @return int
 */

int main()
{
	int localVar = 6;
	int *localVar2 = (int *)malloc(sizeof(int));
	*localVar2 = localVar;
	signal(SIGSEGV, (void *)handler);

	printf("\n\npageSize = %u\n", getpagesize());

	printf("globlVar = %d\n", globlVar);
	printf("&globlVar = %p\n", &globlVar);

	printf("localVar = %d\n", localVar);
	printf("&localVar = %p\n", &localVar);

	printf("*localVar2 = localVar = %d\n", *localVar2);
	printf("localVar2 = %p\n", localVar2);
	printf("&localVar2 = %p\n", &localVar2);

	printf("\nPrototypes: \n");
	printf("void dummyFunc()	//Does nothing\n");
	printf("void testAddress(char* addr)	//Test address\n");
	printf("void handler(int, siginfo_t*, void*)	//To jump the specific location that we defined before in main()\n");

	printf("\nAddresses\n");
	printf("&dummyFunc() = %p\n", &dummyFunc);
	printf("&testAddress() = %p\n", &testAddress);
	printf("&handler() = %p\n", &handler);
	printf("&main() = %p\n", &main);

	printf("\ntext-seg 1st page  = %p\n", &__executable_start);
	printf("text-seg end = %p\n", &etext);
	printf("data-seg end = %p\n", &edata);
	printf("heap-seg end = %p\n", sbrk(0));

	testAddress((void *)&globlVar);
}

/**
 * @brief Sadece tanımlanmış bir fonksiyondur.
 *
 */

void dummyFunc() {}

/**
 * @brief Bu fonksiyon, bir bellek adresinin okunabilirliğini ve yazılabilirliğini test etmek için kullanılır.
 *
 * @param addr
 */

void testAddress(char *addr)
{
	char c;
	printf("\nReading %p: \n", addr);
	c = *addr;

	printf("Value is %d\n", c);
	printf("Writing %d back to %p: \n", c, addr);
	fflush(stdout);
	*addr = c;

	printf("ok\n\n\n\n");
}

/**
 * @brief Bu fonksiyon, bir SIGSEGV sinyali (segmentasyon hatası) yakalandığında çalışacak olan bir işleyici işlevidir.
 *
 * @param a
 * @param b
 * @param c
 */

void handler(int a, siginfo_t *b, void *c)
{
	printf("Segmentation Fault handled.\n");
	longjmp(temp, SIGSEGV);
}