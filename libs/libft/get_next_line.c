/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfleritt <rfleritt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:48:53 by rfleritt          #+#    #+#             */
/*   Updated: 2024/10/20 18:44:05 by rfleritt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free_strjoin(char *r, char *buffer)
{
	char	*aux;
	int		i;

	aux = ft_strjoin(r, buffer);
	if (!aux)
		return (free(r), NULL);
	i = 0;
	if (aux[i] == '\0')
	{
		free(aux);
		return (free(r), NULL);
	}
	return (free(r), aux);
}

static char	*ft_next_line(char *read)
{
	char	*buffer;
	int		i;
	int		j;
	int		s;

	i = 0;
	buffer = NULL;
	while (read[i] != '\n' && read[i] != '\0')
		i++;
	if (read[i] == '\n')
		i++;
	j = 0;
	s = i;
	while (read[s++] != '\0')
		j++;
	if (j > 0)
		buffer = ft_calloc(j + 1, sizeof(char));
	if (!buffer)
		return (free(read), NULL);
	j = 0;
	while (read[i] != '\0')
		buffer[j++] = read[i++];
	if (!buffer)
		return (free(read), NULL);
	return (free(read), buffer);
}

static char	*ft_cut_line(char *read)
{
	char	*buffer;
	int		i;

	i = 0;
	while (read[i] != '\n' && read[i] != '\0')
		i++;
	if (read[i] == '\n')
		buffer = ft_calloc(i + 2, sizeof(char));
	else
		buffer = ft_calloc(i + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (read[i] != '\n' && read[i] != '\0')
	{
		buffer[i] = read[i];
		i++;
	}
	if (read[i] == '\n')
		buffer[i] = '\n';
	return (buffer);
}

static char	*ft_mall_read(int fd, char *buffer, int n)
{
	int		i;
	char	*r;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	r = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!r || !buffer)
		return (free(buffer), free(r), NULL);
	while (n > 0)
	{
		i = 0;
		n = read(fd, r, BUFFER_SIZE);
		if (n < 0)
			return (free(buffer), free(r), NULL);
		r[n] = '\0';
		while (r[i] != '\n' && r[i] != 0)
			i++;
		if (r[i] == '\n')
			n = 0;
		buffer = ft_free_strjoin(buffer, r);
		if (!buffer)
			return (free(r), free(buffer), buffer = NULL, NULL);
	}
	return (free(r), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	int			n;

	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_mall_read(fd, buffer[fd], n);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		return (NULL);
	}
	line = ft_cut_line(buffer[fd]);
	buffer[fd] = ft_next_line(buffer[fd]);
	if (!line)
		return (NULL);
	return (line);
}

/*int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*ptr;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	ptr = get_next_line(fd1);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd1);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd1);
	printf("%s\n", ptr);
	free(ptr);
	ptr = get_next_line(fd2);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd2);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd2);
	printf("%s\n", ptr);
	free(ptr);
	ptr = get_next_line(fd3);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd3);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd3);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(fd3);
	printf("%s", ptr);
	free(ptr);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/