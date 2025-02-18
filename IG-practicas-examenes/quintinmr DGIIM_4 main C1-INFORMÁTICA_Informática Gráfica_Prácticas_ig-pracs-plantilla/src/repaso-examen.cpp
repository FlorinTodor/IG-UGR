// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#include "repaso-examen.h"
#include <iostream>

// REPASO EXAMEN PRÁCTICAS - EXTRA

Piramide::Piramide()
{

    vertices=
    {
        {-1.0,-1.0,+1.0}, // 0  -- 0
        {+1.0,-1.0,+1.0}, // 1  -- 1
        {+1.0,-1.0,-1.0}, // 2  -- 2
        {-1.0,-1.0,-1.0}, // 3  -- 3

        {-1.0,-1.0,+1.0}, // 0  -- 4
        {+1.0,-1.0,+1.0}, // 1  -- 5
        {+0.0,+1.0,+0.0}, // 4  -- 6

        {+1.0,-1.0,+1.0}, // 1  -- 7
        {+1.0,-1.0,-1.0}, // 2  -- 8
        {+0.0,+1.0,+0.0}, // 4  -- 9

        {+1.0,-1.0,-1.0}, // 2  -- 10
        {-1.0,-1.0,-1.0}, // 3  -- 11
        {+0.0,+1.0,+0.0}, // 4  -- 12

        {-1.0,-1.0,-1.0}, // 3  -- 13
        {-1.0,-1.0,+1.0}, // 0  -- 14
        {+0.0,+1.0,+0.0}, // 4  -- 15

    };

    triangulos=
    {
        {0,1,3},
        {1,2,3},

        {4,5,6},
        {7,8,9},
        {10,11,12},
        {13,14,15},
        
    };

    cc_tt_ver=
    {
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},
        {0.0,0.0},

        {0.0,1.0},
        {1.0,1.0},
        {0.5,0.5},

        {1.0,1.0},
        {1.0,0.0},
        {0.5,0.5},

        {1.0,0.0},
        {0.0,0.0},
        {0.5,0.5},

        {0.0,0.0},
        {0.0,1.0},
        {0.5,0.5},

    };

    calcularNormales();

}


NodoPiramide::NodoPiramide()
{

    ponerNombre("Piramide");
    Textura * textura = new Textura("textura-examen.jpg");
    agregar( new Material(textura, 0.6,0.8,0.1,15.0)); 
    agregar( new Piramide());

}


Tablero::Tablero()
: MallaInd("Tablero")
{

    vertices=
    {
        // Tablero
        {-2.0,+0.0,+1.0},  // 0 -- 0
        {+2.0,+0.0,+1.0},  // 1 -- 1
        {+2.0,+0.0,-1.0},  // 2 -- 2
        {-2.0,+0.0,-1.0},  // 3 -- 3

        {-2.0,+0.0,+1.0},  // 0 -- 4
        {+2.0,+0.0,+1.0},  // 1 -- 5
        {+2.0,+1.0,+1.0},  // 5 -- 6
        {-2.0,+1.0,+1.0},  // 4 -- 7

        {+2.0,+0.0,+1.0},  // 1 -- 8
        {+2.0,+0.0,-1.0},  // 2 -- 9
        {+2.0,+1.0,-1.0},  // 6 -- 10
        {+2.0,+1.0,+1.0},  // 5 -- 11

        {+2.0,+0.0,-1.0},  // 2 -- 12
        {-2.0,+0.0,-1.0},  // 3 -- 13
        {-2.0,+1.0,-1.0},  // 7 -- 14
        {+2.0,+1.0,-1.0},  // 6 -- 15

        {-2.0,+0.0,-1.0},  // 3 -- 16
        {-2.0,+0.0,+1.0},  // 0 -- 17
        {-2.0,+1.0,+1.0},  // 4 -- 18
        {-2.0,+1.0,-1.0},  // 7 -- 19

        {-2.0,+1.0,+1.0},  // 4 -- 20
        {+2.0,+1.0,+1.0},  // 5 -- 21
        {+2.0,+1.0,-1.0},  // 6 -- 22
        {-2.0,+1.0,-1.0},  // 7 -- 23

        
    };

    triangulos=
    {
        {0,1,3},{1,2,3},

        {4,5,7}, {5,6,7},
        {8,9,11},{9,10,11},
        {12,13,14},{12,14,15},
        {16,17,18},{16,18,19},

        {20,21,23},{21,22,23},
    };

    cc_tt_ver=
    {
        // cara de abajo
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},

        // Cara frontal
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},

        // Cara dcha
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},

        // Cara lateral
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},

        // Cara izda
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},

        //Cara de arriba
        {0.0,0.0},
        {0.0,1.0},
        {1.0,1.0},
        {1.0,0.0},


    };

    calcularNormales();
}

NodoTablero::NodoTablero()
{

    Textura * madera = new Textura("text-madera.jpg");
    agregar( new Material(madera, 0.6,0.8,0.1,15.0));
    agregar( new Tablero());
}

NodoPata::NodoPata(const glm::vec3 traslacion)
{
   
    pos_inic = traslacion;
    unsigned i = agregar(glm::translate(glm::vec3(0.0,0.0,0.0)));
    agregar(glm::translate(pos_inic));
    agregar(glm::scale(glm::vec3(0.5,0.5,0.15)));
    agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0.0,0.0,1.0)));

    agregar( new NodoTablero());

    pm_pata = leerPtrMatriz(i);

}

