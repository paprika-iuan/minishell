/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:13:44 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/10 10:19:54 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H 

/****** EXPANSIONS.C ***************/
char		**expand(char **args, t_env *env);

/****** EXP_FIND.C *****************/
int			set_possible_exp(char *args);

/****** DO_DOUBLEQUOTE.C ***********/
void		do_doublequote(char **args, int i, t_env *env);
void		update_case_n2(char **args, char *expanded, int i);

/****** DO_SINGLEQUOTE.C ***********/
void		do_singlequote(char **args, int i, t_env *env);
void		update_case_n1(char **args, char *first, char *second, int i);

/****** DO_JUST_EXPANSION.C ********/
char		**do_just_expansion(char **args, int i, t_env *env);

/****** WS_IFS.C *******************/
int			is_ifs(char c, t_env *env);
char		**do_ws_ifs(char *args, char ifs);

/****** EXPANSION_VAR_UTILS.C ******/
char		*set_after_dollar(char *args);
char		*set_before_dollar(char *args);
char		*dollar_expanded(char *args, t_env *env);
int			ft_arraylen(char **args);
static char	**free_result(char **result, int j);

/****** MATRIX_UTILS.C *************/
char		**update_matrix(char **args, char **splited, int i);
void		concat_before(char **args, char *splited, char *before, int i);
void		concat_after(char **args, char *splited, char *after, int i);
void		update_no_ws_expansion(char **args, int i, char *before, char *after);

/****** FT_SPLITSTR.C **************/
char		**ft_splitstr(char const *s, char *c);

