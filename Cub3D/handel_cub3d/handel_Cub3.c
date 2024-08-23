/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_Cub3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:50 by hidriouc          #+#    #+#             */
/*   Updated: 2024/08/23 16:08:36 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}
void    free_myallocation(t_map *map)
{
    char    **arr;
    int     i;
    
    i = -1;
    arr = map->tab_map;
    free(map->tex_no);
    map->tex_no = NULL;
    free(map->tex_so);
    map->tex_so = NULL;
    free(map->tex_we);
    map->tex_we = NULL;
    free(map->tex_ea);
    map->tex_ea = NULL;
    while (arr[++i])
        free(arr[i]);
    free(arr);
    map->tab_map = NULL;
}

int is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
    return (0);
}

void    check_namemap(t_map *map, char *name_map)
{
    int     i;
    char    *ptr;

    i = 0;
    while (name_map[i])
        i++;
    ptr = &name_map[i - 4];
    if (ft_strncmp(ptr, ".cub", 4))
    {
        free (map);
        printf("Name of file_map Unvalide!\n");
        printf("EXE : PATH/filename.cub\n");
        exit(EXIT_SUCCESS);
    }
}
int check_beginning(char *line)
{
    if (!ft_strncmp(line, "NO ", 3))
        return (1);
    else if (!ft_strncmp(line, "SO ", 3))
        return (2);
    else if (!ft_strncmp(line, "WE ", 3))
        return (3);
    else if (!ft_strncmp(line, "EA ", 3))
        return (4);
    else if (!ft_strncmp(line, "C ", 2))
        return (5);
    else if (!ft_strncmp(line, "F ", 2))
        return (6);
   return (0); 
}

int ft_check_maxcollor(int R, int G, int B)
{
    if (R > 255 || R < 0 || G > 255 || G < 0 ||  B > 255 || B < 0)
        return (1);
    return (0);
}

void    check_syntax(t_map *map, char *line, int index_line)
{
    int i;
    int len;

    len = ft_strlen(line); 
    i = 0;
    if((line[0] < '0' || line[0] > '9') || line[len - 1] < '0' || line[len - 1] > '9')
    {
            printf ("Error file input_map in the line %d\n", index_line);
            free(map);
            exit(EXIT_FAILURE);
    }
    while (line[i])
    {
        if ((line[i] < '0' || line[i] > '9') && line[i] != ',')
        {
            printf ("Error file input_map in the line %d chara %c\n", index_line, line[i]);
            free(map);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

int chift_coolor(unsigned int R, unsigned int G, unsigned int B)
{
     return (R << 24 | G << 16 | B << 8 | (unsigned int)255);
}
void    check_colloers(char *line, t_map *map, int ret, int index_line) 
{   char   **ptr;
    unsigned int    R;
    unsigned int    G;
    unsigned int    B;
    
    (void)map;
    check_syntax(map, line, index_line);
    ptr = ft_split(line, ',');
    if (ptr && *ptr)
    {
        R = ft_atoi(ptr[0]);
        G = ft_atoi(ptr[1]);
        B = ft_atoi(ptr[2]);
        if (ft_check_maxcollor(R, G, B) || ptr[3])
        {
            printf ("Invalid input_map in line %d\n", index_line);
            free(map);
            exit(EXIT_FAILURE);
        }
        if (ret == 5)
            map->ceil = chift_coolor(R, G, B);
        else if (ret == 6)
            map->floor = chift_coolor(R, G, B);
        free_arr(ptr);
    }
    else
    {
        free(map);
        printf ("malloc failed !!\n");
        exit(EXIT_FAILURE);
    }
}

int ft_stor_line(char *line, t_map *map, int ret, int index_line)
{
    if (ret == 1)
    {
        map->tex_no = ft_strdup(line);
        if (!map->tex_no)
            return (0);  
    }
    else if (ret == 2)
    {
        map->tex_so = ft_strdup(line);
        if (!map->tex_so)
            return (0);  
    }
   else if (ret == 3)
    {
        map->tex_we = ft_strdup(line);
        if (!map->tex_we)
            return (0);  
    }
   else if (ret == 4)
    {
        map->tex_ea = ft_strdup(line);
        if (!map->tex_ea)
            return (0);  
    }
    else
        check_colloers(line, map, ret, index_line);
  return (1);
}
int ft_check_line(char *line, int index_line, t_map *map)
{
    int i;
    int j;
    int ret;

    i = 2;
    ret = check_beginning(line);
    if (!ret)
    {
        printf ("Missing element's input of file_map in line %d\n", index_line);
        return (0);
    }
    while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
        i++;
    j = i;
    while (line[j] && line[j] != '\n')
        j++;
    line[j] = '\0';
   if (!ft_stor_line(&line[i], map, ret, index_line))
   {
        printf ("malloc failed !!\n");
        free (map);
        exit(EXIT_FAILURE);
   }
    return (1);
}

int is_avalidchar(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13) || c == '0' || c == '1')
        return (1);
    return (0);
}
void    check_linemap(t_map *map, char *line, int index_line, int *flag)
{
    int i;

    i = -1;
    while (line && line[++i])
    {
        if (is_player(line[i]) && !*flag)
        {
            *flag = 1;
        }
        else if (is_player(line[i]) && *flag)
        {
            free(map);
            printf ("At least one player must exist in the map\n");
            printf("exist other player in line %d collone %d\n", index_line, i + 1);
            exit(EXIT_SUCCESS);
        }
        if (!is_player(line[i]) && !is_avalidchar(line[i]))
        {
            free(map);
            printf("Error input_map {l :%d c :%d}\n", index_line, i + 1);
            exit(EXIT_SUCCESS);
        }
    }
    
}

int ft_emptyline(char *line)
{
    int i;

    i = 0;
    while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
        i++;
    if(!line[i] || line[i] == '\n')
        return (1);
    return(0);
}
int ft_readline(t_map *map, char *line, int fd, int *flag)
{
    int len;
    int index_line;

    len = 0;
    index_line = 1;
      if (!line)
    {
        printf("Empty file_map !!\n");
        free(map);
        exit(EXIT_SUCCESS);
    }
    while (line)
    {
        if (!ft_emptyline(line))
        {
            len++;
            if (len > 6)
                check_linemap(map, line, index_line, flag);
        }
        free(line);
        line = get_next_line(fd);
        index_line++;
    }
    return (len);
}

int ft_lenmap(t_map *map , const char *path_map)
{
    int     len;
    int     fd;
    int     flag;
    char    *line;
    
    len = 0;
    flag = 0;
    fd = open(path_map,  O_RDONLY , 0644);
    if (fd == -1)
    {
        printf ("open() failed{check path_filemap, ...}\n");
        free(map);
        exit(EXIT_FAILURE);
    }
    line = get_next_line(fd);
    len = ft_readline(map, line, fd, &flag);
    close(fd);
    if (!flag || !len)
    {
        printf("Invalid map !!\n");
        printf("check existance of player or elements of file map.\n");
        free (map);
        exit(EXIT_FAILURE);
    }
    return (len);
}

int check_valid_map(char **av, t_map *map)
{
    int     fd;
    int     i;
    int     j;
    int     index_line;
    char    *line;
    int     len_map;
    
    i = 0;
    j = 0;
    index_line = 1;
    check_namemap(map, av[1]);
    len_map = ft_lenmap(map, av[1]) - 6;
    map->tab_map = malloc((len_map + 1) * sizeof(char *));
    if (!map->tab_map)
    {
        printf("malloc failed !!\n");
        free(map);
        exit(EXIT_FAILURE);
    }
    fd = open(av[1],  O_RDONLY , 0644);
    if (fd == -1)
    {
        printf ("open() failed ! maby Pathfile_map {%s} is not exist\n", av[1]);
        free_arr(map->tab_map);
        free(map);
       exit(EXIT_FAILURE);
    }
    line = get_next_line(fd);
    while (line)
    {
        if (i < 6 && line && line[0] != '\n')
        {
            if (!ft_check_line(line, index_line, map))
            {
                free(map);
                exit(EXIT_SUCCESS);
            }
            i++;
        }
        else if (i >= 6 && line && line[0] != '\n' && (ft_strchr(line, '0') || ft_strchr(line, '1')))
        {
            map->tab_map[j] = ft_strdup(line);
            j++;
        }
        free (line);   
        line = get_next_line(fd);
        index_line++;
    }
    map->tab_map[len_map] = NULL;
    return (len_map);
}

void  check_firstlastline(t_map *map,char **arr, int len)
{
    int i;
    
    i = 0;
    while(arr[0] && arr[0][i])
    {
        if (arr[0][i] != '1' && arr[0][i] != '\n' && !is_space(arr[0][i]))
        {
            if (is_player(arr[0][i]))
                printf("Invalid posotin of player !\n");
            else
                printf("Invalid map\n");
            free_myallocation(map);
            exit(EXIT_SUCCESS);
        }
        i++;
    }
    i = 0;
    while(arr[len -1] && arr[len -1][i])
    {
        if (arr[len - 1][i] != '1' && arr[len - 1][i] != '\n' && !is_space(arr[len - 1][i]))
        {   
            if (is_player(arr[len - 1][i]))
                printf("Invalid posotin of player !\n");
            else
                printf("Invalid map\n");
            free_myallocation(map);
            exit(EXIT_SUCCESS);
        }
        i++;
    }
    
}
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
       while (arr[i][j] && arr[i + 1][j])
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
       while (arr[i + 1][j])
       {
        
            if ((arr[i + 1][j] != '1' && arr[i + 1][j] != '\n' && arr[i + 1][j] != ' ') || is_player(arr[i + 1][j]))
            {
                if (is_player(arr[i + 1][j]))
                    printf("**Invalid position of player !\n");
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

int ft_handel_input(char **av)
{
    t_map   *map;
    int     len_map;
    
    map = malloc (sizeof(t_map));
    if (!map)
    {
        printf("malloc failed !!\n");
        exit(EXIT_FAILURE);
    }
   len_map = check_valid_map(av, map);
    check_arrmap(map, len_map);
    return (1);
}