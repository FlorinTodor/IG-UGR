// Nombre: Florín Emanuel Todor Gliga Titulación: GIIADE.
// email: flotodor@correo.ugr.es.

#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

class CuboCuerpo : public MallaInd {
public:
    CuboCuerpo();
};

class MinecraftMuñeco : public NodoGrafoEscena {
public:
    MinecraftMuñeco();
    unsigned leerNumParametros() const;
    virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

protected:
    glm::mat4 *rotacionCabeza;
    glm::mat4 *rotacionBrazoIzq;
    glm::mat4 *rotacionBrazoDer;
    glm::mat4 *rotacionPiernaIzq;
    glm::mat4 *rotacionPiernaDer;
};

#endif // MODELO_JER_H
