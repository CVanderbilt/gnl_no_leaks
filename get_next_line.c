#include "get_next_line.h"

t_list	*ft_get_list(t_list **head, int fd)
{
	t_list *tmp;

	tmp = *head;
	while(tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = malloc(sizeof(t_list))))
		return (0);
	tmp->str = 0;
	tmp->fd = fd;
	tmp->open = 1;
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}

char	*ft_strjoin_free(char *str1, char *str2, char c)
{
	int i;
	int j;
	char *ret;

	i = 0;
	j = 0;
	if (!str1)
	{
		if (!(str1 = ft_strdup("")))
			return (0);
		if (c == 'R')
			c = 'B';
		else if (c != 'B')
			c = 'L';
	}
	if (!str2)
	{
		if (!(str2 = ft_strdup("")))
			return (0);
		if (c == 'B' || c == 'L')
			c = 'B';
		else
			c = 'R';
	}
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	if (!(ret = malloc(i + j + 1)))//liberando?
		return (0);
	i = -1;
	j = -1;
	while (str1[++i])
		ret[i] = str1[i];
	while (str2[++j])
		ret[i + j] = str2[j];
	ret[i + j] = 0;
	if (c == 'L' || c == 'B')
		free(str1);
	if (c == 'R' || c == 'B')
		free(str2);
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	i = i > n ? i : n;
	if (!(ret = malloc (i + 1)))
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strdup(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (ft_strndup(str, i));
}

int		ft_get_pos(char *str, char *set)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (!str || !set)
		return (-1);
	while (str[++i])
	{
		while (set[++j])
		{
			if (set[j] == str[i])
				return (i);
		}
		j = -1;
	}
	return (-1);
}

int		ft_aux(char **line, t_list *tmp, int pos)
{
	char *aux;

	printf("ENTRADA AUX:\n");
	if (!(*line = ft_strjoin_free(*line, ft_strndup(tmp->str, pos), 'B')))
		return (0);//linea + resto
	printf("line: >%s<\n", *line);
	aux = ft_strdup(tmp->str + pos + 1);//resto nuevo
	free(tmp->str);
	tmp->str = aux;
	return (1);
}

int		ft_supr_lst(t_list **head, t_list *to_del)
{
	t_list *tmp;

	tmp = *head;
	if (tmp == to_del)
	{
		tmp = tmp->next;
		free(to_del->str);
		to_del->str = 0;
		free(to_del);
		to_del = 0;
		return (0);
	}
	while (tmp)
	{
		if (tmp->next == to_del)
		{
			tmp->next = to_del->next;
			free(to_del->str);
			to_del->str = 0;
			free(to_del);
			to_del = 0;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		get_next_line_rec(int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;
	int				pos;//
	//char			*aux;//
	char			line_r[BUFFER_SIZE + 1];

	if (!(tmp = ft_get_list(&head, fd)))
		return (-1);
	//printf("entrada guardado: >%s<\n", tmp->str);
	pos = ft_get_pos(tmp->str, "\n\r");
	//printf("pos = %d\n", pos);
	if (pos >= 0)
	{
		if (!ft_aux(line, tmp, pos))
			return (0);
		return (1);

		/*if (!(*line = ft_strjoin_free(*line, ft_strndup(tmp->str, pos), 'B')))
			return (-1);//linea + resto
		aux = ft_strdup(tmp->str + pos + 1);//resto nuevo
		free(tmp->str);
		tmp->str = aux;
		return (1);*/
	}
	while (tmp->open)
	{
		pos = read(fd, line_r, BUFFER_SIZE);
		line_r[pos] = 0;
		tmp->open = pos;
		//printf("leido: >%s<\n", line_r);
		//printf("control %d\n", pos);
		tmp->str = ft_strjoin_free(tmp->str, line_r, 'L');
		//printf("join: >%s<\n", tmp->str);
		pos = ft_get_pos(tmp->str, "\n\r");
		//printf("pos? = %d\n", pos);
		if (pos > 0)
			if (!ft_aux(line, tmp, pos))
				return (-1);
	}
	if (!(*line = ft_strjoin_free(*line, ft_strdup(tmp->str), 'B')))
		return (-1);
	//printf("last_line: >%s<\n", *line);
	return (ft_supr_lst(&head, tmp));
}

int		get_next_line(int fd, char **line)
{
	if(fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	return (get_next_line_rec(fd, line));
}







