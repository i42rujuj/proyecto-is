// --------------------------------------------------
// CÓDIGO DE LAS PRUEBAS DEL CASO DE USO CU-06 - SISTEMA DE ALERTAS
// --------------------------------------------------

#include <cassert>
#include "CU-06.h"
#include "global.h"
using namespace std;

map<string, Usuario*> usuarios;

// --------------------------------------------------
//PRUEBA 1 - Se envía alerta a tutor y coordinador
// --------------------------------------------------

int main()
{
    usuarios.clear();
    historialAlertas.clear();

    Usuario* estudiante = new Usuario("ana@uco.es", "123", "Estudiante", "Ana");
    Usuario* tutor = new Usuario("tutor1@uco.es", "156", "Tutor", "Tutor Uno");
    Usuario* coord = new Usuario("coord1@uco.es", "000", "Coordinador", "Coordinador Uno");

    estudiante->tutorAsignado = tutor->nombrecompleto;

    usuarios[estudiante->username] = estudiante;
    usuarios[tutor->username] = tutor;
    usuarios[coord->username] = coord;

    // Enviar alerta
    enviarAlerta(estudiante->username, "Prueba de riesgo académico");

    // Verificar que se generaron 2 alertas
    assert(historialAlertas.size() == 2);

    // Verificar alerta al tutor
    assert(historialAlertas[0].estudiante == estudiante->nombrecompleto);
    assert(historialAlertas[0].motivo == "Prueba de riesgo académico");
    assert(historialAlertas[0].destinatario == tutor->nombrecompleto);

    // Verificar alerta al coordinador
    assert(historialAlertas[1].estudiante == estudiante->nombrecompleto);
    assert(historialAlertas[1].motivo == "Prueba de riesgo académico");
    assert(historialAlertas[1].destinatario == coord->nombrecompleto);

    cout << "Prueba 1 (envío de alertas) pasada correctamente\n";
}