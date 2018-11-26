/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:14:48 by skarev            #+#    #+#             */
/*   Updated: 2018/07/10 15:14:51 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = (char*)malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int			ft_line(char **tmp, char **line, char *buf)
{
	char		*check;
	char		*sk;
	int			dif;

	check = ft_strchr(*tmp, '\n');
	if (check)
	{
		sk = *tmp;
		dif = check - sk;
		*line = ft_strndup(sk, dif);
		*tmp = ft_strsub(sk, dif + 1, ft_strlen(sk) - (dif + 1));
		ft_strdel(&sk);
		ft_strdel(&buf);
		return (1);
	}
	return (0);
}

int			ft_stack(int byte, char *buf, char **tmp, char **line)
{
	char			*sk;

	buf[byte] = '\0';
	if (*tmp == NULL)
		*tmp = ft_strdup(buf);
	else
	{
		sk = *tmp;
		*tmp = ft_strjoin(*tmp, buf);
		ft_strdel(&sk);
	}
	if (ft_line(tmp, line, buf))
		return (1);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int				byte;
	char			*buf;
	static char		*tmp[MAX_FD];

	buf = NULL;
	if ((fd < 0 || fd > MAX_FD || !line ||
		read(fd, buf, 0) < 0) || BUFF_SIZE < 1)
		return (-1);
	buf = ft_strnew(BUFF_SIZE + 1);
	if (tmp[fd] != NULL)
		if (ft_line(&tmp[fd], line, buf))
			return (1);
	while ((byte = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (ft_stack(byte, buf, &tmp[fd], line))
			return (1);
	}
	ft_strdel(&buf);
	if (tmp[fd] == NULL || *tmp[fd] == '\0')
		return (0);
	*line = ft_strdup(tmp[fd]);
	ft_strdel(&tmp[fd]);
	return (1);
}
