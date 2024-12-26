// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C
#include "examen-ec-p123.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace glm;

Ejercicio1::Ejercicio1()
{

    // 12 vértices y 10 triángulos
    
    vertices = {
        {-2.0f, 0.0f, 0.0f}, {-2.0f, 0.0f, 1.0f},   //X = -2
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},   //X = 0
        {0.33f,1.0f,0.0f}, {0.33f,1.0f,1.0f}, // X = 0
        {0.66f,1.0f,0.0f}, {0.66f,1.0f,1.0f}, // X = 1
        {0.99f,1.0f,0.0f}, {0.99f,1.0f,1.0f}, // X = 2
        {1.33,1.0f,0.0f}, {1.33f,1.0f,1.0f}, // X = 3


    };

    triangulos = 
    {
        // Cuadrado alargado  y subída a y=1
        {0, 1, 3},
        {0, 2, 3},
        {2, 3, 5},
        {2, 4, 5},

        // cuadrícula de arriba
        {4, 5, 7},
        {4, 6, 7},
        {6, 7, 9},
        {6,8,9},
        {8,9,11},
        {8,10,11},
    };

    col_ver.resize(vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    
        if(i == 0 || i == 2 )
            col_ver[i] = {1.0f, 1.0f, 1.0f}; //Blanco
        else
            col_ver[i] = {0.2f, 0.2f, 0.2f}; //Gris oscuro

}
Ejercicio2::Ejercicio2(int n) {
    assert(n >= 1);


    // Vértices comunes del eje
    vertices.push_back({-2.0f, 0.0f, 0.0f}); // Vértice 0
    vertices.push_back({-2.0f, 0.0f, 1.0f}); // Vértice 1
    col_ver.push_back({0.2f, 0.2f, 0.2f});   // Gris oscuro
    col_ver.push_back({0.2f, 0.2f, 0.2f});   // Gris oscuro

    // Generar réplicas rotadas
    for (unsigned i = 0; i < n; ++i) {
        float angle = i * (2.0f * M_PI / n); // Ángulo de rotación
        float cos_angle = cos(angle);
        float sin_angle = sin(angle);

        // Generar los vértices de la réplica actual
        for (int j = 2; j < 12; ++j) { // Evitamos vértices 0 y 1 (eje común)
            vec3 original_vertex = {
                (j == 2 || j == 3) ? 0.0f : (j <= 5) ? 0.33f : (j <= 7) ? 0.66f : (j <= 9) ? 0.99f : 1.33f,
                (j >= 4) ? 1.0f : 0.0f,
                (j % 2 == 0) ? 0.0f : 1.0f
            };

            // Aplicar rotación en torno al eje Z, algo no estoy calculando bie naquí
            vec3 rotated_vertex = {
                cos_angle * original_vertex.x - sin_angle * original_vertex.y ,
                sin_angle * original_vertex.x + cos_angle * original_vertex.y,
                original_vertex.z
            };

            vertices.push_back(rotated_vertex);
            col_ver.push_back((j == 4 || j == 5) ? vec3(1.0f, 1.0f, 1.0f) : vec3(0.2f, 0.2f, 0.2f));
        }

        // Generar los triángulos de la réplica actual
        unsigned base = 2 + i * 10; // Base de los índices para la réplica actual

        triangulos.push_back({0, 1, base + 1});
        triangulos.push_back({0, base + 0, base + 1});
        triangulos.push_back({base + 0, base + 1, base + 3});
        triangulos.push_back({base + 0, base + 2, base + 3});
        triangulos.push_back({base + 2, base + 3, base + 5});
        triangulos.push_back({base + 2, base + 4, base + 5});
        triangulos.push_back({base + 4, base + 5, base + 7});
        triangulos.push_back({base + 4, base + 6, base + 7});
        triangulos.push_back({base + 6, base + 7, base + 9});
        triangulos.push_back({base + 6, base + 8, base + 9});
    }
}


