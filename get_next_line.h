#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_list
{
	int				fd;
	int				open;
	char			*str;
	struct s_list	*next;
}					t_list;

t_list				*ft_get_list(t_list **head, int fd);

int					get_next_line(int fd, char **line);
int					get_next_line_rec(int fd, char **line);

char				*ft_strdup(char *str);
char				*ft_strndup(char *str, int n);
char				*ft_strjoin_free(char *str1, char *str2, char c);

int					ft_get_pos(char *str, char *set);


#endif