/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:40:12 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 18:41:39 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

// vector.c
t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);
t_color3	color3(double x, double y, double z);

// vector_utils.c
void		vector_set(t_vec3 *vec, double x, double y, double z);
double		length(t_vec3 vec);
double		length_squared(t_vec3 vec);
t_vec3		unit_vector(t_vec3 vec);
t_vec3		reflect(t_vec3 vec, t_vec3 normal);

// vector_operation.c
t_vec3		vector_add(t_vec3 vec1, t_vec3 vec2);
t_vec3		vector_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3		vector_mul(t_vec3 vec1, t_vec3 vec2);
t_vec3		scala_mul(t_vec3 vec, double scala);
t_vec3		scala_div(t_vec3 vec, double scala);

// vector_product.c
double		dot(t_vec3 vec1, t_vec3 vec2);
t_vec3		cross(t_vec3 vec1, t_vec3 vec2);

#endif