unsigned NodoPata::leerNumParametros() const
{
    return num_params;
}

void NodoPata::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
    {
        float p = fijarMovEsfera(-3.0,0.0,1.0,t_sec);
        *pm_pata = glm::translate(glm::vec3(0.0,p,0.0));
    
    }
        break;

    default:
        break;
    }   
}

float NodoPata::fijarMovEsfera(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    return( a+b*sin(2*M_PI*v*t_sec) );
}


Bola::Bola()
{
    
    agregar(glm::scale(glm::vec3(0.25,0.25,0.25)));
    unsigned i = agregar(glm::translate(glm::vec3(0.0,0.0,0.0)));
    //Textura * bola = new Textura("rulo.jpg");
    //agregar( new Material(bola, 0.6,0.8,0.1,15.0));
    agregar( new Esfera(50,50));

    pm_bola = leerPtrMatriz(i);
    ponerIdentificador(1);

}

unsigned Bola::leerNumParametros() const
{
    return num_params;
}

void Bola::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    switch (iParam)
    {
    case 0:
        
        glm::vec3 p = fijarMovEsfera(-1.0,+1.0,1.0,t_sec);
        
        *pm_bola = glm::translate(p);

        break;

    }
}

glm::vec3 Bola::fijarMovEsfera(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    glm::vec3 point =glm::vec3(a+(b+1)*cos(2*M_PI*v*t_sec),0.0,a+(b+1)*sin(2*M_PI*v*t_sec));
   
    return point;
}

bool Bola::cuandoClick(const glm::vec3 & centro_wc)
{
   if (tieneColor())
   {
      if (leerColor() == glm::vec3(1.0,1.0,1.0))
         ponerColor(glm::vec3(1.0,0.0,0.0));
      else if (leerColor() == glm::vec3(1.0,0.0,0.0))
         ponerColor(glm::vec3(1.0,1.0,1.0));
   }

   else ponerColor(glm::vec3(1.0,0.0,0.0)); 
   
   return true;
}

Mesa::Mesa()
{
    agregar( new NodoTablero());
    
    pata_1 = agregar( new NodoPata(glm::vec3(-1.5, -1.0, +0.8)));

    pata_2 = agregar(new NodoPata(glm::vec3(-1.5,-1.0,-1.0)));

    pata_3 = agregar(new NodoPata(glm::vec3(2.0,-1.0,-0.8)));

    pata_4 = agregar(new NodoPata(glm::vec3(2.0,-1.0,0.8)));

    NodoGrafoEscena * rej = new NodoGrafoEscena();
    rej->agregar(glm::translate(glm::vec3(-0.5,1.1,-0.5)));
    rej->agregar(new RejillaY(10,10));
    agregar(rej);
    

    ponerNombre("Bola encima de mesa");
    agregar(glm::translate(glm::vec3(0.0,1.25, 0.0)));
    bola = agregar( new Bola());
    ponerIdentificador(1);
}

unsigned Mesa::leerNumParametros() const
{
    return num_params;
}

void Mesa::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    switch (iParam)
    {
    case 0:

        ((Bola*)(entradas[bola].objeto))->actualizarEstadoParametro(iParam,t_sec);
        break;

    case 1:
        ((NodoPata*)(entradas[pata_1].objeto))->actualizarEstadoParametro(iParam-1,t_sec);
        ((NodoPata*)(entradas[pata_2].objeto))->actualizarEstadoParametro(iParam-1,t_sec);
        ((NodoPata*)(entradas[pata_3].objeto))->actualizarEstadoParametro(iParam-1,t_sec);
        ((NodoPata*)(entradas[pata_4].objeto))->actualizarEstadoParametro(iParam-1,t_sec); 
        break;
    }
}

bool Mesa::cuandoClick(const glm::vec3 & centro_wc)
{
    return ((Bola*)(entradas[bola].objeto))->cuandoClick(centro_wc);
}



// FILAS DE TABLEROS (PARALELAS)

NodoTablero_BIS::NodoTablero_BIS(const unsigned num_tablero, const unsigned num_fila)
{
    i = num_fila;
    j = num_tablero;

    unsigned r = agregar(glm::rotate(glm::radians(0.0f), glm::vec3(1.0,0.0,0.0)));
    agregar( new NodoTablero());

    pm_tablero = leerPtrMatriz(r);

}

bool NodoTablero_BIS::cuandoClick(const glm::vec3 & centro_wc)
{
    *pm_tablero = glm::rotate(glm::radians(90.0f*contador), glm::vec3(1.0,0.0,0.0));
    contador++;
    std::cout << "Seleccionado tablero " << j << " de la fila "<< i << std::endl;

    return true;
}

