#include "read_config.h"

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    printf ("arg %d = %s\n", i, argv[i]);
  }

  read_config ("test.cfg", "output.cfg");

  return (EXIT_SUCCESS);
}
