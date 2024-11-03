// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#ifndef REPASO_EXAMEN_HPP
#define REPASO_EXAMEN_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

// REPASO EXAMEN PRÁCTICAS - EXTRA

// PIRÁMIDE
class Piramide : public MallaInd
{
    public:
        Piramide();
};

class NodoPiramide : public NodoGrafoEscena
{
    public:
        NodoPiramide();
};


// TABLERO DE MADERA
class Tablero : public MallaInd
{
    public:
        Tablero();
};

class NodoTablero : public NodoGrafoEscena
{
    public:
        NodoTablero();
};

// PATA DE MADERA
class NodoPata : public NodoGrafoEscena
{
    protected:
        unsigned int num_params = 1;
        glm::mat4 * pm_pata = nullptr;
        glm::vec3 pos_inic;
    public:
        NodoPata(const glm::vec3 traslacion);
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        float fijarMovEsfera(const float min, const float max, const float v, const float t_sec);
    
};

// MESA DE 4 PATAS CON BOLA ENCIMA
class Mesa : public NodoGrafoEscena
{
    protected:
        unsigned int num_params = 2;
        unsigned bola,pata_1,pata_2,pata_3,pata_4;

    public:
        Mesa();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        bool cuandoClick(const glm::vec3 & centro_wc);
};


// BOLA
class Bola : public NodoGrafoEscena
{
    protected:
        const unsigned num_params = 1;
        unsigned contador = 1;
        glm::mat4 * pm_bola = nullptr;

    public:
        Bola();
        bool cuandoClick(const glm::vec3 & centro_wc);
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        glm::vec3 fijarMovEsfera(const float min, const float max, const float v, const float t_sec);

};

// FILAS DE TABLEROS (PARALELAS)
class NodoTablero_BIS : public NodoGrafoEscena
{
    
    protected:
        glm::mat4 * pm_tablero = nullptr;
        unsigned i,j;
        unsigned contador = 1;

    public:
        NodoTablero_BIS(const unsigned num_tablero, const unsigned num_fila);
        bool cuandoClick(const glm::vec3 & centro_wc);
};

class GrafoTableros_V1 : public NodoGrafoEscena
{
    public:
        GrafoTableros_V1(const unsigned nFilas, const unsigned numTabxFil);
};

// CAJA DE MADERA
class Caja : public MallaInd
{
    public:
        Caja();
};

class NodoCaja : public NodoGrafoEscena
{
    protected:
        unsigned int num_params = 1;
        glm::mat4 * pm_caja = nullptr;
        glm::mat4 * pm_bola = nullptr;
        unsigned contador = 1;
    public:
        NodoCaja();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        glm::vec3 fijarMovEsfera(const float min, const float max, const float v, const float t_sec);
};

// Malla barrido respecto del eje Z
class P2Barrido : public MallaInd
{
   public:
      P2Barrido(unsigned m, unsigned n);
};

// Malla barrido respecto del eje X
class P2BarridoX : public MallaInd
{
   public:
      P2BarridoX(unsigned m, unsigned n);
};


// Casa REPASO

class Casa : public MallaInd
{

    public:
        Casa();
};

class NodoCasa : public NodoGrafoEscena
{
    protected:
        unsigned contador = 1;   
    public:
        NodoCasa();
        bool cuandoClick(const glm::vec3 & centro_wc); 
        
};

class NodoBarrio: public NodoGrafoEscena
{ 
    public:
        NodoBarrio(const int nCalles, const int nCasasXCalle);
             
};


// CRUZ REPASO

class NodoCruz : public NodoGrafoEscena
{
    
    protected:
        unsigned int num_params = 1;
        glm::mat4 * pm_suelo = nullptr;

    public:
        NodoCruz();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        bool cuandoClick(const glm::vec3 & centro_wc); 


};

class Suelo : public NodoGrafoEscena
{

    public:
        Suelo();    

};


// Lápiz

class Lapiz : public NodoGrafoEscena
{

    protected:
        unsigned int num_params = 1;
        unsigned contador = 1;
        glm::mat4 * pm_punta   = nullptr;
        glm::mat4 * rot_punta  = nullptr;
        glm::mat4 * pm_tronco  = nullptr;

    public:
        Lapiz();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        float fijarMovLapiz(const float min, const float max, const float v, const float t_sec);
        bool cuandoClick(const glm::vec3 & centro_wc); 

};


// Cubo dado

class Dado : public MallaInd
{

    public:
        Dado();
};

class NodoDado : public NodoGrafoEscena
{

    protected:
        unsigned contador = 1;
        unsigned aux = 1;
        unsigned int num_params = 1;
        glm::mat4 * pm_dado = nullptr;
        glm::mat4 * dado = nullptr;
    public:
        NodoDado();
        unsigned leerNumParametros() const;   //leer número de grados de libertad
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        float fijarMovDado(const float min, const float max, const float v, const float t_sec);
        bool cuandoClick(const glm::vec3 & centro_wc);

};



// Casa tetraédrica

class CasaTetra : public MallaInd
{

    public:
        CasaTetra();
};

class NodoCasaTetra : public NodoGrafoEscena
{

    public:
        NodoCasaTetra();
};


#endif