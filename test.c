# include "parser.h"
void	print_node_argv(char **argv)
{
	// char	**argv = node->argv;
	// t_rdr	*s = (t_rdr *)node->rdrlst;

	// printf("f = %d\n", s->type);
	while (argv && *argv)
		printf("%s\n", *argv++);
}
// t_cmd *cmd_ccomponents(t_lexer *lexer, t_cmd	*cmd, t_rdr_node	*rdr)
// {
// 	t_token	token;

//     token = get_next_token(lexer);
// 	while(token.type != END || token.type != ERROR ||
// 		token.type != PIPE )
// 	{
// 		if (token.type == WORD)
// 			cmd_addback(cmd, ft_new_cmd(ft_substr(lexer->str, 0, token.len), NULL));
// 		else if(token.type == VAR)
// 			cmd_addback(cmd, ft_new_cmd(token.pos, NULL));
// 		else if(token.type == WLDC)
// 			cmd_addback(cmd, ft_new_cmd(token.pos, token.wildcard));
// 		else if(token.type == RD_APP || token.type == RD_IN ||
// 				token.type == RD_OUT || token.type == HERDOC)
// 			rdr_addback(&rdr, collect_rdr);
// 		token = get_next_token(lexer);
// 	}
// 	return (cmd);
// }
int main()
{
    t_cmd *list;
    t_wc_node   **wc_;
    char **av;
    t_lexer *lexer;
    t_rdr_node *rdr;
    t_parser_node *tree;

    // *wc_ = wc_ld_create("*");
    list = ft_new_cmd("aaa", NULL);
    // list->next = ft_new_cmd("aaa", wc_);
    lexer = lex_init(quote_def("echo << as | ls -la | echo $USER"));
    tree = parse_input(lexer);
    // rdr = collect_rdr(lexer, rdr);
    av = av_creat(&list);
    // print_node_argv(av);
    // cmd_clear(&list);
	if (!list->wc)
    	printf("%s\n", list->word);
}