// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-04 - COMUNICACIÓN INTERNA DEL SISTEMA
// --------------------------------------------------

#include <cassert>
#include "CU-04.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
// PRUEBA 2 - Estudiante no puede enviar un mensaje a otro estudiante
// --------------------------------------------------

int main() {
    // Crear dos estudiantes con tutores distintos
    Usuario* estudiante1 = new Usuario("luis@uco.es", "passLuis", "Estudiante", "Luis");
    Usuario* estudiante2 = new Usuario("jose@uco.es", "passJose", "Estudiante", "Jose");

    estudiante1->tutorAsignado = "Carlos";
    estudiante2->tutorAsignado = "Pedro";

    usuarios[estudiante1->username] = estudiante1;
    usuarios[estudiante2->username] = estudiante2;

    assert(historialMensajes.empty());

    // ESTO debe ser FALSE
    assert(!puedeComunicar(estudiante1, estudiante2));

    // Intento de enviar: debe bloquearse
    enviarMensaje(estudiante1, estudiante2, "Hola Jose!");

    // El historial debe seguir vacío
    assert(historialMensajes.empty());

    cout << "Prueba 2 pasada correctamente (estudiante no puede enviar a otro estudiante)\n";
    return 0;
}