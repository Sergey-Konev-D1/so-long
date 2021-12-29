#include "GNL/get_next_line.h"
#include "stdio.h"
#include "minilibx/mlx.h"
#include "so_long.h"
#include <string.h>
int	close_window(t_vars *vars);


void  func1()
{
}

static int	get_size(int i)
{
	int	cnt;

	if (i == 0)
		return (1);
	cnt = 0;
	while (i)
	{
		i /= 10;
		cnt++;
	}
	return (cnt);
}

static char	*val(char *str, int i, int cnt)
{
	long	j;

	j = i;
	if (j < 0)
	{
		j *= -1;
		str[0] = '-';
	}
	if (j == 0)
		str[0] = '0';
	while (j)
	{
		str[cnt - 1] = j % 10 + 48;
		j /= 10;
		cnt--;
	}
	return (str);
}

char	*ft_itoa(int i)
{
	char	*str;
	int		cnt;

	cnt = get_size(i);
	if (i < 0)
		cnt++;
	str = malloc(cnt + 1);
	if (!str)
		return (0);
	str[cnt] = '\0';
	return (val(str, i, cnt));
}

 void func_errors(int num)
 {
	if (num == 1)
		printf("Error: wrong number of arguments specified\n");
	else if (num == 2)
		printf("Error: file read error\n");
	else if (num == 3)
		printf("Map error: invalid string length\n");
	else if (num == 4)
		printf("Map error: map borders are set incorrectly\n");
	else if (num == 5)
		printf("Map error: invalid symbols in the map\n");
	else if (num == 6)
		printf("Map error: empty lines in file\n");
	else if (num == 7)
		printf("Map error: wrong number of players or entering the field\n");
	else if (num == 8)
		printf("Map error: there must be at least one collectible on the field\n");		
 	exit(1);
 }

typedef struct	s_coord {
	int	x;
	int y;	
}				t_coord;


void move_player(int a, int b, t_vars *vars)
{
	int i;
	int j;

	i = -1;
	while (++i < vars->count)
	{
		j = -1;
		while (++j < vars->length)
		{
			if (vars->arr[i][j] == 'P' && (vars->arr[i - a][j + b] == '0' || vars->arr[i - a][j + b] == 'C'))
			{
				if (vars->arr[i - a][j + b] == 'C')
					vars->collectibles--;
				vars->arr[i - a][j + b] = 'P';
				vars->arr[i][j] = '0';
				vars->move_player1++;
				return ;
			}
			else if (vars->arr[i][j] == 'P' && vars->arr[i - a][j + b] == 'E' && vars->collectibles == 0)
			{
				// vars->arr[i - a][j + b] = 'P'; //победа!!!!!
				// vars->arr[i][j] = '0';
				// vars->move_player1++;
				close_window(vars);	
			}
			else if (vars->arr[i][j] == 'P' && vars->arr[i - a][j + b] == 'V')
			{
				//проиграл!!!!
				close_window(vars);
			}
		}
	}	
}


void	cnt_moves(t_vars *vars)
{
	char    *moves_str;
    char    *moves_cnt;

    moves_str = ft_strdup("MOVES: ");
    moves_cnt = ft_itoa(vars->move_player1);
    mlx_string_put(vars->mlx, vars->win, 60, 20, 0x1ad1ff, moves_str);
    mlx_string_put(vars->mlx, vars->win, 120, 20, 0x1ad1ff, moves_cnt);
    free(moves_str);
    free(moves_cnt);
}


void draw(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	printf ("start F\n");
	while (i < vars->count)
	{
		j = 0;
		while (j < vars->length)
		{
			printf ("%c", vars->arr[i][j++]);
		}
		printf ("\n");
		i++;	
	}
	printf ("\n");
	printf ("end F\n");
}

