#include "../Cub3D.h"

float check_angle(float angle)
{
    float   valid_angle;

    valid_angle = fmod(angle, (2 * M_PI));
    if (valid_angle < 0) {
        valid_angle = (2 * M_PI) + valid_angle;
    }
    return (valid_angle);
}

float	calcul_distance(t_point	a, t_point b)
{
	return (sqrt(pow(2, b.x - a.x) + pow(2, b.y - a.y)));
}

float	distanceBetweenPoints(float x1,float y1,float x2,float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

t_point	ray_casting(float ray_angle, t_data *data)
{
	bool	is_up;
	bool	is_down;
	bool	is_right;
	bool	is_left;
	t_point	step;
	t_point	next_hor;
	t_point	first_intercept;

				// horisontal
				// init var :
    // the normalizeAngle function is used to keep the rayAngle within a predictable and standard range.
    ray_angle = check_angle(ray_angle);
    // data->p.rotation_angle = check_angle(ray_angle);
    //this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
	is_down = (ray_angle > 0 && ray_angle < M_PI);
	is_up = !is_down;
	//this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
	is_right = (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
	is_left = !is_right;
    

				/*
					find first intercept :
				*/
	// Find the y-coordinate of the closest horizontal grid intersenction
	first_intercept.y = floor(data->p.y / CUBE_SIZE) * CUBE_SIZE;
	first_intercept.y += is_down ? CUBE_SIZE : 0;
	// Find the x-coordinate of the closest horizontal grid intersection
	first_intercept.x = data->p.x + (first_intercept.y - data->p.y) / tan(ray_angle);

	// Calculate the increment xstep and ystep
	step.y = CUBE_SIZE;
	step.y *= is_up ? -1 : 1;
	step.x = CUBE_SIZE / tan(ray_angle);
	step.x *= (is_left && step.x > 0) ? -1 : 1;
	step.x *= (is_right && step.x < 0) ? -1 : 1;

	next_hor.x = first_intercept.x;
	next_hor.y = first_intercept.y;

	if (is_up)
	    next_hor.y--;

	// Increment xstep and ystep until we find a wall
	while ((next_hor.x / CUBE_SIZE) >= 0 && (next_hor.x / CUBE_SIZE) <= data->WIDTH && (next_hor.y / CUBE_SIZE) >= 0 && (next_hor.y/ CUBE_SIZE) <= data->HEIGHT)
	{
		// printf("(%2.f,%2.f)===>(%d,%d)\n", (next_hor.x / CUBE_SIZE), next_hor.y / CUBE_SIZE, data->WIDTH, data->HEIGHT);
		if (is_wall(next_hor.x, next_hor.y, data)) {              
			break;
		}
		else
		{
			next_hor.x += step.x;
			next_hor.y += step.y;
		}
	}
			/*
				vertical :
			*/
	// find first intersction point : (the same). 
	t_point	next_ver;
				
				// find first intercept :
	// Find the x-coordinate of the closest horizontal grid intersenction
	first_intercept.x = floor(data->p.x / CUBE_SIZE) * CUBE_SIZE;
	first_intercept.x += is_right ? CUBE_SIZE : 0;
	// Find the y-coordinate of the closest horizontal grid intersection
	first_intercept.y = data->p.y + (first_intercept.x - data->p.x) * tan(ray_angle);

	// Calculate the increment xstep and ystep
	step.x = CUBE_SIZE;
	step.x *= is_left ? -1 : 1;
	
	step.y = CUBE_SIZE * tan(ray_angle);
	step.y *= (is_up && step.y > 0) ? -1 : 1;
	step.y *= (is_down && step.y < 0) ? -1 : 1;

	next_ver.x = first_intercept.x;
	next_ver.y = first_intercept.y;

	if (is_left)
		next_ver.x--;

	// Increment xstep and ystep until we find a wall
	while ((next_ver.x / CUBE_SIZE) >= 0 && (next_ver.x / CUBE_SIZE) <= data->WIDTH && (next_ver.y / CUBE_SIZE) >= 0 && (next_ver.y/ CUBE_SIZE) <= data->HEIGHT)
	{
		// printf("(%2.f,%2.f)===>(%d,%d)\n", (next_ver.x / CUBE_SIZE), next_ver.y / CUBE_SIZE, data->WIDTH, data->HEIGHT);
		if (is_wall(next_ver.x, next_ver.y, data)) {
			break;
		}
		else
		{
			next_ver.x += step.x;
			next_ver.y += step.y;
		}
	}
	

	// cmp :
	float	distance_hor;
	float	distance_ver;

	distance_hor = distanceBetweenPoints(data->p.x, data->p.y, next_hor.x, next_hor.y);
	distance_ver = distanceBetweenPoints(data->p.x, data->p.y, next_ver.x, next_ver.y);

	t_point	res;

	res.x = (distance_hor < distance_ver) ? next_hor.x : next_ver.x;
	res.y = (distance_hor < distance_ver) ? next_hor.y : next_ver.y;
	return (res);
}
