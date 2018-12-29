#include "lem_in.h"

static char   *append_char(char **s, char c)
{
    char   *temp;
    size_t   len;

    if (!*s)
    {
        temp = ft_memalloc(2);
        temp[0] = c;
        temp[1] = '\0';
        return (temp);
    }
    len = ft_strlen(*s);
    temp = ft_memalloc(len + 2);
    ft_strcpy(temp, *s);
    temp[len] = c;
    temp[len + 1] = '\0';
    free(*s);
    *s = NULL;
    return (temp);
}

int     lgnl(int fd, char **line)
{
    char   buf;

    if (fd < 0 || !line)
        return (-1);
    *line = NULL;
    while (read(fd, &buf, 1) > 0)
    {
        if (buf == '\n' || buf == '\0')
            break ;
        *line = append_char(line, buf);
    }
    return ((int)ft_strlen(*line));
}