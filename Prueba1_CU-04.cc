// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-04 - COMUNICACIÓN INTERNA DEL SISTEMA
// --------------------------------------------------

#include <cassert>
#include "CU-04.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
//PRUEBA 1 - Coordinador puede enviar un mensaje a cualquiera
// --------------------------------------------------

int main() 
{
    Usuario* coord = new Usuario("marta@uco.es", "passCoord", "Coordinador", "Marta");
    Usuario* tutor = new Usuario("carlos@uco.es", "passTutor", "Tutor", "Carlos");
    Usuario* estudiante = new Usuario("maria@uco.es", "passEst", "Estudiante", "Maria");

    usuarios[coord->username] = coord;
    usuarios[tutor->username] = tutor;
    usuarios[estudiante->username] = estudiante;

    tutor->estudiantes.push_back(estudiante->nombrecompleto);
    estudiante->tutorAsignado = tutor->nombrecompleto;

    // El coordinador debe poder comunicarse con todos
    assert(puedeComunicar(coord, tutor));
    assert(puedeComunicar(coord, estudiante));

    enviarMensaje(coord, tutor, "Hola Carlos, soy la coordinadora.");
    assert(historialMensajes.back().emisor == "Marta");
    assert(historialMensajes.back().destinatario == "Carlos");
    assert(historialMensajes.back().contenido == "Hola Carlos, soy la coordinadora.");

    cout << "Prueba 1 pasada correctamente\n";

    return 0;
}