// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#include "examen-extr-pracs.h"


// EJERCICIO 1 - EXAMEN 06/02/2024
P1Malla::P1Malla()
{

    vertices=
    {
        // Base cuadrada
        {-3.0,0.0,+3.0},   // 0
        {-1.0,0.0,+3.0},   // 1
        {+3.0,0.0,+3.0},   // 2
        {+3.0,0.0,+1.0},   // 3
        {+3.0,0.0,-3.0},   // 4
        {+1.0,0.0,-3.0},   // 5
        {-3.0,0.0,-3.0},   // 6
        {-3.0,0.0,-1.0},   // 7
        

        // Base piramide
        {-1.0,0.0,+1.0},  // 8
        {+1.0,0.0,+1.0},  // 9
        {+1.0,0.0,-1.0},  // 10
        {-1.0,0.0,-1.0},  // 11

        // Ápice
        {0.0,3.0,0.0},    // 12

    };

    triangulos=
    {
        {0,1,8},
        {1,9,8},
        {1,2,9},
        {2,3,9},
        {3,10,9},
        {3,4,10},
        {4,5,10},
        {5,11,10},
        {5,6,11},
        {6,7,11},
        {7,8,11},
        {7,0,8},

        {8,9,12},
        {9,10,12},
        {10,11,12},
        {11,8,12},
    };

    calcularNormales();
}


// EJERCICIO 2 - EXAMEN 06/02/2024

P2Fuente::P2Fuente(unsigned n, unsigned m)
{
    assert(n%3 == 0 and n>=24);

    using namespace glm;
    using namespace std;

    vector<vec3> perfil;

    //Añadimos en primer lugar,el vértice (4,0)
    perfil.push_back(vec3(4.0,0.0,0.0));

    // Añadimos n/3 vértices entre (4,0) y (1,1/2)
    // Todos ellos equiespaciados una cantidad
    vec3 curr;
    vec4 rot_point, aux;

    // Rotamos alrededor del eje Y
    float angle = 360.0/n;
    mat4 rot_mat = rotate(radians(angle), vec3(0, 1.0, 0.0));

    float y = 0.0;
    // Generamos perfil rotando un punto
    for (unsigned i = 1; i < n/3 and y<0.5; ++i) {
        curr = perfil[i-1];
        aux = {curr.x, curr.y, curr.z, 1};
        rot_point = rot_mat * aux;
        curr = {rot_point.x, rot_point.y, rot_point.z};
        y = rot_point.y;
        perfil.push_back(curr);
    }

    perfil.push_back(vec3(1.0,0.5,0.0));

    // Generamos perfil rotando un punto
    for (unsigned i = n/3; i < 2*n/3 and y<6; ++i) {
        curr = perfil[i-1];
        aux = {curr.x, curr.y, curr.z, 1};
        rot_point = rot_mat * aux;
        curr = {rot_point.x, rot_point.y, rot_point.z};
        y = rot_point.y;
        perfil.push_back(curr);
    }

    perfil.push_back(vec3(0.5,6.0,0.0));

    for (unsigned i = 2*n/3; i < n and y<7.5; ++i) {
        curr = perfil[i-1];
        aux = {curr.x, curr.y, curr.z, 1};
        rot_point = rot_mat * aux;
        curr = {rot_point.x, rot_point.y, rot_point.z};
        y = rot_point.y;
        perfil.push_back(curr);
    }

    perfil.push_back(vec3(4.0,7.5,0.0));


    inicializar(perfil,m);


    
}


