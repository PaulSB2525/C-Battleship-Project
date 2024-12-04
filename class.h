#include<iostream>
#include <chrono> //tiempo
#include <thread> //tiempo
using namespace std;

void time(int x){

    this_thread::sleep_for(chrono::seconds(x));
}

class Tablero{
private:
    char tablero[11][11];
    int navesColocadas;

public:
        Tablero(){
        for (int i = 1; i < 11; i++){
            for (int j = 1; j < 11; j++){
                tablero[i][j] = '~';
                 //El tablero lo podemos llenar de puros ceros o algo así pero lo llené de tildes para que parezca agua, igual si quieren cambiarlo por algo más es muy fácil.
            }
        }

        tablero[0][0] = ' ';
        

        for(int i = 1;i < 11; i++){
            tablero[i][0] = '0' + (i-1);
            tablero[0][i] = '0' + (i-1);
        }
    }

    void mostrarTablero()const{ //A lo largo del codigo van a ver varios metodos que tienen "const", no los quiten porque sin eso no jalan 
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                cout<<tablero[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    bool colocarBarco(int x, int y, int tamano, char orientacion) {
        // Valida y coloca un barco en el tablero.
        if (orientacion == 'H') {
            if (y + tamano > 10) return false;
            for (int i = 0; i < tamano; i++) {
                if (tablero[x][y + i] != '~') return false;
            }
            for (int i = 0; i < tamano; i++) {
                tablero[x][y + i] = 'N'; // Coloca el barco.
            }
        } else if (orientacion == 'V') {
            if (x + tamano > 10) return false;
            for (int i = 0; i < tamano; i++) {
                if (tablero[x + i][y] != '~') return false;
            }
            for (int i = 0; i < tamano; i++) {
                tablero[x + i][y] = 'N'; // Coloca el barco.
            }
        }
        return true;
    }

    bool registrarAtaque(int x, int y) {
        if(tablero[x][y] == 'N'){
            tablero[x][y] = 'X';
            cout<< "!Impacto en ("<< x <<", "<< y <<")."<<endl;
            return true;
        }
        else if (tablero[x][y] == 'O' || tablero[x][y] == 'X') { 
            cout << "Ya atacaste en esa posicion" << endl; 
            return false; 
        }
        else if(tablero[x][y] == '~'){
            tablero[x][y] = 'O';
            cout<<"Agua! en ("<<x<<", "<<y<<")."<<endl;
            return false;    
        }

        return false;
    }
            
    bool recibirAtaque(int x, int y){
        if (tablero[x][y] == 'N'){ //Esto es para verificar el impacto a una nave
            tablero[x][y] = 'X';
            cout<< "Impacto! en ("<< x <<", "<< y <<")."<<endl;
            return true; 
        }
        

        else if(tablero[x][y] == '~'){ //Aqui se registra un impacto en el agua
            tablero[x][y] = 'O';
            cout<<"Agua! en ("<<x<<", "<<y<<")."<<endl;
            return false;
        }

        return false;

    }

    bool verificarBarcos() const {
        // Revisa si quedan barcos en el tablero.
        for (int i = 1; i < 11; i++) {
            for (int j = 1; j < 11; j++) {
                if (tablero[i][j] == 'N') return true;
            }
        }
        return false;
    }

};

class Naves{
private:
    string tipo;         
    int tamano;
    int celdasRestantes;          

public:
    Naves(string tipoNave, int tam) : tipo(tipoNave), tamano(tam), celdasRestantes(tam){}
    
    void recibirImpacto(){
        if(celdasRestantes > 0){
            celdasRestantes--;
            cout<< "!La "<<tipo<<" fue impactado/a! Celdas restantes: "<<celdasRestantes<<endl;
        

            if(celdasRestantes == 0){
                cout<<"!La "<< tipo << " ha sido destruida!"<< endl;
            }
        }
    }


};

class Jugador{ 
private:
    string nombre;
    Tablero propio;
    Tablero ataques;


public:
    Jugador(string nombre_) : nombre(nombre_){}

    string getNombre()const{
        return nombre;
    }
    void setNombre(string name){
        nombre = name;
    }
    void mostrarTablero()const{
        cout<< "Tablero de naves de "<<nombre<<":"<<endl;
        propio.mostrarTablero();
    }

    void mostrarTableroAtaque() const{
        cout<< "Tablero de ataque de "<<nombre<<":"<<endl;
        ataques.mostrarTablero();
        
    }

    void colocarNave(){
    int x, y, tamano;
    char orientacion;

        // Colocar lanchas (Tamaño 2)
        for (int i = 0; i < 2; ++i) {
            cout << "Colocar Lancha (Tamano 2)\n" << endl;
            cout << "Teclea la coordenada en y: ";
            cin >> x;
            x++;
            cout << "Teclea la coordenada en x: ";
            cin >> y;
            y++;
            cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
            cin >> orientacion;
            

            while (!propio.colocarBarco(x, y, 2, orientacion)) {
                cout << "\nPosicion invalida. Intenta nuevamente.\n" << endl;
                cout << "Teclea la coordenada en y: ";
                cin >> x;
                x++;
                cout << "Teclea la coordenada en x: ";
                cin >> y;
                y++;
                cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
                cin >> orientacion;
                
            }
            propio.mostrarTablero();
        }
        

        // Colocar submarinos (Tamaño 3)
        for (int i = 0; i < 2; ++i) {
            cout << "\nColocar Submarino (Tamano 3)\n" << endl;
            cout << "Teclea la coordenada en y: ";
            cin >> x;
            x++;
            cout << "Teclea la coordenada en x: ";
            cin >> y;
            y++;
            cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
            cin >> orientacion;
            

            while (!propio.colocarBarco(x, y, 3, orientacion)) {
                cout << "\nposicion invalida. Intenta nuevamente.\n" << endl;
                cout << "Teclea la coordenada en y: ";
                cin >> x;
                x++;
                cout << "Teclea la coordenada en x: ";
                cin >> y;
                y++;
                cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
                cin >> orientacion;
                
            }
            propio.mostrarTablero();
        }

        // Colocar acorazado (Tamaño 4)
        cout << "\nColocar Acorazado (Tamano 4)\n" << endl;
        cout << "Teclea la coordenada en y: ";
        cin >> x;
        x++;
        cout << "Teclea la coordenada en x: ";
        cin >> y;
        y++;
        cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
        cin >> orientacion;
        

        while (!propio.colocarBarco(x, y, 4, orientacion)) {
            cout << "\nposicion invalida. Intenta nuevamente.\n" << endl;
            cout << "Teclea la coordenada en y: ";
            cin >> x;
            x++;
            cout << "Teclea la coordenada en x: ";
            cin >> y;
            y++;
            cout << "Orientacion ('H' o 'V') Asegurate que la letra sea mayuscula.: ";
            cin >> orientacion;
            
        }
        propio.mostrarTablero();

    }

    bool navesRestantes() const{
        return propio.verificarBarcos();
    }

    void Atacar(Jugador &oponente, Jugador&actual){
        int x,y;
        cout<<"Ingresa la coordenada en y donde desees atacar: "<<endl;
        cin>> x;
        cout<<"Ahora ingresa la coordenada en x: "<<endl;
        cin>> y;
        x++;
        y++;
        oponente.propio.recibirAtaque(x, y);
        actual.ataques.registrarAtaque(x, y);

    }

    
};



class Referi{

    private:
        Jugador jugador1, jugador2;
        int turnoActual;

    public:

        Referi(Jugador j1, Jugador j2) : jugador1(j1), jugador2(j2), turnoActual(1){}

        void iniciarTurno(){
            turnoActual = (turnoActual == 1) ? 2:1;
            cout << "Es el turno del Jugador " << turnoActual << "." << endl;
        }

        bool verificarGanador() const{
            if (!jugador1.navesRestantes()){
                return true;
            }
            if (!jugador2.navesRestantes()){
                return true;
            }
            return false;  
        }

        Jugador& getJugadorActual(){
            return (turnoActual == 1) ? jugador1 : jugador2;
        }

        Jugador& getJugadorOponente(){
            return (turnoActual == 1) ? jugador2 : jugador1; 
        }    
        
};

class Juego{

    private:
        Referi juan;
    
    public:
        Juego(Jugador j1, Jugador j2) : juan(j1, j2){}

        void iniciarJuego(){
            
            while(!juan.verificarGanador()){
                juan.iniciarTurno();
                Jugador &actual = juan.getJugadorActual();
                Jugador &oponente = juan.getJugadorOponente();

                actual.mostrarTablero();
                actual.mostrarTableroAtaque();
                
                actual.Atacar(oponente, actual);
                time(2);
                system("cls");
                cout<<"Cambia de jugador"<<endl;
                time(2);
                if (juan.verificarGanador()){
                    cout<< "!El jugador "<<juan.getJugadorActual().getNombre()<<" ha ganado"<<endl;
                    break;
                }

            }
        }
};