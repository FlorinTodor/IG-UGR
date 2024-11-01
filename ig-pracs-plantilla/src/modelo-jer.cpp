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
    cuerpo->agregar(translate(vec3(0.0, 1.0, 0.0)) * scale(vec3(1.0, 2.0, 0.5)));
    cuerpo->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el abrigo
    cuerpo->agregar(new CuboCuerpo());

    // Cabeza

    NodoGrafoEscena* cabeza = new NodoGrafoEscena();
    cabeza->ponerNombre("Cabeza del Muñeco");
    unsigned indiceRotCabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0}));
    cabeza->agregar(translate(vec3(0.0, 3.0, 0.0)) * scale(vec3(1.0, 1.0, 1.0)));
    cabeza->agregar(new CuboCuerpo());
    cabeza->ponerColor({1.0f, 0.8f, 0.6f}); // Color piel para la cara
    rotacionCabeza = cabeza->leerPtrMatriz(indiceRotCabeza);

    // Sombrero (colocado encima de la cabeza)

    NodoGrafoEscena* sombrero = new NodoGrafoEscena();
    sombrero->ponerNombre("Sombrero del Muñeco");
    // Posiciona el sombrero justo encima de la cabeza y lo hace un poco más ancho
    sombrero->agregar(translate(vec3(0.0, 1.1, 0.0)) * scale(vec3(1.2, 0.4, 1.2)));
    sombrero->ponerColor({0.0f, 0.0f, 0.0f}); // Color negro para el sombrero
    sombrero->agregar(new CuboCuerpo());


    // Ojos (dos cubos pequeños en el frente de la cabeza)
    NodoGrafoEscena* ojoIzq = new NodoGrafoEscena();
    ojoIzq->agregar(translate(vec3(-0.3, 0.2, 1.05)) * scale(vec3(0.2, 0.2, 0.1)));
    ojoIzq->ponerColor({1.0f, 1.0f, 1.0f}); // Color blanco para los ojos
    ojoIzq->agregar(new CuboCuerpo());

    NodoGrafoEscena* ojoDer = new NodoGrafoEscena();
    ojoDer->agregar(translate(vec3(0.3, 0.2, 1.05)) * scale(vec3(0.2, 0.2, 0.1)));
    ojoDer->ponerColor({1.0f, 1.0f, 1.0f}); // Color blanco para los ojos
    ojoDer->agregar(new CuboCuerpo());

    // Pupilas (cubos pequeños en el centro de cada ojo)
    NodoGrafoEscena* pupilaIzq = new NodoGrafoEscena();
    pupilaIzq->agregar(translate(vec3(-0.3, 0.2, 1.15)) * scale(vec3(0.1, 0.1, 0.05)));
    pupilaIzq->ponerColor({0.0f, 0.0f, 0.0f}); // Color negro para las pupilas
    pupilaIzq->agregar(new CuboCuerpo());

    NodoGrafoEscena* pupilaDer = new NodoGrafoEscena();
    pupilaDer->agregar(translate(vec3(0.3, 0.2, 1.15)) * scale(vec3(0.1, 0.1, 0.05)));
    pupilaDer->ponerColor({0.0f, 0.0f, 0.0f}); // Color negro para las pupilas
    pupilaDer->agregar(new CuboCuerpo());


    // Boca (un cubo pequeño en la parte baja del frente de la cabeza)
    NodoGrafoEscena* boca = new NodoGrafoEscena();
    boca->agregar(translate(vec3(0.0, -0.2, 1.05)) * scale(vec3(0.4, 0.1, 0.1)));
    boca->ponerColor({1.0f, 0.5f, 0.5f}); // Rosa claro para la boca
    boca->agregar(new CuboCuerpo());

    // Añadir ojos y boca a la cabeza
    cabeza->agregar(ojoIzq);
    cabeza->agregar(sombrero);
    cabeza->agregar(pupilaIzq);
    cabeza->agregar(pupilaDer);
    cabeza->agregar(ojoDer);
    cabeza->agregar(boca);


    // Brazos
        // Brazo izquierdo
    NodoGrafoEscena* hombroIzq = new NodoGrafoEscena();
    hombroIzq->ponerNombre("Hombro Izquierdo");
    hombroIzq->agregar(translate(vec3(-1.5, 1.5, 0.0))); // Posición del hombro en el cuerpo

    NodoGrafoEscena* brazoIzq = new NodoGrafoEscena();
    brazoIzq->ponerNombre("Brazo Izquierdo");
    // Aplica la rotación en el punto de unión, luego traslada la parte inferior
    unsigned indiceRotBrazoIzq = brazoIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    brazoIzq->agregar(translate(vec3(0.0, -0.75, 0.0))); // Baja desde el punto de rotación
    brazoIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Tamaño del brazo
    brazoIzq->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo
    brazoIzq->agregar(new CuboCuerpo());

    rotacionBrazoIzq = brazoIzq->leerPtrMatriz(indiceRotBrazoIzq);
    hombroIzq->agregar(brazoIzq); // Añade el brazo al hombro
    agregar(hombroIzq); // Añade el hombro al muñeco

    // Brazo derecho
    NodoGrafoEscena* hombroDer = new NodoGrafoEscena();
    hombroDer->ponerNombre("Hombro Derecho");
    hombroDer->agregar(translate(vec3(1.5, 1.5, 0.0))); // Posición del hombro en el cuerpo

    NodoGrafoEscena* brazoDer = new NodoGrafoEscena();
    brazoDer->ponerNombre("Brazo Derecho");
    // Aplica la rotación en el punto de unión, luego traslada la parte inferior
    unsigned indiceRotBrazoDer = brazoDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    brazoDer->agregar(translate(vec3(0.0, -0.75, 0.0))); // Baja desde el punto de rotación
    brazoDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Tamaño del brazo
    brazoDer->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo
    brazoDer->agregar(new CuboCuerpo());

    rotacionBrazoDer = brazoDer->leerPtrMatriz(indiceRotBrazoDer);
    hombroDer->agregar(brazoDer); // Añade el brazo al hombro
    agregar(hombroDer); // Añade el hombro al muñeco

    // Pierna izquierda
    NodoGrafoEscena* piernaIzq = new NodoGrafoEscena();
    piernaIzq->ponerNombre("Pierna Izquierda");
    // Asegura que la rotación esté en el punto superior de la pierna
    unsigned indiceRotPiernaIzq = piernaIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    piernaIzq->agregar(translate(vec3(-0.5, -1.0, 0.0)) * scale(vec3(0.5, 1.5, 0.5)));
    piernaIzq->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna
    piernaIzq->agregar(new CuboCuerpo());
    rotacionPiernaIzq = piernaIzq->leerPtrMatriz(indiceRotPiernaIzq);

    // Pierna derecha
    NodoGrafoEscena* piernaDer = new NodoGrafoEscena();
    piernaDer->ponerNombre("Pierna Derecha");
    // Asegura que la rotación esté en el punto superior de la pierna
    unsigned indiceRotPiernaDer = piernaDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0}));
    piernaDer->agregar(translate(vec3(0.5, -1.0, 0.0)) * scale(vec3(0.5, 1.5, 0.5)));
    piernaDer->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna
    piernaDer->agregar(new CuboCuerpo());
    rotacionPiernaDer = piernaDer->leerPtrMatriz(indiceRotPiernaDer);

    // Agregar al muñeco
    agregar(cuerpo);
    agregar(cabeza);
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
