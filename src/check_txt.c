/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:09:30 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 13:57:36 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_map(char *world_map)
{
	int i;

	i = 0;
	while (world_map[i])
	{
		if ((world_map[i] >= '0' && world_map[i] <= '9')
		|| world_map[i] == '\0' || world_map[i] == '\n')
			i++;
		else
			return (-1);
	}
	if (world_map[i - 1] != '\n')
		return (-1);
	return (0);
}
