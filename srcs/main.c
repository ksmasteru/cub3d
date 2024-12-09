#include "../includes/cub3d.h"

int main()
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 720, 720, "CUB3D");
    mlx_loop(mlx_ptr);
    return (0);
}