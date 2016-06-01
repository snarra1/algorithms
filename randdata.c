#include <stdio.h>

int main(int argc, char *argv[])
{
  int i, n;

  sscanf(argv[1], "%d", &n);

  printf("%d\n", n);

  for (i = 0; i < n; ++i)
    {
      printf("%d\n", random());
    }
}