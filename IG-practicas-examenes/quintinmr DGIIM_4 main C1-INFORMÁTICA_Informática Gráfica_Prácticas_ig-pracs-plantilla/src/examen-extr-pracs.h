// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#ifndef EXAMEN_EXTR_PRACS_HPP
#define EXAMEN_EXTR_PRACS_HPP

#include "malla-ind.h"
#include "malla-revol.h"
#include "grafo-escena.h"

// EJERCICIO 1 - EXAMEN 06/02/2024
class P1Malla : public MallaInd
{

    public:
        P1Malla();
};


// EJERCICIO 2 - EXAMEN 06/02/2024
class P2Fuente : public MallaRevol
{

    public:
        P2Fuente(unsigned n, unsigned m);
};

class P2Anillo : public MallaRevol
{

    public:
        P2Anillo(unsigned n, unsigned m, unsigned w);
};

// EJERCICIO 3 - EXAMEN 06/02/2024
class P3Rotonda : public NodoGrafoEscena
{

    protected:
        unsigned int num_params = 2;
        glm::mat4 * pm_circ1 = nullptr;
        glm::mat4 * pm_circ2 = nullptr;
    public:
        P3Rotonda();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        void fijarMovCoche(glm::vec3 pos);
};


// EJERCICIO 4 - EXAMEN 06/02/2024
class P4Rotonda : public NodoGrafoEscena
{

    public:
        P4Rotonda();

};

// EJERCICIO 5 - EXAMEN 06/02/2024

class NodoFuente : public NodoGrafoEscena
{
    public:
        NodoFuente();
        bool cuandoClick(const glm::vec3 & centro_wc);
};

class P5Rotonda : public NodoGrafoEscena
{

    public:
        P5Rotonda();

};



#endif