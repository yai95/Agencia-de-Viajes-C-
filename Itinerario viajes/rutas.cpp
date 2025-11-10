#include "rutas.hpp"
#include "aeropuertos.hpp"
#include <iostream>
#include <fstream>

using namespace std;

namespace bblProgII{
    // Constructor por defecto.
	// Inicializa la lista de Rutas a lista vacía
	Rutas::Rutas(){
	     lista=NULL;
	}

	// Constructor de copia de Rutas.
	// Parámetros:
	//	- otro_objeto (E): objeto Rutas a copiar
	Rutas::Rutas(const Rutas &otro_objeto){

        lista=NULL;
            if (otro_objeto.lista != NULL){
            Lista otro = otro_objeto.lista;
            Lista aux = lista;
            while (otro!= NULL){
                if (lista == NULL){
                    lista = new TNodo;
                    aux = lista;
                }else{
                    aux->sig = new TNodo;
                    aux = aux->sig;
                }
                aux->ruta = otro->ruta;
                otro = otro->sig;
            }
            aux->sig = NULL;
        }
	}




	// Destructor de la clase
	Rutas::~Rutas(){
	    borrar_rutas();;
	}

	// Devuelve el número de rutas
	unsigned Rutas::num_rutas() const{
	    unsigned contador;
	    if (lista == NULL) contador=0;

	    else{
            Lista aux = lista;
            contador = 0;

            while (aux != NULL){
                contador++;
                aux = aux->sig;
            }
                return contador;
	    }

	}

	// Escribe por pantalla las Rutas actuales.
	// Formato de salida por pantalla:
	// <origen>, <destino>, <precio>, <duracion>, <linea_aerea>
	// Por ejemplo:
	// AER, KZN, 344, 151, Aerocondor
	// ASF, KZN, 232, 112, Aerocondor
	// ASF, MRV, 106, 84, Aerocondor
	// ...

	void Rutas::escribir_rutas() const{
        Lista aux = lista;

        while (aux != NULL){
            aux->ruta.escribir_ruta();
            cout << endl;
            aux = aux->sig;
        }
	}

	// Consulta la ruta de la posición 'num' de
	// la lista de Rutas. Si num < num_rutas(),
	// devuelve la ruta correspondiente
	// y 'OK' a través de 'res'. Si no, devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	// 	- num (E): posición de la ruta a consultar
	//	- ruta (S): ruta de la posición 'num'
	//  - res (S): resultado de la operación
	void Rutas::consultar_ruta(unsigned num,
	                    Ruta &ruta,
	                    Resultado &res) const{
        Lista aux = lista;
        unsigned pos = 0;
        while (aux != NULL && num>pos){
             pos++;
            aux= aux -> sig;

        }

        if (aux != NULL && pos == num){
            ruta = aux->ruta;
            res = OK;
        }else{
            res = NO_EXISTE;
        }

    }

	// Consulta las rutas con un determinado 'origen'
	// y 'destino'. Si existe/n alguna/s ruta/s con ese
	// 'origen' y 'destino' se devuelve/n a través de
	// 'rutas' y se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	// 	- origen (E): aeropuerto de origen de la ruta
	// 	- destino (E): aeropuerto de destino de la ruta
	// 	- rutas (S): lista de rutas con esos aeropuertos de
	//				 origen y destino
	// 	- res (S): resultado de la operación
	void Rutas::consultar_rutas(const std::string &origen,
	                     const std::string &destino,
	                     Rutas &rutas,
	                     Resultado &res) const{
        res=NO_EXISTE;
        Lista aux = lista;
        rutas.borrar_rutas();


        while (aux!= NULL){
            if (aux->ruta.consultar_origen() == origen && aux->ruta.consultar_destino()== destino){
                Resultado resIn;
               // Ruta rut(aux->ruta);
                rutas.insertar_ruta(aux->ruta,resIn);
                res=OK;
            }

            aux = aux->sig;
        }
    }

