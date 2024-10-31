// Nombre: Daniel, Apellidos: Alconchel Vázquez, Titulación: GIM.
// email: danieeeld2@correo.ugr.es, DNI o pasaporte: 49617109Z

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "modelo-jer.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;


CuboCuerpo::CuboCuerpo() {
    vertices = {
        {+1.0, -1.0, +1.0}, {-1.0, -1.0, +1.0},
        {-1.0, +1.0, +1.0}, {+1.0, +1.0, +1.0},
        {+1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0},
        {-1.0, +1.0, -1.0}, {+1.0, +1.0, -1.0}
    };
    triangulos = {
        {0, 1, 2}, {0, 2, 3}, {4, 7, 6}, {4, 6, 5},
        {0, 3, 7}, {0, 7, 4}, {1, 5, 6}, {1, 6, 2},
        {3, 2, 6}, {3, 6, 7}, {0, 4, 5}, {0, 5, 1}
    };
    calcularNormales();
}

MinecraftMuñeco::MinecraftMuñeco() {
    ponerNombre("Muñeco de Minecraft");

    // Cuerpo
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("Cuerpo del Muñeco");
    cuerpo->agregar(translate(vec3(0.0, 1.0, 0.0)) * scale(vec3(1.0, 2.0, 0.5)));
    cuerpo->agregar(new CuboCuerpo());

    // Cabeza
    NodoGrafoEscena* cabeza = new NodoGrafoEscena();
    cabeza->ponerNombre("Cabeza del Muñeco");
    unsigned indiceRotCabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    cabeza->agregar(translate(vec3(0.0, 3.0, 0.0)) * scale(vec3(1.0, 1.0, 1.0)));
    cabeza->agregar(new CuboCuerpo());
    rotacionCabeza = cabeza->leerPtrMatriz(indiceRotCabeza);

    // Brazos
    // Brazo izquierdo
NodoGrafoEscena* brazoIzq = new NodoGrafoEscena();
brazoIzq->ponerNombre("Brazo Izquierdo");
// Primero aplica la rotación, luego la traslación
unsigned indiceRotBrazoIzq = brazoIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
brazoIzq->agregar(translate(vec3(-1.5, 1.5, 0.0))); // Coloca el brazo en su posición relativa al cuerpo
brazoIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala para definir el tamaño del brazo
brazoIzq->agregar(new CuboCuerpo());
rotacionBrazoIzq = brazoIzq->leerPtrMatriz(indiceRotBrazoIzq);

// Brazo derecho
NodoGrafoEscena* brazoDer = new NodoGrafoEscena();
brazoDer->ponerNombre("Brazo Derecho");
// Primero aplica la rotación, luego la traslación
unsigned indiceRotBrazoDer = brazoDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
brazoDer->agregar(translate(vec3(1.5, 1.5, 0.0))); // Coloca el brazo en su posición relativa al cuerpo
brazoDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala para definir el tamaño del brazo
brazoDer->agregar(new CuboCuerpo());
rotacionBrazoDer = brazoDer->leerPtrMatriz(indiceRotBrazoDer);

    // Piernas
    NodoGrafoEscena* piernaIzq = new NodoGrafoEscena();
    piernaIzq->ponerNombre("Pierna Izquierda");
    unsigned indiceRotPiernaIzq = piernaIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    piernaIzq->agregar(translate(vec3(-0.5, -1.0, 0.0)) * scale(vec3(0.5, 1.5, 0.5)));
    piernaIzq->agregar(new CuboCuerpo());
    rotacionPiernaIzq = piernaIzq->leerPtrMatriz(indiceRotPiernaIzq);

    NodoGrafoEscena* piernaDer = new NodoGrafoEscena();
    piernaDer->ponerNombre("Pierna Derecha");
    unsigned indiceRotPiernaDer = piernaDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    piernaDer->agregar(translate(vec3(0.5, -1.0, 0.0)) * scale(vec3(0.5, 1.5, 0.5)));
    piernaDer->agregar(new CuboCuerpo());
    rotacionPiernaDer = piernaDer->leerPtrMatriz(indiceRotPiernaDer);

    // Agregar al muñeco
    agregar(cuerpo);
    agregar(cabeza);
    agregar(brazoIzq);
    agregar(brazoDer);
    agregar(piernaIzq);
    agregar(piernaDer);
}

unsigned MinecraftMuñeco::leerNumParametros() const {
    return 5;
}

void MinecraftMuñeco::actualizarEstadoParametro(const unsigned iParam, const float tSec) {
    switch (iParam) {
        case 0:
            *rotacionCabeza = rotate(float(M_PI / 4 * sin(tSec)), vec3{0.0, 1.0, 0.0});
            break;
        case 1:
            *rotacionBrazoIzq = rotate(float(M_PI / 4 * sin(tSec)), vec3{1.0, 0.0, 0.0});
            break;
        case 2:
            *rotacionBrazoDer = rotate(float(-M_PI / 4 * sin(tSec)), vec3{1.0, 0.0, 0.0});
            break;
        case 3:
            *rotacionPiernaIzq = rotate(float(M_PI / 8 * sin(tSec)), vec3{1.0, 0.0, 0.0});
            break;
        case 4:
            *rotacionPiernaDer = rotate(float(-M_PI / 8 * sin(tSec)), vec3{1.0, 0.0, 0.0});
            break;
    }
}
