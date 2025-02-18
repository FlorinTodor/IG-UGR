// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

// EJERCICIO 4 EXAMEN 19/01/2024

class MallaP4 : public MallaInd
{
    public:
        MallaP4();
};

class NodoP4 : public NodoGrafoEscena
{
    protected:
        glm::mat4 * matrix = nullptr;
        unsigned contador = 1;
    public:
        NodoP4(const std::string & archivoTextura);
        bool cuandoClick(const glm::vec3 & centro_wc);

};

// EJERCICIO 5 EXAMEN 19/01/2024

class NodoUrbaP5: public NodoGrafoEscena
{ 
    public:
        NodoUrbaP5(const std::string & archivoTextura, const int n);
             
};





#endif