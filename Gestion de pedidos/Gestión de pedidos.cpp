#include <iostream>

using namespace std;

const int MAX_PEDIDOS = 500;
const int MAX_INGREDIENTES_PIZZA=10;
const int MAX_INGREDIENTES = 10;
const string INGREDIENTES[MAX_INGREDIENTES] =
    {
        "tomate", "queso", "mozarella", "mortadela",
        "atun", "aceitunas","gambas","mejillon","jamon","oregano"};

typedef int TIngredientesPizza[MAX_INGREDIENTES_PIZZA];

typedef struct{
    unsigned telefono,numpedido,numingredientes;
    string nombre;
    TIngredientesPizza ingredientes;
}TPedido;

typedef TPedido TArrayItems[MAX_PEDIDOS];
typedef struct{
    TArrayItems pedido;
    unsigned tam;
}TPedidos;



char menu();
void leerpedido(TPedido & pedido);
bool eliminarPedido(TPedidos &p,int codigo);
void visualizarDatos(const TPedidos &p );
bool insertarPedido(TPedidos &p, const TPedido & pedido);
void inicializarPedidos(TPedidos &p);
bool buscarpedido(const TPedidos &p, const string &nombre, TPedido & pedido );
double frecuenciaUnIngrediente(const TPedidos & p,int indiceIngrediente);
int buscarCodigoIngrediente(const string &ingred);
void escribirPedido(const TPedido & p);

void escribirPedidos(const TPedidos & p);

void frecuenciaIngredientes(const TPedidos & p);
int buscarPedido(TPedidos &p,int codigo);

//void codigoaingredientes(int codigo,string & ingred);


int main(){
    cout <<"Elaborado por: YUNES ABDELKADER ISMAEL" << endl;

    char opcion = menu();
    TPedidos p;
    inicializarPedidos(p);
    TPedido ped;
    int codigo;
    string nombre;


    while (opcion != 'x' && opcion != 'X'){
        int maxPedido = -1;
        switch (opcion){
            case 'a':
            case 'A':
                leerpedido(ped);
                for (int i = 0; i < p.tam; i++){
                    if (p.pedido[i].numpedido>maxPedido) maxPedido= p.pedido[i].numpedido;
                }
                ped.numpedido = maxPedido+1;
                if (insertarPedido(p, ped)) cout << "Pedido insertado";
                else cout << "error insertando pedido";
                break;
            case 'b':
            case 'B':
                cout<<"Introduzca codigo pedido:";

                cin>>codigo;
                if (eliminarPedido(p,codigo)) cout << "Pedido eliminado" << endl;
                else cout << "Error eliminando el pedido" << endl;
                break;
            case 'c':
            case 'C':
                visualizarDatos(p);
                break;
            case 'd':
            case 'D':
                cout<<"Introduzca nombre cliente:";
                cin>>nombre;
                buscarpedido(p,nombre,ped);
                escribirPedido(ped);
                break;
            case 'e':
            case 'E':
                frecuenciaIngredientes(p);
                break;
        }

        cout << "----------------------------" << endl;

        opcion = menu();
    }
    cout << "Gracias por su Sobresaliente";
}

char menu(){
    cout << "PIZERRIA" << endl;
    cout << "=========================================" << endl;
    cout << "A. Leer e insertar pedido" << endl;
    cout << "B. Eliminar pedido" << endl;
    cout << "C. Visualizar pedidos." << endl;
    cout << "D. Visualizar pedido de una persona." << endl;
    cout << "E. Frecuencia de aparicion de los ingredientes." << endl;
    cout << "X. Salir del Programa." << endl;
    cout << "Introduzca Opción:" << endl;
    char c;
    cin >> c;
    return c;
}



void leerpedido(TPedido & pedido){
    cout << "Nombre :"; cin >> pedido.nombre;
    cout << "Numero telefono:"; cin >> pedido.telefono;
    cout<<"Numero de ingredientes:";cin>>pedido.numingredientes;
    string ingred;

    int i=0;
    while (i< pedido.numingredientes  ){
        cout << "Introduzca ingrediente:";

        cin >> ingred;
        int cod = buscarCodigoIngrediente(ingred);
        while (cod == -1){
            cout << "No existe el ingrediente... Pruebe otra vez" << endl;
            cin >> ingred;
            cod = buscarCodigoIngrediente(ingred);
        }
        pedido.ingredientes[i] = cod;
        cout << "Ingrediente introducido"<<endl;

        i++;
    }
}

int buscarPedido(TPedidos &p,int codigo){
    int i = p.tam-1;
    while (i<=0 && p.pedido[i].numpedido != codigo) i--;
    return i;
}

bool eliminarPedido(TPedidos &p,int codigo){
    int i = buscarPedido(p,codigo);
    if (i==-1) return false;
    else{
        for (int j = i; j < p.tam-1; j++)
        {
            p.pedido[j]=p.pedido[j+1];
        }
        p.tam--;
        return true;
    }
}

void visualizarDatos(const TPedidos &p ){
    escribirPedidos(p);
    cout << endl;
    for (int i= 0; i < MAX_INGREDIENTES; i++){
        if (i>0) cout << ", ";
        cout << INGREDIENTES[i];
    }
}

bool insertarPedido(TPedidos &p, const TPedido & pedido){
    if (p.tam<MAX_PEDIDOS){
        p.pedido[p.tam]= pedido;
        p.tam++;
        return true;
    }else{
        return false;
    }
}

void inicializarPedidos(TPedidos &p){
    p.tam=0;
}

bool buscarpedido(const TPedidos &p, const string &nombre, TPedido & pedido ){
    int  i = 0;
    while (i<p.tam && p.pedido[i].nombre != nombre) i++;
    if (i < p.tam){
            pedido = p.pedido[i];
            return true;
    }
    return false;
}


int buscarCodigoIngrediente(const string &ingred){
    int i = MAX_INGREDIENTES-1;
    while (i>=0 && INGREDIENTES[i] != ingred) i--;
    return i;
}


void escribirPedido(const TPedido & p){
    cout << "SU PEDIDO CONTIENE" << endl;
    cout << "====================" << endl;

    cout << "Nombre\t: " << p.nombre << endl;
    cout << "Numero telefono\t: " << p.telefono << endl;
    cout << "Numero de pedidos\t: " << p.numpedido << endl;
    cout << "Numero de ingredientes\t: " << p.numingredientes << endl;
    cout << "Ingredientes\t: ";
    for(int i=0;i<p.numingredientes ;i++){
        cout<< INGREDIENTES[p.ingredientes[i]] <<" ";
    }
    cout << endl;
}
void escribirPedidos(const TPedidos & p){
    for (int i = 0; i < p.tam;i++){
        escribirPedido(p.pedido[i]);
    }
}
double frecuenciaUnIngrediente(const TPedidos & p,int indiceIngrediente){
    double apariciones = 0;
    double ingredientesTotales = 0;
    for (int i = 0; i < p.tam; i++){
        ingredientesTotales += p.pedido[i].numingredientes;
        for (int j = 0; j< p.pedido[i].numingredientes; j++){
            if (p.pedido[i].ingredientes[j] == indiceIngrediente) apariciones++;
        }
    }
    return apariciones ;
}

void frecuenciaIngredientes(const TPedidos & p){
    for (int i = 0; i < MAX_INGREDIENTES; i++){
        cout << INGREDIENTES[i] <<":" << frecuenciaUnIngrediente(p,i)<<" ";
    }
}

