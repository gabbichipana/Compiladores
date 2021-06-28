#include "Production.h"


class Gramatica
{
	private:
		std::vector<Produccion> producciones;
		std::vector<std::string> NoTerminales;
		std::vector<std::string> Terminales;
	public:
		Grammar() = default;

	    	void setProducciones(vector <Produccion> producciones)
	    	{
	      		this->producciones = producciones;
	    	}

	    	std::vector<Produccion> getProducciones(std::string nt)
	    	{
	      		return this->producciones
	    	}		


	    	std::vector<Produccion> getPrimeros(string nt)
		{
			
		}
		std::vector<Produccion> getSiguientes(string nt)
		{
			
		}
};
