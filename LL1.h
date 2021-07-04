#include "TAS.h"
#include <stack>
#include <queue>

using namespace std;


class LL1{
  private:
    Gramatica g;
    TAS tas;
  public:

    //Le pasamos como parámetro al constructor el nombre del archivo que contiene la gramática
    LL1 (std::string fileName){
      g.setGramatica(fileName);
      //Identificamos los no terminales y los terminales
      g.llenarTerminales_NoTerminales();

      //Se muestran todos los no terminales
      g.printNoTerminales();

      //Se muestrna todos los terminales
      g.printTerminales();

      //Se muestran todos los primeros de todos los nt
      g.printAllPrimeros();

      //Se muestran todos los siguientes de todos los nt
      g.printAllSiguientes();

      //El TAS se construye de forma manual
      TAS taSs;
      this->tas = taSs;
      this->tas.mostrarTAS();
    }
    
    //Tokeniza la entrada, añade cada token a una cola y devuelve la cola
    queue<string> tokenizarEntrada(string cadena){
      int i=0;
      queue <string> cola;

      while(!cadena.empty()){

        int pos = cadena.find_first_of(" ");
        string aux;

        if(pos != -1){
          aux = "\'";
          aux += cadena.substr(0,pos);
          cadena.erase(0, pos+1);
          aux += "\'";
          cola.push(aux);
        }

        else{
          aux = "\'";
          aux += cadena;
          aux += "\'";
          cola.push(aux);
          cadena = "";
          break;
        }
      }

      return cola;
    }

    //Analizamos una cadena
    bool analizar(string cadena){
      
      //Pila, añadimos el dólar y el estado inicial
      stack <string> pila;
      pila.push("\'$\'");
      pila.push(this->g.producciones[0].izquierda);

      //Cola, se tokeniza la entrada y se añade un dólar al final
      queue <string> cola;
      cola = tokenizarEntrada(cadena);
      cola.push("\'$\'");

      while(!pila.empty() && !cola.empty()){
      
        //Son terminales
        if(pila.top() == cola.front()){
          pila.pop();
          cola.pop();
        }

        //Buscamos la producción del no terminal con el terminal en el TAS
        else{
          string nt = pila.top();
          pila.pop();
          
          Produccion ptmp = tas.buscarProduccion(nt, cola.front());
          cout<<ptmp<<endl;
          if(ptmp.derecha.size() == 0){
            return false;
          }

          int size = ptmp.derecha.size();
          for(int i=0; i<size; i++){
            if(ptmp.derecha[size- i -1] == "\'\'"){
              continue;
            }
            else{
              pila.push(ptmp.derecha[size- i -1]);
            }
          }
          
        }
      }

      if(pila.empty() && cola.empty()){
        return true;
      }
      else{
        return false;
      }
    }
    
    
};