P2Anillo::P2Anillo(unsigned n, unsigned m, unsigned w)
{


    float angle;
    std::vector<glm::vec3> perfil;
    glm::vec3 curr;
    glm::vec4 rot_point, aux;

    // Rotamos alrededor del eje Y
    angle = 360.0/(n-1);

    glm::mat4 rot_mat = glm::rotate(glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    perfil.push_back(glm::vec3(1.0+w, 0.0, 0.0));

    // Generamos perfil rotando un punto
    for (unsigned i = 1; i < m; ++i) {
        curr = perfil[i-1];
        aux = {curr.x, curr.y, curr.z, 1};
        rot_point = rot_mat * aux;
        curr = {rot_point.x, rot_point.y, rot_point.z};
        perfil.push_back(curr);
    }

    float desplazamiento_en_Z;
    float desplazamiento_en_X;

    for (unsigned int i = 0; i < m; ++i) {
        // Calculo ángulo de rotación en grados y su matriz
        desplazamiento_en_Z = -1.0*i/m;
        desplazamiento_en_X = -1.0*i/m;
        glm::mat4 trans_mat = glm::translate(glm::vec3(desplazamiento_en_X, +0.0, desplazamiento_en_Z));

        // Recorro perfil
        for (unsigned j = 0; j < n; ++j) {
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
    for (unsigned int i = 0; i < m-1; ++i) {
        // Recorro perfil
        for (unsigned j = 0; j < n-1; ++j) {
            // Índice del punto del perfil de la instancia dada
            k = i*n+j;
            // Añado triángulos
            triangulos.push_back(glm::vec3(k, k+n, k+n+1));
            triangulos.push_back(glm::vec3(k, k+n+1, k+1));
        }
        
    } 

}

// EJERCICIO 3 - EXAMEN 06/02/2024
P3Rotonda::P3Rotonda()
{
    using namespace glm;

    NodoGrafoEscena * anillo1 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(1.2,1.0,1.2)));
    anillo1->agregar( new P2Anillo(30,30,4.5));
    agregar(anillo1);

    NodoGrafoEscena * anillo2 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(6.0,1.0,6.0)));
    anillo2->agregar( new P2Anillo(30,30,9.0));
    agregar(anillo2);

    NodoGrafoEscena * fuente = new NodoGrafoEscena();
    fuente->agregar(scale(vec3(0.2,0.2,0.2)));
    fuente->agregar(new P2Fuente(30,40));

    agregar(fuente);

    NodoGrafoEscena * circuloCoches1 = new NodoGrafoEscena();

    float numCochesExt = 9;

    unsigned k = circuloCoches1->agregar(rotate(radians(0.0f), vec3(0.0,1.0,0.0)));
    circuloCoches1->agregar(translate(vec3(6.0,1.0,6.0)));
    circuloCoches1->agregar(scale(vec3((0.1,0.1,0.1))));
    circuloCoches1->agregar( new MallaRevolPLY("big_dodge",50));

    for (unsigned i = 0; i < numCochesExt; i++)
    {
        circuloCoches1->agregar( glm::rotate( glm::radians(360.0f/numCochesExt), vec3( 0.0, 1.0, 0.0 )));
        circuloCoches1->agregar(new MallaRevolPLY("big_dodge",50));
    }

    agregar(circuloCoches1);

    pm_circ1 = circuloCoches1->leerPtrMatriz(k);
}

unsigned P3Rotonda::leerNumParametros() const
{
    return num_params;
}

void P3Rotonda::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

    switch (iParam)
    {
    case 0:
    {
        
        const float radio = 10.0f;

        // Velocidad angular en radianes por segundo
        const float velocidadAngular = 1.0f;

        // Calcular la nueva posición del palo en función del tiempo
        float nuevaPosX = radio * cos(velocidadAngular * t_sec);
        float nuevaPosZ = radio * sin(velocidadAngular * t_sec);

        // Construir la nueva posición en el espacio 3D
        glm::vec3 nuevaPosicion = glm::vec3(nuevaPosX, 0.0f, nuevaPosZ);

        // Establecer la nueva posición del palo
        fijarMovCoche(nuevaPosicion);
    }
        break;

    default:
        break;

    }
}

void P3Rotonda::fijarMovCoche(glm::vec3 pos)
{
    *pm_circ1 = glm::translate(pos);
}


