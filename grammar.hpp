#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <iostream>
#include <string>
#include <vector>

enum Type
{
	Non_terminal,
	Terminal
};

struct Nodo
{
	Type type;
	std::string value;
};

class Production
{
	private:
		std::string left;
		std::vector<std::string> right;	
	
	public: 
		Production() = default
		
		Nodo getLeft();
	    std::vector<Nodo> getRight();
	    void setLeft(Nodo left);
	    void setRight(std::vector<Nodo> right);
		
		std::vector<Production> getProducciones(std::string nt);
		std::vector<Production> getPrimeros(string nt);
		std::vector<Production> getSiguientes(string nt);
		
};

class Grammar
{
	private:
	    std::vector<Production> productions;
	    std::vector<Nodo> NonTerminals;
	    std::vector<Nodo> Terminals;
	public:
		Grammar() = default;
};

#include "grammar.inl"
#endif //GRAMMAR_HPP
