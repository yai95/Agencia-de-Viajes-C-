/******************************************************************************
 * test_aeropuertos.cpp
 *
 * Programa principal de prueba del módulo aeropuertos
 *
 * Alumno: Yunes Abdelkader Ismael
 * Fecha: 27/06/2018
 *****************************************************************************/
#include "rutas.hpp"
#include "aeropuertos.hpp"
#include <iostream>

using namespace std;
using namespace bblProgII;

//1. Pide por teclado un aeropuerto de <origen>.
//2. Pide por teclado un aeropuerto de <destino>.
//3. Obtiene e imprime por pantalla el itinerario entre los aeropuertos de <origen> y <destino> introducidos.
//4. Genera y escribe en el fichero <origen>_<destino>.txt los billetes correspondientes al itinerario encontrado.
// Ejemplo de ejecución del programa:
//      Introduzca código del aeropuerto de origen: FUE
//    Introduzca código del aeropuerto de destino: REU
//Buscando vuelo de FUE a REU...
//Itinerario encontrado...
//--
//FUE, MAD, 254, 188, Iberia Airlines
// MAD, PMI, 133, 71, Air Europa
// PMI, REU, 85, 46, Ryanair
// --
// Número de escalas del itinerario: 2
// --
//Generando billetes en fichero FUE_REU.txt...
//Introduzca código del aeropuerto de origen:



int main(){
    cout << "Comenzando..." << endl;
    Rutas rutas;
    Aeropuertos aeropuertos;
    Resultado res;
    cout<<"Cargando el fichero localizacion.txt..."<<endl;
    aeropuertos.obtener_aeropuertos("localizacion.txt","SPAIN",res);
    cout << "Cargando el fichero precios.txt..." << endl;
    rutas.obtener_rutas("precios.txt",aeropuertos,res);
    if (res==OK){
        cout << "fichero cargado..." << endl;
        cout << rutas.num_rutas() << " cargadas" <<endl;

        string origen,destino;

        while (true){

            Rutas filtro;
            cout << "Introduzca codigo del aeropuerto de origen: ";
            cin >> origen;
            cout << "Introduzca código del aeropuerto de destino: ";
            cin >> destino;

            cout << "Buscando vuelo de "<< origen <<" a "<< destino <<"..." << endl;



            rutas.obtener_itinerario(origen,destino,filtro,res);



            if (res == OK) {

                cout << "...Encontrado";
                //Ruta r;
                //filtro.consultar_ruta(0,r,res);

                //filtro.escribir_rutas();

                cout << "--" <<endl;
                filtro.escribir_rutas();
                cout << "--" <<endl;
                cout << "Número de escalas del itinerario:" << filtro.num_rutas()<<endl;
                cout << "--" << endl;

                string file = origen + "_" + destino + ".txt";
                cout << "Generando billetes en fichero " << file <<endl;

                filtro.guardar_billetes(file,res);

            }else{
                cout << "NO HAY NADA!" << endl;
            }
        }
    }else{
        cout << "ERROR FICHERO CARGADO" << endl;
    }



}