	// Devuelve un objeto Rutas con la lista de rutas
	// cuyo aeropuerto de origen coincide con el que
	// se pasa como parámetro. Si existe al menos una
	// ruta con ese aeropuerto de origen, se devuelve
	// 'OK' a través de 'res'. Si no, se devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- origen (E): aeropuerto de origen de la ruta
	// 	- rutas (S): lista de rutas con ese aeropuerto
	//				de origen.
	//	- res (S): resultado de la operación.
	void Rutas::consultar_rutas_origen(const std::string &origen,
	                            Rutas &rutas,
	                            Resultado &res) const{
        res=NO_EXISTE;
	    Lista aux = lista;
        rutas.borrar_rutas();


        while (aux!= NULL){
            if (aux->ruta.consultar_origen() == origen){
                Resultado resIn;
                //Ruta rut(aux->ruta);
                rutas.insertar_ruta(aux->ruta,resIn);
                res=OK;
            }

            aux = aux->sig;
        }
    }


	// Devuelve un objeto Rutas con la lista de rutas
	// cuyo aeropuerto de destino coincide con el que
	// se pasa como parámetro. Si existe al menos una
	// ruta con ese aeropuerto de destino, se devuelve
	// 'OK' a través de 'res'. Si no, se devuelve
	// 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- destino (E): aeropuerto de destino de la ruta
	// 	- rutas (S): lista de rutas con ese aeropuerto
	//				de origen.
	//	- res (S): resultado de la operación.
	void Rutas::consultar_rutas_destino(const std::string &destino,
	                             Rutas &rutas,
	                             Resultado &res) const{
        res=NO_EXISTE;
        Lista aux = lista;
        rutas.borrar_rutas();

        while (aux!= NULL){
            if (aux->ruta.consultar_destino()== destino){
                Resultado resIn;
               // Ruta rut(aux->ruta);
                rutas.insertar_ruta(aux->ruta,resIn);
                res = OK;
            }

            aux = aux->sig;
        }
    }


	// Consulta la lista de rutas que contienen,
	// ya sea como aeropuerto de origen o como aeropuerto de destino,
	// alguno de los 'aeropuertos' que se pasan como parámetro.
	// Si existe al menos una ruta con alguno de esos aeropuertos, se
	// devuelve 'OK' a través de 'res'. Si no, se devuelve 'NO_EXISTE'.
	// Parámetros:
	//	- aeropuertos (E): objeto Aeropuertos con la lista de aeropuertos
	//				cuyas rutas se quieren obtener.
	//	- rutas (S): lista de rutas que contienen esos aeropuertos
	//	- res (S): resultado de la operación
	// PRECONDICIÓN: aeropuertos.num_aeropuertos() > 0
	 //Pregunto origen esta en aeropuertos.Sii pues se inserta
    //Pregunto destino esta en aeropuertos.Sii pues se inserta
	void Rutas::consultar_rutas_aeropuertos(const Aeropuertos &aeropuertos,
	                                 Rutas &rutas,
	                                 Resultado &res) const{
        res=NO_EXISTE;
        rutas.borrar_rutas();
        Lista aux = lista;



        while (aux!= NULL){
            Resultado resDest;
            Resultado resOrig;
            Aeropuerto aero;
            aeropuertos.consultar_aeropuerto(aux->ruta.consultar_destino(),aero,resDest);
            aeropuertos.consultar_aeropuerto(aux->ruta.consultar_origen(),aero,resOrig);

            if (resOrig == OK || resDest == OK){
                res = OK;
                Resultado resIn;
               // Ruta rut(aux->ruta);
                rutas.insertar_ruta(aux->ruta,resIn);//resIn devuelve si se ha podido insertar
            }

            aux = aux->sig;
        }


    }

	// Devuelve la ruta más barata (menor precio) de la lista de Rutas.
	// Si la lista está vacía, devuelve 'NO_EXISTE' a través
	// de 'RES'. Si no, devuelve OK.
	// Parámetros:
	//	- ruta (S): ruta más barata de la lista
	// 	- res (S: resultado de la operación

