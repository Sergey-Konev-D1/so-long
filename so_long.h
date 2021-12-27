
#define PIXEL 64

typedef struct	s_image{
	void 	*image_wall;
	void 	*image_floor;
	void 	*image_collectibles1;
	void 	*image_collectibles2;
	void 	*image_player;
	void 	*image_exit;
	void 	*image_enemy;
}		t_image;



typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char 	**arr;
	int		length;
	int		count;
	int		move_player1;
	int 	fd;
	int 	collectibles;
	int 				players;
	int 				exits;
	unsigned int		random_for_enemy;
	int 				frame_enemy_patrol;
	int 	flag_dir;
	int 	k_count_player_image;
	t_image  image;
}				t_vars;

void move_player(int a, int b, t_vars *vars);
void rename_enemy(t_vars *vars, char a, char b);