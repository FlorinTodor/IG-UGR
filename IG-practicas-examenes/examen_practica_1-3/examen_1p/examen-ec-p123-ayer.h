
#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"
//...declaraciones de clases
#endif

using namespace std;
using namespace glm;


class Ejercicio1 : public MallaInd
{
   public:
        Ejercicio1 ();
};

class Ejercicio2 : public MallaInd
{
    public:
        Ejercicio2(int n);
};

class Ejercicio3 : public NodoGrafoEscena
{
    public:
        Ejercicio3(float w, float h);
        unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
    
    protected:
        mat4 *pm_matriz_sca_inferior = nullptr;
        mat4 *pm_matriz_rot_superior = nullptr;
        float h;
};