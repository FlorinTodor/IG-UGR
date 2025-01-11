// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "modelo-jer.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

/* Los brazos no van a tener la generación de coordenadas de textura para que se genere automáticamente como se nos solicita*/

CuboBrazos::CuboBrazos(){
     vertices =
      {
         {+1.0, -1.0, +1.0}, // 0
         {+1.0, +1.0, +1.0}, // 1
         {+1.0, +1.0, -1.0}, // 2
         {+1.0, -1.0, -1.0}, // 3


         {-1.0, -1.0, +1.0}, // 4
         {-1.0, +1.0, +1.0}, // 5
         {+1.0, +1.0, +1.0}, // 6
         {+1.0, -1.0, +1.0}, // 7


         {-1.0, -1.0, -1.0}, // 8
         {-1.0, +1.0, -1.0}, // 9
         {-1.0, +1.0, +1.0}, // 10
         {-1.0, -1.0, +1.0}, // 11

         {+1.0, -1.0, -1.0}, // 12
         {+1.0, +1.0, -1.0}, // 13
         {-1.0, +1.0, -1.0}, // 14
         {-1.0, -1.0, -1.0}, // 15


         {+1.0, +1.0, +1.0}, // 16
         {-1.0, +1.0, +1.0}, // 17
         {-1.0, +1.0, -1.0}, // 18
         {+1.0, +1.0, -1.0}, // 19

         {+1.0, -1.0, +1.0}, // 20
         {-1.0, -1.0, +1.0}, // 21
         {-1.0, -1.0, -1.0}, // 22
         {+1.0, -1.0, -1.0}  // 23
      };

   triangulos =
      {
         {0, 3, 2},
         {0, 2, 1},

         {4, 7, 6},
         {4, 6, 5},

         {8, 11, 10},
         {8, 10, 9},

         {12, 15, 14},
         {12, 14, 13},

         {16, 19, 18},
         {16, 18, 17},

         {20, 22, 23},
         {20, 21, 22}
      };

       calcularNormales();

}
CuboCuerpo::CuboCuerpo() {
    // 24 vértices: 6 caras * 4 vértices por cara
    // Usamos las mismas coordenadas que en tu cubo 1x2x0.5 (centrado),
    // pero replicadas para que cada cara tenga sus propios 4 vértices.

     vertices =
      {
         {+1.0, -1.0, +1.0}, // 0
         {+1.0, +1.0, +1.0}, // 1
         {+1.0, +1.0, -1.0}, // 2
         {+1.0, -1.0, -1.0}, // 3


         {-1.0, -1.0, +1.0}, // 4
         {-1.0, +1.0, +1.0}, // 5
         {+1.0, +1.0, +1.0}, // 6
         {+1.0, -1.0, +1.0}, // 7


         {-1.0, -1.0, -1.0}, // 8
         {-1.0, +1.0, -1.0}, // 9
         {-1.0, +1.0, +1.0}, // 10
         {-1.0, -1.0, +1.0}, // 11

         {+1.0, -1.0, -1.0}, // 12
         {+1.0, +1.0, -1.0}, // 13
         {-1.0, +1.0, -1.0}, // 14
         {-1.0, -1.0, -1.0}, // 15


         {+1.0, +1.0, +1.0}, // 16
         {-1.0, +1.0, +1.0}, // 17
         {-1.0, +1.0, -1.0}, // 18
         {+1.0, +1.0, -1.0}, // 19

         {+1.0, -1.0, +1.0}, // 20
         {-1.0, -1.0, +1.0}, // 21
         {-1.0, -1.0, -1.0}, // 22
         {+1.0, -1.0, -1.0}  // 23
      };

   triangulos =
      {
         {0, 3, 2},
         {0, 2, 1},

         {4, 7, 6},
         {4, 6, 5},

         {8, 11, 10},
         {8, 10, 9},

         {12, 15, 14},
         {12, 14, 13},

         {16, 19, 18},
         {16, 18, 17},

         {20, 22, 23},
         {20, 21, 22}
      };
      
      
  cc_tt_ver = {
      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0}
   };


    calcularNormales();
}