GrafoTableros_V1::GrafoTableros_V1(const unsigned nFilas, const unsigned numTabxFil)
{

    // factor de escala de los tableros
    float factor = 0.4/numTabxFil;

    // Aplicamos un escalado uniforme a los tableros
    agregar(glm::scale(glm::vec3(factor,factor,factor)));

    // Comenzamos agregando los tableros por cada una de las filas, trasladando
    // una cantidad hacia la derecha cada uno, con respecto al anterior
    for (unsigned i = 0; i < nFilas; i++)
    {
        NodoGrafoEscena * filaTableros = new NodoGrafoEscena();

        for (unsigned j = 0; j < numTabxFil; j++)
        {
            NodoTablero_BIS * tablero = new NodoTablero_BIS(j,i);
            tablero->ponerIdentificador(nFilas*i+j+1);
            filaTableros->agregar(glm::translate(glm::vec3(5.0,0.0,0.0)));
            filaTableros->agregar(tablero);
        }

        agregar(filaTableros);
        agregar(glm::translate(glm::vec3(0.0,0.0,3.0)));
        agregar( glm::rotate( glm::radians(360.0f/nFilas), glm::vec3( 0.0, 1.0, 0.0 ))); 
    }
}


// CAJA

Caja::Caja()
: MallaInd("Caja de madera")
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
         { -0.8, +1.0, +0.8 }, // 8 -- 22
         { +0.8, +1.0, +0.8 }, // 9 -- 23

         { +1.0, +1.0, +1.0 }, // 5 -- 24
         { +1.0, +1.0, -1.0 }, // 6 -- 25
         { +0.8, +1.0, -0.8 }, // 10 --26
         { +0.8, +1.0, +0.8 }, // 9 -- 27

         { +1.0, +1.0, -1.0 }, // 6 -- 28
         { -1.0, +1.0, -1.0 }, // 7 -- 29
         { -0.8, +1.0, -0.8 }, // 11 -- 30
         { +0.8, +1.0, -0.8 }, // 10 -- 31

         { -1.0, +1.0, -1.0 }, // 7 -- 32
         { -1.0, +1.0, +1.0 }, // 4 -- 33
         { -0.8, +1.0, +0.8 }, // 8 -- 34
         { -0.8, +1.0, -0.8 }, // 11 -- 35

      };

      triangulos=
      {
        {0,1,2},{0,2,3},

        {4,5,7}, {5,6,7},

        {8,9,11}, {9,10,11},

        {12,13,14}, {12,14,15},

        {16,17,18}, {16,18,19},

        {20,21,22}, {21,23,22},
        {24,25,27}, {25,26,27},
        {28,29,30}, {28,30,31},
        {32,33,35}, {33,34,35},

      };

      cc_tt_ver=
      {
           // cara de abajo
            {0.0,0.0},  
            {0.0,1.0},
            {1.0,1.0},
            {1.0,0.0},

           // cara frontal
            {0.0,0.0},  
            {0.0,1.0},
            {1.0,1.0},
            {1.0,0.0},

            // cara dcha
            {0.0,0.0},  
            {0.0,1.0},
            {1.0,1.0},
            {1.0,0.0},

            // cara de atrás
            {0.0,0.0},  
            {0.0,1.0},
            {1.0,1.0},
            {1.0,0.0},

            // cara izda
            {0.0,0.0},  
            {0.0,1.0},
            {1.0,1.0},
            {1.0,0.0},

            // borde frontal
            {0.0,0.0},
            {0.0,1.0},
            {0.25,1.0},
            {0.25,0.0},

            // borde dcho
            {0.0,0.0},
            {0.0,1.0},
            {0.25,1.0},
            {0.25,0.0},

            // borde atrás
            {0.0,0.0},
            {0.0,1.0},
            {0.25,1.0},
            {0.25,0.0},


            // borde izdo
            {0.0,0.0},
            {0.0,1.0},
            {0.25,1.0},
            {0.25,0.0},

      };

      calcularNormales();
}

NodoCaja::NodoCaja()
{
    Textura * lamas = new Textura("textura-lamas-madera.jpg");
    agregar( new Material(lamas,  0.6,0.8,0.1,15.0));
    agregar( new Caja());

    NodoGrafoEscena * tapadera = new NodoGrafoEscena();
    unsigned i = tapadera->agregar(glm::translate(glm::vec3(0.0,1.15,0.0)));
    tapadera->agregar((glm::scale(glm::vec3(1.0,0.15,1.0))));
    tapadera->agregar(glm::rotate(glm::radians(180.0f), glm::vec3(0.0,0.0,1.0)));
    tapadera->agregar( new Caja());

    agregar(tapadera);

    pm_caja = tapadera->leerPtrMatriz(i);

    NodoGrafoEscena * pelota = new NodoGrafoEscena();
    unsigned j = pelota->agregar(glm::translate(glm::vec3(0.0,0.0,0.0)));
    pelota->agregar(glm::scale(glm::vec3(0.25,0.25,0.25)));
    Textura * bola = new Textura("rulo.jpg");
    pelota->agregar( new Material(bola,  0.6,0.8,0.1,15.0));
    pelota->agregar( new Esfera(50,50));

    agregar(pelota);

    pm_bola = pelota->leerPtrMatriz(j);

}

unsigned NodoCaja::leerNumParametros() const
{
    return num_params;
}

void NodoCaja::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    switch (iParam)
    {
    case 0:
    {
        
        glm::vec3 p = fijarMovEsfera(1.15,+5.0,1.0,t_sec);
        *pm_caja = glm::translate(p);
    

        glm::vec3 q = fijarMovEsfera(0.5,+3.0,1.0,t_sec);
        *pm_bola = glm::translate(q);
    }
        break;

    default:
        break;

    }
}

