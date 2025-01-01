// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C


// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....


   for (int i = 0; i < nt; i++) {
      glm::vec3 p = vertices[triangulos[i][0]];
      glm::vec3 q = vertices[triangulos[i][1]];
     glm::vec3 r = vertices[triangulos[i][2]];

     glm::vec3 a = q - p;
     glm::vec3 b = r - p;

     glm::vec3 m_c = cross(a, b);

      glm::vec3 n_c;
      if (length(m_c) != 0.0)
         n_c = normalize(m_c);
      else
         n_c = glm::vec3(0.0, 0.0, 0.0);

      nor_tri.push_back(n_c);
   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......

    calcularNormalesTriangulos();

   nor_ver = std::vector<vec3>(vertices.size(), vec3(0.0, 0.0, 0.0));

   for (int i = 0; i < triangulos.size(); i++) {
      for (int j = 0; j < 3; j++) {
         unsigned indice_vertice = triangulos[i][j];

         nor_ver[indice_vertice] = nor_ver[indice_vertice] + nor_tri[i];
      }
   }

   for (int i = 0; i < nor_ver.size(); i++)
      if (length(nor_ver[i]) != 0.0)
         nor_ver[i] = normalize(nor_ver[i]);


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')

if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }
   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //

if(dvao == nullptr){
      dvao = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones,vertices));
      dvao->agregar(new DescrVBOInds(triangulos));
      if(cc_tt_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver));
      if(col_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_colores,col_ver));
      if(nor_ver.size() > 0)
         dvao->agregar(new DescrVBOAtribs(ind_atrib_normales,nor_ver));
   }
   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'

dvao->draw(GL_TRIANGLES);
   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
if(tieneColor())
      cauce->popColor();
}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   if(cc_tt_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_coord_text,0);
   if(col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores,0);
   if(nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales,0);
   //    2. Dibujar la malla (únicamente visualizará los triángulos)
   dvao->draw(GL_TRIANGLES);
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   if(cc_tt_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_coord_text,1);
   if(col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores,1);
   if(nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales,1);

}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:

    if (dvao_normales == nullptr) {
        
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
       for (int i = 0; i < vertices.size(); i++) {
         segmentos_normales.push_back(vertices[i]);
         segmentos_normales.push_back(vertices[i] + (0.35f * nor_ver[i]));
      }

   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
      dvao_normales = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones, segmentos_normales));
   // 
    }
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.
    dvao_normales->draw(GL_LINES);

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch,vertices,triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
   calcularNormales();

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
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
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

CuboColores::CuboColores()
:  MallaInd( "cubo con colores" )
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
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)
         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)
         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   // Añadimos los colores de los vértices
   // El color de cada vértice depende de su posición:
   // R depende de X (-1 → 0, +1 → 1)
   // G depende de Y (-1 → 0, +1 → 1)
   // B depende de Z (-1 → 0, +1 → 1)
   for (const auto & v : vertices) {
      col_ver.push_back({
         (v.x + 1.0f) / 2.0f,  // R: normalizado entre 0 y 1
         (v.y + 1.0f) / 2.0f,  // G: normalizado entre 0 y 1
         (v.z + 1.0f) / 2.0f   // B: normalizado entre 0 y 1
      });
   }
}





Tetraedro::Tetraedro() : MallaInd (" tetaedro 4 vértices y 4 caras "){
   ponerColor({0.0, 1.0, 0.0});

/* EXPLICACIÓN DE LOS VÉRTICES Y TRIÁNGULOS

   Los vértices son puntos en el espacio tridimensional que definen la geometría del objeto.

   Los triángulos son las caras del objeto, definidas por tres vértices.

   Por ejemplo triangulos = { {0,1,2}} -> significa que la primera cara del objeto está definida por los vértices 0, 1 y 2.

*/


// Tetaedro Regular 
   /*
      vertices = {
      {1.0, 1.0, 1.0},
      {-1.0, -1.0, 1.0},
      {-1.0, 1.0, -1.0},
      {1.0, -1.0, -1.0}
      };

      triangulos = {
         {0, 1, 2},
         {0, 2, 3},
         {0, 3, 1},
         {1, 3, 2}
      }; 
   */

// Tetaedro No Regular
   vertices = {
      {0.0, 0.0, 1.0},
      {2.0, 0.0, 0.0},
      {0.0, 3.0, 0.0},
      {0.0, 0.0, 0.0}
   };


   triangulos = {
      {0, 1, 2},
      {0, 2, 3},
      {0, 3, 1},
      {1, 3, 2}
   };


}

