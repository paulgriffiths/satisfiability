#include <stdbool.h>
#include "token.h"

bool token_is_id(struct token * token)
{
	if ( token ) {
		return token->type == TOKEN_ID;
	}
	else {
		return false;
	}
}

bool token_is_operator(struct token * token)
{
	if ( token ) {
		return token->type == TOKEN_OP;
	}
	else {
		return false;
	}
}

bool token_is_not(struct token * token)
{
	if ( token ) {
		return (token->type == TOKEN_OP) && (token->value.type == OP_NOT);
	}
	else {
		return false;
	}
}

bool token_is_and(struct token * token)
{
	if ( token ) {
		return (token->type == TOKEN_OP) && (token->value.type == OP_AND);
	}
	else {
		return false;
	}
}

bool token_is_or(struct token * token)
{
	if ( token ) {
		return (token->type == TOKEN_OP) && (token->value.type == OP_OR);
	}
	else {
		return false;
	}
}

bool token_is_lparen(struct token * token)
{
	if ( token ) {
		return token->type == TOKEN_LPAREN;
	}
	else {
		return false;
	}
}

bool token_is_rparen(struct token * token)
{
	if ( token ) {
		return token->type == TOKEN_RPAREN;
	}
	else {
		return false;
	}
}
