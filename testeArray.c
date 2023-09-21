#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   // The multidimentional array...
   char balance[5][100] = {
       "Subham",
       "Messi"
   };

   char (*p)[5][100] = &balance; // Pointer initialization...

   printf("%s\n",(*p)[0]); // Calling...
   printf("%s\n",(*p)[1]); // Calling...

  return 0;
}