	void Rutas::consultar_mas_barata(Ruta &ruta, Resultado &res) const{
        if (lista == NULL) res = NO_EXISTE;
        else{
            Lista Masbarata = lista;
            Lista aux = Masbarata->sig;

            while(aux != NULL ){
                if (Masbarata->ruta.consultar_precio()> aux->ruta.consultar_precio()){
                    Masbarata = aux;
                }

                aux = aux->sig;
            }
            ruta = Masbarata->ruta;
            res = OK;
        }

    }

	// Insertar nueva ruta al final de la lista de Rutas.
	// Si la ruta no existe (es decir, no hay una ruta
	// en la lista con los mismos atributos que ésta),
	// se inserta al final de la lista y se devuelve 'OK'
	// a través de 'res'. Si la ruta existe (hay una ruta
	// con los mismos  atributos), se
	// devuelve 'YA_EXISTE' a través de 'res'.
	// Parámetros:
	//	- ruta (E): ruta a insertar en la lista de Rutas.
	//	- res (S): resultado de la operación
	void Rutas::insertar_ruta(const Ruta &ruta, Resultado &res){
       Lista nuevo = new TNodo;
        nuevo->ruta = ruta;
        nuevo->sig = NULL;
        res=YA_EXISTE;

        if (lista == NULL){
                lista = nuevo;
                res=OK;
        }
        else{
            Lista anterior=NULL;
            Lista aux = lista;
            while (aux!=NULL && !(aux->ruta==ruta)){
                anterior=aux;
                aux = aux->sig;
            }
            if(aux==NULL){
                anterior->sig=nuevo;
                res=OK;
            }

        }


	}

	// Elimina la ruta que se pasa como parámetro de la
	// lista de Rutas.
	// Si la ruta existe, se elimina de la lista de Rutas
	// y se devuelve 'OK' a través de 'res'. Si no, se
	// devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- ruta (E): ruta a eliminar
	//	- res (S): resultado de la operación
	void Rutas::eliminar_ruta(const Ruta &ruta,
	                   Resultado &res){
        res=NO_EXISTE;
        if (lista == NULL) res =NO_EXISTE;
        else{
            if (lista->ruta == ruta){
                Lista aux = lista;
                lista = lista->sig;
                delete aux;
                res = OK;
        }else{
            Lista aux = lista;
            while (aux->sig != NULL){
                    if(aux->sig->ruta==ruta){
                        Lista punt=aux->sig;
                        aux->sig=punt->sig;
                        delete punt;
                        res=OK;
                    }
                    else{
                        aux = aux->sig;
                    }
            }

        }
    }
    }

	// Elimina todas las rutas de la lista de Rutas que
	// contengan ese aeropuerto como aeropuerto de origen
	// o destino de la ruta. Si se ha eliminado al menos
	// una ruta con ese aeropuerto, se devuelve 'OK' a
	// través de 'res'. Si no, se devuelve 'NO_EXISTE'.
	// Parámetros:
	//	- aeropuerto (E): aeropuerto cuyas rutas se eliminan
	//	- res (S): resultado de la operación
	void Rutas::eliminar_rutas_aeropuerto(const std::string aeropuerto,
	                               Resultado &res){
        res = NO_EXISTE;
        if (lista != NULL){
            while (lista->ruta.consultar_origen() == aeropuerto ||
                   lista->ruta.consultar_destino() == aeropuerto ){
                Lista aux = lista;
                lista = lista->sig;
                delete aux;
                res = OK;
            }

            if (lista != NULL){
                Lista aux = lista;
                while (aux->sig != NULL ){
                    if (aux->sig->ruta.consultar_origen() == aeropuerto
                        || aux->sig->ruta.consultar_destino() == aeropuerto){
                        Lista punt = aux->sig;
                        aux->sig = punt->sig;
                        delete punt;
                        res = OK;
                    }else{
                        aux = aux->sig;
                    }
                }
            }
        }
    }

	// Elimina todas las rutas que contienen como 'origen'
	// el aeropuerto cuyo nombre se pasa como parámetro.
	// Si se ha eliminado al menos una ruta con ese aeropuerto
	// de origen, se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- origen (E): aeropuerto de origen de las rutas a
	//			eliminar.
	//	- res (S): resultado de la operación.


void Rutas::eliminar_rutas_origen(const std::string &origen,
                                  Resultado &res) {
    res = NO_EXISTE;
    Lista aux=lista;

    while (aux!= NULL) {
        if (aux->ruta.consultar_origen() == origen) {

            Resultado resIn;
            eliminar_ruta(aux->ruta, resIn);
            res = OK;

        }

        aux =aux->sig;
    }
}