/*

El constructor inicializa las tablas de vértices, triángulos y colores de una malla indexada con 2n trián-
gulos y 2n + 1 vértices, en forma de estrella, plana (en el plano perpendicular al eje Z) y con n puntas.
Los vértices tienen coordenadas entre 0 y 1 en X y en Y (y todos tienen Z igual a cero). El centro de la
estrella está en (0,5, 0,5) en X e Y, y los radios hasta las puntas son de longitud 0,5
El vértice central tiene color blanco.

El resto de vértices tienen colores cuyas componentes R, G y B coin-
ciden con sus coordenadas X, Y y Z, respectivamente.
*/

//Ejercicios ADICIONALES PRACTICA 1

EstrellaZ::EstrellaZ(unsigned n) : 
MallaInd("EstrellaZ " + std::to_string(2 * n) + " triángulos y " + std::to_string(2 * n + 1) + " vértices") {
   ponerColor({0.0, 1.0, 0.0}); //malla verde

   vertices.push_back({0.5, 0.5, 0.0}); // Centro de la estrella, vértice central o vértice 0
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para el centro

   /* Añadir vértices exteriores e interiores*/
   
   for (unsigned i = 0; i < n; ++i) {
      float angulo = 2.0f * M_PI * i / n; // Ángulo de cada vértice
      float x_exterior = 0.5f + 0.5f * cos(angulo); // Coordenadas del vértice exterior
      float y_exterior = 0.5f + 0.5f * sin(angulo); // Coordenadas del vértice exterior
      float x_interior = 0.5f + 0.25f * cos(angulo + M_PI / n); // Coordenadas del vértice interior
      float y_interior = 0.5f + 0.25f * sin(angulo + M_PI / n); // Coordenadas del vértice interior

      vertices.push_back({x_exterior, y_exterior, 0.0}); // Añadir vértice exterior
      vertices.push_back({x_interior, y_interior, 0.0}); // Añadir vértice interior

      col_ver.push_back({x_exterior, y_exterior, 0.0}); // Añadir color del vértice exterior, colores iguales a las coordenas
      col_ver.push_back({x_interior, y_interior, 0.0}); // Añadir color del vértice interior
   }


   /* Definimos los triángulos*/
   for (unsigned i = 0; i < n; ++i) {
      /* Explica el por qué de esos valores aquí:

         Los vértices exteriores son los vértices que están en la parte exterior de la estrella
         Los vértices interiores son los vértices que están en la parte interior de la estrella

         Los vértices exteriores son impares y los interiores son pares
      
      
      */
      unsigned exterior1 = 1 + 2 * i ; // Vértice exterior 1
      unsigned interior1 = 2 + 2 * i; // Vértice interior 1
      unsigned exterior2 = 1 + 2 * ((i + 1) % n);  // Vértice exterior 2
     // unsigned interior2 = 2 + 2 * ((i + 1) % n); // Vértice interior 2

      triangulos.push_back({0, exterior1, interior1}); // Triángulo interior
      triangulos.push_back({0, interior1, exterior2}); // Triángulo exterior
   }
}


CasaX::CasaX()
: MallaInd("Casa X"){
   vertices =
   vertices =
      {  { 0.0, 0.5, 0.5 },  // frente, arriba izquierda    0
         { 1.0, 0.5, 0.5 },  // frente, arriba derecha      1
         { 0.0, 0.0, 0.5 },  // frente, abajo izquierda     2
         { 1.0, 0.0, 0.5 },  // frente, abajo derecha       3
         { 1.0, 0.5, 0.0 },  // atrás, arriba izquierda     4
         { 0.0, 0.5, 0.0 },  // atrás, arriba derecha       5
         { 1.0, 0.0, 0.0 },  // atrás, abajo izquierda      6
         { 0.0, 0.0, 0.0 },  // atrás, abajo derecha        7
         { 0.0, 1.0, 0.25 }, // pico izquierda (de frente)  8
         { 1.0, 1.0, 0.25 },  // pico derecha (de frente)    9
      } ;
   
   triangulos =
         {  //paredes
            {0,1,2}, {1,3,2}, //frente 
            {5,6,7}, {4,5,6}, //atrás
            {1,3,4}, {3,4,6}, //derecha
            {0,2,7}, {5,7,0}, //izquierda
            //techo
            {0,8,9}, {1,9,0}, //frente 
            {9,8,5}, {4,5,9}, //atrás
            {0,5,8}, //derecha
            {1,4,9}, //izquierda
         } ;

   for(unsigned i=0; i<vertices.size(); i++) {
      col_ver.push_back(vertices[i]);
   }
}


MallaTriangulo::MallaTriangulo()
:  MallaInd( "MallaTriangulo" )
{
   // Vértices: base centrada en el origen, altura raíz de 2
   vertices = {
      { -0.5, 0.0, 0.0 },    // vértice 0: esquina izquierda
      { +0.5, 0.0, 0.0 },    // vértice 1: esquina derecha
      { 0.0, sqrt(2.0), 0.0 } // vértice 2: punta superior
   };

   // Un único triángulo
   triangulos = { {0, 1, 2} };
}