glm::vec3 NodoCaja::fijarMovEsfera(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    glm::vec3 point =glm::vec3(0.0,a+b*sin(2*M_PI*v*t_sec),0.0);
   
    return point;
}


// Malla barrido respecto del eje Z (PRÁCTICA 2)
P2Barrido::P2Barrido(unsigned m, unsigned n)
:  MallaInd( "Examen p2" )
{
    assert(m > 2);
    assert(n > 2);
    // Perfil
    using namespace glm;
    float angle;
    std::vector<glm::vec3> perfil;
    glm::vec3 curr;
    glm::vec4 rot_point, aux;

    // Rotamos alrededor del eje z
    angle = 360.0/(m-1);
    mat4 rot_mat = rotate(radians(angle), vec3(0, 0, +1.0));
    perfil.push_back(glm::vec3(0, -1.0, 0));

    // Generamos perfil rotando un punto
    for (unsigned i = 1; i < m; ++i) {
        curr = perfil[i-1];
        aux = {curr.x, curr.y, curr.z, 1};
        rot_point = rot_mat * aux;
        curr = {rot_point.x, rot_point.y, rot_point.z};
        perfil.push_back(curr);
    }

    // Recorro instancias
    unsigned sz = perfil.size();

    for (unsigned i = 0; i < sz; ++i) {
        perfil[i].z += 1.0;
    }  
    float despl_z;
    for (unsigned int i = 0; i < n; ++i) {
        // Calculo ángulo de rotación en grados y su matriz
        despl_z = -2.0*i/n;
        mat4 trans_mat = translate(vec3(+0.0, +0.0, despl_z));

        // Recorro perfil
        for (unsigned j = 0; j < sz; ++j) {
            curr = perfil[j];
            aux = {curr.x,curr.y,curr.z,1};
            rot_point = trans_mat * aux;
            curr = {rot_point.x, rot_point.y, rot_point.z};
            // Añado punto
            vertices.push_back(curr);
        }
    }

    // Triángulos
    // Recorro instancias
    int k = 0;
    for (unsigned int i = 0; i < n-1; ++i) {
        // Recorro perfil
        for (unsigned j = 0; j < sz-1; ++j) {
            // Índice del punto del perfil de la instancia dada
            k = i*sz+j;
            // Añado triángulos
            triangulos.push_back(vec3(k, k+sz, k+sz+1));
            triangulos.push_back(vec3(k, k+sz+1, k+1));
        }
        triangulos.push_back(vec3(i*sz, (i+1)*sz, (i+1)*sz-1));
        triangulos.push_back(vec3((i+1)*sz, (i+2)*sz-1, (i+1)*sz-1));
    }
}

// Malla Barrido respecto del eje X (PRÁCTICA 2)


// PRIMERA FORMA (utilizando matrices de rotación y traslación)

/* 
P2BarridoX::P2BarridoX(unsigned m, unsigned n)
: MallaInd("Malla Barrido (Eje X) - P2")
{

    assert(m>2 and n>2);
    using namespace glm;
    using namespace std;

    // Variables necesarias para la generación del perfil
    vector<vec3> perfil;
    vec3 punto_actual;
    vec4 punto_auxiliar, punto_rotado;
    mat4 mat_rotacion_X = rotate(radians(180.0f/(m-1)), vec3(1.0,0.0,0.0));

    // En primer lugar, vamos a generar el perfil, punto a punto,
    // de tal forma que un punto generado es el rotado respecto del eje X
    // a partir del anterior. Insertemos uno:

    perfil.push_back(vec3(0.0,-1.0,0.0));

    for (unsigned i = 1; i < m; i++)
    {
        punto_actual   = perfil[i-1];
        punto_auxiliar = {punto_actual.x, punto_actual.y,punto_actual.z, 1.0};
        punto_rotado   = mat_rotacion_X * punto_auxiliar;
        punto_actual   = {punto_rotado.x,punto_rotado.y,punto_rotado.z};

        perfil.push_back(punto_actual);

    }

    // Una vez generado el perfil, hemos de calcular la tabla de vértices.

    float desplazamiento_X;

    for (unsigned i = 0; i < n; i++)
    {
        desplazamiento_X = +2.0*i/n;  // variable para controlar cómo de espaciadas están las copias del perfil

        // Vamos a trasladar los vértices del perfil una distancia en X de desplazamiento_X
        mat4 mat_traslacion_X = translate(vec3(desplazamiento_X, 0.0,0.0));

        for (unsigned j = 0; j < m; j++)
        {
            punto_actual   = perfil[j];
            punto_auxiliar = {punto_actual.x, punto_actual.y, punto_actual.z, 1};
            punto_rotado   = mat_traslacion_X * punto_auxiliar;
            punto_actual   = {punto_rotado.x, punto_rotado.y, punto_rotado.z};

            vertices.push_back(punto_actual);
        } 
    }

    // Una vez creada la tabla de vértices, procedemos a calcular la tabla de triángulos
    for (unsigned i = 0; i < n-1; i++)
    {
        for (unsigned j = 0; j < m-1; j++)
        {
            unsigned k = i*m+j;

            vec3 t1 = {k,k+m,k+m+1};
            vec3 t2 = {k,k+m+1,k+1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
        }

        vec3 t1 = {i*m,(i+1)*m,(i+1)*m-1};
        vec3 t2 = {(i+1)*m,(i+2)*m-1,(i+1)*m-1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
    }


} */

