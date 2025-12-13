// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-02 - ASIGNACIÓN DE TUTORES A ESTUDIANTES
// --------------------------------------------------

#include <cassert>
#include "CU-02.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
//PRUEBA 1 - Se realiza la asginación automática correctamente
// --------------------------------------------------

int main() {
    usuarios.clear();

    Usuario* tutor = new Usuario("tutor1@uco.es", "conTutor", "Tutor", "Tutor Uno");
    tutor->maxAlumnos = 2;
    usuarios[tutor->username] = tutor;

    // Crear dos estudiantes
    Usuario* est1 = new Usuario("manuel@uco.es", "conManuel", "Estudiante", "Manuel");
    Usuario* est2 = new Usuario("pablo@uco.es", "conPablo", "Estudiante", "Pablo");
    usuarios[est1->username] = est1;
    usuarios[est2->username] = est2;

    // Ejecutar asignación automática
    asignarAutomaticamente();

    // Verificar que ambos estudiantes fueron asignados al tutor
    assert(est1->tutorAsignado == "Tutor Uno");
    assert(est2->tutorAsignado == "Tutor Uno");
    assert(tutor->estudiantes.size() == 2);

    cout << "Prueba 1 (asignación automática) pasada correctamente\n";
    return 0;
}