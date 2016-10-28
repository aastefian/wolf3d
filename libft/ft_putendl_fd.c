/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 21:21:00 by svilau            #+#    #+#             */
/*   Updated: 2016/03/15 22:13:31 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char const *str, int fd)
{
	write(fd, (char *)str, ft_strlen((char *)str));
	write(fd, "\n", 1);
}
