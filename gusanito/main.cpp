#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

bool GameOver = false;
int score = 0;

const int W = 30, H = 15;

int caracter_presionado = 0;
const int ARRIBA  = 72;
const int ABAJO  = 80;
const int IZQUIERDA  = 75;
const int DERECHA  = 77;
const int ESC = 27;

int movimiento;

int Pos_player[2], Pos_food[2];

char tablero;

int num_bucle = 1;

//cola
int taillenght;
int tailX[150];
int tailY[150];


void dibujar() // dibujar el juego(tablero, gusano, comida)
{
    // std::cout << "movimiento: " << movimiento << std::endl; 
    std::cout << "score: " << score << std::endl; 
    std::cout << "tail lenght: " << taillenght << std::endl; 
    for (int i = 0; i < H + 2 ; ++i) {
        for (int j = 0; j < W + 2; ++j) {
            if (i==0 || i == H+1) 
            {
                std::cout << "-";
            }
            else if (j==0 || j == W+1)
            {
                std::cout << "|";
            }
            else if (i == Pos_player[0] && j == Pos_player[1]) 
            {
                std::cout << "S";
            }
            else if (i == Pos_food[0] && j == Pos_food[1])
            {
                 std::cout << "C";
            } 
            else if(taillenght > 0){
                // bool draw_tail = false;
                for(int k = 0; k < taillenght; k++)
                {
                    if (tailX[k] == i && tailY[k] == j) 
                    {
                        std::cout << "s";
                        // draw_tail = true;
                    }
                }
            }
            else{
                        std::cout << " ";
                    // std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void input() // entrada 
{
    if (kbhit()) {
        caracter_presionado = getch();
        switch (caracter_presionado) {
            case ARRIBA:
                movimiento = ARRIBA;
                break;
            case ABAJO:
                movimiento = ABAJO;
                break;
            case IZQUIERDA:
                movimiento = IZQUIERDA;
                break;
            case DERECHA:
                movimiento = DERECHA;
                break;
        }
    } 
}

void posicion_food()
{
    Pos_food[0] = rand() % H + 1;
    Pos_food[1] = rand() % W + 1;
}

void fisicas() // la logica del juego
{
    // movimiento
    switch (movimiento) {
        case ARRIBA:
            Pos_player[0]--; 
            break;
        case ABAJO:
            Pos_player[0]++; 
            break;
        case IZQUIERDA:
            Pos_player[1]--; 
            break;
        case DERECHA:
            Pos_player[1]++; 
            break;
    }
    // comida
    if (Pos_player[0] == Pos_food[0] && Pos_player[1] == Pos_food[1]) {
        score += 10;
        posicion_food();
        taillenght++;
    }
    // cola del gusano
    int TailPosX = tailX[0];
    int TailPosY = tailY[0];
    int TailPosX2, TailPosY2;

    tailX[0] = Pos_player[0];
    tailY[0] = Pos_player[1];

    for(int i = -1; i < taillenght; ++i){
        TailPosX2 = tailX[i];
        TailPosY2 = tailY[i];

        tailX[i] = TailPosX;
        tailY[i] = TailPosY;

        TailPosX = TailPosX2;
        TailPosY = TailPosY2;
    }
}

int main(){

    srand(time(0));
    Pos_player[0] = H / 2;
    Pos_player[1] = W / 2;
    posicion_food();
    while(!GameOver)
    {
        // if(num_bucle % 10000 == 0)
        {
            Sleep(100);
            input();
            fisicas();
            // tail();
            dibujar();
            std::cout << "X: " << Pos_food[0] << " Y: " << Pos_food[1] << std::endl;

            if (num_bucle % 300 == 0){
                posicion_food();
            }
        }
        num_bucle++;
    }
}

