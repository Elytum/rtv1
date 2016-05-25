/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:38:26 by achazal           #+#    #+#             */
/*   Updated: 2016/03/08 22:38:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tools.h>
#include <stdlib.h>
#include <unistd.h>

void	*safe_malloc(size_t size)
{
	const char	error[] = "Malloc error\n";
	void		*ret;

	if (!(ret = malloc(size)))
	{
		write(2, error, sizeof(error) - 1);
		exit(1);
	}
	return (ret);
}
