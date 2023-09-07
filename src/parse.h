/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:42:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/09/07 17:48:58 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// Parse_utils
int				get_tokens(void);
char			**alloc_tokens(char *str, int nbr_tokens);
void			handle_special_characters(char **str, int *count);

// Parse_init
void			parse_init(void);
char			*my_getenv(char *str);

// Parse_quotes
int				check_quotes(char *str);
int				nbr_outside_quotes(char *str);
int				nbr_inside_quotes(char *str, char c);
char			*check_envp(char *str);
char			*handle_quote(char	*str, char c);

// Utils
char			*env_var(char *str);
void			handle_error_var(void);
void			handle_shlvl(char c);
char			*strjoin_var(char *s1, char s2);
char			*strjoin_here(char *s1, char *s2);
char			*strjoin_null(char *s1, char *s2);

// Utils 2
void			handle_env(char *str);
int				skip_whitespace(char *str);
void			skip_non_whitespace_and_dolar_sign(char **str);

// Utils 3
int				handle_dollar_sign(char *str);
void			check_echo(void);
int				token_is_space(char *str, int *i);

// Utils 4
char			**init_tokens(int nbr_tokens);
int				token_inside_quote(char	*str, char **tokens);
int				token_special_char(char *str, char **token, int *i);
int				token_space_dolar_sig(char *str, char **token, int nbr_tokens);
int				token_other_chars(char *str, char **token, int *i);

// Utils 5
char			*handle_single_spc_quote(char *str);

#endif
