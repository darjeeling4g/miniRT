/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_lst.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:16:38 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 21:55:21 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_LST_H
# define GENERIC_LST_H

# include <stddef.h>

typedef struct s_generic_lst
{
	struct s_generic_lst	*next;
	int						id;
}	t_generic_lst;

int				gl_lstsize(t_generic_lst *lst);
void			gl_lstadd_back(t_generic_lst **head, t_generic_lst *new);
t_generic_lst	*gl_lstreverse(t_generic_lst *lst);

#endif
