// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "malla-ind.h"
#include "grafo-escena.h"
#include "malla-revol.h"


class Lata : public NodoGrafoEscena
{
    public:
        Lata(const std::string & archivoTextura);
};

class PeonMadera : public NodoGrafoEscena
{
    protected:
        glm::mat4 * pm_madera = nullptr;
        unsigned contador = 1;

    public:
        PeonMadera();
        bool cuandoClick(const glm::vec3 & centro_wc);
};

class PeonBlanco : public NodoGrafoEscena
{
    protected:
        glm::mat4 * pm_blanco = nullptr;
        unsigned contador = 1;

    public:
        PeonBlanco();
        bool cuandoClick(const glm::vec3 & centro_wc);
};

class PeonNegro : public NodoGrafoEscena
{
    protected:
        glm::mat4 * pm_negro = nullptr;
        unsigned contador = 1;

    public:
        PeonNegro();
        bool cuandoClick(const glm::vec3 & centro_wc);
};

class LataPeones : public NodoGrafoEscena
{
    public:
        LataPeones();
};

class LataCoca : public NodoGrafoEscena
{
    public:
        LataCoca();
};

class LataPepsi : public NodoGrafoEscena
{
    public:
        LataPepsi();
};

class LataUGR : public NodoGrafoEscena
{
    public:
        LataUGR();
};

class Latas : public NodoGrafoEscena
{
    public:
        Latas();
};

class Peones : public NodoGrafoEscena
{
    protected:
        const unsigned num_params = 1;
        unsigned madera;

    public:
        //unsigned leerNumParametros() const;
        //void actualizarEstadoParametro( const unsigned iParam, const float tSec );
        Peones();
};

class VariasLataPeones : public NodoGrafoEscena
{
    protected:
        const unsigned num_params = 1;
        unsigned madera;
        
    public:
        //unsigned leerNumParametros() const;
        //void actualizarEstadoParametro( const unsigned iParam, const float tSec );
        VariasLataPeones();
};

#endif