// SEGUNDA FORMA (utilizando cos y sin)

P2BarridoX::P2BarridoX(unsigned m, unsigned n)
: MallaInd("Malla Barrido (Eje X) - P2")
{

    assert(m>2 and n>2);
    using namespace glm;
    using namespace std;

    // Variables necesarias para la generación del perfil
    vector<vec3> perfil;

    // En primer lugar, vamos a generar el perfil, punto a punto,

    perfil.push_back(vec3(0.0,0.0,-1.0));

    for (unsigned i = 0; i < m; i++)
    {
        float angle = M_PI*i/(m-1);
        vec3 q = {0.0,cos(angle), -sin(angle)};
        perfil.push_back(q);

    }

    //************************************************************************
    // CÁLCULO DE NORMALES
    //************************************************************************
    vector<vec3> nor_aritas,aristas;
    vector<vec3> nor_vertices;
    vector<float> long_aristas;

  
    // 1. Cálculo previo de las aristas y guardamos su longitud
    for (unsigned i = 0; i < perfil.size()-1; i++)
    {
        aristas.push_back(perfil[i+1]-perfil[i]);
        long_aristas.push_back(aristas[i].length());
    }


    // 2. Cáculo de normales de las aristas

    for (unsigned i = 0; i < aristas.size(); i++)
    {
        vec3 aux = vec3(aristas[i].y, -aristas[i].x,0);

        if (aux.length() != 0.0)
            aux = normalize(aux);
        
        else aux = vec3(0.0,0.0,0.0);

        nor_aritas.push_back(aux);
    }
   
   // 3. Cálculo de las normales de los vértices
   nor_vertices.push_back(nor_aritas[0]);

   for (unsigned i = 1; i < perfil.size()-1; i++)
   {
      vec3 aux = nor_aritas[i-1] + nor_aritas[i];

      if (aux.length() != 0.0)
         aux = normalize(aux);
      
      else aux = vec3(0.0,0.0,0.0);

      nor_vertices.push_back(aux);

   }

   nor_vertices.push_back(nor_aritas[perfil.size()-2]);

    // A continuación, calculamos la tabla de vértices a partir del perfil
    // Además, calculamos la tabla de normales de vértices

    for (unsigned i = 0; i < n; i++)
    {
        float desplazamiento_X = 2.0*i/n;

        for (unsigned j = 0; j < m; j++)
        {
            vec3 q = {desplazamiento_X, perfil[j].y, perfil[j].z};
            vertices.push_back(q);

            // rotación de las normales
            float angle = M_PI*i/(n-1);
            float ratio_n = nor_vertices[j].x;
            vec3 rotation(ratio_n*cos(angle), nor_vertices[j].y, ratio_n*sin(angle));
            
            if (rotation.length() != 0.0)
                rotation = normalize(rotation);
            else rotation = vec3(0.0,0.0,0.0);
            
            nor_ver.push_back(rotation);
        }
    }

    // Una vez creada la tabla de vértices, procedemos a calcular la tabla de triángulos
    for (unsigned i = 0; i < n-1; i++)
    {
        for (unsigned j = 0; j < m-1; j++)
        {
            unsigned k = i*m+j;

            vec3 t1 = {k,k+m,k+m+1};
            vec3 t2 = {k,k+m+1,k+1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
        }

        vec3 t1 = {i*m,(i+1)*m,(i+1)*m-1};
        vec3 t2 = {(i+1)*m,(i+2)*m-1,(i+1)*m-1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
    }

}


// CASA
Casa::Casa()
{

    vertices=
    {
        { 0.0, 0.0, 0.0 }, // 0
        { 0.0, 0.0, +1.0 }, // 1
        { +2.0, 0.0, +1.0 }, // 2
        { +2.0, 0.0, 0.0 }, // 3

        { 0.0, 0.0, +1.0 }, // 1   -- 4
        { +2.0, 0.0, +1.0 }, // 2  -- 5
        { +2.0, +1.0, +1.0 }, // 7 -- 6
        { 0.0, +1.0, +1.0 }, // 4  -- 7

        { +2.0, 0.0, +1.0 }, // 2  -- 8
        { +2.0, 0.0, 0.0 }, // 3   -- 9
        { +2.0, +1.0, 0.0 }, // 6  -- 10
        { +2.0, +1.0, +1.0 }, // 7 -- 11

        { +2.0, 0.0, 0.0 }, // 3   -- 12
        { 0.0, 0.0, 0.0 }, // 0    -- 13
        { 0.0, +1.0, 0.0 }, // 5   -- 14
        { +2.0, +1.0, 0.0 }, // 6  -- 15

        { 0.0, 0.0, 0.0 }, // 0    -- 16
        { 0.0, 0.0, +1.0 }, // 1   -- 17
        { 0.0, +1.0, +1.0 }, // 4  -- 18
        { 0.0, +1.0, 0.0 }, // 5   -- 19

        { 0.0, +1.0, +1.0 }, // 4  -- 20
        { +2.0, +1.0, +1.0 }, // 7 -- 21
        { +2.0, +1.5, +0.5 },  // 8 -- 22
        { 0.0,  +1.5, +0.5 },  // 9 -- 23

        { +2.0, +1.0, +1.0 }, // 7  -- 24
        { +2.0, +1.0, 0.0 }, // 6   -- 25
        { +2.0, +1.5, +0.5 },  // 8 -- 26
 
       { +2.0, +1.0, 0.0 }, // 6    -- 27
        { 0.0, +1.0, 0.0 }, // 5    -- 28
        { 0.0,  +1.5, +0.5 },  // 9 -- 29
        { +2.0, +1.5, +0.5 },  // 8 -- 30

        { 0.0, +1.0, 0.0 }, // 5    -- 31
        { 0.0, +1.0, +1.0 }, // 4   -- 32
        { 0.0,  +1.5, +0.5 },  // 9 -- 33
        
    };

    triangulos=
    {
        {1,2,3}, {1,3,0},
        {4,5,7}, {5,6,7},
        {8,9,11},{9,10,11},
        {12,13,14}, {12,14,15},
        {16,17,18}, {16,18,19},

        {20,21,23}, {21,22,23},
        {24,25,26}, {27,28,29},
        {27,29,30}, {31,32,33},
    };

    cc_tt_ver=
    {

        // Cara de abajo
        {0.5,0.5},
        {0.5,1.0},
        {1.0,1.0},
        {1.0,0.5},

        // Cara frontal
        {0.5,0.5},
        {1.0,0.5},
        {1.0,0.0},
        {0.5,0.0},

        // Cara izquierda (aquí va la puerta)
        {0.0,0.5},
        {0.5,0.5},
        {0.5,0.0},
        {0.0,0.0},

        // Cara de atrás
        {0.5,0.5},
        {1.0,0.5},
        {1.0,0.0},
        {0.5,0.0},

        // Cara dcha
        {0.5,0.5},
        {1.0,0.5},
        {1.0,0.0},
        {0.5,0.0},

        // Tejado cara 1
        {0.0,1.0},
        {0.5,1.0},
        {0.5,0.5},
        {0.0,0.5},

        // Tejado cara 2
        {0.0,1.0},
        {0.5,1.0},
        {0.25,0.75},

        // Tejado cara 3
        {0.0,1.0},
        {0.5,1.0},
        {0.5,0.5},
        {0.0,0.5},

        // Tejado cara 4
        {0.0,1.0},
        {0.5,1.0},
        {0.25,0.75},
        

    };

    calcularNormales();
}

NodoCasa::NodoCasa()
{
    Textura * casa = new Textura("casa.jpeg");
    agregar( new Material(casa, 0.6,0.8,0.1,15.0));
    agregar( new Casa());
}

bool NodoCasa::cuandoClick(const glm::vec3 & centro_wc)
{
    
    const unsigned numCasas = 4;

    for (unsigned i = 0; i < numCasas; i++)
    {
        glm::vec3 q;

        switch (contador)
        {
        case 1:
            
            q = {-1.0, 0.0, 0.0};
            break;

        case 2:
            
            q = {0.0, 0.0, -1.0};
            break;

        case 3:
            
            q = {+1.0, 0.0, 0.0};
            break;

        case 4:
            
            q = {0.0, 0.0, -1.0};
            break;
        
        default:
            break;
        }

        agregar(glm::translate(q));
        agregar( new NodoCasa());

        contador++;
    }

    contador = 1;
    

    return true;
}

NodoBarrio::NodoBarrio(const int nCalles, const int nCasasXCalle)
{

    // Las casas del barrio estarán escaladas uniformemente con un factor
    // de escala igual para todas las casas
    float factor = 2.0/nCasasXCalle;

    agregar(glm::scale(glm::vec3(factor,factor,factor)));

    // Una vez aplicado el factor de escala, vamos a ir creando e identificando cada una de las 
    // casas del barrio, por calles

    for (int i = 0; i < nCalles; i++)
    {
        NodoGrafoEscena * calleNueva = new NodoGrafoEscena;

        for (int j = 0; j < nCasasXCalle; j++)
        {
            NodoCasa * casaNueva = new NodoCasa();
            casaNueva->ponerIdentificador(i*nCalles+j);
            calleNueva->agregar(glm::translate(glm::vec3(3.0,0.0,0.0)));
            calleNueva->agregar(casaNueva);
        }

        agregar(calleNueva);
        agregar(glm::translate(glm::vec3(0.0,0.0,3.0)));
    }
}


// CRUZ (REPASO)

Suelo::Suelo()
{

    agregar( new RejillaY(50,50));
    
}



NodoCruz::NodoCruz()
{

    NodoGrafoEscena * palo1 = new NodoGrafoEscena();
    palo1->agregar(glm::translate(glm::vec3(0.5,0.0,0.0)));
    palo1->agregar(glm::scale(glm::vec3(1.0,2.5,0.4)));
    palo1->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0.0,0.0,1.0)));
    palo1-> agregar( new NodoTablero());

    agregar(palo1);

    NodoGrafoEscena * palo = new NodoGrafoEscena();

    palo->agregar(glm::translate(glm::vec3(0.0,2.5,0.0)));
    palo->agregar(glm::scale(glm::vec3(2.0,1.0,0.4)));
    palo->agregar( new NodoTablero());

    agregar(palo);

    NodoGrafoEscena * suelo = new NodoGrafoEscena();

    unsigned i = suelo->agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0.0,1.0,0.0)));
    suelo->agregar(glm::translate(glm::vec3(-3.75,-5.0,-3.75)));
    suelo->agregar(glm::scale(glm::vec3(7.0,1.0,7.0)));
    suelo->agregar( new Suelo());

    pm_suelo = suelo->leerPtrMatriz(i);

    agregar(suelo);

    ponerIdentificador(1);

}

