// --------------------------------------------------
// CÓDIGO DEL CASO DE USO CU-06 - SISTEMA DE ALERTAS
// --------------------------------------------------


#ifndef CU_06_H
#define CU_06_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include "global.h"
using namespace std;

// ---------------------------
// Struct Alertas (como se representa la alerta enviada)
// ---------------------------
struct Alerta {
    string estudiante;
    string motivo;
    string destinatario;
};

vector<Alerta> historialAlertas;

// --------------------------------------------------
// Función que detecta alumnos en riesgo (Simulamos 5 notas diferentes, hacemos la media y si esta es menor a 5 significa que el alumno está en riesgo)
// --------------------------------------------------
vector<string> detectarAlumnosEnRiesgo() 
{
    vector<string> riesgo;

    for (auto &par : usuarios) 
    {
        Usuario* u = par.second;

        if (u->rol == "Estudiante") 
        {
            int suma = 0;

            // Generar 5 números enteros aleatorios entre 0 y 10
            for (int i = 0; i < 5; i++) 
            {
                int nota = rand() % 11;
                suma += nota;
            }

            float media = suma / 5.0;

            if (media < 5.0) 
            {
                riesgo.push_back(u->username);
            }
        }
    }

    return riesgo;
}


// --------------------------------------------------
// Enviar alerta al tutor y coordinador
// --------------------------------------------------
void enviarAlerta(const string& estudiante, const string& motivo) 
{

    Usuario* alumno = usuarios[estudiante];

    // 1. Enviar alerta al tutor asignado
    string tutor = alumno->tutorAsignado;

    Alerta a;
    a.estudiante = alumno->nombrecompleto;
    a.motivo = motivo;
    a.destinatario = tutor;

    historialAlertas.push_back(a);

    cout << "\n[ALERTA] Se ha enviado una alerta al tutor " << tutor << " sobre el estudiante " << alumno->nombrecompleto << endl;

    // 2. Enviar alerta al coordinador
    for (auto &par : usuarios) 
    {
        Usuario* u = par.second;

        if (u->rol == "Coordinador") 
        {
            Alerta a;
            a.estudiante = alumno->nombrecompleto;
            a.motivo = motivo;
            a.destinatario = u->nombrecompleto;

            historialAlertas.push_back(a);

            cout << "[ALERTA] Se ha enviado una alerta al coordinador " << u->nombrecompleto << endl;
        }
    }
}

// --------------------------------------------------
// Mostrar el historial de alertas
// --------------------------------------------------
void mostrarHistorial() 
{
    cout << "\n---- HISTORIAL DE ALERTAS ----\n";

    if (historialAlertas.empty()) 
    {
        cout << "No hay alertas registradas.\n";
    }

    else
    {
        for (auto &a : historialAlertas) 
        {
        cout << "Estudiante: " << a.estudiante<< " | Motivo: " << a.motivo << " | Enviado a: " << a.destinatario << endl;
        }
    }
}

void moduloAlertas() 
{
    srand(time(0)); // inicializar aleatorio si lo necesitas

    cout << "\n--- MODULO DE ALERTAS ---\n\n";

    // Detectar alumnos en riesgo
    vector<string> riesgo = detectarAlumnosEnRiesgo();

    if (riesgo.empty()) {
        cout << "No se han detectado alumnos en riesgo.\n";
    } else {
        for (auto &r : riesgo) {
            enviarAlerta(r, "Bajo rendimiento detectado");
        }
    }

    int opcion;
    do {
        cout << "\n--- MENÚ DE ALERTAS ---\n";
        cout << "1. Mostrar historial de alertas\n";
        cout << "2. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
                mostrarHistorial();
                break;
            
            case 2:
                cout << "Volviendo al menú principal...\n"; 
                break;

            default:
                cout << "[ERROR] Opción inválida.\n";
        }
    }  while(opcion != 2);
}

#endif