// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C

#include "prueba.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

// Constructor del cuerpo básico
CuerpoAmongUs::CuerpoAmongUs() {
    // Vértices para un cuerpo más ovalado
    float radioX = 0.5;    // Radio en X
    float radioY = 0.7;    // Radio en Y (más alto)
    float radioZ = 0.3;    // Radio en Z (más delgado)
    int numSegmentos = 12; // Número de segmentos para hacer el óvalo

    // Generamos los vértices en forma de óvalo
    for (int i = 0; i < numSegmentos; i++) {
        float angulo = (2.0f * M_PI * i) / numSegmentos;
       // float siguienteAngulo = (2.0f * M_PI * (i + 1)) / numSegmentos;
        
        // Vértices superiores
        vertices.push_back({
            radioX * cos(angulo),
            radioY,
            radioZ * sin(angulo)
        });
        
        // Vértices inferiores
        vertices.push_back({
            radioX * cos(angulo),
            -radioY,
            radioZ * sin(angulo)
        });
        
        // Generamos los triángulos
        int baseIndex = i * 2;
        int nextBaseIndex = ((i + 1) % numSegmentos) * 2;
        
        // Triángulos laterales
        triangulos.push_back({baseIndex, baseIndex + 1, nextBaseIndex + 1});
        triangulos.push_back({baseIndex, nextBaseIndex + 1, nextBaseIndex});
    }

    // Triángulos para la tapa superior e inferior
    unsigned int indiceCentroSuperior = static_cast<unsigned int>(vertices.size());
    unsigned int indiceCentroInferior = static_cast<unsigned int>(vertices.size() + 1);
    
    // Añadir vértices centrales
    vertices.push_back({0.0f, radioY, 0.0f});    // Centro superior
    vertices.push_back({0.0f, -radioY, 0.0f});   // Centro inferior
    
    // Generar triángulos para las tapas
    for (int i = 0; i < numSegmentos; i++) {
        int actual = i * 2;
        int siguiente = ((i + 1) % numSegmentos) * 2;
        
        // Tapa superior
        triangulos.push_back({actual, siguiente, indiceCentroSuperior});
        
        // Tapa inferior
        triangulos.push_back({actual + 1, indiceCentroInferior, siguiente + 1});
    }
}

AmongUsMuñeco::AmongUsMuñeco() {
    ponerNombre("Muñeco de Among Us");

    // Cuerpo principal
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    unsigned indiceTraslacionCuerpo = agregar(translate(vec3(0.0f, 0.0f, 0.0f)));
    movimientoCuerpo = leerPtrMatriz(indiceTraslacionCuerpo);
    cuerpo->ponerNombre("Cuerpo del Among Us");
    cuerpo->agregar(scale(vec3(1.0, 1.2, 0.8))); 
    cuerpo->ponerColor({1.0f, 0.0f, 0.0f}); // Rojo
    cuerpo->agregar(new CuerpoAmongUs());

    // Visor
    NodoGrafoEscena* visor = new NodoGrafoEscena();
    visor->ponerNombre("Visor del Among Us");
    unsigned indiceRotVisor = visor->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    visor->agregar(translate(vec3(0.0, 0.3, 0.31)));
    visor->agregar(scale(vec3(0.7, 0.3, 0.1)));
    visor->ponerColor({0.5f, 0.8f, 1.0f}); // Azul claro
    visor->agregar(new CuerpoAmongUs());
    rotacionVisor = visor->leerPtrMatriz(indiceRotVisor);

    // Mochila
    NodoGrafoEscena* mochila = new NodoGrafoEscena();
    mochila->ponerNombre("Mochila del Among Us");
    unsigned indiceRotMochila = mochila->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    mochila->agregar(translate(vec3(0.0, 0.0, -0.4)));
    mochila->agregar(scale(vec3(0.6, 0.8, 0.2)));
    mochila->ponerColor({0.8f, 0.0f, 0.0f}); // Rojo oscuro
    mochila->agregar(new CuerpoAmongUs());
    rotacionMochila = mochila->leerPtrMatriz(indiceRotMochila);

    // Piernas
    NodoGrafoEscena* piernas = new NodoGrafoEscena();
    piernas->ponerNombre("Piernas del Among Us");
    unsigned indiceMovPiernas = piernas->agregar(translate(vec3(0.0f, 0.0f, 0.0f)));
    piernas->agregar(translate(vec3(0.0, -0.9, 0.0)));
    piernas->agregar(scale(vec3(0.8, 0.2, 0.6)));
    piernas->ponerColor({1.0f, 0.0f, 0.0f}); // Rojo
    piernas->agregar(new CuerpoAmongUs());
    movimientoPiernas = piernas->leerPtrMatriz(indiceMovPiernas);

    // Agregar todas las partes al muñeco
    agregar(cuerpo);
    agregar(visor);
    agregar(mochila);
    agregar(piernas);
}

unsigned AmongUsMuñeco::leerNumParametros() const {
    return 4; // movimiento cuerpo, rotación visor, rotación mochila, movimiento piernas
}

void AmongUsMuñeco::actualizarEstadoParametro(const unsigned iParam, const float tSec) {
    switch (iParam) {
        case 0: // Movimiento del cuerpo (flotando)
            *movimientoCuerpo = translate(vec3(0.0f, 0.1f * sin(tSec*2.0f), 0.0f));
            break;
        case 1: // Rotación del visor
            *rotacionVisor = rotate(float(M_PI/8 * sin(tSec)), vec3{0.0, 1.0, 0.0});
            break;
        case 2: // Rotación de la mochila
            *rotacionMochila = rotate(float(M_PI/16 * sin(tSec*2.0f)), vec3{1.0, 0.0, 0.0});
            break;
        case 3: // Movimiento de las piernas
            *movimientoPiernas = translate(vec3(0.0f, 0.05f * sin(tSec*4.0f), 0.0f));
            break;
    }
}

