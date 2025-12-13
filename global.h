// --------------------------------------------------
// EN ESTE ARCHIVO SE ENCUENTRA DEFINIDO LO SIGUIENTE
// - MAPA (DONDE GUARDAREMOS LOS ALUMNOS OBTENIDOS DEL ARCHIVO CSV (usuarios_ficticios.csv))
// - CLASE USUARIO 
// --------------------------------------------------


#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// --------------------------------------------------
// Class Usuario
// --------------------------------------------------
class Usuario 
{
    public:
    string nombrecompleto;
    string username;
    string password;
    string rol; // Estudiante, Tutor, Coordinador
    string tutorAsignado; // Solo para estudiantes
    vector<string> estudiantes; // Solo para tutor
    int maxAlumnos;

    Usuario(string u, string p, string r, string name) 
    {
        nombrecompleto = name;
        username = u;
        password = p;
        rol = r;
        maxAlumnos = 4;
        tutorAsignado = "";
    } 
};

extern std::map<std::string, Usuario*> usuarios;

#endif

//En este archivo definimos el mapa donde declararemos el mapa que usaremos para guardar los usuarios del sistema