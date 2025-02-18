// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"


// EJERCICIO 1 EXAMEN 20/11/2023
class P1MallaCubo : public MallaInd
{

    public:

        P1MallaCubo();

};


// EJERCICIO 2 EXAMEN 20/11/2023
class P2Rejilla : public MallaInd
{

    public:

        P2Rejilla(unsigned m, unsigned n);

};


// EJERCICIO 3 EXAMEN 20/11/2023

class P3Cuadrado : public MallaInd
{
    public:
        P3Cuadrado();
};

class P3Caja : public NodoGrafoEscena
{

    protected:

        unsigned num_params = 2;     // grados de libertad
        glm::mat4* pm_esfera = nullptr;  // matriz esfera
        glm::mat4* pm_hoja1  = nullptr;   // matriz hojas
        glm::mat4* pm_hoja2  = nullptr;
    public:

        P3Caja();     //constructor
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        float fijarMovEsfera(const float min, const float max, const float v, const float t_sec);
        float fijarRotacionHojas(const float min, const float max, const float v, const float t_sec);
    
};
# endif