/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:10:25 by hchreif           #+#    #+#             */
/*   Updated: 2024/06/16 15:23:48 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putnbr_fd(nb / 10, fd);
		write_('8', fd);
	}
	else if (nb < 0)
	{
		write_('-', fd);
		ft_putnbr_fd(-nb, fd);
	}
	else
	{
		if (nb > 9)
		{
			ft_putnbr_fd(nb / 10, fd);
		}
		write_(48 + nb % 10, fd);
	}
}
