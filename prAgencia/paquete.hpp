#ifndef PAQUETE_HPP_INCLUDED
#define PAQUETE_HPP_INCLUDED
namespace umalcc{
    class Paquete{
    private:
        std::string codigo;
        int plazas;
        int precio;
    public:

        ~Paquete();
        Paquete();
        Paquete(const std::string&c;int p1,int pr);
        Paquete(const Paquete&o);
        Paquete& operator=(const Paquete&o);
        bool error() const;
        std::string obtener_codigo() const;
        int obtener_plazas() const;
        int obtener_precio() const;
        void modificar_plazas(int p,bool& ok);
        void modificar_precio(int p,bool & ok);
        void mostrar() const;
    };
}


#endif // PAQUETE_HPP_INCLUDED
