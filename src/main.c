#include <stdio.h>
#include <fizzbuzz.h>

int main() {
  int i;

  for (i = 1; i <= 100; ++i)
    printf("%s\n", fizzbuzz(i));

  return 0;
}