    //____________________________________________
	// Elimina todas las rutas que contienen como 'destino'
	// el aeropuerto cuyo nombre se pasa como parámetro.
	// Si se ha eliminado al menos una ruta con ese aeropuerto
	// de destino, se devuelve 'OK' a través de 'res'. Si no,
	// se devuelve 'NO_EXISTE' a través de 'res'.
	// Parámetros:
	//	- destino (E): aeropuerto de destino de las rutas a
	//			eliminar.
	//	- res (S): resultado de la operación.

    void Rutas::eliminar_rutas_destino(const std::string &destino,
                                  Resultado &res) {
     res = NO_EXISTE;
    Lista aux=lista;

    while (aux!= NULL) {
        if (aux->ruta.consultar_destino() == destino) {

            Resultado resIn;
            eliminar_ruta(aux->ruta, resIn);
            res = OK;

        }

        aux =aux->sig;
    }
}
    //----------------------------------


	// Lee de 'fichero' la lista de rutas correspondientes
	// a los 'aeropuertos' que se pasan como parámetro y
	// las inserta al final de la lista de rutas actual.
	// Si la lista de 'aeropuertos' es vacía, lee todas
	// las rutas del fichero y las inserta en la lista
	// de Rutas actual. Si el fichero ha podido abrirse
	// correctamente para lectura, devuelve 'OK' a través
	// de 'res'. Si no, devuelve 'FIC_ERROR'.
	//
	// El formato de fichero de entrada es el siguiente:
	// <origen>,<destino>,<precio>,<duracion>,<linea_aerea>
	// Por ejemplo:
	// AER,KZN,344,151,Aerocondor
	// ASF,KZN,232,112,Aerocondor
	// ASF,MRV,106,84,Aerocondor
	// ...
	// (obsérvese que no hay espacios tras los campos)
	//
	// Parámetros:
	//	- fichero (E): nombre del fichero de lectura.
	// 	- aeropuertos (E): objeto de tipo Aeropuertos con la
	//			lista de aeropuertos para los que obtener rutas.
	//	- res (S): resultado de la operación.
	//Lee el fichero e inserta la ruta que tenga tal origen y/o aeropuerto de la lista aeropuertos
	void Rutas::obtener_rutas(const std::string &fichero,
	                   const Aeropuertos &aeropuertos,
	                   Resultado &res){
        ifstream ifs;
        Rutas obtener;
        ifs.open(fichero.c_str());
        if (ifs.fail()) res = FIC_ERROR;
        else{
            string orig, dest, aero;
            double precio;
            unsigned duracion;

            getline(ifs,orig,',');
            while (!ifs.eof()){
                getline(ifs,dest,',');
                ifs >> precio;
                ifs.ignore();
                ifs >> duracion;
                ifs.ignore();
                getline(ifs,aero);

                Resultado res;
                Aeropuerto ae;

                Ruta rut(orig,dest,precio,duracion,aero);
                if (aeropuertos.num_aeropuertos() == 0) obtener.insertar_ruta(rut,res);
                else{
                    aeropuertos.consultar_aeropuerto(orig,ae,res);
                    if (res == OK){
                        aeropuertos.consultar_aeropuerto(dest, ae, res);
                    }

                    if (res == OK){
                        obtener.insertar_ruta(rut,res);
                    }
                }
                getline(ifs,orig,',');
            }
            ifs.close();
            copiar_rutas(obtener);
            res = OK;
        }
    }

