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
	public:
		std::string left;
		std::vector<std::string> right;	
};

class Grammar
{
	private:
	    std::vector<Production> productions;
	    std::vector<Nodo> NonTerminals;
	    std::vector<Nodo> Terminals;
	public:
		Grammar() = default;
		
		std::vector<Production> getProducciones(std::string nt);
		std::vector<Production> getPrimeros(string nt);
		std::vector<Production> getSiguientes(string nt);
};

std::vector<Production> Grammar::getProducciones(std::string nt)
{
	std::vector<Production> tmp;
	for(const auto i : productions) //recorremos en el vector de producciones de la gramatica
	{ 
		for(const auto j : i.right)  //REcprremos los strings en el vector de string del lago derecho de la produccio,
		{
			if(j == nt)  //vericamos si es el string j conincide con nt
			{
				tmp.push_back(i);  //Si es que si coincide pusheamos la produccion i en el vector que sera devuelto
			}
		}
	}
	return tmp;
};
