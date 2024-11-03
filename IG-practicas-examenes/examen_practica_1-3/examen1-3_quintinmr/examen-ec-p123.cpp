// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q

#include "examen-ec-p123.h"

using namespace glm;
using namespace std;


// EJERCICIO 1 - EXAMEN 20/11/2023
// ****************************************************************************
// Clase 'CuboColores

P1MallaCubo::P1MallaCubo()
:  MallaInd( "P1 malla cubo" )
{
 
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { +0.0, +1.0, +0.0},  // 8: VÉRTICE CENTRAL CARA SUPERIOR
         { +0.0, -1.0, +0.0}   // 9: VÉRTICE CENTRAL CARA IFERIOR
      } ;



   triangulos =
      {  
        {0,1,3}, {0,3,2}, // X-
         {5,4,7}, {4,6,7}, // X+ (+4)

         // TRIÁNGULOS CARA SUPERIOR
         {3,7,8}, {7,6,8},
         {2,3,8}, {6,2,8},

         // TRIÁNGULOS CARA INFERIOR
         {1,5,9}, {5,4,9},
         {0,1,9}, {4,0,9},

         {4,0,2}, {4,2,6}, // Z-
         {1,5,3}, {5,7,3}  // Z+ (+1)

      } ;

   col_ver = 
      {
         { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, +1.0 }, // 1
         { 0.0, +1.0, 0.0 }, // 2
         { 0.0, +1.0, +1.0 }, // 3
         { +1.0, 0.0, 0.0 }, // 4
         { +1.0, 0.0, +1.0 }, // 5
         { +1.0, +1.0, 0.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { +1.0, 0.0, 0.0},    // COLOR VÉRTICE SUPERIOR
         { 0.0, +1.0, +1.0}   // COLOR VÉRTICE SUPERIOR

      };

}

// EJERCICIO 2 EXAMEN 20/11/2023

P2Rejilla::P2Rejilla
(   
    unsigned m,  // número de vértices 
    unsigned n   // número de filas de la rejilla

)
{   

    assert(n>=2 and m>=2);

    for (unsigned i = 0; i < m; i++)
    {
        for (unsigned j = 0; j < n; j++)
        {
            float factor = 1 + 3*float(i)/(m-1); 
            vertices.push_back({factor*float(j)/(n-1), 0, 1.4*float(i)/(m-1)});
        }
    }  

    for (unsigned i = 0; i < m-1; i++ ){
      for (unsigned j = 0; j < n-1; j++){
        if ((i+j) % 2 == 0) 
        {
            triangulos.push_back({i*n+j, (i+1)*n+j, (i+1)*n+j+1});
            triangulos.push_back({i*n+j, (i+1)*n+j+1, i*n+j+1});
        }
        else 
        {
            triangulos.push_back({i*n+j, (i+1)*n+j, i*n+j+1});
            triangulos.push_back({i*n+j+1, (i+1)*n+j, (i+1)*n+j+1});
        }

      }
   }


}


// EJERCICIO 3 EXAMEN 20/11/2023
P3Cuadrado::P3Cuadrado()
{
    vertices = 
    {
        {-1.0,0.0,-1.0},
        {-1.0,0.0,+1.0},
        {+1.0,0.0,-1.0},
        {+1.0,0.0,+1.0}
    };

    triangulos=
    {
        {0,1,3},
        {0,3,2}
    };

}


P3Caja::P3Caja()
{

    agregar(new P3Cuadrado());
    
    NodoGrafoEscena * hoja = new NodoGrafoEscena();
    hoja->agregar(translate(vec3(0.0,1.0,0.0)));
    hoja->agregar(scale(vec3(0.5,1.0,1.0)));
    hoja->agregar(rotate(radians(-90.0f), vec3(0.0,1.0,0.0)));
    hoja->agregar(new P3Cuadrado());

    NodoGrafoEscena * hoja1 = new NodoGrafoEscena();
    unsigned i = hoja1->agregar(rotate(radians(0.0f), vec3(0.0,0.0,1.0)));
    hoja1->agregar(translate(vec3(-0.5,0.0,0.0)));
    hoja1->agregar(hoja);

    agregar(hoja1);

    NodoGrafoEscena * hoja2 = new NodoGrafoEscena();
    unsigned k = hoja2->agregar(rotate(radians(0.0f), vec3(0.0,0.0,1.0)));
    hoja2->agregar(translate(vec3(0.5,0.0,0.0)));
    hoja2->agregar(hoja);

    agregar(hoja2);

    NodoGrafoEscena * hoja3 = new NodoGrafoEscena();
    hoja3->agregar(rotate(radians(-90.0f),vec3(1.0,0.0,0.0)));
    hoja3->agregar(scale(vec3(1.0,1.0,0.5)));
    hoja3->agregar(translate(vec3(0.0,-1.0,1.0)));
    
    hoja3->agregar(new P3Cuadrado());

    agregar(hoja3);

    agregar(translate(vec3(0.0,0.0,-2.0)));
    agregar(hoja3);

    agregar(rotate(radians(90.0f),vec3(0.0,1.0,0.0)));
    agregar(translate(vec3(-2.0,0.0,0.0)));
    agregar(hoja3);

    agregar(rotate(radians(-180.0f),vec3(0.0,1.0,0.0)));
    agregar(translate(vec3(0.0,0.0,0.0)));
    agregar(hoja3);

    pm_hoja1 = hoja1->leerPtrMatriz(i); 
    pm_hoja2 = hoja2->leerPtrMatriz(k);

    NodoGrafoEscena * esfera = new NodoGrafoEscena();
    unsigned j = esfera->agregar(translate(vec3(0.0,0.0,0.0)));
    esfera->agregar(scale(vec3(0.25,0.20,0.25)));
    esfera->agregar(translate(vec3(0.0,1.0,0.0)));
    esfera->agregar(new Esfera(50,50));
    agregar(esfera);

    pm_esfera = esfera->leerPtrMatriz(j);
    
    
}

unsigned P3Caja::leerNumParametros() const   //leer número de grados de libertad
{
    return num_params;
}
        
void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    switch (iParam)
    {
    case 0:
        
        *pm_hoja1 = rotate(radians(90.0f*sinf(M_PI*1*t_sec)), vec3(0.0,0.0,1.0));
        *pm_hoja2 = rotate(radians(-90.0f*sinf(M_PI*1*t_sec)), vec3(0.0,0.0,1.0));

        break;
    
    case 1:
        float p = fijarMovEsfera(0.0,3.0,1.0,t_sec);
        *pm_esfera = translate(vec3(0.0,p,0.0));
        break;
    }
}

float P3Caja::fijarMovEsfera(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    return( a+b*sin(2*M_PI*v*t_sec) );
}

