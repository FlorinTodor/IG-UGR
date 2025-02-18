// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
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

  // Práctica 4: Creación de tablas de normales
   vector<vec3> nor_aritas,aristas;
   vector<vec3> nor_vertices;
   vector<float> long_aristas;

  
   // 1. Cálculo previo de las aristas
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

   // 4. Cálculo de coordenadas de textura

   vector<float> t;
   float suma;
   float long_total = 0.0;

   for (unsigned i = 0; i < long_aristas.size(); i++)
      long_total += long_aristas[i];

   for (unsigned i = 0; i < perfil.size(); i++)
   {
      suma = 0.0;

      for(unsigned j = 0; j < i; j++)
         suma += long_aristas[i];
      
      t.push_back(suma / long_total);
   } 
      

   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //

   // Partimos de la tabla de vértices vacía.
   vertices.clear();
   unsigned int m = perfil.size();
   unsigned int n = num_copias;

   //Para cada i desde 0 hasta n − 1 (ambos incluidos)
   // • Para cada j desde 0 hasta m − 1 (ambos incluidos)
   //    ◦ Sea q = vértice obtenido rotando pj un ángulo igual a 2πi/(n − 1) radianes.
   //    ◦ Añadir q a la tabla de vértices (al final).

   for (unsigned int i = 0; i < n; i++){

      for (unsigned int j = 0; j < m; j++){

         float angle = (2.0*M_PI*float(i))/(n-1.0);
         float ratio = perfil.at(j).x;
         glm::vec3 q = {ratio*cos(angle), perfil.at(j).y, -ratio*sin(angle)};
         vertices.push_back(q);

         // rotación de las normales
         float ratio_n = nor_vertices[j].x;
         vec3 rotation(ratio_n*cos(angle), nor_vertices[j].y, -ratio_n*sin(angle));
         
         if (rotation.length() != 0.0)
            rotation = normalize(rotation);
         else rotation = vec3(0.0,0.0,0.0);
         
         nor_ver.push_back(rotation);

         cc_tt_ver.push_back(vec2(i/(n-1.0f),1-t[j]));

      }
   }

   // Partimos de la tabla de triángulos vacía
   // Para cada i desde 0 hasta n − 2 (ambos incluidos)
   //    • Para cada j desde 0 hasta m − 2 (ambos incluidos)
   //         ◦ Sea k = im + j
   //         ◦ Añadir triángulo formado por los índices k, k + m y k + m + 1.
   //         ◦ Añadir triángulo formado por los índices k, k + m + 1 y k + 1.

   triangulos.clear();
   for (unsigned int i = 0; i < n-1; i++){
      for (unsigned int j = 0; j < m-1; j++){
         unsigned int k = i*m+j;
         glm::vec3 t1 = {k,k+m,k+m+1};
         glm::vec3 t2 = {k,k+m+1,k+1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
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
   std::vector<glm::vec3> vertices_perfil;
   LeerVerticesPLY(nombre_arch,vertices_perfil);
   inicializar(vertices_perfil, nperfiles);

}

// -----------------------------------------------------------------------------
Cilindro::Cilindro
(
   const int num_verts_per,   //m
   const unsigned nperfiles   //n
)
{
   // Cilindro de base con centro en el (0,0,0) y radio y altura 1. 
   // 1. Creación del perfil a revolucionar
   std::vector<glm::vec3>  perfil_cili;

   perfil_cili.push_back(glm::vec3(0.0, 0.0, 0.0));

   float h;

   for(int i=0; i<num_verts_per-1; i++){

       h = float(i)/(num_verts_per-1);
      perfil_cili.push_back(glm::vec3(1.0,h,0.0));

   }

   perfil_cili.push_back(glm::vec3(0.0, h, 0.0));

   inicializar(perfil_cili, nperfiles);

}

// -----------------------------------------------------------------------------
Cono::Cono
(
   const int num_verts_per,   //m
   const unsigned nperfiles   //n
)
{
   // Cono de base con centro en el (0,0,0) y radio y altura 1. 
   // 1. Creación del perfil a revolucionar
   std::vector<glm::vec3>  perfil_cono;
   
   for(int i=0; i<num_verts_per; i++){

      float h = float(i)/(num_verts_per-1);
      perfil_cono.push_back(glm::vec3(1-h,h,0.0));

   }

   inicializar(perfil_cono, nperfiles);

}

// -----------------------------------------------------------------------------
Esfera::Esfera
(
   const int num_verts_per,   //m
   const unsigned nperfiles   //n
)
{
   // Esfera de base con centro en el (0,0,0) y radio y altura 1. 
   std::vector<glm::vec3>  perfil_Esfera;
   
   for (int i = 0; i < num_verts_per; i++){
      double alpha = (-M_PI / 2.0 + float(i) / (num_verts_per -1) * M_PI);
      perfil_Esfera.push_back(glm::vec3(cos(alpha), sin(alpha),0.0));

   }
   

   inicializar(perfil_Esfera, nperfiles);

}


// -----------------------------------------------------------------------------
RelojArena::RelojArena
(
   const int num_verts_per,   //m
   const unsigned nperfiles   //n
)
{

   // 1. Creación del perfil a revolucionar
   std::vector<glm::vec3>  perfil_ra;
   glm::vec3 punto_inicial = {0.0,0.0,0.0};
   perfil_ra.push_back(punto_inicial);
   
   for (int i = 0; i < num_verts_per; i++){
      
      double angle = (2*i*M_PI)/num_verts_per;
      glm::vec3 q  = {sin(angle), cos(angle/2), 0.0 };
      perfil_ra.push_back(q);

   }

   inicializar(perfil_ra, nperfiles);

}

// -----------------------------------------------------------------------------
Toro::Toro
(
   const int num_verts_per,   //m
   const unsigned nperfiles,   //n
   const float x,
   const float y,
   const float radio_menor
)
{

   ponerNombre( std::string("malla por revolución del perfil de un Toro") );

   std::vector<glm::vec3> perfil;
   
   float distancia_ptos = 2*M_PI/num_verts_per;

   for( int i = 0; i <= num_verts_per; ++i)
      perfil.push_back( {(radio_menor)*cos(i*distancia_ptos)+x, (radio_menor)*sin(i*distancia_ptos)+y, 0} ); 

   inicializar(perfil, nperfiles);

}

// -----------------------------------------------------------------------------
Semiesfera::Semiesfera
(
   const int num_verts_per,   //m
   const unsigned nperfiles,  //n  
   const float radio          // radio 
)
{
   std::vector<glm::vec3>  perfil_semiesfera;

   

   for (int i = 0; i < num_verts_per; i++)
   {
      float angle = (-M_PI + float(i) / (num_verts_per -1) * M_PI);
      perfil_semiesfera.push_back({radio*cosf(angle), -radio*sin(angle),0.0f});
   }

   inicializar(perfil_semiesfera, nperfiles);

}

//------------------------------------------------------------------------------------
// EJERCICIO REPASO PRÁCTICA 2
//------------------------------------------------------------------------------------
void MallaBarrido::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // Partimos de la tabla de vértices vacía.
   vertices.clear();
   unsigned int m = perfil.size();
   unsigned int n = num_copias;

   // creamos la tabla de vértices trasladando el perfil 
   // a lo largo del eje y tantas veces como copias del perfil tengamos
   for (unsigned int i = 0; i < n; i++){

      for (unsigned int j = 0; j < m; j++){

         glm::vec3 q = {perfil.at(j).x, float(i)/5.0, perfil.at(j).z};
         vertices.push_back(q);

      }
   }

   // creación de la tabla de triángulos
   triangulos.clear();
   for (unsigned int i = 0; i < n-1; i++){
      for (unsigned int j = 0; j < m-1; j++){
         unsigned int k = i*m+j;
         glm::vec3 t1 = {k,k+m,k+m+1};
         glm::vec3 t2 = {k,k+m+1,k+1};

         triangulos.push_back(t1);
         triangulos.push_back(t2);
      }
   }


}

SemiCilindroBarrido::SemiCilindroBarrido
(
   const int m, // número de vértices del perfil original
   const unsigned n // número de perfiles
)
{

   std::vector<glm::vec3>  perfil_semiesfera;
   

   for (int i = 0; i < m; i++)
   {
      float angle = (-M_PI + float(i) / (m -1) * M_PI);
      perfil_semiesfera.push_back({cosf(angle), 0.0f, -sin(angle)});
   }

   inicializar(perfil_semiesfera, m);

}


