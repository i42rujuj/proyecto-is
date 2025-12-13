// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-02 - ASIGNACIÓN DE TUTORES A ESTUDIANTES
// --------------------------------------------------

#include <cassert>
#include "CU-02.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
//PRUEBA 2 - Solo el coordinador puede modificar una asignación
// --------------------------------------------------


int main() {
    usuarios.clear();

    Usuario* coord = new Usuario("coord@uco.es", "pass1", "Coordinador", "Coordinador");
    usuarios[coord->username] = coord;

    Usuario* tutorA = new Usuario("tutorA@uco.es", "pass2", "Tutor", "Tutor A");
    Usuario* tutorB = new Usuario("tutorB@uco.es", "pass3", "Tutor", "Tutor B");
    usuarios[tutorA->username] = tutorA;
    usuarios[tutorB->username] = tutorB;

    Usuario* est = new Usuario("antonio@uco.es", "pass4", "Estudiante", "Antonio");
    est->tutorAsignado = tutorA->nombrecompleto;
    tutorA->estudiantes.push_back(est->username);
    usuarios[est->username] = est;

    // Caso 1: Coordinador modifica -> debe funcionar
    modificarAsignacion("coord@uco.es", "antonio@uco.es", "tutorB@uco.es");
    assert(est->tutorAsignado == "Tutor B");
    assert(tutorB->estudiantes.back() == "Antonio");

    // Caso 2: Tutor intenta modificar -> debe fallar y NO cambiar nada
    modificarAsignacion("tutorB@uco.es", "antonio@uco.es", "tutorA@uco.es");
    assert(est->tutorAsignado == "Tutor B");

    // Caso 3: Estudiante intenta modificar -> debe fallar y NO cambiar nada
    modificarAsignacion("antonio@uco.es", "antonio@uco.es", "tutorA@uco.es");
    assert(est->tutorAsignado == "Tutor B");

    cout << "Prueba 2 (reasignación por coordinador) pasada correctamente\n";
    return 0;
}