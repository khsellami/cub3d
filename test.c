/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:29:32 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/22 15:49:21 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
Player player = { .x = 1.5 * GRID_SIZE, .y = 1.5 * GRID_SIZE, .moveSpeed = MOVE_STEP };
int map[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE];
int main() {
    player.mlx_conex = mlx_init();
    player.mlx_window = mlx_new_window(player.mlx_conex, WINDOW_WIDTH, WINDOW_HEIGHT, "Map Display");
    
    t_image *map_image = create_image(player.mlx_conex, WINDOW_WIDTH, WINDOW_HEIGHT);
    readMapFromFile("map.txt");
    
    render(map_image);
    mlx_key_hook(player.mlx_window, handle_input, NULL);
    
    mlx_loop(player.mlx_conex);

    destroy_image(player.mlx_conex, map_image);
    mlx_destroy_window(player.mlx_conex, player.mlx_window);
    
    return 0;
}


t_image *create_image(void *mlx, int width, int height) {
    t_image *img = malloc(sizeof(t_image));
    if (!img) {
        perror("Failed to allocate memory for image");
        return NULL;
    }

    img->img = mlx_new_image(mlx, width, height);
    if (!img->img) {
        free(img);
        perror("Failed to create image");
        return NULL;
    }

    img->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
    img->width = width;
    img->height = height;

    return img;
}

void destroy_image(void *mlx, t_image *img) {
    if (img) {
        mlx_destroy_image(mlx, img->img);
        free(img);
    }
}

void put_pixel(t_image *img, int x, int y, int color) {
    int *img_data = (int *)img->data;
    img_data[y * img->size_line / 4 + x] = color;
}

void render(t_image *map_image) {
    mlx_clear_window(player.mlx_conex, player.mlx_window);

    for (int i = 0; i < (WINDOW_HEIGHT / GRID_SIZE); i++) {
        for (int j = 0; j < (WINDOW_WIDTH / GRID_SIZE); j++) {
            int color;
            if ((int)(player.x / GRID_SIZE) == j && (int)(player.y / GRID_SIZE) == i) {
                color = WHITE_PIXEL;
            } 
            else if (map[i][j] == 1) {
                color = RED; 
            } 
            else {
                color = SPACE; 
            }

            put_pixel(map_image, j * GRID_SIZE, i * GRID_SIZE, color);
        }
    }
    mlx_put_image_to_window(player.mlx_conex, player.mlx_window, map_image->img, 0, 0);
}

bool isCollidingWithWall(float newX, float newY) {
    int gridX = (int)(newX / GRID_SIZE);
    int gridY = (int)(newY / GRID_SIZE);

    if (gridX >= 0 && gridX < (WINDOW_WIDTH / GRID_SIZE) && gridY >= 0 && gridY < (WINDOW_HEIGHT / GRID_SIZE)) {
        return map[gridY][gridX] == 1;
    }
    return true;
}

void updatePlayer(char direction) {
    float newX = player.x;
    float newY = player.y;

    switch (direction) {
        case W_KEY: newY -= player.moveSpeed; break;
        case S_KEY: newY += player.moveSpeed; break;
        case A_KEY: newX -= player.moveSpeed; break;
        case D_KEY: newX += player.moveSpeed; break;
        default: return;
    }

    if (!isCollidingWithWall(newX, newY)) {
        player.x = newX;
        player.y = newY;
        t_image *map_image = create_image(player.mlx_conex, WINDOW_WIDTH, WINDOW_HEIGHT);
        render(map_image);
        destroy_image(player.mlx_conex, map_image);
    }
}

void readMapFromFile(const char *filename) {
   int fd = open(filename, O_RDONLY);
   
   if (fd < 0) {
       perror("Error opening map file");
       exit(EXIT_FAILURE);
   }

   char *line;
   int i = 0;

   while (i < (WINDOW_HEIGHT / GRID_SIZE) && (line = get_next_line(fd)) != NULL) {
       for (int j = 0; j < (WINDOW_WIDTH / GRID_SIZE); j++) {
           if (line[j] == '\0') break; // Stop if we reach the end of the line
           map[i][j] = (line[j] == '1') ? 1 : 0; // 1 = Wall, 0 = Empty space
       }
       free(line); // Free the line after processing
       i++;
   }

   close(fd);
}

// Handle keyboard input
int handle_input(int keycode) {
    if (keycode == ESC) {
        exit(0); 
    } else if (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY || keycode == D_KEY) { 
        updatePlayer(keycode);
    }
    return 0;
}



