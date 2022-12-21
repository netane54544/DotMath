#include <vector>
#include <string>
#include <iostream>
#include "Token.h"
#include "Tree.h"
using namespace std;

template<typename T>
bool findItem(const T ourArray[],size_t arraySize, T item) 
{
	for (unsigned int i = 0; i < arraySize; i++) 
	{
		if (ourArray[i] == item)
			return true;
	}

	return false;
}

const string ids[]{ "out", "case", "a", "AWhile"};
const string operations[] {"^", "*", "/","+", "-", "=", "(", ")"};
vector<Token>* tokenize(const vector<string>& text) 
{
	vector<Token> storeTokens;
	bool isString = false;

	for (unsigned int i = 0; i < text.size(); i++) 
	{
		string line = text.at(i);
		string sT;
		size_t length = line.length();

		for (unsigned int j = 0; j < length; j++)
		{
			if (line.find_first_not_of(' ') == std::string::npos && line == "\n")
			{
				break;
			}
			else
			{
				string sL;
				if (line[j] == '(')
				{
					bool found = false;
					isString = true;

					size_t lookForQ = line.find_first_of('%', j+1);
					size_t lookLeft = line.find(")", j + 1);
					bool checkSpace = (lookForQ == j + 1);

					if (lookLeft == string::npos && checkSpace)
					{
						sL += line.substr(j + 1, line.length() - j + 1);

						for (unsigned int w = i + 1; w < text.size(); w++)
						{
							const string& tempLine = text.at(w);
							size_t getPlace = tempLine.find(')');

							if (getPlace == string::npos || tempLine.find('(') != string::npos)
							{
								sL += tempLine;
							}
							else
							{
								sL += tempLine.substr(0, getPlace);
								found = true;
								j = getPlace+1;
								i = w;
								line = text.at(i);
								length = line.length();
								break;
							}
						}
					}
					else if(checkSpace)
					{
						sL = line.substr(j + 2, lookLeft - j - 1);
						size_t findBracket = sL.find(')');

						if(findBracket != string::npos)
							sL.replace(findBracket, 1, "");

						found = true;
						j += lookLeft - j + 1;
					}

					if (found == false)
					{
						if (lookForQ != string::npos) 
						{
							//storeTokens.push_back(Token("Exception", sL + " is not an expression"));
						}
						else 
						{
							storeTokens.push_back(Token("Exception", "missing ')'"));
						}

						//return new vector<Token>(storeTokens);
					}
					else
					{
						storeTokens.push_back(Token("string", sL));
					}
					isString = false;
				}

				if (j >= length)
				{
					break;
				}

				bool numberCheck = false;
				if (!isString) 
				{
					if((line[j] >= (char)48 && line[j] <= (char)57))
					{
						storeTokens.push_back(Token("number", string::basic_string(1, line[j])));
						numberCheck = true;
					}
					else 
					{
						for (const string& op : operations)
						{
							if (op[0] == line[j])
							{
								if (j + 1 < length && line[j + 1] == '%') 
								{
									j -= 1;
									break;
								}

								storeTokens.push_back(Token("operator", op));
								numberCheck = true;
							}
						}
					}
				}

				if (!isString && line[j] != ' ' && line[j] != '\n')
				{
					sT += line[j];
					for (const string& tempId : ids)
					{
						if (sT == tempId)
						{
							storeTokens.push_back(Token("id", tempId));
							sT = "";
							break;
						}
					}
				}
				else if(!isString)
				{
					size_t findFirst = sT.find_first_not_of(' ');

					if (findFirst != std::string::npos && !numberCheck) 
					{
						if (!((sT[findFirst] >= (char)48 && sT[findFirst] <= (char)57) || findItem<string>(operations, size(operations),string::basic_string(1, sT[findFirst]))))
						{
							storeTokens.push_back(Token("Exception", sT + " is not an expression"));
						}
					}

					sT = "";
				}	
			}
		}

		//For the last word
		/*
		if (sT.find_first_not_of(' ') != std::string::npos)
		{
			storeTokens.push_back(Token("Exception", sT + " is not an expression"));

			//return new vector<Token>(storeTokens);
		}
		*/
	}

	return new vector<Token>(storeTokens);
}

vector<btree>* createAst(const vector<Token>& tokens)
{
	vector<btree> sequanceOfAst;
	int counter = -1;

 	for (const Token& token: tokens) 
	{
		if(token.id == "id")
		{
			sequanceOfAst.push_back(btree(token.id, token.value));
			counter++;
		}
		else 
		{
			if (token.id == "string")
			{
				sequanceOfAst.at(counter).insert(token.id, token.value);
			}
			else if (token.id == "operator" || token.id == "number") 
			{
				if (sequanceOfAst.at(counter).getId() == "id") 
				{
					sequanceOfAst.at(counter).insert(token.id, token.value);
				}
				else 
				{
					sequanceOfAst.push_back(btree(token.id, token.value));
					counter++;
				}
			}
		}
	}

	return new vector<btree>(sequanceOfAst);
}

void printBT(const std::string& prefix, const node* _node, bool isLeft)
{
	if (_node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "L--");

		// print the value of the node
		std::cout << "(" + _node->id + ", " + _node->value + ")" << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), _node->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), _node->right, false);
	}
}

void printBT(const node* _node)
{
	printBT("", _node, false);
}

int main() 
{
	vector<string> read;
	read.push_back("out (6 + 2) - 2");
	read.push_back("out out");

	vector<Token>* tokens = tokenize(read);
	vector<btree>* treeList = createAst(*tokens);

	for (Token& token : *tokens)
	{
		cout << token.ToString() << endl;
	}

	for(btree& tree: *treeList)
	{
		printBT(tree.getRoot());
	}

	for (btree& tree : *treeList)
	{
		tree.destroy_tree();
	}

	delete(tokens);
	delete(treeList);

	return 0;
}
