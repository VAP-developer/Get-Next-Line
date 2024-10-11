/*
Esta funcion lee un un fichero
Trabaja con el buffer del fichero para encontrar un /n o un vacio
Lee la linea de texto
Actualiza el buffer
*/

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(int count, int size)
{
	char	*ptr;
	char	*start;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	start = ptr;
	while(count--)
		*ptr++ = '\0';
	return (start);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int	i;
	int	j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3 || !s1 || !s2)
	{
		printf("ERROR");
		return (NULL);
	}
	i = -1;
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int	ft_strnchr(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	char	*tmp;
	char	*buf;
	int	bytesrd;

	int	bucle_bytesrd;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		printf("ERROR FD - BUFFER_SIZE\n");
		return (NULL);
	}
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	bytesrd = 1;
	bucle_bytesrd = 0;
	while (bytesrd > 0)
	{
		bucle_bytesrd++;
		printf("Bucle bytes: %d\n", bucle_bytesrd);
		bytesrd = read(fd, tmp, BUFFER_SIZE);
		if (bytesrd < 0)
		{
			printf ("ERROR LECTURA");
			//free(tmp);
			return (NULL);
		}
		// Si encontramos /n paramos
		if (ft_strnchr(buf))
		{
			//free(tmp);
			break ;
		}
		// Sino añadimos la palabra
		buf = ft_strjoin(buf, tmp);
		if (!buf)
		{
			//free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	printf("Bytes leidos: %d\n", bytesrd);
	printf("Texto leido:\n%s\n", buf);
	return (buf);
}

int	main(void)
{
	int	fd;
	char	*next_line;
	char	*str1 = "Hola ";
	char	*str2;
	char	*test_strjoin;

	fd = open("archivo.txt",0);
	//next_line = get_next_line(fd);
	free(next_line);
	close(fd);
	test_strjoin = ft_strjoin(str1,str2);
	if (!test_strjoin)
	{
		return (1);
	}
	printf("Test join: %s\n", test_strjoin);
	free(test_strjoin);
	printf("OKOKOK\n");
	return (0);
}
/*
void	*ft_calloc(size_t count, size_t size)
{
	char	*cell;
	
	cell = malloc(count * size);
	if (!cell)
		return (NULL);
	printf("TEST * -> Asignando memoria");
	while (*cell)
		*cell++ = 0;
	return (cell);
}

char	*alloc_buffer(int fd,char *buffer)
{
	int	check_line;
	char	*tmp;
	// Vamos a asignar memoria para la linea
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	printf("TEST 3 -> Memoria asignada");
	free(tmp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return ;
	// Vamos a trabajar con el buffer
	printf("TEST 2 -> asignar buffer correcto");
	buffer = alloc_buffer(fd, buffer);
	return (NULL);
}

int	main(int argc, char **argv)
{
	// Comprobamos que todo esta ok
	if (argc == 2)
	{
		printf("TEST 1 -> Solo 2 argumentos.\n");
		get_next_line(argv[1][0]);
		printf("Function OK");
	}
	return (0);
}
*/
