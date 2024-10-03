#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	size_t			i;
	int				fd;
	static uint8_t	buffer[1250000 * 8];

	fd = open("rand_bin_data.bin", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
	srand(time(NULL));
	i = 0;
	while (i < 1250000 * 8)
	{
		buffer[i] = (rand() % 0xFF);
		i++;
	}
	write(fd, buffer, 1250000 * 8);
	close(fd);
	return (0);
}
