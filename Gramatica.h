#include "Produccion.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//Comprobar si una cadena existe en un vector
bool existe(std::vector<std::string> v, std::string cadena){
  for(int i=0; i<v.size(); i++){
    if(v[i] == cadena){
      return true;
    }
  }
  return false;
}

//Borrar el vacio de un vector
void borrarVacio(std::vector<string> &vec) {
  int i;
  string lambda = "\'\'";
  for(i=0; i<vec.size(); i++){
    if(vec[i] == lambda){
      vec.erase (vec.begin()+i);
      break;
    }
  }
  
}

//Borra los elementos repetidos de un vector
template <typename Type>
void borrarRepetidos(std::vector<Type>& vec) {
  std::sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
}


class Gramatica
{
	private:
		vector<Produccion> producciones;
		vector<string> NoTerminales;
		vector<string> Terminales;
	public:
		Gramatica() = default;

    //Se lee la gramática
    void setGramatica(std::string nombre)
    {
      ifstream archivo;
      archivo.open(nombre);
      std::string cadena;
      while (!archivo.eof())
      {
        Produccion pr;
        getline(archivo, cadena);
        cout<<cadena<<endl;

        //Se leen las producciones de acuerdo a las funciones de la clase Produccion
        pr.readProduccionIzquierda(cadena);
        pr.readProduccionDerecha(cadena);

        //Se añade la producción al vector de producciones
        producciones.push_back(pr);
      }
      std::cout<<"----------Gramatica Leida!------------"<<std::endl;
    }

    //Getters de Terminales y No terminales
    vector<string> getNoTerminales(){
      return this->NoTerminales;
    }

    vector<string> getTerminales(){
      return this->Terminales;
    }

    //Se llenan los vectores de nodos terminales y no terminales
    void llenarTerminales_NoTerminales(){
      for(int i=0; i<producciones.size(); i++){
        Produccion aux = producciones[i];
        //Añadir todos los nodos de la izquierda
        if(!existe(NoTerminales, aux.izquierda)){
          NoTerminales.push_back(aux.izquierda);
        }
        
        //Vamos a buscar los terminales a la derecha
        for(int j=0; j<aux.derecha.size(); j++){

          //Si es un terminal
          if(aux.derecha[j][0] == '\''){
            if(!existe(Terminales, aux.derecha[j])){
              Terminales.push_back(aux.derecha[j]);
            }
          }
        }
      }
    }
    
    //Mostrar todos los nodos no terminales
    void printNoTerminales(){
      cout<<"No terminales: "<<endl;
      for(int i=0; i<NoTerminales.size(); i++){
        cout<<NoTerminales[i]<<", ";
      }
      cout<<endl;
    }
  
    //Mostrar todos los nodos terminales
    void printTerminales(){
      cout<<"Terminales: "<<endl;
      for(int i=0; i<Terminales.size(); i++){
        cout<<Terminales[i]<<", ";
      }
      cout<<endl;
    }

    //Retorna un vector con las producciones de un nodo no terminal
    vector<string> getProducciones(std::string nt){
      for(int i=0; i<producciones.size(); i++){
        if(producciones[i].izquierda == nt){
          return producciones[i].derecha;
        }
      }
      return vector<string>();
    }

    //Retorna el primero del nodo señalado y busca en las producciones
    std::string getPrimero(vector<string> &primeros, std::string nt){
      for(int i=0; i<producciones.size(); i++){
        if(producciones[i].izquierda == nt){
          //Si es un terminal
          if(producciones[i].derecha[0][0] == '\''){
            primeros.push_back(producciones[i].derecha[0]);
          }

          //Si es un no terminal, se usa recursividad
          else{
            primeros.push_back(getPrimero(primeros, getProducciones(nt)[0]));
          }
        }
      }
      return "";
    }

    //Retorna un vector con todos los primeros del nodo señalado
    vector<string> getPrimeros(std::string nt){

      //Vector de primeros
      vector<string> primeros;

      //Se pushean en el vector los primeros
      for(int i=0; i<NoTerminales.size(); i++){
        if(NoTerminales[i] == nt){
          getPrimero(primeros, nt);
        }
      }

      return primeros;
    }
    
    //Se muestran los primeros de todos los no terminales
    void printAllPrimeros(){
      cout<<endl<<"-----------------PRIMEROS------------"<<endl;
      for(int i=0; i<NoTerminales.size(); i++){
        vector<string> primeros = getPrimeros(NoTerminales[i]);
        cout<<"Primeros de "<<NoTerminales[i]<<": ";
        for(int j=0; j<primeros.size(); j++){
          cout<<primeros[j]<<" ";
        }
        cout<<endl;
      }
    }

    //Retorna el siguiente del nodo señalado, según la segunda y tercera regla, buscando las producciones
    std::string getSiguiente(std::string nt, vector<string> &siguientes){
      
      for(int i=0; i<producciones.size();i++){
	 //Esta es la primera regla
         if(nt==producciones[0].izquierda){
            siguientes.push_back("\'$\'");
         }      
	 
        if(existe(producciones[i].derecha, nt)){
          
          int j;
          //Averiguaremos en que posicion del vector de la derecha de la producción se encuentra nt
          for(j=0; j<producciones[i].derecha.size(); j++){
            if(nt==producciones[i].derecha[j]){
              break;
            }
          }

          //Verificamos si estamos en la segunda regla
          if(j != producciones[i].derecha.size()-1){
            //Si es un terminal, ese será el siguiente
            if(producciones[i].derecha[j+1][0] == '\'' ){
              siguientes.push_back(producciones[i].derecha[j+1]);
              return producciones[i].derecha[j+1];
            }
            //Será un no terminal
            else{
              vector<string> primeros;
              getPrimero(primeros, producciones[i].derecha[j+1]);
            
              for(int k=0; k<primeros.size(); k++){
                siguientes.push_back(primeros[k]);
              }

              //Verificamos si hay una excepción de la segunda regla
              if(existe(primeros, "\'\'")){
                //Aplicamos la tercera regla
                //Verificamos que el siguiente que vayamos a comprobar no sea el mismo nt
                if(nt != producciones[i].izquierda){
                  vector<string> aux;
                  getSiguiente(producciones[i].izquierda, aux);
                  for(int k=0; k<aux.size(); k++){
                    siguientes.push_back(aux[k]);
                  }
                }
              }
            }

          }

          //Nos encontramos en la tercera regla
          else{

            //Verificamos que el siguiente que vayamos a comprobar no sea el mismo nt
            if(nt != producciones[i].izquierda){
              vector<string> aux;
              getSiguiente(producciones[i].izquierda, aux);
              for(int j=0; j<aux.size(); j++){
                siguientes.push_back(aux[j]);
              }
            }
          }
          
        }
      }

      return "";
    }

    //Función que devolverá todos los siguientes de un nt
    vector<string> getSiguientes(std::string nt){
      vector<string> siguientes;
      getSiguiente(nt,siguientes);

      //Borramos los elementos repetidos y el vacío
      borrarRepetidos(siguientes);
      borrarVacio(siguientes);

      return siguientes;
    }

    //Se muestran los siguientes de todos los no terminales
    void printAllSiguientes(){
      cout<<endl<<"-----------------SIGUIENTES------------"<<endl;
      for(int i=0; i<NoTerminales.size(); i++){
        vector<string> siguientes = getSiguientes(NoTerminales[i]);
        cout<<"Siguientes de "<<NoTerminales[i]<<": ";
        for(int j=0; j<siguientes.size(); j++){
          cout<<siguientes[j]<<" ";
        }
        cout<<endl;
      }
    }

    friend class TAS;

};
