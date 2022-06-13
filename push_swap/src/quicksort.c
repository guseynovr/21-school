static int	partition(int *arr, int lo, int hi)
{
	int	tmp;
	int	pivot;

	pivot = arr[(lo + hi) / 2];
	while (1)
	{
		while (arr[lo] < pivot)
			lo++;
		while (arr[hi] > pivot)
			hi--;
		if (lo >= hi)
			return (hi);
		tmp = arr[lo];
		arr[lo++] = arr[hi];
		arr[hi--] = tmp;
	}
}

void	quicksort(int *arr, int lo, int hi)
{
	int	p;

	if (lo >= hi)
		return ;
	p = partition(arr, lo, hi);
	quicksort(arr, lo, p);
	quicksort(arr, p + 1, hi);
}
