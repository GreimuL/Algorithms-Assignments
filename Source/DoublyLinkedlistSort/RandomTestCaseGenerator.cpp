#include<time.h>
#include<stdlib.h>
#include<cstdio>
int main()
{
	FILE *file_pointer;
	file_pointer = fopen("test.txt", "w");

	//Number of inputs
	int n;	
	scanf("%d",&n);

	fprintf(file_pointer, "%d ", n);
	srand(time(NULL));
	for (int i = 0; i < 100000; i++) {
		fprintf(file_pointer, "%d ", rand() % 100000 + 1);
	}
	fprintf(file_pointer, "\n");
	fclose(file_pointer);
	return 0;
}