unsigned NodoCruz::leerNumParametros() const
{
    return num_params;
}



void NodoCruz::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
    {
        // Calcular el ángulo de rotación en función del tiempo
        float v_angular = (60.0f) * t_sec;
        *pm_suelo = glm::rotate(glm::radians(v_angular), glm::vec3(0.0, 1.0, 0.0));
    }
        break;

    default:
        break;
    }   
}

bool NodoCruz::cuandoClick(const glm::vec3 & centro_wc)
{
    
    std::cout << "Amén Jesús" << std::endl;

    return true;
}



// LÁPIZ (REPASO)

Lapiz::Lapiz()
{

    NodoGrafoEscena * punta = new NodoGrafoEscena();
    punta->agregar( new Material(new Textura("text-madera-lapiz.jpg"),0.6,0.8,0.1,15.0 ));
    unsigned i = punta->agregar(glm::rotate((glm::radians(0.0f)), glm::vec3(0.0,1.0,0.0)));
    unsigned k = punta->agregar(glm::translate(glm::vec3(0.0,0.0,0.0)));
    punta->agregar(glm::translate(glm::vec3(0.0,3.0,0.0)));
    punta->agregar(glm::scale(glm::vec3(0.5,0.65,0.5)));
    punta->agregar( new Piramide());

    punta->ponerNombre("Punta Lapiz");

    agregar(punta); 

    rot_punta = punta->leerPtrMatriz(i);
    pm_punta  = punta->leerPtrMatriz(k);

    agregar( new Material(new Textura("textura-examen.jpg"),0.6,0.8,0.1,15.0 ));
    unsigned j = agregar(glm::rotate((glm::radians(0.0f)), glm::vec3(0.0,1.0,0.0)));
    agregar(glm::scale(glm::vec3(0.5,2.35,0.5)));
    agregar( new Cubo24());

    pm_tronco = leerPtrMatriz(j);
    ponerIdentificador(1);

}