/** 

// Constructor para el cuerpo básico del helicóptero
CuerpoHelicoptero::CuerpoHelicoptero() {
    // Vértices para un cuerpo aerodinámico
    float radioX = 0.5;    
    float radioY = 0.3;    
    float radioZ = 0.8;    // Más largo en Z para forma de helicóptero
    int numSegmentos = 12; 

    // Generamos los vértices en forma ovalada pero más alargada
    for (int i = 0; i < numSegmentos; i++) {
        float angulo = (2.0f * M_PI * i) / numSegmentos;
        
        // Vértices superiores
        vertices.push_back({
            radioX * cos(angulo),
            radioY * sin(angulo),
            radioZ
        });
        
        // Vértices inferiores
        vertices.push_back({
            radioX * cos(angulo),
            radioY * sin(angulo),
            -radioZ
        });
        
        // Generamos los triángulos
        int baseIndex = i * 2;
        int nextBaseIndex = ((i + 1) % numSegmentos) * 2;
        
        // Triángulos laterales
        triangulos.push_back({baseIndex, baseIndex + 1, nextBaseIndex + 1});
        triangulos.push_back({baseIndex, nextBaseIndex + 1, nextBaseIndex});
    }

    // Añadir vértices centrales y tapas
    unsigned int indiceCentroDelantero = static_cast<unsigned int>(vertices.size());
    unsigned int indiceCentroTrasero = static_cast<unsigned int>(vertices.size() + 1);
    
    vertices.push_back({0.0f, 0.0f, radioZ});     // Centro delantero
    vertices.push_back({0.0f, 0.0f, -radioZ});    // Centro trasero
    
    // Generar triángulos para las tapas
    for (int i = 0; i < numSegmentos; i++) {
        int actual = i * 2;
        int siguiente = ((i + 1) % numSegmentos) * 2;
        
        triangulos.push_back({actual, siguiente, indiceCentroDelantero});
        triangulos.push_back({actual + 1, indiceCentroTrasero, siguiente + 1});
    }
}

HelicopteroCompleto::HelicopteroCompleto() {
    ponerNombre("Helicóptero");

    // Cuerpo principal
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    unsigned indiceTraslacionCuerpo = agregar(translate(vec3(0.0f, 0.0f, 0.0f)));
    movimientoCuerpo = leerPtrMatriz(indiceTraslacionCuerpo);
    cuerpo->ponerNombre("Cuerpo del Helicóptero");
    cuerpo->agregar(scale(vec3(1.0, 0.8, 1.2))); 
    cuerpo->ponerColor({0.2f, 0.2f, 0.7f}); // Azul oscuro
    cuerpo->agregar(new CuerpoHelicoptero());

    // Hélice principal
    NodoGrafoEscena* helicePrincipal = new NodoGrafoEscena();
    helicePrincipal->ponerNombre("Hélice Principal");
    unsigned indiceRotHelice = helicePrincipal->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    helicePrincipal->agregar(translate(vec3(0.0, 0.4, 0.0)));
    helicePrincipal->agregar(scale(vec3(2.0, 0.05, 0.2)));
    helicePrincipal->ponerColor({0.3f, 0.3f, 0.3f}); // Gris
    helicePrincipal->agregar(new CuerpoHelicoptero());
    rotacionHelicePrincipal = helicePrincipal->leerPtrMatriz(indiceRotHelice);

    // Hélice de cola
    NodoGrafoEscena* heliceCola = new NodoGrafoEscena();
    heliceCola->ponerNombre("Hélice de Cola");
    unsigned indiceRotHeliceCola = heliceCola->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    heliceCola->agregar(translate(vec3(0.0, 0.2, -1.0)));
    heliceCola->agregar(scale(vec3(0.5, 0.05, 0.5)));
    heliceCola->ponerColor({0.3f, 0.3f, 0.3f}); // Gris
    heliceCola->agregar(new CuerpoHelicoptero());
    rotacionHeliceCola = heliceCola->leerPtrMatriz(indiceRotHeliceCola);

    // Cola
    NodoGrafoEscena* cola = new NodoGrafoEscena();
    cola->ponerNombre("Cola del Helicóptero");
    cola->agregar(translate(vec3(0.0, 0.2, -0.8)));
    cola->agregar(scale(vec3(0.2, 0.2, 0.8)));
    cola->ponerColor({0.2f, 0.2f, 0.7f}); // Azul oscuro
    cola->agregar(new CuerpoHelicoptero());

    // Agregar todas las partes al helicóptero
    agregar(cuerpo);
    agregar(helicePrincipal);
    agregar(heliceCola);
    agregar(cola);
}

unsigned HelicopteroCompleto::leerNumParametros() const {
    return 3; // movimiento cuerpo, rotación hélice principal, rotación hélice cola
}

void HelicopteroCompleto::actualizarEstadoParametro(const unsigned iParam, const float tSec) {
    switch (iParam) {
        case 0: // Movimiento del cuerpo (flotando)
            *movimientoCuerpo = translate(vec3(0.0f, 0.05f * sin(tSec*2.0f), 0.0f));
            break;
        case 1: // Rotación de la hélice principal
            *rotacionHelicePrincipal = rotate(tSec * 5.0f, vec3{0.0, 1.0, 0.0});
            break;
        case 2: // Rotación de la hélice de cola
            *rotacionHeliceCola = rotate(tSec * 8.0f, vec3{1.0, 0.0, 0.0});
            break;
    }
}

*/