#include "paquete.hpp"

namespace umalcc{
        Paquete::~Paquete(){}
        Paquete::Paquete(){
            codigo="";
            plazas=0;
            precio=0;
        }
        Paquete::Paquete(const std::string&c;int p1,int pr){
            codigo=c;
            plazas=p1;
            precio=pr;
        }
        Paquete::Paquete(const Paquete&o){
            codigo=o.codigo;
            plazas=o.plazas;
            precio=o.precio;
        }
        Paquete& Paquete::operator=(const Paquete&o){
            if(this!=&o){
                       codigo=o.codigo;
            plazas=o.plazas;
            precio=o.precio;
                }return *this;
        }
        bool Paquete::error() const{
            return(codigo==""||plazas<0||precio<0);
        }
        std::string Paquete::obtener_codigo() const{
            return codigo;
        }
        int Paquete::obtener_plazas() const{
            return plazas;
        }
        int Paquete::obtener_precio() const{
            return precio;
        }
        void Paquete::modificar_plazas(int p,bool& ok){
            ok=false;
            if(p>=0){
                plazas=p;
                ok=true;
            }
        }
        void Paquete::modificar_precio(int p,bool & ok){
            ok=false;
            if(p>=0){
                precio=p;
                ok=true;
            }
        }
        void Paquete::mostrar() const{
            std::cout<<codigo<<" "<<plazas<<precio;
        }
}