unsigned Lapiz::leerNumParametros() const
{
    return num_params;
}



void Lapiz::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
    {

        float p = fijarMovLapiz(-3.0,0.0,1.0,t_sec);
        *pm_tronco = glm::translate(glm::vec3(0.0,p,0.0));

        float q    = fijarMovLapiz(-3.0,0.0,1.0,t_sec);
        *pm_punta = glm::translate(glm::vec3(0.0,q,0.0));

            
    }
    break;

    default:
        break;
        
    }   
}

bool Lapiz::cuandoClick(const glm::vec3 & centro_wc)
{

    *rot_punta = glm::rotate(glm::radians(30.0f)*contador,glm::vec3(0.0,1.0,0.0)); 
    contador++;

    return true;
}

float Lapiz::fijarMovLapiz(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    return( a+b*sin(2*M_PI*v*t_sec) );
}


// CuboDomino (Repaso)

Dado::Dado()
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
         { +1.0, +1.0, -1.0 }, // 6 -- 22
         { -1.0, +1.0, -1.0 }, // 7 -- 23

         
      } ;


    triangulos=
    {
        {0,1,2},{0,2,3},

        {4,5,7}, {5,6,7},

        {8,9,11}, {9,10,11},

        {12,13,14}, {12,14,15},

        {16,17,18}, {16,18,19},

        {20,21,22}, {20,22,23},
        
    };

    cc_tt_ver=
    {
        {0.75,0.66666},
        {1.0,0.66666},
        {1.0,0.33333},
        {0.75,0.33333},

        {0.25,1.0},
        {0.5,1.0},
        {0.5,0.66666},
        {0.25,0.66666},

        {0.5,0.66666},
        {0.75,0.66666},
        {0.75,0.33333},
        {0.5,0.33333},

        {0.25,0.33333},
        {0.5,0.33333},
        {0.5,0.0},
        {0.25,0.0},

        {0.0,0.66666},
        {0.25,0.66666},
        {0.25,0.33333},
        {0.0,0.33333},

        {0.25,0.66666},
        {0.5,0.66666},
        {0.5,0.33333},
        {0.25,0.3333},
    };


    calcularNormales();
}

NodoDado::NodoDado()
{

    unsigned j = agregar(glm::translate(glm::vec3(0.0,0.0,0.0)));
    unsigned i = agregar(glm::rotate(glm::radians(0.0f),glm::vec3(1.0,0.0,0.0)));
    agregar( new Material(new Textura("cubo-domino.jpg"),0.6,0.8,0.1,15.0));
    agregar( new Dado());

    pm_dado = leerPtrMatriz(i);
    dado    = leerPtrMatriz(j);
    ponerIdentificador(1);
}