MallaCuadrado::MallaCuadrado()
:  MallaInd( "MallaCuadrado" )
{
   // Vértices: cuadrado centrado en el origen, lado 2
   vertices = {
      { -1.0, -1.0, 0.0 }, // vértice 0: esquina inferior izquierda
      { +1.0, -1.0, 0.0 }, // vértice 1: esquina inferior derecha
      { -1.0, +1.0, 0.0 }, // vértice 2: esquina superior izquierda
      { +1.0, +1.0, 0.0 }  // vértice 3: esquina superior derecha
   };

   // Dos triángulos
   triangulos = {
      {0, 1, 2}, // triángulo inferior
      {1, 3, 2}  // triángulo superior
   };
}

MallaPiramideL::MallaPiramideL()
:  MallaInd( "MallaPiramideL" )
{
   // Vértices de la base en forma de L (en el plano XY)
   vertices = {
      { 0.0, 0.0, 0.0 },  // v0: esquina interior de la L
      { 1.0, 0.0, 0.0 },  // v1: extremo derecho
      { 0.0, 1.0, 0.0 },  // v2: extremo superior
      { -1.0, 0.0, 0.0 }, // v3: extremo izquierdo
      { -1.0, -1.0, 0.0 },// v4: esquina inferior izquierda
      { 0.0, -1.0, 0.0 }, // v5: esquina inferior derecha
      { 0.0, 0.0, 1.0 }   // v6: ápice de la pirámide
   };

   // Triángulos
   triangulos = {
      // Base (3 triángulos mínimos para formar la L)
      {0, 5, 1},  // triángulo derecho
      {0, 4, 5},  // triángulo inferior
      {0, 3, 4},  // triángulo izquierdo
      {0, 2, 3},  // triángulo superior
      // Caras laterales (6 triángulos)
      {6, 1, 0},  // cara lateral derecha
      {6, 0, 2},  // cara lateral superior
      {6, 2, 3},  // cara lateral superior izquierda
      {6, 3, 4},  // cara lateral inferior izquierda
      {6, 4, 5},  // cara lateral inferior
      {6, 5, 1}   // cara lateral inferior derecha
   };
}






/**      EJERCICIOS ADICIONALES PRACTICA 2 */

PiramideEstrellaZ::PiramideEstrellaZ(unsigned n)
: MallaInd("PiramideZ practica 2") {
   ponerColor({0.0, 1.0, 0.0}); //malla verde

   vertices.push_back({0.5, 0.5, 0.0}); // Centro de la estrella, vértice central o vértice 0
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para el centro

   /* Añadir vértices exteriores e interiores*/
   
   for (unsigned i = 0; i < n; ++i) {
      float angulo = 2.0f * M_PI * i / n; // Ángulo de cada vértice
      float x_exterior = 0.5f + 0.5f * cos(angulo); // Coordenadas del vértice exterior
      float y_exterior = 0.5f + 0.5f * sin(angulo); // Coordenadas del vértice exterior
      float x_interior = 0.5f + 0.25f * cos(angulo + M_PI / n); // Coordenadas del vértice interior
      float y_interior = 0.5f + 0.25f * sin(angulo + M_PI / n); // Coordenadas del vértice interior

      vertices.push_back({x_exterior, y_exterior, 0.0}); // Añadir vértice exterior
      vertices.push_back({x_interior, y_interior, 0.0}); // Añadir vértice interior

      col_ver.push_back({x_exterior, y_exterior, 0.0}); // Añadir color del vértice exterior, colores iguales a las coordenas
      col_ver.push_back({x_interior, y_interior, 0.0}); // Añadir color del vértice interior
   }

   // Añadir el vértice del ápice de la pirámide
   vertices.push_back({0.5, 0.5, 0.5});
   col_ver.push_back({1.0, 1.0, 1.0}); // Color blanco para el ápice

   /* Definimos los triángulos*/
   for (unsigned i = 0; i < n; ++i) {
      /* Explica el por qué de esos valores aquí:

         Los vértices exteriores son los vértices que están en la parte exterior de la estrella
         Los vértices interiores son los vértices que están en la parte interior de la estrella

         Los vértices exteriores son impares y los interiores son pares
      
      
      */
      unsigned exterior1 = 1 + 2 * i ; // Vértice exterior 1
      unsigned interior1 = 2 + 2 * i; // Vértice interior 1
      unsigned exterior2 = 1 + 2 * ((i + 1) % n);  // Vértice exterior 2
    //  unsigned interior2 = 2 + 2 * ((i + 1) % n); // Vértice interior 2

      // Triángulos de la base
      triangulos.push_back({0, exterior1, interior1});
      triangulos.push_back({0, interior1, exterior2});

      // Triángulos de las caras laterales
      triangulos.push_back({exterior1, interior1, 2*n+1});
      triangulos.push_back({interior1, exterior2, 2*n+1});
   }
}

