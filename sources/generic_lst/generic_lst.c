/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:28:32 by siyang            #+#    #+#             */
/*   Updated: 2023/06/18 16:54:48 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_lst.h"

int	gl_lstsize(t_generic_lst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	gl_lstadd_back(t_generic_lst **head, t_generic_lst *new)
{
	t_generic_lst	*last;

	if (head == NULL || new == NULL)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_generic_lst	*gl_lstreverse(t_generic_lst *lst)
{
	t_generic_lst	*next;
	t_generic_lst	*reverse_head;

	reverse_head = NULL;
	while (lst)
	{
		next = lst->next;
		lst->next = reverse_head;
		reverse_head = lst;
		lst = next;
	}
	return (reverse_head);
}
