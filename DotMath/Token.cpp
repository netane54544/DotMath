#include "Token.h"

Token::Token(const std::string& _id, std::string _value) {
	this->id = _id;
	this->value = _value;
};

const std::string Token::ToString() 
{
	return id + ": " + value;
}