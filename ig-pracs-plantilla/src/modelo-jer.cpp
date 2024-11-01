// Nombre: Florín Emanuel Todor Gliga Titulación: GIIADE.
// email: flotodor@correo.ugr.es.

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "modelo-jer.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;


CuboCuerpo::CuboCuerpo() {
    // Cubo de 1x2x0.5 centrado en el origen
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
    
}

MinecraftMuñeco::MinecraftMuñeco() {
    ponerNombre("Muñeco de Minecraft");

    // Cuerpo
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("Cuerpo del Muñeco");
    cuerpo->agregar(translate(vec3(0.0, 1.0, 0.0))); // Posición
    cuerpo->agregar(scale(vec3(1.0, 2.0, 0.5))); // Escala
    cuerpo->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el abrigo
    cuerpo->agregar(new CuboCuerpo());

    // Cabeza
    NodoGrafoEscena* cabeza = new NodoGrafoEscena();
    cabeza->ponerNombre("Cabeza del Muñeco");
    unsigned indiceRotCabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0})); // Rotación de la cabeza
    cabeza->agregar(translate(vec3(0.0, 3.0, 0.0))); // Posición de la cabeza
    cabeza->agregar(scale(vec3(1.0, 1.0, 1.0))); // Escala de la cabeza
    cabeza->ponerColor({1.0f, 0.8f, 0.6f}); // Color piel para la cara
    cabeza->agregar(new CuboCuerpo());
    rotacionCabeza = cabeza->leerPtrMatriz(indiceRotCabeza);

    // Sombrero
    NodoGrafoEscena* sombrero = new NodoGrafoEscena();
    sombrero->ponerNombre("Sombrero del Muñeco");
    sombrero->agregar(translate(vec3(0.0, 1.1, 0.0))); // Posición del sombrero encima de la cabeza
    sombrero->agregar(scale(vec3(1.2, 0.4, 1.2))); // Escala del sombrero
    sombrero->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para el sombrero
    sombrero->agregar(new CuboCuerpo());

    // Ojos
    NodoGrafoEscena* ojoIzq = new NodoGrafoEscena();
    ojoIzq->agregar(translate(vec3(-0.3, 0.2, 1.05))); // Posición del ojo izquierdo
    ojoIzq->agregar(scale(vec3(0.2, 0.2, 0.1))); // Escala del ojo izquierdo
    ojoIzq->ponerColor({1.0f, 1.0f, 1.0f}); // Blanco para el ojo izquierdo
    ojoIzq->agregar(new CuboCuerpo());

    NodoGrafoEscena* ojoDer = new NodoGrafoEscena();
    ojoDer->agregar(translate(vec3(0.3, 0.2, 1.05))); // Posición del ojo derecho
    ojoDer->agregar(scale(vec3(0.2, 0.2, 0.1))); // Escala del ojo derecho
    ojoDer->ponerColor({1.0f, 1.0f, 1.0f}); // Blanco para el ojo derecho
    ojoDer->agregar(new CuboCuerpo());

    // Pupilas
    NodoGrafoEscena* pupilaIzq = new NodoGrafoEscena();
    pupilaIzq->agregar(translate(vec3(-0.3, 0.2, 1.15))); // Posición de la pupila izquierda
    pupilaIzq->agregar(scale(vec3(0.1, 0.1, 0.05))); // Escala de la pupila izquierda
    pupilaIzq->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para la pupila izquierda
    pupilaIzq->agregar(new CuboCuerpo());

    NodoGrafoEscena* pupilaDer = new NodoGrafoEscena();
    pupilaDer->agregar(translate(vec3(0.3, 0.2, 1.15))); // Posición de la pupila derecha
    pupilaDer->agregar(scale(vec3(0.1, 0.1, 0.05))); // Escala de la pupila derecha
    pupilaDer->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para la pupila derecha
    pupilaDer->agregar(new CuboCuerpo());

    // Boca
    NodoGrafoEscena* boca = new NodoGrafoEscena();
    boca->agregar(translate(vec3(0.0, -0.2, 1.05))); // Posición de la boca
    boca->agregar(scale(vec3(0.4, 0.1, 0.1))); // Escala de la boca
    boca->ponerColor({1.0f, 0.5f, 0.5f}); // Rosa claro para la boca
    boca->agregar(new CuboCuerpo());

    // Añadir ojos, pupilas, boca y sombrero a la cabeza
    cabeza->agregar(ojoIzq);
    cabeza->agregar(ojoDer);
    cabeza->agregar(pupilaIzq);
    cabeza->agregar(pupilaDer);
    cabeza->agregar(boca);
    cabeza->agregar(sombrero);

    // Brazo izquierdo
    NodoGrafoEscena* hombroIzq = new NodoGrafoEscena();
    hombroIzq->ponerNombre("Hombro Izquierdo");
    hombroIzq->agregar(translate(vec3(-1.5, 1.5, 0.0))); // Posición del hombro izquierdo

    NodoGrafoEscena* brazoIzq = new NodoGrafoEscena();
    brazoIzq->ponerNombre("Brazo Izquierdo");
    unsigned indiceRotBrazoIzq = brazoIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación del brazo izquierdo
    brazoIzq->agregar(translate(vec3(0.0, -0.75, 0.0))); // Posición de la parte inferior del brazo izquierdo
    brazoIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala del brazo izquierdo
    brazoIzq->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo izquierdo
    brazoIzq->agregar(new CuboCuerpo());

    rotacionBrazoIzq = brazoIzq->leerPtrMatriz(indiceRotBrazoIzq);
    hombroIzq->agregar(brazoIzq); // Añade el brazo izquierdo al hombro izquierdo

    // Brazo derecho
    NodoGrafoEscena* hombroDer = new NodoGrafoEscena();
    hombroDer->ponerNombre("Hombro Derecho");
    hombroDer->agregar(translate(vec3(1.5, 1.5, 0.0))); // Posición del hombro derecho

    NodoGrafoEscena* brazoDer = new NodoGrafoEscena();
    brazoDer->ponerNombre("Brazo Derecho");
    unsigned indiceRotBrazoDer = brazoDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación del brazo derecho
    brazoDer->agregar(translate(vec3(0.0, -0.75, 0.0))); // Posición de la parte inferior del brazo derecho
    brazoDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala del brazo derecho
    brazoDer->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo derecho
    brazoDer->agregar(new CuboCuerpo());

    rotacionBrazoDer = brazoDer->leerPtrMatriz(indiceRotBrazoDer);
    hombroDer->agregar(brazoDer); // Añade el brazo derecho al hombro derecho

    // Pierna izquierda
    NodoGrafoEscena* piernaIzq = new NodoGrafoEscena();
    piernaIzq->ponerNombre("Pierna Izquierda");
    unsigned indiceRotPiernaIzq = piernaIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación de la pierna izquierda
    piernaIzq->agregar(translate(vec3(-0.5, -1.0, 0.0))); // Posición de la pierna izquierda
    piernaIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala de la pierna izquierda
    piernaIzq->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna izquierda
    piernaIzq->agregar(new CuboCuerpo());
    rotacionPiernaIzq = piernaIzq->leerPtrMatriz(indiceRotPiernaIzq);

    // Pierna derecha
    NodoGrafoEscena* piernaDer = new NodoGrafoEscena();
    piernaDer->ponerNombre("Pierna Derecha");
    unsigned indiceRotPiernaDer = piernaDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación de la pierna derecha
    piernaDer->agregar(translate(vec3(0.5, -1.0, 0.0))); // Posición de la pierna derecha
    piernaDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala de la pierna derecha
    piernaDer->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna derecha
    piernaDer->agregar(new CuboCuerpo());
    rotacionPiernaDer = piernaDer->leerPtrMatriz(indiceRotPiernaDer);

    // Agregar todas las partes al muñeco
    agregar(cuerpo);
    agregar(cabeza);
    agregar(hombroIzq); // Añade el hombro izquierdo al muñeco
    agregar(hombroDer); // Añade el hombro derecho al muñeco
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
