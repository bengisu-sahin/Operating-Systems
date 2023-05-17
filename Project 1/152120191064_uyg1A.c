/**
 * @file 1521201910648_uyg1C.cpp
 * @author Bengisu Şahin (sahin.bengisu00@gmail.com)
 * @brief Kullanıcıdan alınan sayıdan küçük en büyük ve yine aynı sayıdan büyük en küçük asal sayıları listeleyen kaynak kod
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Bu fonksiyon, fonksiyona gönderilen sayının asal sayı olup olmadığını kontrol eder. Asal ise "1", değilse "0" döndürür.
 *
 * @param n
 * @return 1
 * @return 0
 */

int prime_or_not(int n)
{
  if (n < 2)
  {
    return 0;
  }
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int main(int argc,char* argv[])
{
  /**
   * @brief Kullanıcıdan bir sayı girmesi istenir.
   */
  int num,smaller,bigger;
  num=atoi(argv[1]);
  /**
   * @brief Sayıdan küçük ve sayıdan büyük olan sayılar kontrol edilir. prime_or_not fonksiyonunda
   * gelen ilk "1" (true) yanıtında döngülerden çıkılır , sayıdan küçük en büyük ve sayıdan büyük en küçük
   * asal sayı ekrana yazdırılır.
   */
  smaller = num - 1;
  bigger = num + 1;
  while ( smaller > 1 && prime_or_not(smaller) != 1 )
  {
    smaller = smaller - 1;
  }
  while ( prime_or_not(bigger) != 1 )
  {
    bigger = bigger + 1;
  }
  printf("Result for number %d: ",num);
  printf("%d, ", smaller);
  printf("%d\n", bigger);
  
  return 0;
}