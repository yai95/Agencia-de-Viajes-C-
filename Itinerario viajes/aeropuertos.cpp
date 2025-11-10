#include "aeropuertos.hpp"
#include <iostream>
#include <fstream>

namespace bblProgII{

    Aeropuertos::Aeropuertos(){
        n_aeropuertos = 0;
    }

    Aeropuertos::Aeropuertos(const Aeropuertos &otro_objeto ){
        for (unsigned i = 0; i < otro_objeto.n_aeropuertos; i++){
            aeropuertos[i] = otro_objeto.aeropuertos[i];
        }
        n_aeropuertos = otro_objeto.n_aeropuertos;
    }

    Aeropuertos::~Aeropuertos(){
    }

    Aeropuertos & Aeropuertos::operator=(const Aeropuertos &otro_objeto){
        if (this != &otro_objeto){
            for (unsigned i = 0; i < otro_objeto.n_aeropuertos; i++){
                aeropuertos[i] = otro_objeto.aeropuertos[i];
            }
            n_aeropuertos = otro_objeto.n_aeropuertos;
        }
        return *this;
    }

    void Aeropuertos::consultar_aeropuerto(const std::string &nombre,Aeropuerto &aeropuerto,Resultado &res)const{
        unsigned i = buscar_aeropuerto(nombre);

        if(i!=n_aeropuertos){
             aeropuerto = aeropuertos[i];
            res = OK;
        }
        else{
            res= NO_EXISTE;
        }
    }

    void Aeropuertos::escribir_aeropuertos() const{
        for (unsigned i = 0; i < n_aeropuertos; i++){
            aeropuertos[i].escribir_aeropuerto();


        }
    }

    unsigned Aeropuertos::num_aeropuertos()const{
        return n_aeropuertos;
    }

    void Aeropuertos::insertar_aeropuerto(const Aeropuerto &aeropuerto ,Resultado &res){
        unsigned i = buscar_aeropuerto(aeropuerto.consultar_nombre());

        if(i!=n_aeropuertos){
            res = YA_EXISTE;
        }
        else{
            aeropuertos[i] = aeropuerto;
           n_aeropuertos++;
           res = OK;
        }
    }

    void Aeropuertos::modificar_aeropuerto(const Aeropuerto &aeropuerto, Resultado &res){
        unsigned i = buscar_aeropuerto(aeropuerto.consultar_nombre());


        if (i != n_aeropuertos){
            aeropuertos[i] = aeropuerto;

            res= OK;
        }
        else{
            res = NO_EXISTE;
        }

    }

    void Aeropuertos::eliminar_aeropuerto(const std::string &nombre,Resultado &res){

            unsigned i = buscar_aeropuerto(nombre);


            if (i != n_aeropuertos){
                aeropuertos[i] = aeropuertos[n_aeropuertos-1];
                n_aeropuertos --;
                res= OK;
            }
            else{
                res=NO_EXISTE;
           }

    }

    void Aeropuertos::obtener_aeropuertos(const std::string &fichero,const std::string &pais,Resultado &res){
        std::ifstream ifs;
        ifs.open(fichero.c_str());
        if (!ifs.fail()){
             n_aeropuertos = 0;
            Aeropuerto aero;
            std::string _nombre,_pais;
            double _latitud, _longitud;
            getline(ifs,_nombre,',');//lee hasta la coma
            while (!ifs.eof()){
                getline(ifs,_pais,',');
                ifs >> _latitud;
                ifs.ignore();//elimina la coma
                ifs >> _longitud;
                ifs.ignore();//elimina el retorno de carro


                aero.asignar_nombre(_nombre);
                aero.asignar_pais(_pais);
                aero.asignar_latitud(_latitud);
                aero.asignar_longitud(_longitud);

                if (_pais == pais || pais == "cualquiera"){
                    aeropuertos[n_aeropuertos] = aero;//en la ultima posicion de la lista
                    n_aeropuertos++;
                }

                getline(ifs,_nombre,',');
            }
            ifs.close();
            res = OK;

        }else{
            res = FIC_ERROR;

        }
    }

    void Aeropuertos::guardar_aeropuertos(const std::string &fichero,Resultado &res){
        std::ofstream ofs;
        ofs.open(fichero.c_str());
        if (ofs.fail()) {
                res = FIC_ERROR;
        }
        else{
            for (unsigned i = 0; i < n_aeropuertos;i++){

                ofs << aeropuertos[i].consultar_nombre();
                ofs <<","<< aeropuertos[i].consultar_pais();
                ofs <<"," << aeropuertos[i].consultar_latitud();
                ofs <<"," << aeropuertos[i].consultar_longitud() << std::endl;
            }
            ofs.close();
        }
    }

    void Aeropuertos::escribir_resultado(const Resultado &res)const{
        switch (res) {
            case OK: std::cout << " --- OK." << std::endl;
        break;
            case FIC_ERROR: std::cout << " --- ERROR DE FICHERO. " << std::endl;
        break;
            case NO_EXISTE: std::cout << " --- NO EXISTE. " << std::endl;
        break;
            case YA_EXISTE: std::cout << " --- YA EXISTE. " << std::endl;
        break;
            default: std::cout << " --- CODIGO DE ERROR DESCONOCIDO." << std::endl;

        }
    }

    unsigned Aeropuertos::buscar_aeropuerto(const std::string &nombre) const{
        unsigned i = 0;
        unsigned pos=n_aeropuertos;
        bool encontrado=false;

       while(i<n_aeropuertos && encontrado==false){
            if(aeropuertos[i].consultar_nombre()==nombre){
                pos=i;
                encontrado=true;
            }
            i++;
        }
        return pos;
    }
}
