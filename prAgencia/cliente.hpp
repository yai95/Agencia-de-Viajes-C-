#ifndef CLIENTE_HPP_INCLUDED
#define CLIENTE_HPP_INCLUDED
namespace umalcc{
    class Cliente{
        private:
            std::string nombre;
            int dinero;
        public:
            ~Cliente();
            Cliente();
            Cliente(const std::string &n;int d);
            Cliente(const Cliente& o);
            Cliente& operator=(const Cliente&o);
            bool error() const;
            std::string obtener_nombre() const;
            int obtener_dinero() const;
            void modificar_dinero(int d,bool& ok);
            void mostrar() const;


    };
}


#endif // CLIENTE_HPP_INCLUDED