// EJERCICIO 4 - EXAMEN
P4Rotonda::P4Rotonda()
{
    using namespace glm;

    NodoGrafoEscena * anillo1 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(1.2,1.0,1.2)));
    anillo1->agregar( new Material(new TexturaXZ("window-icon.jpg"), 5.0,0.4,0.3,10));  // textura y material circulo interior
    anillo1->agregar( new P2Anillo(30,30,4.5));
    agregar(anillo1);

    NodoGrafoEscena * anillo2 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(6.0,1.0,6.0)));
    anillo2->agregar( new Material(new Textura("asfalto.jpg"), 0.3,0.4,5.0,50));  // textura y material circulo exterior
    anillo2->agregar( new P2Anillo(30,30,9.0));
    agregar(anillo2);

    NodoGrafoEscena * fuente = new NodoGrafoEscena();
    fuente->ponerColor(vec3(0.5,0.5,1.0));              // color fuente
    fuente->agregar(new Material(0.3,5.0,0.1,10));      // material fuente
    fuente->agregar(scale(vec3(0.2,0.2,0.2)));
    fuente->agregar(new P2Fuente(30,40));

    agregar(fuente);

    NodoGrafoEscena * circuloCoches1 = new NodoGrafoEscena();

    circuloCoches1->agregar(translate(vec3(6.0,1.0,6.0)));
    circuloCoches1->agregar(scale(vec3((0.1,0.1,0.1))));
    circuloCoches1->ponerColor(vec3(0.5,1.0,0.5));            // color coche
    circuloCoches1->agregar( new Material(0.3,0.4,5.0,50));   // Material coche
    circuloCoches1->agregar(new MallaRevolPLY("big_dodge",50));


    agregar(circuloCoches1);
}


// EJERCICIO 5 - EXAMEN (06/02/2024)

bool NodoFuente::cuandoClick(const glm::vec3 & centro_wc)
{
   using namespace glm;
   if (tieneColor())
   {
      if (leerColor() == vec3(1.0,1.0,1.0))
      {
         ponerColor(vec3(1.0,0.0,0.0));
         agregar( new Material(5.0,0.4,0.3,10));

      }
      else if (leerColor() == vec3(1.0,0.0,0.0))
         ponerColor(vec3(1.0,1.0,1.0));
   }

   else ponerColor(vec3(1.0,0.0,0.0));
   
   return true;
}

P5Rotonda::P5Rotonda()
{
    using namespace glm;

    NodoGrafoEscena * anillo1 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(1.2,1.0,1.2)));
    anillo1->agregar( new Material(new TexturaXZ("window-icon.jpg"), 5.0,0.4,0.3,10));  // textura y material circulo interior
    anillo1->agregar( new P2Anillo(30,30,4.5));
    anillo1->ponerIdentificador(1);  // identificador del anillo interior
    agregar(anillo1);

    NodoGrafoEscena * anillo2 = new NodoGrafoEscena();
    anillo1->agregar(scale(vec3(6.0,1.0,6.0)));
    anillo2->agregar( new Material(new Textura("asfalto.jpg"), 0.3,0.4,5.0,50));  // textura y material circulo exterior
    anillo2->agregar( new P2Anillo(30,30,9.0));
    anillo2->ponerIdentificador(2); // identificador del anillo exterior
    agregar(anillo2);

    NodoGrafoEscena * fuente = new NodoGrafoEscena();
    fuente->ponerColor(vec3(0.5,0.5,1.0));              // color fuente
    fuente->agregar(new Material(0.3,5.0,0.1,10));      // material fuente
    fuente->agregar(scale(vec3(0.2,0.2,0.2)));
    fuente->ponerIdentificador(3); // identificador de la fuente
    fuente->agregar(new P2Fuente(30,40));

    agregar(fuente);

    NodoGrafoEscena * circuloCoches1 = new NodoGrafoEscena();

    circuloCoches1->agregar(translate(vec3(6.0,1.0,6.0)));
    circuloCoches1->agregar(scale(vec3((0.1,0.1,0.1))));
    circuloCoches1->ponerColor(vec3(0.5,1.0,0.5));            // color coche
    circuloCoches1->agregar( new Material(0.3,0.4,5.0,50));   // Material coche

    NodoGrafoEscena * coche = new NodoGrafoEscena();
    coche->agregar(new MallaRevolPLY("big_dodge",50));
    coche->ponerIdentificador(4);
    circuloCoches1->agregar(coche);


    agregar(circuloCoches1);
}










