#include "minishell.h"

t_ast ---> 
tok ----- >
void	addb_list(t_ast *ast, t_token **tok)
{
	t_token	*find;

	find = lasttok(((t_command *)ast)->list);
	find->next = ft_newtoken(0, NULL, 0, 0);
	find = find->next;
	find->type = (*tok)->type;
	find->hdoc = (*tok)->hdoc;
	find->expand = (*tok)->expand;
	find->token = (*tok)->token;
	find->down = (*tok)->down;
	find->prev = (*tok)->prev;
	find->next = NULL;
	*tok = (*tok)->next;
}

t_ast	*new_cmd(t_token *list)
{
	t_token		*tmp;
	t_command	*command;

	command = gc(sizeof(t_command), 1, 0);
	if (!command)
		return (NULL);
	command->type = WORD;
	command->list = list;
	tmp = list;
	while (tmp->type == WORD && tmp->type != END)
		tmp = tmp->next;
	tmp = tmp->prev;
	tmp->next = NULL;
	return ((t_ast *)command);
}

t_ast	*new_oper(int type, t_ast *left, t_ast *right)
{
	t_operator	*operator;

	operator = gc(sizeof(t_operator), 1, 0);
	operator->type = type;
	operator->left = left;
	operator->right = right;
	return ((t_ast *)operator);
}

t_ast	*parse_cmd(t_token **tok)
{
	t_ast	*ast;
	t_token	*tmp;

	if ((*tok)->type == OPAR) // Si le jeton actuel est une parenthèse ouvrante
		return (parse_sub(tok)); // Analyser une sous-commande
	if ((*tok)->type == WORD) // Si le jeton actuel est un MOT
	{
		tmp = *tok; // Sauvegarder le jeton actuel
		while ((*tok)->type == WORD && (*tok)->type != END) // Collecter les mots WORD consécutifs
			*tok = (*tok)->next;
		return (ast = new_cmd(tmp), ast); // Créer un nouvel AST de commande avec les mots collectés
	}
	return (NULL); // Retourner NULL si le type de jeton n'est ni OPAR ni WORD
}

t_ast	*redire_info(t_token **tok)
{
	int		type;
	t_ast	*redir;
	t_token	*hold;

	// if ((*tok)->type != RIN && (*tok)->type != ROUT && (*tok)->type != HEREDOC
	// 	&& (*tok)->type != APPEND)
	// 	return (NULL);
	type = (*tok)->type;
	redir = new_reder();
	((t_redir *)redir)->typeredir = type;
	((t_redir *)redir)->flags = O_RDONLY;
	if (type == ROUT || type == APPEND)
		((t_redir *)redir)->flags = O_CREAT | O_WRONLY | ((type == ROUT)
				* O_TRUNC + !(type == RIN) * O_APPEND);
	*tok = (*tok)->next;
	if ((*tok)->type != WORD)
		return (NULL);
	hold = newtoken(*tok);
	((t_redir *)redir)->tok = hold;
	((t_redir *)redir)->arg = join_tokens(hold);
	(type == HEREDOC)
		&& (((t_redir *)redir)->fd_in = heredoc(join_tokens(*tok)));
	if (type == HEREDOC && !((t_redir *)redir)->fd_in)
		return ((*tok)->type = SIGHER, NULL);
	return (*tok = (*tok)->next, redir);
}

t_ast	*parse_redir(t_token **tok)
{
	t_ast	*ast;
	t_ast	*reder;

	ast = parse_cmd(tok); // Analyser la commande
	if ((*tok)->type == RIN || (*tok)->type == ROUT || (*tok)->type == HEREDOC || (*tok)->type == APPEND)
	{
		reder = redire_info(tok); // Collecter les informations de redirection
		if (!reder)
			return (NULL); // Retourner NULL si les informations de redirection ne peuvent pas être collectées
		while ((*tok)->type != AND && (*tok)->type != OR && (*tok)->type != PIPE && (*tok)->type != END)
		{
			if ((*tok)->type != WORD && !addback_redir(reder, redire_info(tok)))
				return (NULL); // Retourner NULL si le type de jeton est invalide ou s'il y a une erreur lors de l'ajout de la redirection
			(!ast && (*tok)->type == WORD) && (ast = parse_cmd(tok)); // Analyser et ajouter des commandes si elles suivent une redirection
			if (ast && (*tok)->type == WORD)
				addb_list(ast, tok); // Ajouter la commande à la liste
		}
		return (addback_redir(reder, ast), reder); // Ajouter la redirection à la liste et la retourner
	}
	return (ast); // Retourner l'AST de la commande s'il n'y a pas de redirection
}

t_ast	*parse_sub(t_token **tok)
{
	t_ast	*ast;

	*tok = (*tok)->next; // Passer au jeton suivant (en sautant la parenthèse ouvrante)
	if ((*tok)->type == CPAR)
		return (NULL); // Retourner NULL si la parenthèse fermante est rencontrée immédiatement
	while ((*tok)->type != CPAR)
	{
		ast = new_sub(parse_oper(tok)); // Analyser le contenu du sous-shell
		if (!((t_subsh *)ast)->sub)
			return (NULL); // Retourner NULL si le contenu du sous-shell ne peut pas être analysé
	}
	*tok = (*tok)->next; // Passer au jeton suivant (en sautant la parenthèse fermante)
	return (ast); // Retourner l'AST du sous-shell
}

t_ast	*parse_pipe(t_token **tok)
{
	t_ast	*ast;

	ast = parse_redir(tok); // Analyser l'opérande gauche
	if (!ast)
		return (NULL); // Retourner NULL si l'analyse de l'opérande gauche échoue
	while ((*tok)->type == PIPE)
	{
		*tok = (*tok)->next; // Passer au jeton suivant (en sautant le PIPE)
		ast = new_oper(PIPE, ast, parse_redir(tok)); // Créer un nouvel opérateur PIPE avec les opérandes gauche et droite
		if (!((t_operator *)ast)->right)
			return (NULL); // Retourner NULL si l'analyse de l'opérande droite échoue
	}
	return (ast); // Retourner l'AST résultant
}

t_ast	*parse_oper(t_token **tok)
{
	t_ast	*ast;

	ast = parse_pipe(tok); // Analyser l'opérande gauche
	if (!ast)
		return (NULL); // Retourner NULL si l'analyse de l'opérande gauche échoue
	while (((*tok)->type == AND || (*tok)->type == OR))
	{
		ast = new_oper((*tok)->type, ast, NULL); // Créer un nouvel opérateur AND ou OR avec l'opérande gauche
		*tok = (*tok)->next; // Passer au jeton suivant
		((t_operator *)ast)->right = parse_pipe(tok); // Analyser l'opérande droite
		if (!((t_operator *)ast)->right)
			return (NULL); // Retourner NULL si l'analyse de l'opérande droite échoue
	}
	return (ast); // Retourner l'AST résultant
}
