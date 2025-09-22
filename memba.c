t_NodeAST ao_loop(t_token *tokens)
{
	t_token		*dup;
	t_NodeAST	*head;
	
	dup = tokens;
	if (head = NULL)
		head = set_subshell_node(dup);
	else if (head = NULL)
		head = set_pipe_node(dup);
	else if (head = NULL)
		head = set_cmd_node(dup);
	else
	{
		set_error();
		return (1);
	}
	tokens = dup;
	return (head);
}

t_NodeAST pipe_loop(t_token *tokens)
{
	t_token *dup;
	dup = tokens;
	if (tokens->type == SUBSHELL)
	head = set_subshell_node(dup);
	else if (tokens->type == WORD)
	head = set_cmd_node(dup);
	else
	{
		set_error();
		return (1);
	}
	tokens = dup;
	return (head);
}

t_NodeAST	*set_ast_and(t_NodeAST *left, t_NodeAST *right)
{
	t_NodeAST	*node;

	node = malloc(sizeof(t_NodeAST));
	node->e_NodeType = NODE_AND;
	node->binary.left = left;
	node->binary.right = right;
	return (node);
}

t_NodeAST	*set_ast_or(t_NodeAST *left, t_NodeAST *right)
{
	t_NodeAST	*node;

	node = malloc(sizeof(t_NodeAST));
	node->e_NodeType = NODE_OR;
	node->binary.left = left;
	node->binary.right = right;
	return (node);
}