#include "Agencia.hpp"
#include <fstream>

namespace umalcc{
        AgViajes::~AgViajes(){
            clear();
            }
           AgViajes::AgViajes();
           AgViajes::AgViajes(const AgViajes& o);
           AgViajes& AgViajes::operator=(const AgViajes& o);
           void AgViajes::identificacion() const{
            cout<<"Yunes Abdelkader Ismael";
           }
           void AgViajes::clear(){
                while(clientes!=NULL){
                    TNodoClientePtr aux=clientes;//aux donde apunta clientes
                    clientes=clientes->sig;
                    delete aux;
                }
                   while(paquetes!=NULL){
                    TNodoClientePtr aux=paquetes;//aux donde apunta clientes
                    paquetes=paquetes->sig;
                    delete aux;
                }
           }
           void AgViajes::leer_paquetes(const std::string & fich_paquetes,bool& ok){
                clear();
                ifstream ifs;
                ifs.open(fich_paquetes.c_str());
                if(ifs.fail){
                    ok=false;
                }
                else{
                    //codigo plaza precios
                    string codigo;
                    int plazas,precio;
                    while(ifs>>codigo){
                        ifs>>plazas;
                        ifs>>precio;


                    Paquete p(codigo,plazas,precio);
                    TNodoPaquetePtr nuevo=new TNodoPaquete;
                    nuevo->paquete=p;
                    nuevo->sig=null;
                    if(paquetes==NULL || paquetes->paquete.codigo>p.codigo){
                        nuevo->sig=paquetes;
                        paquetes=nuevo;
                    }
                    else{
                        TNodoPaquetePtr aux=paquetes;
                        while(aux->sig!=NULL && aux->sig->paquete.codigo<p.codigo){
                            aux=aux->sig;
                        }
                    }
                    nuevo->sig=aux->sig;
                    aux->sig=nuevo;

                }
           }
                ok=true;
                ifs.close();


           }
           void AgViajes::leer_clientes(const std::string & fich_clientes,bool & ok){

                ifstream ifs;
                ifs.open(fich_clientes.c_str());
                if(ifs.fail()){
                    ok=false;
                }
                else{
                           TNodoClientePtr ultimo=NULL;
                        string nombre;
                        int dinero,reservas;
                        while(ifs>>nombre){//si es capaz de leer el nombre ya se supone que si se puedeleer lo siguiente,es decir q sesa linea si se puede leer
                              ifs>>dinero;//el ifs ya introduce el espacio,es como el cin
                            ifs>>reservas;

                            Cliente c(nombre,dinero);
                            TNodoClientePtr nuevo=new TNodoCliente;
                            nuevo->cliente=c;

                            for(int i=0;i<MAX_RESERVAS;i++){
                                    if(i<reservas){
                                string paquetesAbuscar;
                                ifs>>paquetesAbuscar;
                                TNodoClientePtr aux=paquetes;
                                while(aux!=NULL && aux->paquete.codigo!=paquetesAbuscar){
                                    aux=aux->sig;

                                }

                                nuevo->paquetes[i]=aux;
                                    }
                                    else{
                                        nuevo->paquetes[i]=NULL;
                                    }
                            }
                if(dinero>=0){//insercion por el final
                             if(ultimo==NULL){
                                clientes=nuevo;
                                ultimo=nuevo;
                            }
                            else{
                        ultimo->sig=nuevo;
                        ultimo=nuevo;
                    }
                        }
                        }
                        ifs.close();
                        ok=true;

                }
           }
           void AgViajes::listar() const{
                cout<<"-----------PAQUETES------------------";
                TNodoPaquetePtr aux=paquetes;
                while(aux!=NULL){
                      cout<<aux->paquetes.mostrar()<<endl;
                    aux=aux->sig;
                }
                cout<<"----------CLIENTES--------------------------";
                    TNodoClientePtr auxCleinte=clientes;
                    while(auxCleinte!=NULL){
                        cout<<auxCleinte->clientes.mostrar();
                        int i=0;
                        while(auxCleinte->paquetes[i]=NULL){
                            cout<<" "<<auxCleinte->paquetes[i]->paquete.obtener_codigo();
                            i++;
                        }
                        auxCleinte=auxCleinte->sig;
                    }

           }
           void AgViajes::eliminar_reservas_dinero(){
                TNodoClientePtr aux=clientes;
                while(aux!=NULL){
                    int dinero=aux->cliente.obtener_dinero();
                    int i=0;
                    while(dinero>0 && aux->paquetes[i]!=NULL){
                        dinero+=aux->paquetes[i]->paquete.obtener_precio();
                        i++;
                    }

                    if(dinero<0){
                        while(aux->paquetes[i]!=NULL){
                            aux->pauqetes[i]->paquete.modificar_plazas(aux->paquetes[i]->paquete.obtener_plazas()+1,ok);
                            aux->paquetes[i]=NULL;
                            i++;
                        }
                    }


                    aux=aux->sig;
                }

           }
           void AgViajes::eliminar_clientes(int posico )

}
