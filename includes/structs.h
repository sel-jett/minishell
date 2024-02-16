#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct s_node_arg
{
	char    *value;
	struct  s_node_arg *next;
}t_node_arg;

typedef struct s_list_arg
{
	struct s_node_arg	*top;
	struct s_node_arg	*tail;
	int					len;
}t_list_arg;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

typedef struct s_node
{
	char            *value;
	struct s_node   *next;
	struct s_node   *prev;
	int              mode;
	int              val_vide;
	t_list_arg 		*list_arg;
}t_node;

typedef struct s_list
{
	t_node  *top;
	t_node  *tail;
	int     len;
}t_list;

enum{
	TOKEN_EXPR,//  0
	TOKEN_REDIR_IN, //< 1
	TOKEN_REDIR_OUT, //> 2
	TOKEN_REDIR_APPEND, //>> 3
	TOKEN_HEREDOC,// << 4
	TOKEN_PIPE,//5
	TOKEN_AND,//6
	TOKEN_OR,//7
	TOKEN_SPACE,//8
	TOKEN_BRKT_OPEN,//9
	TOKEN_BRKT_CLOSE,//10
	TOKEN_Double_Q,//11
	TOKEN_Single_Q,//12
	TOKEN_DOLLAR,//13
} ;

// TOKEN_EXPR: Represents an expression in the context of a programming language or similar domain.

// TOKEN_REDIR_IN: Indicates a redirection operation for input (e.g., < in some shell scripting languages).

// TOKEN_REDIR_OUT: Indicates a redirection operation for output (e.g., > in some shell scripting languages).

// TOKEN_REDIR_APPEND: Indicates a redirection operation to append output to a file (e.g., >> in some shell scripting languages).

// TOKEN_HEREDOC: Represents a here document, a way to embed multiple lines of input in a script or program.

// TOKEN_PIPE: Represents a pipe (|) used for connecting the output of one process to the input of another in shell scripting.

// TOKEN_AND: Represents a logical AND operator (e.g., && in shell scripting).

// TOKEN_OR: Represents a logical OR operator (e.g., || in shell scripting).

// TOKEN_SPACE: Represents a space character.

// TOKEN_BRKT_OPEN: Represents an opening bracket or parenthesis.

// TOKEN_BRKT_CLOSE: Represents a closing bracket or parenthesis.

// TOKEN_D_Q: Represents a double quote (") in string handling.

// TOKEN_S_Q: Represents a single quote (') in string handling.

// TOKEN_DOLLAR: Represents a dollar sign ($) often used to denote variables or special characters in shell scripting.


#endif