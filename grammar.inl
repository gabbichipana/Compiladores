inline Nodo Production::getLeft()
{
    return leftSide;
}

inline std::vector<Nodo> Production::getRight()
{
    return rightSide;
}

inline void Production::setLeft(Nodo Left)
{
    this->leftSide = LeftSide;
}

inline void Production::setRight(std::vector<Nodo> Right)
{
    this->rightSide = RightSide;
}



inline std::vector<Production> Grammar::getProducciones(std::string nt)
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

inline std::vector<Production> Grammar::getPrimeros(std::string nt)
{
	
}
inline std::vector<Production> Grammar::getSiguientes(std::string nt)
{
	
}
