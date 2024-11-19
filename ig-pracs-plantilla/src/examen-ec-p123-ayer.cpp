
#include "examen-ec-p123-ayer.h"

using namespace std;
using namespace glm;

Ejercicio1::Ejercicio1()
{
    vertices = 
    {
        {-2.0f, 0.0f, 0.0f}, {-2.0f, 0.0f, 1.0f},   //X = -2
        {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 1.0f},   //X = -1
        {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},     //X =  0 //Y = 1
        {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},     //X = +1
        {2.0f, 0.0f, 0.0f}, {2.0f, 0.0f, 1.0f},     //X = +2
    };

    triangulos = 
    {
        {0, 1, 3},
        {0, 2, 3},
        {2, 3, 5},
        {2, 4, 5},
        {4, 5, 7},
        {4, 6, 7},
        {6, 7, 9},
        {6, 9, 8}
    };

    col_ver.resize(vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    
        if(i == 4 || i == 5)
            col_ver[i] = {1.0f, 1.0f, 1.0f}; //Blanco
        else
            col_ver[i] = {0.2f, 0.2f, 0.2f}; //Gris oscuro

}

Ejercicio2::Ejercicio2( int n)
{
   // Crear los vértices y colores
   for (unsigned i = 0; i <= n; ++i) {
      float z = static_cast<float>(i); // Profundidad en el eje Z

      // Añadir los vértices replicando la base en el eje Z
      vertices.push_back({-2.0f, 0.0f, z}); // X = -2    // Vértice 0 con z = 0 y vértice 5 con z = 1, vértice 10 con z = 2 y así con todos los demás vértices 
      vertices.push_back({-1.0f, 0.0f, z}); // X = -1  // Vértice 1 con z = 0 y vértice 6 con z = 1, vértice 11 con z = 2 y así con todos los demás vértices 
      vertices.push_back({0.0f, 1.0f, z});  // X =  0, Y = 1 // Vértice 2 con z = 0 y vértice 7 con z = 1, vértice 12 con z = 2 y así con todos los demás vértices 
      vertices.push_back({1.0f, 0.0f, z});  // X = +1 // Vértice 3 con z = 0 y vértice 8 con z = 1, vértice 13 con z = 2 y así con todos los demás vértices 
      vertices.push_back({2.0f, 0.0f, z});  // X = +2 // Vértice 4 con z = 0 y vértice 9 con z = 1, vértice 14 con z = 2 y así con todos los demás vértices 
 
      

      // Colores: blanco para el vértice central (índice 2), gris oscuro para el resto
      col_ver.push_back({0.2f, 0.2f, 0.2f}); // Gris oscuro
      col_ver.push_back({0.2f, 0.2f, 0.2f}); // Gris oscuro
      col_ver.push_back({1.0f, 1.0f, 1.0f}); // Blanco
      col_ver.push_back({0.2f, 0.2f, 0.2f}); // Gris oscuro
      col_ver.push_back({0.2f, 0.2f, 0.2f}); // Gris oscuro
   }

   // Crear los triángulos
   for (unsigned i = 0; i < n; ++i) {
      unsigned base = i * 5; // Base para la réplica actual (cada réplica tiene 5 vértices, que realmente son 10 cambiando el eje Z, por eso arriba solo tenemos puesto 5 vértices porque se repiten variando solamente el eje Z) 

      // Crear los triángulos conectando las réplicas
      triangulos.push_back({base, base + 1, base + 6}); // Cuadrilátero 1 (formado al principio por vértices (-2, 0, 0), (-1, 0, 0), (-1,0,1))
      triangulos.push_back({base, base + 6, base + 5});  // formado al principio por los vértices (-2, 0, 0), (-1, 0, 1), (-2, 0, 1)

      triangulos.push_back({base + 1, base + 2, base + 7}); // Cuadrilátero 2 (formado al principio por vértices (-1, 0, 0), (0, 1, 0), (0, 1, 1))
      triangulos.push_back({base + 1, base + 7, base + 6}); // formado al principio por los vértices (-1, 0, 0), (0, 1, 1), (-1, 0, 1)

    // así con todos (arriba tengo puesto el número de vértice de cada cosa, va variando según la base debido al número de vértices que se añaden en cada iteración)
      triangulos.push_back({base + 2, base + 3, base + 8}); // Cuadrilátero 3
      triangulos.push_back({base + 2, base + 8, base + 7});

      triangulos.push_back({base + 3, base + 4, base + 9}); // Cuadrilátero 4
      triangulos.push_back({base + 3, base + 9, base + 8});
   }
}



Ejercicio3::Ejercicio3(float w, float h)
{
    this->h = h;
    const float escala_anchura = w / 2.0f;
    const float escala_altura = h / 2.0f;

    Cubo *cubo = new Cubo();
    NodoGrafoEscena *modelo = new NodoGrafoEscena();

    NodoGrafoEscena *prisma_inferior = new NodoGrafoEscena();
    unsigned int indice_matriz_escalado_inferior = prisma_inferior->agregar(scale(vec3(1.0f, 1.0f, 1.0f)));

    prisma_inferior->agregar(scale(vec3(escala_anchura, escala_altura, escala_anchura)));
    prisma_inferior->agregar(translate(vec3(1.0f, 1.0f, 1.0f)));
    prisma_inferior->agregar(cubo);

    NodoGrafoEscena *prisma_superior = new NodoGrafoEscena();
    unsigned int indice_matriz_rotacion_superior = prisma_superior->agregar(rotate(0.0f, vec3(1.0f, 1.0f, 1.0f)));

    prisma_superior->agregar(translate(vec3(0.0f, h, 0.0f)));
    prisma_superior->agregar(scale(vec3(escala_anchura, escala_altura, escala_anchura)));
    prisma_superior->agregar(translate(vec3(1.0f, 1.0f, 1.0f)));
    prisma_superior->agregar(cubo);

    modelo->agregar(prisma_inferior);
    modelo->agregar(prisma_superior);
    agregar(modelo);

    pm_matriz_sca_inferior = prisma_inferior->leerPtrMatriz(indice_matriz_escalado_inferior);
    pm_matriz_rot_superior = prisma_superior->leerPtrMatriz(indice_matriz_rotacion_superior);
}


unsigned Ejercicio3::leerNumParametros() const
{
    return 2;
}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    switch (iParam)
    {
        case 0:
        
        {
            
            float escalado_max = 1.0f;
            float escalado_min = 1.0f/3.0f;
            float frecuencia = 1.0f;

            float escalaActual = escalado_max + (escalado_min - escalado_max) * 0.5f * (1.0f - cos(2.0 * M_PI * frecuencia * t_sec));

            *pm_matriz_sca_inferior = scale(vec3(1.0f, escalaActual, 1.0f));
            float desplazamiento = h * (escalaActual - 1.0f);

            mat4 matriz_desplazamiento = translate(vec3(0.0f, desplazamiento, 0.0f));
            *pm_matriz_rot_superior = matriz_desplazamiento;
            break;
        
        }

        case 1:
        {
            float anguloMax = 90.0f;
            float frecuencia = 0.33;

            float anguloActual = anguloMax * sin(2.0f * M_PI * frecuencia * t_sec);
            
            *pm_matriz_rot_superior =
            (*pm_matriz_rot_superior)
            * translate(vec3(0.0f, h, 0.0f))
            * rotate(radians(anguloActual), vec3(1.0f, 0.0f, 0.0f))
            * translate(vec3(0.0f, -h, 0.0f));

            break;
        }

        default:
        break;
    }
}