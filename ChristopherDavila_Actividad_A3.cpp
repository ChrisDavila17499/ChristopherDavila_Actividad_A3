#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Empleado {
private:
    string nombre;
    string apellidoPaterno;
    string apellidoMaterno;
    int dia, mes, anio;

    // Diccionario interno de palabras inconvenientes (todas en mayúsculas)
    static const vector<string> palabrasInconvenientes;

    // Obtiene la primera vocal interna del apellido paterno
    char obtenerVocalInterna(const string& apellido) {
        for (size_t i = 1; i < apellido.length(); ++i) {
            char c = toupper(apellido[i]);
            if (string("AEIOU").find(c) != string::npos) {
                return c;
            }
        }
        return 'X';
    }

public:
    Empleado(string nom, string apPat, string apMat, int d, int m, int a)
        : nombre(nom), apellidoPaterno(apPat), apellidoMaterno(apMat), dia(d), mes(m), anio(a) {}

    string generarRFC() {
        string rfc;

        // 1. Primera letra del apellido paterno
        rfc += toupper(apellidoPaterno[0]);
        // 2. Primera vocal interna
        rfc += obtenerVocalInterna(apellidoPaterno);
        // 3. Inicial del apellido materno o 'X'
        rfc += (!apellidoMaterno.empty()
                ? toupper(apellidoMaterno[0])
                : 'X');

        // 4. Inicial del nombre (posible historial con palabra inconveniente)
        char inicialNombre = toupper(nombre[0]);
        // Formamos provisionalmente las 4 primeras letras
        string bloque4 = rfc + inicialNombre;

        // Si coinciden con palabra inconveniente, forzamos 'X' en la 4ª posición
        if (find(palabrasInconvenientes.begin(),
                 palabrasInconvenientes.end(),
                 bloque4) != palabrasInconvenientes.end()) {
            inicialNombre = 'X';
        }
        rfc += inicialNombre;

        // 5-10. Fecha: año (2 dígitos), mes (2), día (2)
        int anio2 = anio % 100;
        rfc += (anio2 < 10 ? "0" : "") + to_string(anio2);
        rfc += (mes    < 10 ? "0" : "") + to_string(mes);
        rfc += (dia    < 10 ? "0" : "") + to_string(dia);

        return rfc;
    }
};

// Definición del diccionario
const vector<string> Empleado::palabrasInconvenientes = {
    "BUEI","BUEY","CACA","CACO","CAGA","CAGO",
    "CAKA","CAKO","COGE","COJA","COJE","COJI",
    "COJO","CULO","FETO","GUEY","JOTO","KACA",
    "KACO","KAGA","KAGO","KOGE","KOJO","KAKA",
    "KULO","MAME","MAMO","MEAR","MEAS","MEON",
    "MION","MOCO","MULA","PEDA","PEDO","PENE",
    "PUTA","PUTO","QULO","RATA","RUIN"
};

int main() {
    // Captura de datos
    string nombre, apPat, apMat;
    int dia, mes, anio;

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Apellido paterno: ";
    getline(cin, apPat);

    cout << "Apellido materno (vacío si no tiene): ";
    getline(cin, apMat);

    cout << "Día de nacimiento: "; cin >> dia;
    cout << "Mes de nacimiento: "; cin >> mes;
    cout << "Año de nacimiento (YYYY): "; cin >> anio;

    Empleado emp(nombre, apPat, apMat, dia, mes, anio);
    cout << "RFC generado (sin homoclave): "
         << emp.generarRFC() << endl;

    return 0;
}