Ejercicio3::Ejercicio3(float w, float h)
{
    assert(w > 1);
    assert(h < 0.3);
    this->h = h;
    this->w= w;
    
    // Creamos el cubo base que usaremos para ambos prismas
    Cubo* cubo = new Cubo();
    
    // Nodo raíz del modelo
    NodoGrafoEscena* modelo = new NodoGrafoEscena();
    
    // Prisma inferior (tablero)
    NodoGrafoEscena* prisma_inferior = new NodoGrafoEscena();
    unsigned int indice_matriz_escalado_inferior = prisma_inferior->agregar(scale(vec3(1.0f, 1.0f, 1.0f)));
    
    // Escalamos y posicionamos el prisma inferior
    prisma_inferior->agregar(scale(vec3(w/2.0f, h/2.0f, w/2.0f)));
    prisma_inferior->agregar(translate(vec3(0.0f, 0.0f, 0.0f)));
    prisma_inferior->agregar(cubo);
    
    // Prisma superior (cubo pequeño)
    NodoGrafoEscena* prisma_superior = new NodoGrafoEscena();
    unsigned int indice_matriz_rot_superior = prisma_superior->agregar(rotate(0.0f, vec3(1.0f, 1.0f, 1.0f)));
    
    // Posicionamos el cubo superior sobre el tablero
    //prisma_superior->agregar(translate(vec3(0.0f, h, 0.0f)));
    prisma_superior->agregar(scale(vec3(0.2f, 0.2f, 0.2f)));
    prisma_superior->agregar(translate(vec3(1.0f, 1.0f, 1.0f)));
    prisma_superior->agregar(cubo);
    
    // Agregamos ambos prismas al modelo
    modelo->agregar(prisma_inferior);
    modelo->agregar(prisma_superior);
    agregar(modelo);
    
    // Guardamos los punteros a las matrices para la animación
    pm_matriz_sca_inferior = prisma_inferior->leerPtrMatriz(indice_matriz_escalado_inferior);
    pm_matriz_rot_superior = prisma_superior->leerPtrMatriz(indice_matriz_rot_superior);
}

unsigned Ejercicio3::leerNumParametros() const
{
    return 2; // Dos grados de libertad
}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    switch(iParam)
    {
        case 0: // Escalado del tablero
        {
            float escalado_max = 1.0f;
            float escalado_min = 1.0f/3.0f;
            float frecuencia = 1.0f;
            
            // Oscilación del escalado entre min y max
            float escalaActual = escalado_max + (escalado_min - escalado_max) * 0.5f * 
                               (1.0f - cos(2.0 * M_PI * frecuencia * t_sec));
            
            // Aplicar escalado en Y al prisma inferior
            *pm_matriz_sca_inferior = scale(vec3(1.0f, escalaActual, 1.0f));
            
            // Ajustar posición del cubo superior según el escalado
            float desplazamiento = h * (escalaActual - 1.0f);
            mat4 matriz_desplazamiento = translate(vec3(0.0f, desplazamiento, 0.0f));
            *pm_matriz_rot_superior = matriz_desplazamiento;
            break;
        }
        
        case 1: // Rotación del cubo superior sobre el centro del tablero
        {

            /* Me faltan menos de 5 minutos y no me viene a la cabeza como tenerlo colocado en otro lado que no sea el centro del cuadrado de abajo y que a su vez gire entorno el centro del tablero*/
            float anguloMax = 360.0f; // Rotación completa
            float frecuencia = 0.33f; // Frecuencia diferente para evitar sincronización
            
            float anguloActual = anguloMax * t_sec * frecuencia;
            
            // El cubo superior gira sobre el centro del tablero
            *pm_matriz_rot_superior = 
                
                translate(vec3(0.0f, 0.0f, 0.0f)) * // Ir al origen
                rotate(radians(anguloActual), vec3(0.0f, 1.0f, 0.0f)) * // Rotar sobre Y
                translate(vec3(w/2.0f, 0.0f, 0.0f)); // Desplazar a la distancia del radio
            
            break;
        }
    }
}