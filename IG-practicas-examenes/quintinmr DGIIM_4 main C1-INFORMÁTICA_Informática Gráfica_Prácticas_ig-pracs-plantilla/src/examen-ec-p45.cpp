// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#include "examen-ec-p45.h"
#include <iostream>

// Objeto Malla P4
MallaP4::MallaP4()   
: MallaInd( "Malla p4" )
{

    vertices =
      {  {-1.0,-1.0,+1.0}, // 0    
         { +1.0, -1.0, +1.0 }, // 1
         { +1.0, -1.0, -1.0 }, // 2
         { -1.0, -1.0, -1.0 }, // 3

         {-1.0,-1.0,+1.0}, // 0 -- 4
         { +1.0, -1.0, +1.0 }, // 1 -- 5
         { +1.0, +1.0, +1.0 }, // 5 -- 6
         { -1.0, +1.0, +1.0 }, // 4 -- 7
         
         { +1.0, -1.0, +1.0 }, // 1 -- 8
         { +1.0, -1.0, -1.0 }, // 2 -- 9
         { +1.0, +1.0, -1.0 }, // 6 -- 10
         { +1.0, +1.0, +1.0 }, // 5 -- 11

         { +1.0, -1.0, -1.0 }, // 2 -- 12
         { -1.0, -1.0, -1.0 }, // 3 -- 13
         { -1.0, +1.0, -1.0 }, // 7 -- 14
         { +1.0, +1.0, -1.0 }, // 6 -- 15
        
         { -1.0, -1.0, -1.0 }, // 3 -- 16
         { -1.0, -1.0, +1.0},  // 0 -- 17
         { -1.0, +1.0, +1.0 }, // 4 -- 18
         { -1.0, +1.0, -1.0 }, // 7 -- 19
         
         { -1.0, +1.0, +1.0 }, // 4 -- 20
         { +1.0, +1.0, +1.0 }, // 5 -- 21
         { 0.0,  +2.0, 0.0 },  // 8 -- 22

         { +1.0, +1.0, +1.0 }, // 5 -- 23
         { +1.0, +1.0, -1.0 }, // 6 -- 24
         { 0.0,  +2.0, 0.0 },  // 8 -- 25

         { +1.0, +1.0, -1.0 }, // 6 -- 26
         { -1.0, +1.0, -1.0 }, // 7 -- 27
         { 0.0,  +2.0, 0.0 },  // 8 -- 28

         { -1.0, +1.0, -1.0 }, // 7 -- 29
         { -1.0, +1.0, +1.0 }, // 4 -- 30
         { 0.0,  +2.0, 0.0 },  // 8 -- 31
         
      } ;


    triangulos=
    {
        {0,1,2},{0,2,3},

        {4,5,7}, {5,6,7},

        {8,9,11}, {9,10,11},

        {12,13,14}, {12,14,15},

        {16,17,18}, {16,18,19},

        {20,21,22}, {23,24,25},

        {26,27,28}, {29,30,31},
        
    }; 

    cc_tt_ver = 
    {  
        
        // cara de abajo
        {0.25,0.5},
        {0.5,0.5},
        {0.5,0.0},
        {0.25,0.0},

        // cara de en frente
        {0.0,1.0},
        {0.25,1.0},
        {0.25,0.5},
        {0.0,0.5},

        // cara derecha
        {0.25,1.0},
        {0.5,1.0},
        {0.5,0.5},
        {0.25,0.5},

        // cara de atrás
        {0.5,1.0},
        {0.75,1.0},
        {0.75,0.5},
        {0.5,0.5},

        // cara izquierda
        {0.75,1.0},
        {1.0,1.0},
        {1.0,0.5},
        {0.75,0.5},

        // tejado 1
        {0.0,0.5},
        {0.25,0.5},
        {0.125,0.25},

        // tejado 2
        {0.0,0.5},
        {0.25,0.5},
        {0.125,0.25},

        // tejado 3
        {0.0,0.5},
        {0.25,0.5},
        {0.125,0.25},

        // tejado 4
        {0.0,0.5},
        {0.25,0.5},
        {0.125,0.25},
        
    };


    calcularNormales();  
   

}

NodoP4::NodoP4
(
    const std::string & archivoTextura
)
{
    ponerNombre("Casa examen -P45");
    unsigned i = agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0.0,1.0,0.0)));
    Textura * casa = new Textura(archivoTextura);
    agregar( new Material(casa, 0.6,0.8,0.1,15.0));
    agregar( new MallaP4());

    matrix = leerPtrMatriz(i);
   
}


bool NodoP4::cuandoClick(const glm::vec3 & centro_wc)
{
    *matrix = glm::rotate(glm::radians(30.0f)*contador,glm::vec3(0.0,1.0,0.0)); 
    contador++;
    std::cout << "Casa " << leerIdentificador() << std::endl;

    return true;
}

NodoUrbaP5::NodoUrbaP5(const std::string & archivoTextura,const int n)
{

    agregar(glm::scale(glm::vec3(0.2,0.2,0.2)));

    for (int i = 0; i < n ; i++)
    {
        NodoGrafoEscena * casaNueva = new NodoP4(archivoTextura);
        casaNueva->ponerNombre("Casa " + std::to_string(i));
        casaNueva->ponerIdentificador(i+1);
        agregar(glm::translate(glm::vec3(2.0,0.0,0.0)));
        agregar(casaNueva);
        
    } 
    
}








