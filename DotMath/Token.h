#pragma once
#include<string>

struct Token {
	std::string id;
	std::string value;

	Token(const std::string& _id, std::string _value);

	const std::string ToString();
};