int	handle_keypress(int keysym, t_vars *vars)
{
	if (keysym == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	if (keysym == 126 || keysym == 13)  //up
	{
		vars->flag_dir = 1;
		move_player(1, 0, vars);
		draw(vars);
	}
	else if (keysym == 125 || keysym == 1) // down
	{
		vars->flag_dir = 2;
		move_player(-1, 0, vars);
		draw(vars);
	}
	else if (keysym == 123 || keysym == 0) // left
	{
		vars->flag_dir = 3;
		move_player(0, -1, vars);
		draw(vars);
	}
	else if (keysym == 124 || keysym == 2) // right
	{
		vars->flag_dir = 4;
		move_player(0, 1, vars);
		draw(vars);
	}
	// else
	// 	return (0);
	return (0);

	//printf("Keypress: %d\n", keysym);
}

void choice_image(t_vars *vars)
{
	int w;
	int h;

	//printf ("start image");
	vars->image.image_wall = mlx_xpm_file_to_image(vars->mlx, "./images/wall.xpm", &h, &w);
	vars->image.image_floor = mlx_xpm_file_to_image(vars->mlx, "./images/grass.xpm", &h, &w);
	vars->image.image_player = mlx_xpm_file_to_image(vars->mlx, "./images/r1.xpm", &h, &w);
	vars->image.image_enemy = mlx_xpm_file_to_image(vars->mlx, "./images/dog.xpm", &h, &w);
	vars->image.image_exit = mlx_xpm_file_to_image(vars->mlx, "./images/exit.xpm", &h, &w);
	vars->image.image_collectibles1 = mlx_xpm_file_to_image(vars->mlx, "./images/burger.xpm", &h, &w);
	vars->image.image_collectibles2 = mlx_xpm_file_to_image(vars->mlx, "./images/burger2.xpm", &h, &w);
	//printf ("stop image");
}

void *player_dir_image(t_vars *vars, int i, int j)
{
	int w;
	int h;
	i = j;
	
	if (vars->flag_dir == 4)
	{
		if (vars->k_count_player_image % 2 == 0)
		{
			
			//mlx_put_image_to_window(vars->mlx, vars->win, vars->image.image_floor, (j + 1) * PIXEL , i * PIXEL);
			vars->image.image_player = mlx_xpm_file_to_image(vars->mlx, "./images/r1.xpm", &h, &w);
			vars->k_count_player_image++;
		}
		else 
		{
			vars->image.image_player = mlx_xpm_file_to_image(vars->mlx, "./images/r2.xpm", &h, &w);
			vars->k_count_player_image = 0;
		}
	}

	return (vars->image.image_player);	
}

void draw_images(t_vars *vars, char c, int i, int j)
{
	void *image;

	if (c == '0' || c == 'C' || c == 'P' || c == 'E' || c == 'V')
	{
		//image = vars->image.image_floor;
		//mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
	}
	if (c == '1')
		{image = vars->image.image_wall;
		mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);}
	else if (c == 'P')
	{
		image = vars->image.image_floor;
		mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
		if (vars->flag_dir)
		{
			image = player_dir_image(vars, i, j);
			mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL , i * PIXEL);	
		}
		else
		{
			image = vars->image.image_player;
			mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL , i * PIXEL);
		}	
	}
	else if (c == 'E')
		{image = vars->image.image_exit;
		mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);}
	else if (c == 'C')
	{
		if ((vars->frame_enemy_patrol++) % 7  == 0)
			image = vars->image.image_collectibles1;	
		else
			image = vars->image.image_collectibles2;
			mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
	}
	else if (c != '0')
	{
		//image = vars->image.image_floor;
		//mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
		image = vars->image.image_enemy;
		mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
	}
	//else 
		//image = NULL;
	//mlx_put_image_to_window(vars->mlx, vars->win, image, j * PIXEL, i * PIXEL);
}


void enemy_cordinate(t_vars *vars, t_coord *enemy_coord, int a, int b)
{
	if (vars->arr[enemy_coord->x - a][enemy_coord->y - b] == '0' || vars->arr[enemy_coord->x - a][enemy_coord->y - b ] == 'P')
	{
		if (vars->arr[enemy_coord->x - a][enemy_coord->y - b] == 'P')
		{
			mlx_string_put(vars->mlx, vars->win, 50, 60, 0x1ad1ff, "LOOSE");// нужно вызывать в каждом кадре!!!!!
		//	sleep(10);
			close_window(vars);
		}
		vars->arr[enemy_coord->x - a][enemy_coord->y - b] = 'K';
		vars->arr[enemy_coord->x][enemy_coord->y] = '0';
	}
	else
		vars->random_for_enemy += 1;
	vars->random_for_enemy += 1;
}

void move_enemy(t_vars *vars,int i, int j)
{
	t_coord	enemy_coord;

	enemy_coord.x = i;
	enemy_coord.y = j;

	if (vars->random_for_enemy % 4 == 0)
		enemy_cordinate(vars, &enemy_coord, 1, 0);
	else if (vars->random_for_enemy % 4 == 1)
		enemy_cordinate(vars, &enemy_coord, -1, 0);
	else if (vars->random_for_enemy % 4 == 2)
		enemy_cordinate(vars, &enemy_coord, 0, -1);
	else if (vars->random_for_enemy % 4 == 3)
		enemy_cordinate(vars, &enemy_coord, 0, 1);
}

void rename_enemy(t_vars *vars, char a, char b)
{
	int i;
	int j;

	i = -1;
	while (++i < vars->count)
	{
		j = -1;
		while (++j < vars->length)
		{
			if (vars->arr[i][j] == a)
			{
				vars->arr[i][j] = b;
				if (a == 'V' && b == 'K')
					move_enemy(vars, i, j);
			}
		}
	}	
}

int draw_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	if (vars->frame_enemy_patrol % 5 == 0)
	{
		rename_enemy(vars, 'V', 'K');
		rename_enemy(vars, 'K', 'V');
		vars->frame_enemy_patrol = 0 ;
	}
	while (i < vars->count)
	{
		j = 0;
		while (j < vars->length)
		{
			draw_images(vars, vars->arr[i][j], i, j);
			j++;
		}
		i++;
	}
	cnt_moves(vars);
	vars->frame_enemy_patrol++;
	return (0);
}