RejillaY::RejillaY(unsigned m, unsigned n) : MallaInd ("RejillaY"){

   // Crear los vértices
   for (unsigned i = 0; i < m; ++i) {
      for (unsigned j = 0; j < n; ++j) {
         float x = static_cast<float>(i) / (m - 1);
         float z = static_cast<float>(j) / (n - 1);
         vertices.push_back({x, 0.0f, z});
         col_ver.push_back({x, 0.0f, z});
      }
   }

   // Crear los triángulos
   for (unsigned i = 0; i < m - 1; ++i) {
      for (unsigned j = 0; j < n - 1; ++j) {
         unsigned v0 = i * n + j;
         unsigned v1 = v0 + 1;
         unsigned v2 = v0 + n;
         unsigned v3 = v2 + 1;

         // Primer triángulo de la celda
         triangulos.push_back({v0, v1, v2});

         // Segundo triángulo de la celda
         triangulos.push_back({v1, v3, v2});
      }
   }

}

MallaTorre::MallaTorre(unsigned n) : MallaInd("MallaTorre"){

   // Crear los vértices
   for (unsigned i = 0; i <= n; ++i) {
      float y = static_cast<float>(i);
      vertices.push_back({0.0f, y, 0.0f});
      vertices.push_back({1.0f, y, 0.0f});
      vertices.push_back({1.0f, y, 1.0f});
      vertices.push_back({0.0f, y, 1.0f});

      col_ver.push_back({0.0f, y / n, 0.0f});
      col_ver.push_back({1.0f, y / n, 0.0f});
      col_ver.push_back({1.0f, y / n, 1.0f});
      col_ver.push_back({0.0f, y / n, 1.0f});
   }

   // Crear los triángulos
   for (unsigned i = 0; i < n; ++i) {
      unsigned base = i * 4;

      // Cara 1
      triangulos.push_back({base, base + 1, base + 5});
      triangulos.push_back({base, base + 5, base + 4});

      // Cara 2
      triangulos.push_back({base + 1, base + 2, base + 6});
      triangulos.push_back({base + 1, base + 6, base + 5});

      // Cara 3
      triangulos.push_back({base + 2, base + 3, base + 7});
      triangulos.push_back({base + 2, base + 7, base + 6});

      // Cara 4
      triangulos.push_back({base + 3, base, base + 4});
      triangulos.push_back({base + 3, base + 4, base + 7});
   }
}


   
// ****************************************************************************


// Clase Cubo24

Cubo24::Cubo24() {
   vertices =
      {
         {+1.0, -1.0, +1.0}, // 0
         {+1.0, +1.0, +1.0}, // 1
         {+1.0, +1.0, -1.0}, // 2
         {+1.0, -1.0, -1.0}, // 3


         {-1.0, -1.0, +1.0}, // 4
         {-1.0, +1.0, +1.0}, // 5
         {+1.0, +1.0, +1.0}, // 6
         {+1.0, -1.0, +1.0}, // 7


         {-1.0, -1.0, -1.0}, // 8
         {-1.0, +1.0, -1.0}, // 9
         {-1.0, +1.0, +1.0}, // 10
         {-1.0, -1.0, +1.0}, // 11

         {+1.0, -1.0, -1.0}, // 12
         {+1.0, +1.0, -1.0}, // 13
         {-1.0, +1.0, -1.0}, // 14
         {-1.0, -1.0, -1.0}, // 15


         {+1.0, +1.0, +1.0}, // 16
         {-1.0, +1.0, +1.0}, // 17
         {-1.0, +1.0, -1.0}, // 18
         {+1.0, +1.0, -1.0}, // 19

         {+1.0, -1.0, +1.0}, // 20
         {-1.0, -1.0, +1.0}, // 21
         {-1.0, -1.0, -1.0}, // 22
         {+1.0, -1.0, -1.0}  // 23
      };

   triangulos =
      {
         {0, 3, 2},
         {0, 2, 1},

         {4, 7, 6},
         {4, 6, 5},

         {8, 11, 10},
         {8, 10, 9},

         {12, 15, 14},
         {12, 14, 13},

         {16, 19, 18},
         {16, 18, 17},

         {20, 22, 23},
         {20, 21, 22}
      };
      
   cc_tt_ver = {
      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0},

      {0.0, 1.0-0.0},
      {0.0, 1.0-1.0},
      {1.0, 1.0-1.0},
      {1.0, 1.0-0.0}
   };

   calcularNormales();
   
}
