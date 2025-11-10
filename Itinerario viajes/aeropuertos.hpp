#ifndef AEROPUERTOS_HPP_INCLUDED
#define AEROPUERTOS_HPP_INCLUDED
#include "aeropuerto.hpp"

#include <string>

namespace bblProgII{
    typedef unsigned Resultado;
    const Resultado OK = 0,
                FIC_ERROR = 1,
                NO_EXISTE = 2,
                YA_EXISTE=3;


class Aeropuertos{

public:

    Aeropuertos();

    Aeropuertos(const Aeropuertos &otro_objeto );

    ~Aeropuertos();

    Aeropuertos & operator=(const Aeropuertos &otro_objeto);

    void consultar_aeropuerto(const std::string &nombre,Aeropuerto &aeropuerto,Resultado &res)const;

    void escribir_aeropuertos() const;

    unsigned num_aeropuertos()const;

    void insertar_aeropuerto(const Aeropuerto &aeropuerto ,Resultado &res);

    void modificar_aeropuerto(const Aeropuerto &aeropuerto, Resultado &res);

    void eliminar_aeropuerto(const std::string &nombre,Resultado &res);

    void obtener_aeropuertos(const std::string &fichero,const std::string &pais,Resultado &res);

    void guardar_aeropuertos(const std::string &fichero,Resultado &res);

    //bool operator==(const Aeropuertos &otro_objeto)const{
        //return true;
    //}


private:
    static const unsigned MAX_AEROPUERTOS=1000;

    Aeropuerto aeropuertos[MAX_AEROPUERTOS];
    unsigned n_aeropuertos;

    void escribir_resultado(const Resultado &res) const;

    unsigned buscar_aeropuerto(const std::string &nombre) const;

};

}



#endif // AEROPUERTOS_HPP_INCLUDED