int check_string_symbols(t_vars *vars, char *line)
{
	int i;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == 'P')
			vars->players++;
		else if (line[i] == 'E')
			vars->exits++;	
		else if (line[i] == 'C')
			vars->collectibles++;
		else if (line[i] == '0' || line[i] == '1' || line[i] == 'V');
		else
			func_errors(5); //"Map error: invalid symbols in the map\n"
	}
	return(0);
}

int map_check_symbols(t_vars *vars, char *line, int flag_n) 
{
	int i;

	i = 0;
	if (flag_n)
		line[vars->length - 1] = '\0';	
	if (vars->count == 1 || !flag_n)
	{
		while (i < vars->length - 1)
		{
			if (line[i] != '1')
				func_errors(4); //"Map error: map borders are set incorrectly\n"
			i++;
		}
	}
	if (vars->count > 1 && flag_n)
	{
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			func_errors(4); //"Map error: map borders are set incorrectly\n"	
		check_string_symbols(vars,line);
	}
	return (0);
}

void map_check1(t_vars *vars, int *flag_n, char *line)
{
	*flag_n = 0;
	if (line[ft_strlen(line) - 1] == '\n')
		*flag_n = 1;
	vars->count++;
	if ((*flag_n && ((int)ft_strlen(line) != vars->length)) || 
		(!(*flag_n) && ((int)ft_strlen(line) != vars->length - 1)))
		func_errors(3); // "Map error: invalid string length\n"
	map_check_symbols(vars, line, *flag_n);
}

int map_check(t_vars *vars, char *argv)
{
	char *line;
	int flag_n;

	vars->fd = open(argv, O_RDONLY);
	if (vars->fd < 0)
		func_errors(2); // "Error: file read error\n"
	line = get_next_line(vars->fd);
	vars->length = ft_strlen(line); 
	vars->count = 0;
	while (line)
	{
		map_check1(vars, &flag_n, line);
		free(line);
		line = get_next_line(vars->fd);
	}
	if (flag_n == 1)
		func_errors(6); // "Error: map error, empty lines in file\n"
	if ((vars->players != 1) || (vars->exits != 1))
		func_errors(7); // "Map error: wrong number of players or entering the field"
	if (vars->collectibles == 0)
		func_errors(8); // "Map error: there must be at least one collectibl on the field"	
	close(vars->fd);
	return (0);
}


int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}


void allocate_memory_arr(t_vars *vars)
{
	int	i;
	int	k;
	printf ("start alloc\n");
	vars->length = vars->length - 1; // новая длина строки без \n
	vars->arr = (char **)malloc(vars->count * sizeof(int *));
	if (!vars->arr)
	{
		perror(NULL);
		exit (1);
	}
	i = 0;
	while (i < vars->count)
	{
		vars->arr[i] = malloc((vars->length) * sizeof(char));
		if (!vars->arr[i])
		{
			perror(NULL);
			k = 0;
			while (k < i)
				free(vars->arr[k++]);
			free(vars->arr);
			exit (1);
		}
		i++;
	}
	printf ("end alloc\n");
}


void fill_arr(t_vars *vars, char *argv)
{
	int	i;
	int	j;
	char *line;
	printf ("start Fill\n");
	vars->fd = open(argv, O_RDONLY);
	if (vars->fd < 0)
		func_errors(2);
	line = get_next_line(vars->fd);
	i = 0;
	while (line)
	{
		j = 0;
		while (j < vars->length)
		{
			vars->arr[i][j]= line[j];
			j++;
		}
		i++;
		free(line);
		line = get_next_line(vars->fd);
	}
	close(vars->fd);
	printf ("end Fill\n");
}



int main(int argc, char **argv)
{
	t_vars	vars;
	
	if (argc != 2)
	{
		func_errors(1);// "Error: wrong number of arguments specified\n"
		exit (1);
	}
	vars.collectibles = 0;
	vars.exits = 0;
	vars.players = 0;
	vars.move_player1 = 0;
	vars.random_for_enemy = 0;
	vars.frame_enemy_patrol = 0;
	vars.flag_dir = 0;
	vars.k_count_player_image = 0;
	map_check(&vars, argv[1]);
	allocate_memory_arr(&vars);
	fill_arr(&vars, argv[1]);
	draw(&vars);
	printf ("start FUNC\n");
	choice_image(&vars);
	printf ("end FUNC\n");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, PIXEL * vars.length, PIXEL * vars.count, "So_long");
	mlx_hook(vars.win, 2, 1L<<0, handle_keypress, &vars);
	//mlx_hook(vars.win, 2, 1L << 0, player_dir_image, &vars);
	//mlx_key_hook(vars.win, handle_keypress, &vars); // отработать функцию отжатия клавиши,flag_dir = 0 
	mlx_loop_hook(vars.mlx, draw_map, &vars);
	mlx_hook(vars.win, 17, 1L << 5, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
