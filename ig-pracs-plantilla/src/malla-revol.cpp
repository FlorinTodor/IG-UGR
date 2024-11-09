// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C


// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas creadas por revolución de un perfil (implementación). Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 


/*
Los pseudocódigos de los algoritmos de creación de mallas por revolución se encuentran en el pdf

*/
   //Rellenamos la tabla de vertices
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {

         /**
          *   tita es el ángulo de rotación calculado en radianes
          */
         float tita = (2*M_PI*i)/(num_copias - 1);

         // Matriz que vamos a usar para girar el perfil en el eje (eje vertical)


         /**
          * Esta matriz de rotación es una matriz de 3x3 que se usa para rotar un punto en 3D alrededor del eje Y. La matriz se define usando el ángulo tita:
          * 
            La primera fila corresponde a las nuevas coordenadas X después de la rotación.
            La segunda fila mantiene la coordenada Y sin cambios (rotación alrededor del eje Y).
            La tercera fila corresponde a las nuevas coordenadas Z después de la rotación.
          */
         std::vector<std::vector<float>> matriz_giro = 
         {  {cos(tita), 0.0, sin(tita)},
            {0 ,1, 0},
            {-sin(tita), 0, cos(tita)},
         };

         // Aplicamos la matriz de giro al perfil para obtener el nuevo vertice

         /**
          * 
          * Aquí, se multiplica la matriz de rotación por el vector del perfil original (perfil[j]) para obtener el nuevo vértice (nuevo_vertice).
          * Cada componente del nuevo vértice se calcula como una combinación lineal de las componentes del perfil original, ponderadas por los 
          * elementos correspondientes de la matriz de rotación.
          */
         glm::vec3 nuevo_vertice = {
            matriz_giro[0][0]*perfil[j][0] + matriz_giro[0][1]*perfil[j][1] + matriz_giro[0][2]*perfil[j][2],
            matriz_giro[1][0]*perfil[j][0] + matriz_giro[1][1]*perfil[j][1] + matriz_giro[1][2]*perfil[j][2],
            matriz_giro[2][0]*perfil[j][0] + matriz_giro[2][1]*perfil[j][1] + matriz_giro[2][2]*perfil[j][2],
         };

         // Añadimos el nuevo vertice a la tabla de vertices
         vertices.push_back(nuevo_vertice);  

      }
   }

   //Rellenamos la tabla de triangulos

   for (int i = 0; i < num_copias-1; i++) {
      for (int j = 0; j < perfil.size()-1; j++) {
         int k = i * perfil.size() + j;

         triangulos.push_back({k, k + perfil.size(), k + perfil.size() + 1});
         triangulos.push_back({k, k + perfil.size() + 1, k + 1});
      }
   }




}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................

   /*
   
   El perfil inicial se puede leer de un fichero PLY cuyo contenido sólo ha de tener las coordenadas de los vértices
   */
   std::vector<glm::vec3> perfil; // perfil del archivo ply
   LeerVerticesPLY(nombre_arch,perfil); // leer los vértices del perfil del archivo ply
   inicializar(perfil,nperfiles); // inicializar la malla de revolución

}



Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles) {
   ponerNombre("Cilindro");
   std::vector<glm::vec3> perfil; // perfil del cilindro
   float altura = 1.0f;
   float radio = 1.0f;
   float incremento_altura = altura / (num_verts_per - 1); // incremento de la altura entre dos vértices del perfil

   for (int i = 0; i < num_verts_per; ++i) {
      perfil.push_back(glm::vec3(radio, i * incremento_altura, 0.0f)); // añadir vértice al perfil
   }

   inicializar(perfil, nperfiles); // inicializar la malla de revolución
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles) {
   ponerNombre("Cono");
   std::vector<glm::vec3> perfil; // perfil del cono
   float altura = 1.0f; // altura del cono
   float radio = 1.0f; // radio de la base del cono
   float incremento_altura = altura / (num_verts_per - 1); // incremento de la altura entre dos vértices del perfil

   for (int i = 0; i < num_verts_per; ++i) {
      float r = radio * (1.0f - (float)i / (num_verts_per - 1));
      perfil.push_back(glm::vec3(r, i * incremento_altura, 0.0f)); // añadir vértice al perfil
   }

   inicializar(perfil, nperfiles); // inicializar la malla de revolución
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles) {
   ponerNombre("Esfera");
   std::vector<glm::vec3> perfil; // perfil de la esfera
   float radio = 1.0f; // radio de la esfera
   float incremento_angulo = M_PI / (num_verts_per - 1); // ángulo entre dos vértices del perfil

   for (int i = 0; i < num_verts_per; ++i) {
      float angulo = -M_PI / 2 + i * incremento_angulo; // ángulo del vértice
      perfil.push_back(glm::vec3(radio * cos(angulo), radio * sin(angulo), 0.0f)); // añadir vértice al perfil
   }

   inicializar(perfil, nperfiles); // inicializar la malla de revolución
}




