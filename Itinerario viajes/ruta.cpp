#include "ruta.hpp"

using namespace std;
namespace bblProgII{
    Ruta::Ruta(){
        origen="";
        destino="";
        precio=0.0;
        duracion=0;
        linea_aerea="";
    }

    Ruta::Ruta(const Ruta &otra_ruta){
        origen = otra_ruta.origen;
        destino = otra_ruta.destino;
        precio = otra_ruta.precio;
        duracion = otra_ruta.duracion;
        linea_aerea = otra_ruta.linea_aerea;
    }


    Ruta::Ruta(const std::string &origen_ini,
               const std::string &destino_ini,
               double precio_ini,
               unsigned duracion_ini,
               const std::string &linea_aerea_ini){

                   origen=origen_ini;
                    destino=destino_ini;
                   precio=precio_ini;
                   duracion=duracion_ini;
                   linea_aerea=linea_aerea_ini;
               }


    void Ruta::asignar_origen(const std::string &nuevo_origen){
        origen = nuevo_origen;
        }
    void Ruta::asignar_destino(const std::string &nuevo_destino){
        destino = nuevo_destino;
        }
    void Ruta::asignar_precio(double nuevo_precio){
        precio = nuevo_precio;
        }
    void Ruta::asignar_duracion(unsigned nueva_duracion){
        duracion = nueva_duracion;
        }
    void Ruta::asignar_linea_aerea(const std::string &nueva_linea){
        linea_aerea = nueva_linea;
        }
    std::string Ruta::consultar_origen() const{
        return origen;
        }
    std::string Ruta::consultar_destino() const{
        return destino;
        }
    double Ruta::consultar_precio() const{
        return precio;
        }
    unsigned Ruta::consultar_duracion() const {
        return duracion;
        }
    std::string Ruta::consultar_linea_aerea() const {
        return linea_aerea;
        }
    void Ruta::escribir_ruta() const{
        cout << origen << ", " << destino<< "," << precio <<", " << duracion << ", " << linea_aerea;
        }
    bool Ruta::operator==(const Ruta &otra_ruta) const{
        return (origen == otra_ruta.origen &&
		        destino == otra_ruta.destino &&
		        precio == otra_ruta.precio &&
		        duracion == otra_ruta.duracion &&
		        linea_aerea == otra_ruta.linea_aerea);
    }

}
