// --------------------------------------------------
// CÓDIGO DEL CASO DE USO CU-02 - ASIGNACIÓN DE TUTORES A ESTUDIANTES
// --------------------------------------------------

#ifndef CU_02_H
#define CU_02_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "global.h"
using namespace std;

// ---------------------------------------------------------
// Asignación automática según criterios
// ---------------------------------------------------------
bool asignarAutomaticamente() 
{
    // Recorremos estudiantes
    for (auto &par : usuarios) 
    {
        Usuario* u = par.second;
        if (u->rol != "Estudiante") continue;

        bool asignado = false;

        // Buscar tutor disponible
        for (auto &par : usuarios) 
        {
            Usuario* t = par.second;
            if (t->rol == "Tutor" && t->estudiantes.size() < t->maxAlumnos) 
            {
                u->tutorAsignado = t->nombrecompleto;       // asignación directa
                t->estudiantes.push_back(u->nombrecompleto); // añadir alumno al tutor
                asignado = true;
                break;
            }
        }

        if (asignado == false) {
            cout << "[AVISO] No hay tutores disponibles para " << u->nombrecompleto << endl;
        }
    }

    return true;
}

// ---------------------------------------------------------
// Confirmación de asignaciones
// ---------------------------------------------------------
void confirmarAsignaciones() {cout << "\n[SISTEMA] Asignaciones confirmadas exitosamente.\n";}

// ---------------------------------------------------------
// Mostrar todas las asignaciones
// ---------------------------------------------------------
void mostrarAsignaciones() 
{
    cout << "\n---- LISTADO DE ASIGNACIONES ----\n";
    for (auto &par : usuarios) 
    {
        Usuario* u = par.second;
        if (u->rol == "Estudiante" && u->tutorAsignado != "") 
        {
            cout << "Estudiante: " << u->nombrecompleto << " | Tutor: " << u->tutorAsignado << endl;
        }
    }
}


// ---------------------------------------------------------
// Modificar una asginación (solo para Coordinadores)
// ---------------------------------------------------------
void modificarAsignacion(string coordinador, string estudiante, string nuevoTutor) 
{
    // Verificar que el usuario que llama es coordinador
    if (!usuarios.count(coordinador) || usuarios[coordinador]->rol != "Coordinador") {
        cout << "[ERROR] Solo un coordinador puede modificar asignaciones.\n";
        return;
    }

    Usuario* u = usuarios[estudiante];
    Usuario* tutorNuevo = usuarios[nuevoTutor];

    if (!usuarios.count(estudiante)) {
        cout << "[ERROR] El estudiante " << estudiante << " no existe en el sistema.\n";
        return;
    }

    if (!usuarios.count(nuevoTutor)) {
        cout << "[ERROR] El tutor " << nuevoTutor << " no existe en el sistema.\n";
        return;
    }

    if (u->rol != "Estudiante" || tutorNuevo->rol != "Tutor") {
        cout << "[ERROR] Roles incorrectos para la reasignación.\n";
        return;
    }

    // Eliminar el tutor anterior
    if (u->tutorAsignado != "") 
    {
        Usuario* tutorViejo = nullptr;
        for (auto &par : usuarios) 
        {
            if (par.second->nombrecompleto == u->tutorAsignado) 
            {
            tutorViejo = par.second;
            break;
            }
        }

        if (tutorViejo != nullptr) {
        auto &alumnos = tutorViejo->estudiantes;
        alumnos.erase(remove(alumnos.begin(), alumnos.end(), estudiante), alumnos.end());
        }
    }

    // Asignar al nuevo tutor
    u->tutorAsignado = tutorNuevo->nombrecompleto;
    tutorNuevo->estudiantes.push_back(u->nombrecompleto);

    cout << "[SISTEMA] El coordinador " << coordinador << " ha reasignado al estudiante " << estudiante << " al tutor " << nuevoTutor << ".\n";
}

void moduloAsignacion()
{
    int opcion;
        do {
            cout << "\n--- MODULO DE ASIGNACIÓN DE TUTORES ---\n\n";
            cout << "1. Mostrar asignaciones\n";
            cout << "2. Modificar asignación (solo Coordinadores)\n";
            cout << "3. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch(opcion) {
                case 1:
                    mostrarAsignaciones();
                    break;

                case 2: 
                {
                    string usuarioCoord;
                    cout << "\nIntroduce tu usuario (debe ser Coordinador): ";
                    cin >> usuarioCoord;

                    string estudiante, nuevoTutor;
                    cout << "\n\n--- LISTA DE ESTUDIANTES ---\n";
                    for (auto &par : usuarios) 
                    {
                        Usuario* u = par.second;
                        if (u->rol == "Estudiante") 
                        {
                            cout << "Usuario: " << u->username << " | Nombre: " << u->nombrecompleto << endl;
                        }
                    }
                    cout << "\nIntroduce el estudiante a reasignar (usuario): ";
                    cin >> estudiante;

                    cout << "\n\n--- LISTA DE TUTORES ---\n";
                    for (auto &par : usuarios) 
                    {
                        Usuario* u = par.second;
                        if (u->rol == "Tutor") 
                        {
                            cout << "Usuario: " << u->username << " | Nombre: " << u->nombrecompleto << endl;
                        }
                    }
                    cout << "\nIntroduce el nuevo tutor (usuario): ";
                    cin >> nuevoTutor;

                    modificarAsignacion(usuarioCoord, estudiante, nuevoTutor);
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