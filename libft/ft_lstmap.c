/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksappi <ksappi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:43:48 by ksappi            #+#    #+#             */
/*   Updated: 2019/10/18 12:09:31 by ksappi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstmap_free(t_list *start)
{
	t_list	*next;
	t_list	*current;

	if (start)
	{
		next = start->next;
		if (start->content)
			free(start->content);
		free(start);
		while (next)
		{
			current = next;
			next = current->next;
			if (current->content)
				free(current->content);
			free(current);
		}
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*start;
	t_list	*f_return;
	t_list	*new;

	if (!lst)
		return (NULL);
	f_return = (*f)(lst);
	new = ft_lstnew(f_return->content, f_return->content_size);
	if (!new)
		return (NULL);
	start = new;
	lst = lst->next;
	while (lst)
	{
		f_return = (*f)(lst);
		new->next = ft_lstnew(f_return->content, f_return->content_size);
		if (!new->next)
		{
			ft_lstmap_free(start);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (start);
}
