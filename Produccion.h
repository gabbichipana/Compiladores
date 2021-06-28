#include <iostream>
#include <iostream>
#include <vector>

struct Nodo
{
  char tipo;
  std::string valor;
}

class Produccion
{
	private:
		Nodo izquierda ;
		std::vector<Nodo> derecha;	
	
	public: 
		Production() = default

    		//Setters y Getters
		Nodo getIzquierda(){
			return izquierda; 
		}

		std::vector<Nodo> getDerecha(){
			return derecha;
		}

		void setIzquierda(Nodo izquierda){
			this->izquierda = izquierda;
		}

		void setDerecha(std::vector<Nodo> derecha){
			this->derecha = derecha;
		}
};
