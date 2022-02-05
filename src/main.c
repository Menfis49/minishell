/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:26:47 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 14:57:35 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	pars_ast_exec(t_list **lexer, t_data *data)
{
	if (!parsing(data, lexer))
		return ;
	init(data);
	delete_isspaces_token(lexer);
	init_delimiter(data);
	reverse_order_pipe_lexer(lexer, data);
	create_ast(&data->ast, lexer, data);
	exec_delimiter(&data->ast, data);
	reset_ret_data(data);
	if (data->do_exec)
		exec(&data->ast, data);
	wait_n_close(data);
}

void	norme_signals(void)
{
	signal(SIGINT, handle);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*prompt;

	(void)ac;
	(void)av;
	get_caller_env(&data, env);
	norme_signals();
	prompt = "\033[0;32mminishell \033[1;32m» \033[0m";
	init_first(&data);
	data.line_read = readline(prompt);
	while (data.line_read)
	{
		add_history(data.line_read);
		lexing(data.line_read, &data.lexer, &data);
		pars_ast_exec(&data.lexer, &data);
		free_all_except_env(&data);
		data.line_read = readline(prompt);
	}
	built_exit(&data, NULL);
	return (g_exit_status);
}
