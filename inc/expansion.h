/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:13:44 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/22 10:55:50 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H 

/****** EXPANSIONS.C ***************/
char	**expand(char **args, t_env *env);
int		find_end_var(char *args);

/****** EXP_FIND.C *****************/
int		expansion_type(char *args);
int		find_dollar(char *args, char n, int i);
int		count_var_len(char *args, int start);
int		find_closure(char *args, char n, int i);

/****** DO_DOUBLEQUOTE.C ***********/
char	**do_doublequote(char **args, int i, t_env *env);
void	update_case_n2(char **args, char *expanded);

/****** DOUBLE_QUOTE_UTILS.C ***********/
char	*extract_str(char **args, int i, int begin_join, int num_appear);
char	*expand_dollar_line(char *quotes, t_env *env);
char    **set_tmp_arr(char *after, t_env *env);
char	**fuse_dqvars(char *quotes, char *after, t_env *env);


/****** DO_SINGLEQUOTE.C ***********/
char	**do_singlequote(char **args, int i, t_env *env);
void	update_case_n1(char **args, char *first, char *second);

/****** DO_NOQUOTE.C **************/
char	**do_noquote(char **args, int i, t_env *env);
char	**expand_if_dollar(char *args, t_env *env);

// /****** WS_IFS.C *******************/
// int		is_ifs(char c, t_env *env);
// char	**do_ws_ifs(char *args, char *ifs);

/****** EXPANSION_VAR_UTILS.C ******/
char	*set_after_dollar(char *args);
char	*set_before_dollar(char *args);
char	*dollar_expanded(char *args, t_env *env);
int		ft_arraylen(char **args);

/****** MATRIX_UTILS.C *************/
char	**update_matrix(char **args, char **splited, int i);
char	**concat_before(char **splited, char *before);
char	**concat_after(char **splited, char **after);
char	**update_no_ws_exp(char **args, int i, char *before, char **after);

/****** FT_SPLITSTR.C **************/
char	**ft_splitstr(char const *s, char *c);
int		is_split_ifs(char ch, char *c);

char	*expand_dollar_line(char *quotes, t_env *env);

/****** QUOTES.C *******************/
char	**expand_quotes(char **args);
char	**reset_expanded_quotes(char **args);

/****** NO_QUOTE_UTILS.C ***********/
char	**update_no_ws_exp(char **args, int i, char *before, char **after);
char	**case_no_ws(char *dollar);
char	**do_word_splitting(char *dollar);
void	cleanup_vars(char *before, char *after, char **splited, char **a_s);
char	*set_context_before(char **args, int i);

#endif
