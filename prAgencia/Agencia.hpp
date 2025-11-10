#ifndef AGENCIA_HPP_INCLUDED
#define AGENCIA_HPP_INCLUDED
#include "cliente.hpp"
#include "paquete.hpp"

namespace umalcc{
    class AgViajes{
    private:
        const static int MAX_RESERVAS=5;//CON ESTATICA SI SE CAMBIA CAMBIA EN TODA LA CLASES AGENICA,EN CAMBIO SI LO CAMBIO SIN ESTATICA CAMBIO EN UN LADO Y NO CAMBIO EN LA OTRA CLASE
         typedef struct{
           TNodoPaquete *sig;
           Paquete paquete;
        }TNodoPaquete;
        typedef TNodoPaquete *TNodoPaquetePtr;//es un puntero que apunta a tipo nodo paquete
        typedef TNodoPaquetePtr ArrayPtrPaquetes[MAX_RESERVAS];
       typedef struct{
            Cliente cliente;
           ArrayPtrPaquetes paquetes;;
            TNodoCliente *sig;
        }TNodoCliente;

       typedef TNodoCliente* TNodoClientePtr;
       TNodoClientePtr clientes;
       TNodoPaquetePtr paquetes;

       public:
           ~AgViajes();
           AgViajes();
           AgViajes(const AgViajes& o);
           AgViajes& operator=(const AgViajes& o);
           void identificacion() const;
           void clear();
           void leer_paquetes(const std::string & fich_paquetes,bool& ok);
           void leer_clientes(const std::string & fich_clientes,bool & ok);
           void listar() const;
           void eliminar_reservas_dinero();
           void eliminar_clientes(int )


    };
}


#endif // AGENCIA_HPP_INCLUDED
