#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

#define MLX_ERROR 1

// #include <X11/X.h>
//#include <X11/keysym.h>

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 600, 300, "Hello world!");
// 	img.img = mlx_new_image(mlx, 200, 200);
// 	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 	//							&img.endian);
// 	//my_mlx_pixel_put(mlx, mlx_win, 5, 5, 0x00FF0000);
// 	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);

// 	//printf ("%d", keycode);
// }
// typedef struct s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// }	t_data;

// int	handle_no_event(void *data)
// {
// 	/* This function needs to exist, but it is useless for the moment */
// 	return (0);
// }

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	handle_keypress(int keysym, t_vars *vars)
{
	if (keysym == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

// int	handle_keyrelease(int keysym, void *data)
// {
// 	printf("Keyrelease: %d\n", keysym);
// 	return (0);
// }

// int	main(void)
// {
// 	t_data	data;

// 	data.mlx_ptr = mlx_init();
// 	if (data.mlx_ptr == NULL)
// 		return (MLX_ERROR);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
// 	if (data.win_ptr == NULL)
// 	{
// 		free(data.win_ptr);
// 		return (MLX_ERROR);
// 	}

// 	/* Setup hooks */ 
// 	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

// 	mlx_loop(data.mlx_ptr);

// 	/* we will exit the loop if there's no window left, and execute this code */
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// }

// int	close(int keycode, t_vars *vars)
// {

//  		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	exit (0);
// }

// int	quit(int keycode, t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	exit (0);
// }

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 300, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, handle_keypress, &vars);
	//mlx_hook(vars.win, 17, 1L << 5, close, &vars);
	mlx_loop(vars.mlx);

	

	
	return (0);

}