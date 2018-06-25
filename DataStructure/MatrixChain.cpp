#include "stdafx.h"
#include <vector>

using namespace std;

/*
Input: Sequence d0, d1, ..., dn of integer
Output: For i,j = 0 ... (n-1) the minimum number of multiplication Ni,j needed to compute the product 
Ai.Ai+1....Aj where Ak is a dk x dk+1 matrix
*/
int MatrixChain(const vector<int> &da)
{
	int n = da.size();
	int i, j;

	vector<vector<int>> N(n);
	for (int i = 0; i < n; i++)
	{
		N[i] = vector<int>(n);
		N[i][i] = 0;
	}

	for (i = 0; i < (n - 1); i++)
	{
		for (j = i + 1; j < n; j++)
		{
			N[i][j] = INT_MAX;
			for (int k = i; k < j; k++)
			{
				int tempResult =
					N[i][k] + N[k + 1][j] + da[i] * da[k + 1] * da[j];
				if (N[i][j] < tempResult)
					N[i][j] = tempResult;
			}
		}
	}
	return N[0][n - 1];
}




