// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP


#include "malla-ind.h"
#include "malla-revol.h"
#include "grafo-escena.h"
#include <vector>

using namespace glm;
using namespace std;

struct RotationPair {
    float angle;
    glm::vec3 axis;
};

class MolinoAceite : public NodoGrafoEscena
{
 
    protected:
        unsigned num_param = 4;
        unsigned rulo1,rulo2,rulo3,rulo4,palo,alfarje;
        float angle_alfarje_ini, angle_rulos_ini, angle_palo_ini;
        vec3 pos_palo_ini;
        //vector<mat4*> pm_rot_rulos{nullptr};
    
    public:

        MolinoAceite(float angle_alfarje_inic, float angle_rulos_inic, float angle_palo_inic,vec3 pos_palo_inic);
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec); 
    
};

class Solera : public NodoGrafoEscena
{
    public:
       Solera();
};

class Alfarje : public NodoGrafoEscena
{
    protected:
        unsigned num_param = 1;
        float angle_alfarje_ini;
        mat4* rot_alfarje = nullptr;

    public:
       Alfarje( float angle_alfarje_inic);
       void establecerRotacionAlfarje(float time);
       unsigned leerNumParametros() const;
       void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
};

class CiliMolino : public MallaRevol
{
    public:
      CiliMolino(const int num_verts_per,  const unsigned nperfiles, glm::vec3 color);
};

class Rulo : public NodoGrafoEscena
{
    protected:
        unsigned int num_param = 1;
        float angle_rulo_inic;
        mat4* rot_rulo = nullptr;
    
    public:
        Rulo(const vec3 traslacion, const vec3 escalado, const vector<RotationPair> rotaciones);
        void establecerRotacionRulos(float time);
        unsigned int leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned int iParam, const float t_sec);
};

class ConoRulo : public MallaRevol
{
    public:
       ConoRulo(const int num_verts_per, const unsigned nperfiles);

};

class Tolva : public MallaInd
{
    public:
       Tolva();
};

class Palo : public MallaInd
{
    public:
       Palo();

};

class Hierro : public MallaInd
{
    public:
       Hierro();

}; 

class PaloMolino : public NodoGrafoEscena
{
    
    protected:
       unsigned int num_param = 2;
       unsigned palo;
       float angle_palo_ini;
       vec3 pos_palo_ini;
       mat4x4* pos_palo = nullptr;
       mat4x4* rot_palo = nullptr;

    public:
       PaloMolino(float angle_palo_inic, vec3 pos_palo_inic);
       void establecerRotacionPalo(float time);
       void establecerPosicionPalo(vec3 pos);
       unsigned int leerNumeroParametros() const;
       void actualizarEstadoParametro(const unsigned int iParam, const float t_sec);

};


#endif // MODELO_JER_HPP