	// Guarda en fichero todas las Rutas. El formato
	// de salida coincide con el de entrada (véase
	// la función miembro obtener_rutas). Si el fichero
	// puede abrirse correctamente para escritura,
	// se guardan en él las rutas y se devuelve 'OK' a
	// través de 'res'. Si no, se devuelve 'FIC_ERROR'.
	// Parámetros:
	//	- fichero (E): nombre del fichero de salida
	// 	- res (S): resultado de la operación.
	//La lista rutas obtenida almacenada a traves de obtener ,aqui mostramos por mantalla cada ruta.Cada linea fichero es una ruta
	void Rutas::guardar_rutas(const std::string &fichero,
	                   Resultado &res) const{
        ofstream ofs;
        ofs.open(fichero.c_str());
        if (ofs.fail()) res = FIC_ERROR;
        else{
            Lista aux = lista;
            while (aux != NULL){
                ofs << aux->ruta.consultar_origen()
                    << ","
                    << aux->ruta.consultar_destino()
                    << ","
                    << aux->ruta.consultar_precio()
                    << ","
                    << aux->ruta.consultar_duracion()
                    << ","
                    << aux->ruta.consultar_linea_aerea() << endl;


                aux =aux->sig;
            }
            ofs.close();
            res = OK;
        }
    }

	// Guarda todas las rutas en el `fichero` cuyo nombre
	// se pasa como parámetro de entrada. (El formato
	// de salida está destinado a generar los billetes
	// correspondientes a un itinerario con escalas
	// entre un aeropuerto de origen--el origen de la
	// primera ruta--y otro de destino--el destino de
	// la última ruta.)
	// Finalmente, escribe en el fichero la suma de los
	// costes totales de todas las rutas que se han
	// escrito en él, el número de rutas - 1 (es
	// decir, las escalas que hay que hacer entre
	// el primer aeropuerto y el último) y la duración
	// total de todos los vuelos.
	//
	// Formato de salida:
	// (ojo, incluye los tres guiones antes y después)
	//
	// ---
	// Flight: <origen> to <destino>
	// Carrier: <linea_aerea>
	// Duration: <duracion> minutes
	// Cost: <precio> euros
	// ---
	// .. (se repite tantas veces como rutas haya)
	// ---
	// Total Cost: <precio total> euros
	// ---
	// Number of Stops: <numero rutas - 1>
	// ---
	// Total Flight Duration: <duracion> minutes
	// ---
	//
	// Si no se puede abrir el fichero, se devuelve
	// `FIC_ERROR` a través de `res`. Si no, se
	// devuelve `Ok`.
	// Parámetros:
	//		- fichero (E): nombre del fichero de salida
	//		- res (S): resultado de la operación
	//Muestro los billetes de cada ruta de la lista rutas generada en obtener
	void Rutas::guardar_billetes(const std::string &fichero,
	                      Resultado &res){
            ofstream ofs;
            ofs.open(fichero.c_str());
            if (ofs.fail()) res = FIC_ERROR;
            else{
                Lista aux = lista;
                double precioTotal=0.0;
                unsigned duracionTotal = 0;
                int paradas = 0;
                while (aux!=NULL){
                    ofs << "---" << endl;
                    ofs << "Flight: " << aux->ruta.consultar_origen() << " to " << aux ->ruta.consultar_destino() << endl;
                    ofs << "Carrier: " << aux->ruta.consultar_linea_aerea() << endl;
                    ofs << "Duration: " << aux->ruta.consultar_duracion() << " minutes"<< endl;
                     ofs << "Cost: " << aux->ruta.consultar_precio() << " euros" << endl;
                    precioTotal += aux->ruta.consultar_precio();
                    duracionTotal +=  aux->ruta.consultar_duracion() ;

                    aux = aux->sig;
                    paradas++;
                }

                ofs <<"Total Cost: " <<precioTotal <<" euros" << endl;
                ofs <<"---"<<endl;
                ofs <<"Number of Stops: " <<  paradas << endl;
                ofs <<"---"<<endl;
                ofs <<"Total Flight Duration: " << duracionTotal << " minutes" << endl;
                ofs <<"---"<<endl;
                ofs.close();
                res = OK;
            }
    }

