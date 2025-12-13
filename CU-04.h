// --------------------------------------------------
// CÓDIGO DEL CASO DE USO CU-04 - COMUNICACIÓN INTERNA DEL SISTEMA
// --------------------------------------------------

#ifndef CU_04_H
#define CU_04_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "global.h"
using namespace std;

// --------------------------------------------------
// Struct Mensaje (Como representar el mensaje)
// --------------------------------------------------
struct Mensaje {
    string emisor;
    string destinatario;
    string contenido;
};

// --------------------------------------------------
// Funcion para verificar permisos de comunicacion
// --------------------------------------------------
bool puedeComunicar(Usuario* u, Usuario* destino) 
{
    if (u->rol == "Coordinador") {return true;}
    
    if (u->rol == "Tutor") 
    {
        for (auto &e : u->estudiantes) 
        {
            if (e == destino->nombrecompleto) {return true;}
        }
        return false; // devuelve false solo si no encontró al estudiante
    }

    if (u->rol == "Estudiante") 
    {
        if (u->tutorAsignado == destino->nombrecompleto) {return true;}
        else {return false;}
 
    }

    return false;
}

vector<Mensaje> historialMensajes;

// --------------------------------------------------
// Funcion para enviar mensaje
// --------------------------------------------------
void enviarMensaje(Usuario* emisor, Usuario* receptor, const string& texto)
{
    if (!puedeComunicar(emisor, receptor)) {
        cout << "[ERROR] No tienes permiso para enviar mensajes a " << receptor->username << endl;
        return;
    }

    Mensaje m = {emisor->nombrecompleto, receptor->nombrecompleto, texto};
    historialMensajes.push_back(m); // Guardamos el mensaje en el historial

    cout << "\n[SISTEMA] Mensaje entregado a " << receptor->username << endl;
    cout << "[NOTIFICACIÓN] " << receptor->username << ": Has recibido un mensaje de " << emisor->username << ".\n";
}


// ---------------------------------------------------------
// Función que muestra el historial completo de mensajes (solo para Coordinadores)
// ---------------------------------------------------------
void mostrarHistorialMensajes() 
{
    cout << "\n--- HISTORIAL DE MENSAJES ---\n";
    if (historialMensajes.empty()) 
    {
        cout << "[INFO] No hay mensajes registrados.\n";
        return;
    }
    
    for (auto &msg : historialMensajes) 
    {
        cout << "De: " << msg.emisor << " -> Para: " << msg.destinatario << " | Mensaje: " << msg.contenido << endl;
    }
}

void moduloMensajeria() 
{
    string nombreLogin;
    cout << "\n--- MODULO DE MENSAJERÍA ---\n\n";

    cout << "Ingrese su nombre de usuario: ";
    cin >> nombreLogin;
    if (usuarios.find(nombreLogin) == usuarios.end()) {
        cout << "Usuario no encontrado.\n";
        return; // función es void, no return 0
    }

    Usuario* actual = usuarios[nombreLogin];
    cout << "Bienvenido " << actual->nombrecompleto << " (Su rol actual es " << actual->rol << ")\n\n";

    int opcion;
    do {
        cout << "\n--- MENÚ DE MENSAJERÍA ---\n";
        cout << "1. Seleccionar contacto\n";
        cout << "2. Mostrar historial de mensajes (solo Coordinadores)\n";
        cout << "3. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1: 
            {
                Usuario* destino = nullptr;

                // Mostrar lista de contactos disponibles
                cout << "\n--- Contactos disponibles ---\n";
                bool hayContactos = false;
                for (auto &par : usuarios) {
                    Usuario* posible = par.second;
                    if (posible->username != actual->username && puedeComunicar(actual, posible)) {
                        cout << "- " << posible->username << " (" << posible->nombrecompleto << ")\n";
                        hayContactos = true;
                    }
                }
                if (hayContactos == false) {
                    cout << "No tienes contactos disponibles.\n";
                    break;
                }

                // Selección de contacto
                while(true) {
                    cout << "\nSeleccione un contacto (username): ";
                    string contacto;
                    cin >> contacto;

                    if (usuarios.find(contacto) == usuarios.end()) {
                        cout << "[ERROR] Usuario no existe.\n";
                        continue;
                    }

                    destino = usuarios[contacto];
                    
                    if (puedeComunicar(actual, destino) == false) {
                        cout << "[ERROR] No tienes permiso para contactar con " << destino->username << endl;
                        continue;
                    }

                    break;
                }

                cin.ignore();
                cout << "Escriba su mensaje: ";
                string texto;
                getline(cin, texto);

                enviarMensaje(actual, destino, texto);

                cout << "[SISTEMA] Conversación registrada correctamente.\n";
                break;
            }
            
            case 2:
                if (actual->rol != "Coordinador")
                {
                    cout << "[ERROR] No puedes acceder a esta opción\n";
                    break;
                }
                else 
                {
                    mostrarHistorialMensajes();
                    break;
                }
            
            case 3:
                cout << "Volviendo al menú principal...\n"; 
                break;

            default:
                cout << "[ERROR] Opción inválida.\n";
        }
    } while(opcion != 3);
}

#endif