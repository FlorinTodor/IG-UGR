// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C

#ifndef PRUEBA_H
#define PRUEBA_H

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"

// Clase para el cuerpo básico del Among Us
class CuerpoAmongUs : public MallaInd {
public:
    CuerpoAmongUs();
};

class AmongUsMuñeco : public NodoGrafoEscena {
public:
    AmongUsMuñeco();
    unsigned leerNumParametros() const;
    virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

protected:
    // Matrices para las animaciones
    glm::mat4 *rotacionVisor;
    glm::mat4 *rotacionMochila;
    glm::mat4 *movimientoPiernas;
    glm::mat4 *movimientoCuerpo;
};

/*
class CuerpoHelicoptero : public MallaInd {
public:
    CuerpoHelicoptero();
};

class HelicopteroCompleto : public NodoGrafoEscena {
protected:
    glm::mat4 *movimientoCuerpo = nullptr;
    glm::mat4 *rotacionHelicePrincipal = nullptr;
    glm::mat4 *rotacionHeliceCola = nullptr;

public:
    HelicopteroCompleto();
    unsigned leerNumParametros() const override;
    void actualizarEstadoParametro(const unsigned iParam, const float tSec) override;
}; */

#endif