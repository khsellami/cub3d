void calculate_wall_properties(t_player *player, int ray_id, double distance, t_data *data)
{
    data->angle_diff = player->rays[ray_id].angle - player->rotationAngle;
    data->corrected_distance = distance * cos(data->angle_diff);
    data->wall_height = (TILE_SIZE * SH) / data->corrected_distance;
    data->wall_top = (SH / 2) - (data->wall_height / 2);
    if (data->wall_top < 0) data->wall_top = 0;
    data->wall_bottom = (SH / 2) + (data->wall_height / 2);
    if (data->wall_bottom >= SH) data->wall_bottom = SH - 1;
    data->x_pos = (ray_id * SW) / NUM_RAYS;
}