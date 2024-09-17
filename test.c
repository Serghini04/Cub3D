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



   11111111111          
1111N1111             
1111111111111111 
1111111111111111
1111111111111111
1111111111111111

//ser

              11111111111                       
          1111N1111                          
              1111111111 111111        
             11111111111 1111         
             111111111  11111        
                     111111111111111           




    11111111111          
    1111N1111             
     1111111111111111        
    1111111111111111         
     1111111111111111        
     1111111111111111           


         111111111111111 1111111            
           1111111111N11      1                   
              1111111111 111111                       
             11111111111 111                            
             1           11111                             
           11111111111111111                                  


        11111111111111     
       10000000E0000001    
        111111111111111


SO       textures/SO.xpm
WE       textures/new1.xpm
NO       textures/egy.xpm
EA      textures/wall1.xpm