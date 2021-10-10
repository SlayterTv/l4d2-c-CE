// l4d2 hack.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

using namespace std;//evitar escribir std - avoid typing std

int main()
{
    int dw_Health = 0xEC;//cubrir la salud - health offset
    int ad_Health = 0x09D1F550;//puntero de salud - health pointer
    int writeHealth = 100;//cantidad de salud - amount of health

    int dw_Ammo = 0x1414;//cubrir municion - health offset
    int ad_Ammo = 0x09E77EC0;//puntero de municion - health pointer
    int writeAmmo = 100;//cantidad de municion - amount of health

    int readAmmo = 0;//leer municion -read ammo
    int readHealth = 0;//leer salud - read heal
    
    DWORD Health = (DWORD)(ad_Health + dw_Health);//convertir el offset de vida y el pubntero de vida de int a Dword - turn health offset and health pointer fron int to DWORD
    DWORD Ammo = (DWORD)(ad_Ammo + dw_Ammo); //convertir el offset de municion y el pubntero de municion de int a Dword - turn health offset and health pointer fron int to DWORD
    HWND hwnd = FindWindowA(NULL, "Left 4 Dead 2");//encontrar la ventana con el nombre left 4 dead 2-find window with title left 4 dead 2

    if (hwnd == NULL) {//reviar que el jeugo no este abierto-check if game isn´t open
        cout << "no se encuentra el juego" << endl;//escribir mensaje en consola - write message in console
        Sleep(3000);//esperar 3000 milisegundos(3 segundos) -wait for 3000 milisecond(3 second)
        exit(-1);//cerrar consola - close console
    }
    else {//correr si el juego esta abierto - run if game is open
        DWORD procID;//variable para guardar el Id del proceso - variable to save process ID 
        GetWindowThreadProcessId(hwnd, &procID);//obtener el ID del proceso - get game process ID
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);//dar todos los permisos al juego - give all permissions to game
        cout << "juego encontrado" << endl;//escribir mensaje en consola - write message in console

        if (procID == NULL) {//correr si el juego esta abierto - run if process id isn´t find
            cout << "No se encuentra el proceso" << endl;//escribir mensaje en consola - write message in console
            Sleep(3000);//esperar 3000 milisegundos(3 segundos) -wait for 3000 milisecond(3 second)
            exit(-1);//cerrar consola - close console
        }
        else {//correr si el ID del proceso no es nulo - run if process id isn´t null
            cout << "proceso encontrado" << endl;//escribir mensaje en consola - write message in console
            for (;;) {//correr un loop infinito - run infinite loop
                ReadProcessMemory(handle, (PBYTE*)Health, &readHealth, sizeof(readHealth), 0);//escribir la cantidad especificada de curación en la memoria - write specificed amount  of heal into memory
                ReadProcessMemory(handle, (PBYTE*)Ammo, &readAmmo, sizeof(readAmmo), 0);//leer la cantidad especificada de munición en la memoria - read specificed amount  of ammo into memory
                cout << readAmmo << endl;//escribir mensaje en consola - write message in console
                cout << readHealth << endl;//escribir mensaje en consola - write message in console
                if (readAmmo <= 10) {//verificar que la municion sea igual a 10 - verify that the ammunition is equal to 10
                    cout << "municion restaurada" << endl;//escribir mensaje en consola - write message in console
                    WriteProcessMemory(handle, (PBYTE*)Ammo, &writeAmmo, sizeof(writeAmmo), 0);//escribe la cantidad especificada de munición en la memoria - write specificed amount  of ammo into memory
                }
                if (readHealth <= 50 ) {//verificar que la vida sea menor o igual a 50 - verify that life is less than or equal to 50
                    cout << "cura restaurada" << endl;//escribir mensaje en consola - write message in console
                    WriteProcessMemory(handle, (PBYTE*)Health, &writeHealth, sizeof(writeHealth), 0);//escribir la cantidad especificada de curación en la memoria - write specificed amount  of heal into memory
                }

                Sleep(1000);//esperar 1000 milisegundos(1 segundos) -wait for 1000 milisecond(1 second)
            }
        }

    }
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
