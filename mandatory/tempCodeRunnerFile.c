void	cast_ray(t_player *player, t_ray *ray)
{
	ray->horizontal_distance = FLT_MAX;
	ray->vertical_distance = FLT_MAX;
	horizontal_ray_intersection(player, ray);
	vertical_ray_intersection(player, ray);
	if (ray->horizontal_distance < ray->vertical_distance)
	{
		ray->horz_y = 1;
		ray->distance = ray->horizontal_distance;
		ray->horizontal_distance = ray->horizontal_distance * cos(ray->angle - player->rotationAngle);
		render_3d_wall_slice(player, i, player->rays[i].distance);
	}	
	else
	{
		ray->horz_y = 0;
		ray->distance = ray->vertical_distance;
		ray->vertical_distance = ray->vertical_distance * cos(ray->angle - player->rotationAngle);
		render_3d_wall_slice(player, i, player->rays[i].distance);
	}
}