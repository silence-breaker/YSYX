#include <stdlib.h>
int main() {
	int x;
	if(x>0){
		printf(" ");
	}
  int *p = malloc(sizeof(*p) * 10);
  free(p);
  *p = 0;
  return 0;
}
