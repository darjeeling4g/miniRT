/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/12 20:16:52 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	int	fd;
	
	fd = open(argv[1], O_RDONLY);

	// parser
	parser(fd);
	// mlx init

	// render
	
}

void	make_node()
{

}

int	scan_id(char *str)
{
	int	id;

	if (*str >= 'A' && *str <= 'Z' && *(str + 1) == ' ')
	{
		if (!strncmp(str, "A", 1))
			id = A;
		else if (!strncmp(str, "C", 1))
			id = C;
		else if (!strncmp(str, "L", 1))
			id = L;
	}
	else if (*str >= 'a' && *str <= 'z' && *(str + 1) != ' ')
	{
		if (!strncmp(str, "sp", 2))
			id = SP;
		if (!strncmp(str, "pl", 2))
			id = PL;
		if (!strncmp(str, "cy", 2))
			id = CY;
	}
	else
		id = ERROR;
	return (id);
}

void	parser(int fd)
{
	char *line;

	while()
	{
		// read one line
		line = get_next_line(fd);
		scan_id(line);
		// type
			// make each node in linked_list

			if ()
			//A parser
				// get_ratio()
				// get_color()
			//C parser
				// get_vector()
				// get_coordinate()
				// get_fov()
			//L parser
				// get_coordinate()
				// get_ratio()
				// get_color()
			//sp parser
				// get_coordinate()
				// get_diameter()
				// get_color()
			//pl parser
				// get_coordinate()
				// get_normal_vector()
				// get_color()
			//cy parser
				// get_coordinate()
				// get_vector()
				// get_diameter()
				// get_height()
				// get_color()
	}
}

// focal_length