	// (EJERCICIO DE INVESTIGACIÓN)
	//
	// -- OPCIÓN A - FÁCIL (Y MÍNIMA EXIGIDA)
	// Dado un aeropuerto de 'origen ' y un aeropuerto
	// de 'destino', devuelve la ruta más barata de entre
	// las diferentes rutas existentes entre esos dos
	// aeropuertos. Si existe una ruta entre esos dos
	// aeropuertos, se devuelve insertada en 'itinerario'
	// (como única ruta de la lista) y 'OK' a través de
	// 'res'. Si no existe, se devuelve un 'itinerario'
	// vacío y 'NO_EXISTE' a través de 'res'.
	// --------------------------------------------------
	//
	// ---OPCIÓN B - DIFÍCIL (Y MUCHO MEJOR Y OPCIONAL)
	// Obtener itinerario.
	// Dado un aeropuerto de 'origen' y un aeropuerto
	// de 'destino', devuelve la lista de rutas para llegar,
	// haciendo escalas si es necesario, desde el aeropuerto de 'origen'
	// al aeropuerto de 'destino'. Para ello, se deberá emplear
	// el algoritmo de Dijkstra para calcular, si existe,
	// el itinerario DE MENOR PRECIO entre el aeropuerto de 'origen' y el de
	// 'destino', haciendo escalas, si es preciso, en diferentes aeropuertos.
	// (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Algorithm)
	// Si existe el itinerario, ya sea de una sola ruta (sin escalas entre
	// aeropuertos) o de varias rutas (con escalas entre aeropuertos),
	// se devuelve en el parámetro 'rutas' y se devuelve 'OK' a través
	// de 'res'. Si no existe el itinerario, se devuelve 'NO_EXISTE'
	// a través de 'res'.
	//
	// Parámetros:
	//	- origen (E): aeropuerto de origen
	//	- destino (E): aeropuerto de destino
	//	- rutas (S): itinerario (rutas) entre origen y destino
	// 	- res (S): resultado de la operación
	void Rutas::obtener_itinerario(const std::string &origen,
	                        const std::string &destino,
	                        Rutas &itinerario,
	                        Resultado &res) const{

        itinerario.borrar_rutas();
        Lista mejor = NULL;
        Lista aux = lista;
        while (aux != NULL){
            if (aux->ruta.consultar_origen() == origen && aux->ruta.consultar_destino() == destino){
                if (mejor == NULL || mejor->ruta.consultar_precio()> aux->ruta.consultar_precio()){
                    mejor = aux;
                }
            }
            aux = aux->sig;
        }
        if (mejor != NULL){


            res=OK;
            itinerario.insertar_ruta(mejor->ruta,res);

        }else{
            res = NO_EXISTE;
        }
    }
    Lista aux=lista
    while(aux!=NULL && !(aux->ruta==origen) && !()){
        aux=aux->sig;
    }
    Lista mejor=aux;
    Lista otroaux=aux->sig;
    while(otroaux!=NULL){
        if(otroaux->ruta.consultar_precio() > mejor->ruta){
            mejor=otroaux;
        }
        otroaux=otroaux->sig;
    }
    ruta=mejor->ruta;

	// ---------------------------------------------------------------
	// OPERADORES SOBRECARGADOS. IMPLEMENTADOS ON-LINE POR EL PROFESOR




	// Borra todas las rutas de la lista de Rutas
	// Postcondición: lista == nullptr
	void Rutas::borrar_rutas(){
        while (lista != NULL){
            Lista aux = lista;
            lista = lista->sig;
            delete aux;
        }
	}

	// Copia la lista de rutas del objeto que se pasa como parámetro
	// al final de la lista de rutas actual
	void Rutas::copiar_rutas(const Rutas &otro_objeto){

         Lista ultimo=NULL;
         if(lista!=NULL){
            ultimo=lista;
            while(ultimo->sig!=NULL) ultimo=ultimo->sig;

         }
         Lista aux=otro_objeto.lista;
         while(aux!=NULL){
            Lista nuevo=new TNodo;
            nuevo->ruta=aux->ruta;
            nuevo->sig=NULL;
            if(ultimo==NULL)    lista=nuevo;
            else ultimo->sig=nuevo;
            ultimo=nuevo;
            aux=aux->sig;
         }
	}



}