bool NodoDado::cuandoClick(const glm::vec3 & centro_wc)
{

    if (contador %3 == 0)
    {
        *pm_dado = glm::rotate(glm::radians(90.0f),glm::vec3(1.0,0.0,0.0));
    
    }
    
    else if (contador % 2 == 0)
        *pm_dado = glm::rotate(glm::radians(-90.0f),glm::vec3(0.0,0.0,1.0));
    
    else 
        *pm_dado = glm::rotate(glm::radians(90.0f),glm::vec3(0.0,0.0,1.0));

        

    contador++;

    return true;

}

unsigned NodoDado::leerNumParametros() const
{
    return num_params;
}



void NodoDado::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
    {

        *pm_dado = glm::rotate(glm::radians(-90.0f*sinf(2*M_PI*t_sec)),glm::vec3(0.0,0.0,1.0));
        *dado = glm::translate(glm::vec3(0.5*sinf(2*M_PI*t_sec),0.0,0.0));

            
    }
    break;

    default:
        break;
        
    }   
}

float NodoDado::fijarMovDado(const float min, const float max, const float v, const float t_sec)
{
    
    const float a = (min+max)/2;
    const float b = (max-min)/2;

    return( a+b*sin(2*M_PI*v*t_sec) );
}


// Casa Tetraédrica
CasaTetra::CasaTetra()
{

    vertices=
    {
        // Base Tetraedro
        {-1.0,-1.0,+1.0},            // 0
        {+1.0,-1.0,+1.0},            // 1
        {0.0,-1.0,-1.0},             // 2

        // Cara frontal tetraedro
        {-1.0,-1.0,+1.0},            // 0  -- 3
        {+1.0,-1.0,+1.0},            // 1  -- 4
        {0.0,+1.0,0.0},              // 3  -- 5

        // Cara izda tetraedro
        {+1.0,-1.0,+1.0},            // 1  -- 6
        {0.0,-1.0,-1.0},             // 2  -- 7
        {0.0,+1.0,0.0},              // 3  -- 8

        // Cara dcha tetraedro
        {0.0,-1.0,-1.0},             // 2  -- 9
        {-1.0,-1.0,+1.0},            // 0  -- 10
        {0.0,+1.0,0.0},              // 3  -- 11

        // CUERPO CASA TETRAEDRICA
        // Base
        {-1.0,-3.0,+1.0},            // 5  -- 12
        {+1.0,-3.0,+1.0},            // 6  -- 13
        {0.0,-3.0,-1.0},             // 7  -- 14

        // Cara frontal base
        {-1.0,-3.0,+1.0},            // 5  -- 15
        {+1.0,-3.0,+1.0},            // 6  -- 16
        {+1.0,-1.0,+1.0},            // 1  -- 17
        {-1.0,-1.0,+1.0},            // 0  -- 18

        // Cara izda base
        {+1.0,-3.0,+1.0},            // 6  -- 19
        {0.0,-3.0,-1.0},             // 7  -- 20
        {0.0,-1.0,-1.0},             // 2  -- 21
        {+1.0,-1.0,+1.0},            // 1  -- 22

        // Cara dcha base
        {0.0,-3.0,-1.0},             // 7  -- 23
        {-1.0,-3.0,+1.0},            // 5  -- 24
        {-1.0,-1.0,+1.0},            // 0  -- 25
        {0.0,-1.0,-1.0},             // 2  -- 26


    };

    triangulos=
    {
        // TETRAEDRO
        {0,1,2}, // base
        {3,4,5}, // frontal
        {6,7,8}, // izda
        {9,10,11}, // dcha

        // TRONCO
        {12,13,14},
        {15,16,18},
        {16,17,18},
        {19,20,21},
        {19,21,22},
        {23,24,25},
        {23,25,26},
    };


    cc_tt_ver=
    {

        // base tetraedro (no se ve)
        {0.0,0.0},
        {0.0,0.0},
        {0.0,0.0},

        // cara frontal
        {0.6666,1.0},
        {1.0,1.0},
        {0.83333,0.6666},
        
        // Cara izda
        {0.0,1.0},
        {0.6666,1.0},
        {0.33333,0.5},

        // Cara dcha
        {0.0,0.5},
        {0.6666,0.5},
        {0.3333,0.0},

        // Cara base cuerpo
        {0.0,0.0},
        {0.0,0.0},
        {0.0,0.0},

        // Cara frontal cuerpo
        {0.6666,0.3333},
        {1.0,0.3333},
        {1.0,0.0},
        {0.66666,0.0},

        // Cara izda cuerpo
        {0.6666,0.6666},
        {1.0,0.6666},
        {1.0,0.3333},
        {0.66666,0.3333},

        // Cara dcha cuerpo
        {0.0,0.5},
        {0.6666,0.5},
        {0.6666,0.0},
        {0.0,0.0},


    }; 

    calcularNormales();
}

NodoCasaTetra::NodoCasaTetra()
{

    agregar( new Material(new Textura("comida.jpeg"), 0.6,0.8,0.1,15.0));
    agregar( new CasaTetra());
}