MinecraftMuñeco::MinecraftMuñeco() {
    ponerNombre("Muñeco de Minecraft");

    unsigned identCuerpo = 1;
    unsigned identSombrero = 2;
    unsigned identBrazoIzq = 3;
    unsigned identBrazoDer = 4;
    unsigned identPiernaIzq = 5;
    unsigned identPiernaDer = 6;
    unsigned identCabeza = 7;

    // Cuerpo
    NodoGrafoEscena* cuerpo = new NodoGrafoEscena();
    Textura * TexturaCuerpo = new Textura("ropa.jpg");
    Material * MaterialCuerpo = new Material(TexturaCuerpo,0.5, 0.0, 0.05, 50);
    unsigned indiceTraslacionCuerpo = agregar(translate(vec3(0.0f, 0.0f, 0.0f)));
    movimientoCuerpo = leerPtrMatriz(indiceTraslacionCuerpo);
    cuerpo->ponerNombre("Cuerpo del Muñeco");
    cuerpo->agregar(translate(vec3(0.0, 1.0, 0.0))); // Posición
    cuerpo->agregar(scale(vec3(1.0, 2.0, 0.5))); // Escala
    cuerpo->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el abrigo
    cuerpo->ponerIdentificador(identCuerpo);
    cuerpo->agregar(MaterialCuerpo);
    cuerpo->agregar(new CuboCuerpo());

    // Cabeza
    NodoGrafoEscena* cabeza = new NodoGrafoEscena();
    cabeza->ponerNombre("Cabeza del Muñeco");
    unsigned indiceRotCabeza = cabeza->agregar(rotate(0.0f, vec3{0.0, 1.0, 0.0})); // Rotación de la cabeza
    cabeza->agregar(translate(vec3(0.0, 3.0, 0.0))); // Posición de la cabeza
    cabeza->agregar(scale(vec3(1.0, 1.0, 1.0))); // Escala de la cabeza
    cabeza->ponerColor({1.0f, 0.8f, 0.6f}); // Color piel para la cara
    cabeza->ponerIdentificador(identCabeza);
    cabeza->agregar(new CuboCuerpo());
    rotacionCabeza = cabeza->leerPtrMatriz(indiceRotCabeza);

    // Sombrero
    NodoGrafoEscena* sombrero = new NodoGrafoEscena();
    Material * MaterialSombrero = new Material(0.5, 0.0, 0.05, 50);
    sombrero->ponerNombre("Sombrero del Muñeco");
    sombrero->agregar(translate(vec3(0.0, 1.1, 0.0))); // Posición del sombrero encima de la cabeza
    sombrero->agregar(scale(vec3(1.2, 0.4, 1.2))); // Escala del sombrero
    sombrero->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para el sombrero
    sombrero->agregar(MaterialSombrero);
    sombrero->ponerIdentificador(-1);
    sombrero->agregar(new CuboCuerpo());

    // Ojo Izquierdo y Pupila
    NodoGrafoEscena* ojoIzq = new NodoGrafoEscena();
    ojoIzq->ponerNombre("Ojo Izquierdo");
    ojoIzq->agregar(translate(vec3(-0.3, 0.2, 1.05))); // Posición del ojo izquierdo
    ojoIzq->agregar(scale(vec3(0.2, 0.2, 0.1))); // Escala del ojo izquierdo
    ojoIzq->ponerIdentificador(-1);
    ojoIzq->ponerColor({1.0f, 1.0f, 1.0f}); // Blanco para el ojo izquierdo
    ojoIzq->agregar(new CuboCuerpo());

    NodoGrafoEscena* pupilaIzq = new NodoGrafoEscena();
    pupilaIzq->ponerNombre("Pupila Izquierda");
    pupilaIzq->agregar(translate(vec3(0.0, 0.0, 1.1))); // Posición de la pupila en el ojo
    pupilaIzq->agregar(scale(vec3(0.5, 0.5, 0.5))); // Escala de la pupila
    pupilaIzq->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para la pupila
    pupilaIzq->ponerIdentificador(-1);
    pupilaIzq->agregar(new CuboCuerpo());

    ojoIzq->agregar(pupilaIzq); // Añadir pupila al ojo izquierdo

    // Ojo Derecho y Pupila
    NodoGrafoEscena* ojoDer = new NodoGrafoEscena();
    ojoDer->ponerNombre("Ojo Derecho");
    ojoDer->agregar(translate(vec3(0.3, 0.2, 1.05))); // Posición del ojo derecho
    ojoDer->agregar(scale(vec3(0.2, 0.2, 0.1))); // Escala del ojo derecho
    ojoDer->ponerColor({1.0f, 1.0f, 1.0f}); // Blanco para el ojo derecho
    ojoDer->ponerIdentificador(-1);
    ojoDer->agregar(new CuboCuerpo());

    NodoGrafoEscena* pupilaDer = new NodoGrafoEscena();
    pupilaDer->ponerNombre("Pupila Derecha");
    pupilaDer->agregar(translate(vec3(0.0, 0.0, 1.1))); // Posición de la pupila en el ojo
    pupilaDer->agregar(scale(vec3(0.5, 0.5, 0.5))); // Escala de la pupila
    pupilaDer->ponerColor({0.0f, 0.0f, 0.0f}); // Negro para la pupila
    pupilaDer->ponerIdentificador(-1);
    pupilaDer->agregar(new CuboCuerpo());

    ojoDer->agregar(pupilaDer); // Añadir pupila al ojo derecho

    // Boca
    NodoGrafoEscena* boca = new NodoGrafoEscena();
    boca->ponerNombre("Boca");
    boca->agregar(translate(vec3(0.0, -0.2, 1.05))); // Posición de la boca
    boca->agregar(scale(vec3(0.4, 0.1, 0.1))); // Escala de la boca
    boca->ponerColor({1.0f, 0.5f, 0.5f}); // Rosa claro para la boca
    boca->ponerIdentificador(-1);
    boca->agregar(new CuboCuerpo());

    // Añadir componentes a la cabeza
    cabeza->agregar(ojoIzq);     // Añadir ojo izquierdo (con pupila) a la cabeza
    cabeza->agregar(ojoDer);     // Añadir ojo derecho (con pupila) a la cabeza
    cabeza->agregar(boca);       // Añadir boca a la cabeza
    cabeza->agregar(sombrero);   // Añadir sombrero a la cabeza

    // Brazo izquierdo
    // Nodo para mover todo el cuerpo hacia adelante y atrás
    
    NodoGrafoEscena* hombroIzq = new NodoGrafoEscena();
    

    hombroIzq->ponerNombre("Hombro Izquierdo");
    hombroIzq->agregar(translate(vec3(-1.5, 1.5, 0.0))); // Posición del hombro izquierdo

    NodoGrafoEscena* brazoIzq = new NodoGrafoEscena();
    TexturaXY * TexturaBrazoIzq = new TexturaXY("ropa.jpg");
    Material * MaterialBrazoIzq = new Material(TexturaBrazoIzq,0.5, 0.85, 0.05, 20);
    brazoIzq->ponerNombre("Brazo Izquierdo");
    unsigned indiceRotBrazoIzq = brazoIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación del brazo izquierdo, rota en el eje X
    brazoIzq->agregar(translate(vec3(0.0, -0.75, 0.0))); // Posición de la parte inferior del brazo izquierdo
    brazoIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala del brazo izquierdo
    brazoIzq->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo izquierdo
    brazoIzq->agregar(MaterialBrazoIzq);
    brazoIzq->ponerIdentificador(identBrazoIzq);
    brazoIzq->agregar(new CuboBrazos());

    rotacionBrazoIzq = brazoIzq->leerPtrMatriz(indiceRotBrazoIzq);
    hombroIzq->agregar(brazoIzq); // Añade el brazo izquierdo al hombro izquierdo

    // Brazo derecho
    NodoGrafoEscena* hombroDer = new NodoGrafoEscena();
    hombroDer->ponerNombre("Hombro Derecho");
    hombroDer->agregar(translate(vec3(1.5, 1.5, 0.0))); // Posición del hombro derecho

    NodoGrafoEscena* brazoDer = new NodoGrafoEscena();
    TexturaXY * TexturaBrazoDer = new TexturaXY("ropa.jpg");
    Material * MaterialBrazoDer = new Material(TexturaBrazoDer,0.5, 0.85, 0.05, 20);
    brazoDer->ponerNombre("Brazo Derecho");
    unsigned indiceRotBrazoDer = brazoDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación del brazo derecho
    brazoDer->agregar(translate(vec3(0.0, -0.75, 0.0))); // Posición de la parte inferior del brazo derecho
    brazoDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala del brazo derecho
    brazoDer->ponerColor({0.5f, 0.0f, 0.0f}); // Rojo oscuro para el brazo derecho
    brazoDer->agregar(MaterialBrazoDer);
    brazoDer->ponerIdentificador(identBrazoDer);
    brazoDer->agregar(new CuboBrazos());

    rotacionBrazoDer = brazoDer->leerPtrMatriz(indiceRotBrazoDer);
    hombroDer->agregar(brazoDer); // Añade el brazo derecho al hombro derecho

    // Pierna izquierda
    NodoGrafoEscena* piernaIzq = new NodoGrafoEscena();
    Textura * TexturaPiernaIzq = new Textura("piernas.jpg");
    Material * MaterialPiernaIzq = new Material(TexturaPiernaIzq,0.75, 0.85, 0.75, 50);
    piernaIzq->ponerNombre("Pierna Izquierda");
    unsigned indiceRotPiernaIzq = piernaIzq->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación de la pierna izquierda
    piernaIzq->agregar(translate(vec3(-0.5, -1.0, 0.0))); // Posición de la pierna izquierda
    piernaIzq->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala de la pierna izquierda
    piernaIzq->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna izquierda
    piernaIzq->agregar(MaterialPiernaIzq);
    piernaIzq->ponerIdentificador(identPiernaIzq);
    piernaIzq->agregar(new CuboCuerpo());
    rotacionPiernaIzq = piernaIzq->leerPtrMatriz(indiceRotPiernaIzq);

    // Pierna derecha
    NodoGrafoEscena* piernaDer = new NodoGrafoEscena();
    Textura * TexturaPiernaDer = new Textura("piernas.jpg");
    Material * MaterialPiernaDer = new Material(TexturaPiernaDer,0.75, 0.85, 0.5, 50);
    piernaDer->ponerNombre("Pierna Derecha");
    unsigned indiceRotPiernaDer = piernaDer->agregar(rotate(0.0f, vec3{1.0, 0.0, 0.0})); // Rotación de la pierna derecha
    piernaDer->agregar(translate(vec3(0.5, -1.0, 0.0))); // Posición de la pierna derecha
    piernaDer->agregar(scale(vec3(0.5, 1.5, 0.5))); // Escala de la pierna derecha
    piernaDer->ponerColor({0.3f, 0.15f, 0.1f}); // Marrón oscuro para la pierna derecha
    piernaDer->agregar(MaterialPiernaDer);
    piernaDer->ponerIdentificador(identPiernaDer);
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
    return 6;
}

void MinecraftMuñeco::actualizarEstadoParametro(const unsigned iParam, const float tSec) {
     assert(iParam < leerNumParametros());
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
        case 5:
            *movimientoCuerpo = translate(vec3(0.0f, 0.0f, sin(tSec)));
            break;
}

    }
