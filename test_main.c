#include "lem_in.h"

int     main(int ac, char **av)
{
	int     fd;
    char    *line;
    int     count;
    int     ret;

    ret = 0;
    count = 0;
    fd = open("/Users/skarev/Desktop/tmp/test1", O_RDONLY);
    while (count < 20)
    {
        ret = get_next_line(fd, &line);
        printf("%d ", ret);
        printf("%s\n", line);
        ft_strdel(&line);
        count++;
    }
    close(fd);
    return (0);
}