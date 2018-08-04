#include <stdio.h>

typedef unsigned int u32;

/* Value matrix */
#if 0
u32 matrix[9][9] =
{
{0,3,0,0,0,0,1,6,0},
{0,9,0,0,8,0,0,4,2},
{6,0,2,3,7,0,0,0,0},
{8,0,3,6,4,2,0,0,0},
{0,7,0,8,0,5,0,3,0},
{0,0,0,1,3,7,4,0,5},
{0,0,0,0,1,4,8,0,9},
{2,8,0,0,5,0,0,1,0},
{0,1,9,0,0,0,0,2,0}
};
#endif
#if 0
u32 matrix[9][9] =
{
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}
};
#endif
#if 1
u32 matrix[9][9] =
{
{1,0,0,0,0,6,0,3,7},
{0,0,0,0,0,0,0,0,0},
{0,5,0,9,2,0,0,8,0},
{5,0,0,0,0,8,0,9,0},
{6,0,0,4,0,2,0,0,8},
{0,8,0,3,0,0,0,0,1},
{0,7,0,0,4,3,0,6,0},
{0,0,0,0,0,0,0,0,0},
{9,6,0,7,0,0,0,0,4}
};
#endif
/* Probability Matrix */
u32 pr[9][9];

u32 validate_num(u32 num, u32 x, u32 y)
{
	u32 i, j;
	u32 m, n;

	for (i = 0; i < 9; i++) {
		if (matrix[x][i] == num)
			return 0;
		if (matrix[i][y] == num)
			return 0;
	}

	m = (x/3)*3;
	n = (y/3)*3;
	for (i = m; i < (m + 3); i++) {
		for (j = n; j < (n + 3); j++) {
			if (matrix[i][j] == num)
				return 0;
		}
	}

	return 1;
}

u32 fill_num(const u32 x, const u32 y)
{
	u32 num = 1;

	if (x > 9 || y > 9) {
		printf("%s %d Invalid condition!\n", __func__, __LINE__);
		exit(1);
	}

	if (pr[x][y] == 100) {
		return 1;
	}

	if (matrix[x][y] == 0) {
		num = 1;
	} else {
		num = matrix[x][y];
	}

	for(; num <= 9; num++) {
		if (validate_num(num, x, y)) {
			matrix[x][y] = num;
			break;
		}
	}

	if (num > 9) {
		matrix[x][y] = 0;
		pr[x][y] = 0;
		return 0;
	}

	return 1;
}

void print_sudoku()
{
	u32 i, j;

	for(i = 0; i < 9; i++) {
		printf("\n-------------------------\n");
                for (j = 0; j < 9; j++) {
			if (j%3 == 0)
				printf("| ");
			printf("%d ", matrix[i][j]);
		}
	}
	printf("\n-------------------------\n");
}

void go_back(u32 *i, u32 *j)
{
	u32 m = *i;
	u32 n = *j;

	while(1) {
		if (n == 0) {
			if (m == 0) {
				printf("%s %d Invalid condition!\n", __func__, __LINE__);
				print_sudoku();
				exit(1);
			} else {
				m--;
				n = 8;
			}
		} else {
			n--;
		}

		if (pr[m][n] != 100) {
			break;
		}
	}

	*i = m;
	*j = n;
}

int main()
{
	u32 i, j;

	/* Initialize value matrix and probability matrix */
	for(i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			//matrix[i][j] = 0;
			if (matrix[i][j] > 0)
				pr[i][j] = 100;
			else
				pr[i][j] = 0;
		}
	}

	print_sudoku();

	unsigned long long itr = 0;
#if 0
	unsigned long long max_itr;
	scanf("%Ld", &max_itr);
#endif
	for(i = 0; i < 9; i++) {
		for (j = 0; j < 9; ) {
			itr++;
#if 0
			if (itr > max_itr) {
				printf("%s %d Invalid condition!\n", __func__, __LINE__);
				print_sudoku();
				exit(1);
			}
#endif
			//printf("(%d, %d) %d %d\t", i, j, matrix[i][j], pr[i][j]);
			if (!fill_num(i,j)) {
				go_back(&i, &j);
				continue;
			}
			j++;
		}
		//printf("\n");
	}


	print_sudoku();

	printf("Number of iterations: %Ld\n", itr);

	return 0;
}
