#include "Gramatica.h"

using namespace std;

class TAS {
  private:
    vector <string> NoTerminales;
    vector <string> Terminales; 
    Produccion **tabla;
  public: 
    TAS(){
      Gramatica g;
      g.setGramatica("g.txt");
      //Identificamos los no terminales y los terminales
      g.llenarTerminales_NoTerminales();
      this->Terminales = g.getTerminales();

      //Agregamos el dólar y quitamos el vacío
      this->NoTerminales = g.getNoTerminales();
      this->Terminales.push_back("\'$\'"); 
      borrarVacio(this->Terminales);

      //Agregamos las producciones
      tabla = new Produccion*[5];
      for(int i=0; i<5; i++){
        tabla[i] = new Produccion[6];
      }

      //<E> con '('  : E := T E'
      tabla[0][2] = g.producciones[0];
      //<E> con 'id'  : E := T E'
      tabla[0][4] = g.producciones[0];
      //<E'> con '+'  : E' := + T E'
      tabla[1][0] = g.producciones[1];
      //<E'> con ')'  : E' := ''
      tabla[1][3] = g.producciones[2];
      //<E'> con '$'  : E' := ''
      tabla[1][5] = g.producciones[2];
      //<T> con '('  :  T := F T'
      tabla[2][2] = g.producciones[3];
      //T con 'id'   : T := F T'
      tabla[2][4] = g.producciones[3];
      //T' con '+'   : T' := ''
      tabla[3][0] = g.producciones[5];
      //T' con '*'   : T' := * F T'
      tabla[3][1] = g.producciones[4];
      //T' con ')'   : T' := ''
      tabla[3][3] = g.producciones[5];      
      //T' con '$'   : T' := ''
      tabla[3][5] = g.producciones[5];
      //F con '('   : F := ( E )
      tabla[4][2] = g.producciones[6]; 
      //F con 'id'   : F := id
      tabla[4][4] = g.producciones[7]; 
    }

    void mostrarTAS(){
      cout<<"------------TAS-------"<<endl<<"              ";
      for(int i=0; i<Terminales.size(); i++){
        cout<<Terminales[i]<<"           ";
      }
      cout<<endl;
      for(int i=0; i<NoTerminales.size(); i++){
        cout<<NoTerminales[i]<<" | ";
        for(int j=0; j<6; j++){
          cout<<tabla[i][j]<<"    ";
        }
        cout<<endl;
      }
    }

    //Dados un Terminal y un No Terminal, se busca la producción que le corresponde de acuerdo a la tabla del TAS
    Produccion buscarProduccion(string nt, string t){
      int x = -1;
      int y = -1;

      //Buscamos la posición x
      for(int i=0; i<Terminales.size(); i++){
        if(Terminales[i] == t){
          x=i;
          break;
        }
      }

      //Buscamos la posición y
      for(int i=0; i<NoTerminales.size(); i++){
        if(NoTerminales[i] == nt){
          y=i;
          break;
        }
      }

      //En caso x o y sean -1, la producción no existirá
      if(x == -1 || y == -1){
        cout<<"ERROR"<<endl;
        return Produccion();
      }
      else{
        return tabla[y][x];
      }
    }

    friend class LL1;
};
