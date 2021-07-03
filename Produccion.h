#include <iostream>
#include <vector>

//Retorna la posicion de una cadena cuando se encuentra >
int findNonTerminal(std::string text, int pos){
  for(int i=pos+1; i<text.size(); i++){
    if(text[i] == '>'){
      return i;
    }
  }
  return -1;
}

//Retorna la posicion de una cadena cuando se encuentra '
int findTerminal(std::string text, int pos){
  for(int i=pos+1; i<text.size(); i++){
    if(text[i] == '\''){
      return i;
    }
  }
  return -1;
}

class Produccion
{
	private:
		std::string izquierda ;
		std::vector<std::string> derecha;	
	
	public: 
		Produccion() = default;

    //Setters y Getters
		std::string getIzquierda(){
      return izquierda; 
    }

		std::vector<std::string> getDerecha(){
      return derecha;
    }

		void setIzquierda(std::string izquierda){
      this->izquierda = izquierda;
    }

		void setDerecha(std::vector<std::string> derecha){
      this->derecha = derecha;
    }

    void readProduccionIzquierda(std::string produccion){

      //Buscamos el nodo no terminal del lado izquierdo
      for(int i=0; i<produccion.size(); i++){
        if(produccion[i] == '<'){
          this->izquierda = produccion.substr(i, findNonTerminal(produccion, -1)-i+1);
          break;
        }
      }
    }

    void readProduccionDerecha(std::string produccion){
      //Eliminamos la parte izquierda 
      for(int i=0; i<produccion.size(); i++){
        if(produccion[i] == '='){
          produccion.erase(produccion.begin(), produccion.begin()+i+1);
          break;
        }
      }
     
      //Ahora solo trabajamos con la parte derecha
      for(int i=0; i<produccion.size(); i++){

        //Terminal
        if(produccion[i] == '\''){
          std::string terminal = produccion.substr(i, findTerminal(produccion, i)-i+1);
          produccion.erase(produccion.begin(), produccion.begin()+findTerminal(produccion, i)+1);
          i=0;
          
          derecha.push_back(terminal);
        }

        //No terminal
        else if(produccion[i] == '<'){
          std::string no_terminal = produccion.substr(i, findNonTerminal(produccion, i)-i+1);
          produccion.erase(produccion.begin(), produccion.begin()+findNonTerminal(produccion, i)+1);
          i=0;
          derecha.push_back(no_terminal);
        }
      }
      
    }

    friend class Gramatica;
    friend std::ostream& operator << (std::ostream &o,const Produccion &p);
  
};


using namespace std;
// Sobrecarga del operador << para la clase Producción
ostream& operator << (ostream &o,const Produccion &p){
  if(p.derecha.size()==0){
    o<<"           ";
    return o;
  }
  else{
    o<<p.izquierda<<": ";
    for(int i=0; i<p.derecha.size(); i++){
      o<<p.derecha[i]<<" ";
    }
    return o;
  }
  
}
