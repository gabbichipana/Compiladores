#include <iostream>
#include <vector>
#include <string>

struct Nodo{
  char tipo;
  std::string valor;
}

class Produccion{
	private:
		Nodo izquierda ;
		std::vector<Nodo> derecha;	
	
	public: 
		Production() = default

		Nodo getIzquierda();
		std::vector<Nodo> getDerecha();
		void setIzquierda(Nodo izquierda);
		void setDerecha(std::vector<Nodo> derecha);
};

Nodo Produccion::getIzquierda()
{
  return izquierda; 
}

std::vector<Nodo> Produccion::getDerecha()
{
  return derecha;
}

void Produccion::setIzquierda(Nodo izquierda)
{
  this->izquierda = izquierda;
  //this -> izquierda.tipo = izquierda.tipo;
  //this -> izquierda.valor = izquierda.valor;
}

void Produccion::setDerecha(std::vector<Nodo> derecha)
{
  this->derecha = derecha;
}
