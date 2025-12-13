// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-06 - SISTEMA DE ALERTAS
// --------------------------------------------------

#include <cassert>
#include "CU-06.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
//PRUEBA 2 - Se detecta el alumnno en riesgo correctamente
// --------------------------------------------------


// Sobrescribimos rand() SOLO PARA LA PRUEBA
int rand() {
    return 2; //Siempre generara un 2 como nota
}

int main()
{
    usuarios.clear();

    // Crear alumno
    Usuario* estudiante = new Usuario("juan@uco.es", "456", "Estudiante", "Juan");
    estudiante->tutorAsignado = "tutor1";
    usuarios[estudiante->username] = estudiante;

    vector<string> riesgo = detectarAlumnosEnRiesgo();

    // Verificar que el alumno en riesgo está en la lista
    bool encontrado = false;
    for (auto &nombre : riesgo) 
    {
        if (nombre == "juan@uco.es") 
        {
            encontrado = true;
            break;
        }
    }

    assert(encontrado == true);

    cout << "Prueba 2 (el alumno fue detectado en riesgo) pasada correctamente\n";
}