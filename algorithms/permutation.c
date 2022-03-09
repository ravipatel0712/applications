#include <stdio.h>

#define M 100

int sequence[M];
int len;

void process()
{
	for (int i = 0; i < len; i++) {
		printf("%d", sequence[i]);
	}
	printf("\n");
}

void swap(int a, int b)
{
	int temp = sequence[a];
	sequence[a] = sequence[b];
	sequence[b] = temp;
}

void permute(int left, int right)
{
	if (left == right)
		process();

	for (int i = left; i <= right; i++) {
		swap(left, i);
		permute(left+1, right);
		swap(left, i);
	}
}

int main()
{
	int i;

	scanf("%d", &len);
	for (i = 0; i < len; i++) {
		scanf("%d", &sequence[i]);
	}

	permute(0, len-1);

	return 0;
}
