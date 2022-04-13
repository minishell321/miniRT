
#include "../include/minirt.h"

static void shape_init(t_shapes *shape)
{
	shape->type = NULL;
	shape->coordinates[0] = 0;
	shape->coordinates[1] = 0;
	shape->coordinates[2] = 0;
	shape->vect_3d[0] = 0;
	shape->vect_3d[1] = 0;
	shape->vect_3d[2] = 0;
	shape->diameter = 0;
	shape->height = 0;
	shape->color = 0;
	shape->colors[0] = 0;
	shape->colors[1] = 0;
	shape->colors[2] = 0;
	shape->next = NULL;
}

static int  create_plan(t_scene *scene, char **split)
{
    t_shapes *shape;

    shape = malloc(sizeof(t_shapes));
    if (shape == NULL)
        return (1);
	shape_init(shape);
    shape->type = ft_strdup("pl");
    if  (init_coord(shape, split[1]) == 1)
            return (1);
	if (init_vect_3d(shape, split[2]) == 1)
            return (1);
    if (init_colors(shape, split[3]) == 1)
            return (1);
    shape->next = NULL;
    insert_shape_at_end(scene, shape);
    return (0);
}

static int  create_sphere(t_scene *scene, char **split)
{
    t_shapes *shape;

    shape = malloc(sizeof(t_shapes));
    if (shape == NULL)
        return (1);
	shape_init(shape);
    shape->type = ft_strdup("sp");
    if (init_coord(shape, split[1]) == 1)
        return (1);
    shape->diameter = ft_atof(split[2]);
    if (init_colors(shape, split[3]) == 1)
        return (1);
    shape->next = NULL;
    shape->height = 0;
    insert_shape_at_end(scene, shape);
    return (0);
}

static int  create_cylinder(t_scene *scene, char **split)
{
    t_shapes *shape;

    shape = malloc(sizeof(t_shapes));
    if (shape == NULL)
        return (1);
	shape_init(shape);
    shape->type = ft_strdup("cy");
    if (init_coord(shape, split[1]) == 1)
            return (1);
	if (init_vect_3d(shape, split[2]) == 1)
            return (1);
    if (init_colors(shape, split[5]) == 1)
        return (1);
    shape->diameter = ft_atof(split[3]);
    shape->height = ft_atof(split[4]);
    shape->next = NULL;
    insert_shape_at_end(scene, shape);
    return (0);
}

int	create_shape(char **split, t_scene *scene)
{
    if (!ft_strncmp(split[0], "sp", 3))
    {
        if (create_sphere(scene, split) == 1)
            return (1);
    }
    if (!ft_strncmp(split[0], "cy", 3))
    {
        if (create_cylinder(scene, split) == 1)
            return (1);
    }
    if (!ft_strncmp(split[0], "pl", 3))
    {
        if (create_plan(scene, split) == 1)
            return (1);
    }
	return (0);
}
