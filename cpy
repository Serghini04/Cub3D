void check_arrmap(t_map *map, int len)
{
    int     i;
    int     j;
    char    **arr;

    i = 0;
    arr = map->tab_map;
    check_firstlastline(map, arr, len);
    while (i < len - 1)
    {
       j = 0;
       while ((arr[i] && arr[i + 1]) && (arr[i][j] && arr[i + 1][j]))
       {
            if((arr[i][j] == '0' && arr[i + 1][j] == ' ') || arr[i][0] == '0')
            {
                free_myallocation(map);
                printf ("0Invalid map\n");
                exit(EXIT_SUCCESS);
            }
            else if (arr[i][j] == ' ' && arr[i + 1][j] == '0')
            {
                free_myallocation(map);
                printf ("1Invalid map\n");
                exit(EXIT_SUCCESS);
                
            }
            else if (arr[i][j + 1] == ' ' && arr[i][j] == '0'  )
            {
                free_myallocation(map);
                printf ("2Invalid map\n");
                exit(EXIT_SUCCESS);
                
            }
            else if (arr[i][j] == ' ' && (arr[i][j + 1] == '0' || is_player(arr[i + 1][j])))
            {
                if (is_player(arr[i + 1][j]))
                    printf ("Invalid position of player !\n");
                else
                    printf ("3Invalid map\n");
                free_myallocation(map);
                exit(EXIT_SUCCESS);
            }
            else if (arr[i][j] == '0' && (arr[i][j + 1] == '\0' || arr[i][j + 1] == ' ' || arr[i][j + 1] == '\n'))
            {
                free_myallocation(map);
                printf ("4Invalid map\n");
                exit(EXIT_SUCCESS);
            }
            else if ((is_player(arr[i][j])) && (j == 0 || arr[i][j + 1] == ' ' || arr[i + 1][j] == ' ' || arr[i][j + 1] == '\n'))
            {
                free_myallocation(map);
                printf("Invalid position of player !\n");
                exit(EXIT_SUCCESS);
            }
            else if ((is_player(arr[i][j + 1])) && (arr[i][j] == ' ' || arr[i + 1][j + 1] == ' ' || arr[i][j + 1] == '\n'))
            {
                free_myallocation(map);
                printf("Invalid position of player !\n");
                exit(EXIT_SUCCESS);
            }

            j++;
       }
       while (arr[i] && arr[i][j])
       {
        
            if ((arr[i][j] != '1' && arr[i][j] != '\n' && arr[i][j] != ' ') || is_player(arr[i][j]))
            {
                if (is_player(arr[i][j]))
                    printf("Invalid position of player !\n");
                else
                    printf ("5Invalid map\n");
                free_myallocation(map);
                exit(EXIT_SUCCESS);
            }
            j++;
       }
       {
        
       }
       i++;
    }
    
}