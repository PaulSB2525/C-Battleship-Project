#include "class.h"
using namespace std;





int main(){

    string nombre;
   


    cout<<"Ingrese el nombre del primer jugador: "<<endl;
    cin>>nombre;
    Jugador jugador1(nombre); //Creamos los dos jugadores
    system("cls");
    cout<<"Ingrese el nombre del segundo jugador: "<<endl;
    cin>>nombre;
    Jugador jugador2(nombre);
    system("cls");
    

    cout<<"Es el turno del jugador 1 para colocar sus naves\n"<<endl;
    jugador1.colocarNave();
    system("cls");
    cout<<"\nEs el turno del jugador 2 para colocar sus naves\n"<<endl;
    jugador2.colocarNave();
    system("cls");
    

    Juego juego(jugador1, jugador2);
    juego.iniciarJuego();


    return 0;
}
