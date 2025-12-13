// --------------------------------------------------
// MAIN DE PROGRAMA - DEBES EJECUTAR ESTE ARCHIVO PARA ACCEDER AL SISTEMA
// CADA CASO DE USO TIENE SU PROPIO CÓDIGO EN UN FICHERO
// --------------------------------------------------

#include "CU-02.h"
#include "CU-04.h"
#include "CU-06.h"
#include "global.h"
#include <fstream>
#include <sstream>

map<string, Usuario*> usuarios;

void cargarCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[ERROR] No se pudo abrir el fichero " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string nombrecompleto, username, password, rol;

        getline(ss, nombrecompleto, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, rol, ',');

        usuarios[username] = new Usuario(username, password, rol, nombrecompleto);
    }

    file.close();
}

int main() {
    cargarCSV("usuarios_ficticios.csv");
    
    if (asignarAutomaticamente()) 
    {
    confirmarAsignaciones();
    }

    Usuario* actual = nullptr;

    int opcion;
    do 
    {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Iniciar sesión\n";
        cout << "2. Módulo de Asignación\n";
        cout << "3. Módulo de Mensajería\n";
        cout << "4. Módulo de Alertas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) 
        {
            case 1:
            {
                string user, password;
                cout << "Introduzca su usuario: "; 
                cin >> user;
                cout << "Introduzca su contraseña: "; 
                cin >> password;

                if (usuarios.find(user) == usuarios.end()) 
                {
                    cout << "[SISTEMA] Usuario no existe.\n";
                    char opcion;
                    cout << "¿Desea registrarse (r) o volver al menú principal (m)? ";
                    cin >> opcion;

                    if (opcion == 'r') 
                    {
                        string nombre, rol;
                        cout << "Introduzca su nombre completo: ";
                        cin.ignore();
                        getline(cin, nombre);
                        bool rolValido = false;
                        while (rolValido == false) {
                            cout << "Introduzca su rol (Estudiante/Tutor/Coordinador): ";
                            cin >> rol;
                            if (rol == "Estudiante" || rol == "Tutor" || rol == "Coordinador") {
                                rolValido = true;
                            } else {
                                cout << "[ERROR] Rol inválido. Intente de nuevo.\n";
                            }
                        }
                        usuarios[user] = new Usuario(user, password, rol, nombre);
                        cout << "[SISTEMA] Usuario registrado correctamente.\n";
                    } 
                    else if (opcion == 'm') 
                    {
                        cout << "Volviendo al menú principal...\n";
                        break;
                    } 
                    else 
                    {
                        cout << "[ERROR] Opción inválida, regresando al menú.\n";
                        break;
                    }
                }
                actual = usuarios[user];
                cout << "Bienvenido " << actual->nombrecompleto << " (Rol: " << actual->rol << ")\n";
                break;
            }

            case 2: 
                if (actual == nullptr)
                {
                    cout << "[ERROR] Debe iniciar sesión antes de acceder al módulo de mensajería.\n";
                }
                else
                {
                    moduloAsignacion(); 
                }
                break;

            case 3: 
                if (actual == nullptr)
                {
                    cout << "[ERROR] Debe iniciar sesión antes de acceder al módulo de mensajería.\n";
                }
                else
                {
                    moduloMensajeria(); 
                }
                break;

            case 4: 
                if (actual == nullptr)
                {
                    cout << "[ERROR] Debe iniciar sesión antes de acceder al módulo de mensajería.\n";
                }
                else
                {
                    moduloAlertas(); 
                }
                break;

            case 5: cout << "Saliendo...\n"; break;

            default: cout << "[ERROR] Opción inválida.\n";
        }
    } while(opcion != 5);

    return 0;
}