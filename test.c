void check_devided(char **arr,int len, int i, int j)
{
	if ( i == len - 1)
	{
		printf ("oooooooooo\n");
		exit(1);
	}
	while (arr[i][j] && arr[i][j] == ' ')
		j++;
	while (j >= 0 && arr[i][j] == ' ')
	{
		if (arr[i + 1] && arr[i + 1][j] == ' ')
			check_devided(arr,i + 1, j);
		if (arr[i][j - 1] == ' ')
			j--;
		else
			break ;
	}
	return (i);
}