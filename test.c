
#include<stdio.h>
#include<unistd.h>
#include <sys/errno.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef struct t_list
{
  char *content;
  struct t_list *next;
}t_list;

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		size;
	int		j;

	size = 0;
	while (s1[size])
		size++;
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (copy == NULL)
		return (copy);
	j = 0;
	while (s1[j])
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
void dell(void *content)
{
  free(content);
  content = NULL;
  return ;
}
void	ft_lstdelone(t_list *lst,  void (*del)(void *))
{
	if (lst && del)
		del(lst->content);
	free(lst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (lst)
	{
		lst->content = content;
		lst->next = NULL;
	}
	return (lst);
}
void  print_list(t_list *lst)
{
  t_list *temp;
  temp = lst;
  while(temp)
  {
    printf("%s\n",temp->content);
    temp = temp->next;
  }
}
int main()
{
  t_list *head;
  t_list *second;
  t_list *third;

  head = ft_lstnew(ft_strdup("zack"));
  second = ft_lstnew(ft_strdup("oussama"));
  third = ft_lstnew(ft_strdup("anas"));


  head->next = second;
  second->next = third;
  third->next = NULL;

  print_list(head);

  ft_lstdelone(second, &dell);

  print_list(second);
}