#include <stdio.h>
#include <uuid/uuid.h>

int main(void)
{
  uuid_t uu;
  int i;
  uuid_generate(uu);

  for(i = 0; i < 16; i++)
  {
    printf("%02X", uu[i]);
  }

  printf("\n");

  return 0;
}
