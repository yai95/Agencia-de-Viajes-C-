#ifndef RUTA_HPP_INCLUDED
#define RUTA_HPP_INCLUDED

#include <iostream>


namespace bblProgII{
    class Ruta{
    private:
        std::string origen,destino,linea_aerea;
        double precio;
        unsigned duracion;

    public:
        Ruta();
        Ruta(const Ruta &otra_ruta);
        Ruta(const std::string &origen_ini, const std::string &destino_ini, double precio_ini, unsigned duracion_ini, const std::string &linea_aerea_ini);

        void asignar_origen(const std::string &nuevo_origen);
        void asignar_destino(const std::string &nuevo_destino);
        void asignar_precio(double nuevo_precio);
        void asignar_duracion(unsigned nueva_duracion);
        void asignar_linea_aerea(const std::string &nueva_linea);
        std::string consultar_origen() const;
        std::string consultar_destino() const;
        double consultar_precio() const;
        unsigned consultar_duracion() const;
        std::string consultar_linea_aerea() const;
        void escribir_ruta() const;
        bool operator==(const Ruta &otra_ruta) const;

    };

}

#endif // RUTA_HPP_INCLUDED
