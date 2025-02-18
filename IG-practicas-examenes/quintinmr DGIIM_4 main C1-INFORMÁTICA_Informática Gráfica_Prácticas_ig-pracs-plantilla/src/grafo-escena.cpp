// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 

using namespace glm;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   if (apl->iluminacion)
      pila_materiales->push();

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //

   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   if (tieneColor()){

      cauce->pushColor();
      cauce->fijarColor(leerColor()); 
   }

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 

   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')

   for (unsigned i = 0; i < entradas.size(); i++)

      switch( entradas[i].tipo )
      {
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGL();  // 3.1
            break;

         case TipoEntNGE::transformacion:
            cauce->compMM( *(entradas[i].matriz ) ); // 3.2
            break;

         case TipoEntNGE::material:
            if (apl->iluminacion)
               pila_materiales->activar(entradas[i].material);
            break;

         case TipoEntNGE::noInicializado:
            break;
      
      }

   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();


   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if (tieneColor()){

      cauce->popColor();
   }


   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)
   if (apl->iluminacion)
      pila_materiales->pop();


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //

    // 1. Guardar copia de la matriz de modelado (con 'pushMM'),
    cauce->pushMM();

    // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').

   for (unsigned i = 0; i < entradas.size(); i++)

      switch (entradas[i].tipo)
      {
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGeomGL();
            break;
         
         case TipoEntNGE::transformacion:
            cauce->compMM( *(entradas[i].matriz ) );
            break;

         case TipoEntNGE::material:
            break;
            
         case TipoEntNGE::noInicializado:
            break;
      }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   cauce->popMM();


}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   cauce->pushMM();

   for (unsigned i = 0; i < entradas.size(); i++)
   {
     
      switch (entradas[i].tipo)
      {
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarNormalesGL();
            break;

         case TipoEntNGE::transformacion: 
            cauce->compMM( *(entradas[i].matriz) );
            break;

         default:
            break;
      }
      
   }

   cauce->popMM();

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   
   int id = leerIdentificador();

   if (id != -1)
   {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(id));
   }

   cauce->pushMM();

   for (unsigned i = 0; i < entradas.size(); i++)
   {
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         entradas[i].objeto->visualizarModoSeleccionGL();
         break;

      case TipoEntNGE::transformacion:
         cauce->compMM( *(entradas[i].matriz) );
      
      default:
         break;
      }
   }

   cauce->popMM();

   if (id != -1) cauce->popColor();


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);
   return (entradas.size()-1) ; 

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   assert(indice < entradas.size()); 
   assert(entradas[indice].tipo == TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);
   
   return entradas[indice].matriz;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
  
   if (!centro_calculado)
   {
      mat4 matrix (1.0f);
      vec3 centro (0.0,0.0,0.0);
      float n_centros = 0;
      
      for (unsigned i = 0; i < entradas.size(); i++)
      {
         
         switch (entradas[i].tipo)
         {
         case TipoEntNGE::objeto:
            entradas[i].objeto->calcularCentroOC();
            centro = centro + vec3(matrix*vec4(entradas[i].objeto->leerCentroOC(),1.0f));
            n_centros++;
            break;
         
         case TipoEntNGE::transformacion:
            matrix = matrix * (*entradas[i].matriz);
            break;
         }
       
      }

      centro = centro / n_centros;
      ponerCentroOC(centro);
      centro_calculado = true; 
   }

   else return;

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   if (ident_busc == leerIdentificador())
   {
      centro_wc = leerCentroOC();

      if (objeto == nullptr)
         cout << "identificador con puntero asociado nulo" << endl;
      
      *objeto = this;

      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   mat4 matrix = mmodelado;

   for (unsigned i = 0; i < entradas.size(); i++)
   {
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         if(entradas[i].objeto->buscarObjeto(ident_busc, matrix, objeto, centro_wc)) return true;
         break;

      case TipoEntNGE::transformacion:
         matrix = matrix * (*entradas[i].matriz);

      default:
         break;
      }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ; 
}


//-----------------------------------------------------------------------------------
// EJERCICIO 1 ADICIONAL - P3
// --> GrafoEstrellaX
//-----------------------------------------------------------------------------------
GrafoEstrellaX::GrafoEstrellaX(unsigned n)
{
   NodoGrafoEscena * star = new NodoGrafoEscena();

   unsigned i = agregar(rotate(radians(0.0f),vec3(0.0,0.0,1.0)));
   
   star->agregar(rotate(radians(float(90.0f)), vec3(0.0,1.0,0.0)));
   star->agregar(scale(vec3(1.3/0.5,1.3/0.5,1)));
   star->agregar(translate(vec3(-0.5,-0.5,0.0)));
   
   
   // Estrella de n puntas
   star->agregar(new EstrellaZ(n));
   agregar(star);

   NodoGrafoEscena * cono = new NodoGrafoEscena();

   cono->agregar(translate(vec3(0.0,1.3,0.0)));
   cono->agregar(scale(vec3(0.14,0.15,0.14)));
   cono->agregar(new Cono(50,50));

   for (unsigned i = 0; i < n; i++)
   {
      agregar(rotate(float(2*M_PI/n), vec3(1.0,0.0,0.0)));
      agregar(cono);
      
   } 

   pm_estrellaX = leerPtrMatriz(i);

   
}

unsigned GrafoEstrellaX::leerNumParametros() const
{
   return num_params;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

      switch (iParam)
      {
      case 0:
         
         *pm_estrellaX = rotate(radians(2.5f*360.0f*t_sec), vec3(1.0,0.0,0.0));
         break;
      
      default:
         break;
      }
}

//-----------------------------------------------------------------------------------
// EJERCICIO 2 ADICIONAL - P3
// --> GrafoCubos
//-----------------------------------------------------------------------------------
GrafoCubos::GrafoCubos()
{
   
   
   NodoGrafoEscena * rejilla = new NodoGrafoEscena();

   rejilla->agregar(translate(vec3(-0.5,-0.5,-0.5)));
   rejilla->agregar(new RejillaY(10,10));

   NodoGrafoEscena * cubos   = new NodoGrafoEscena();
   unsigned i = cubos->agregar(rotate(radians(0.0f),vec3(0.0,1.0,0.0)));
   cubos->agregar(scale(vec3(0.1,0.1,0.1)));
   cubos->agregar(translate(vec3(0.0,-6.0,0.0)));
   cubos->agregar(new Cubo());

   

   for (unsigned j = 0; j < 4; j++)
   {
      agregar(rotate(radians(90.0f),vec3(1.0,0.0,0.0)));
      agregar(rejilla);
      agregar(cubos);

   }

   agregar(rotate(radians(90.0f),vec3(0.0,0.0,1.0)));
   agregar(rejilla);
   agregar(cubos);

   agregar(rotate(radians(180.0f),vec3(0.0,0.0,1.0)));
   agregar(rejilla);
   agregar(cubos);



   pm_grafoCubos = cubos->leerPtrMatriz(i);

   
}

unsigned GrafoCubos::leerNumParametros() const
{
   return num_params;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

      switch (iParam)
      {
      case 0:
         *pm_grafoCubos = rotate(radians(2.5f*360.0f*t_sec), vec3(0.0,1.0,0.0));
         break;
      
      default:
         break;
      }
}

//-----------------------------------------------------------------------------------
// EJERCICIO TOROS
// --> Toros
//-----------------------------------------------------------------------------------
Toros::Toros()
{


   NodoGrafoEscena * toro = new NodoGrafoEscena();

   unsigned i = agregar(rotate(radians(0.0f),vec3(0.0,1.0,0.0)));
   toro->agregar(new Toro(32,64,6.5,0,0.5));
   agregar(toro);

   
   NodoGrafoEscena * toro1 = new NodoGrafoEscena();

   unsigned j = toro1->agregar(rotate(radians(0.0f),vec3(1.0,0.0,0.0)));
   toro1->agregar(translate(vec3(-3.0,0.0,0.0)));
   toro1->agregar(new Toro(32,64,2.5,0,0.5));
   agregar(toro1);

   NodoGrafoEscena * toro2 = new NodoGrafoEscena();

   unsigned k = toro2->agregar(rotate(radians(0.0f),vec3(1.0,0.0,0.0)));
   toro2->agregar(translate(vec3(3.0,0.0,0.0)));
   toro2->agregar(new Toro(32,64,2.5,0,0.5));
   agregar(toro2);

   pm_toro1 = leerPtrMatriz(i);
   pm_toro2 = toro1->leerPtrMatriz(j);
   pm_toro3 = toro2->leerPtrMatriz(k);

}

unsigned Toros::leerNumParametros() const
{
   return num_params;
}

void Toros::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

      switch (iParam)
      {
      case 0:
         *pm_toro1 = rotate(radians(360.0f*t_sec), vec3(0.0,1.0,0.0));
         *pm_toro2 = rotate(radians(360.0f*t_sec), vec3(1.0,0.0,0.0));
         *pm_toro3 = rotate(radians(-360.0f*t_sec), vec3(1.0,0.0,0.0));
         break;
      
      default:
         break;
      }
}


//-----------------------------------------------------------------------------------
// EJERCICIO COCHE - P3
// --> Coche
//-----------------------------------------------------------------------------------
Coche::Coche()
{

   NodoGrafoEscena * rueda = new NodoGrafoEscena();
   unsigned i = rueda->agregar(rotate(0.0f,vec3(0.0,0.0,1.0)));
   unsigned j = agregar(translate(vec3(0.0,0.0,0.0)));
   unsigned k = agregar(rotate(0.0f,vec3(0.0,1.0,0.0)));
   rueda->agregar(scale(vec3(0.25,0.25,0.15)));
   rueda->agregar(rotate(radians(90.0f), vec3(1.0,0.0,0.0)));
   rueda->agregar(new Cilindro(50,50));

   NodoGrafoEscena * rueda1 = new NodoGrafoEscena();
   rueda1->agregar(translate(vec3(1.25,0.0,1.15)));
   rueda1->agregar(rueda);
   agregar(rueda1);

   NodoGrafoEscena * rueda2 = new NodoGrafoEscena();
   rueda2->agregar(translate(vec3(1.25,0.0,-1.15)));
   rueda2->agregar(rueda);
   agregar(rueda2);

   NodoGrafoEscena * rueda3 = new NodoGrafoEscena();
   rueda3->agregar(translate(vec3(-1.25,0.0,1.15)));
   rueda3->agregar(rueda);
   agregar(rueda3);

   NodoGrafoEscena * rueda4 = new NodoGrafoEscena();
   rueda4->agregar(translate(vec3(-1.25,0.0,-1.15)));
   rueda4->agregar(rueda);
   agregar(rueda4);

   pm_ruedas = rueda->leerPtrMatriz(i);

   NodoGrafoEscena * coche = new NodoGrafoEscena();

   coche->agregar(translate(vec3(0.0,0.5,0.0)));
   coche->agregar(scale(vec3(1.5,0.5,1.0)));
   coche->agregar(new Cubo());

   coche->agregar(translate(vec3(0.0,1.5,0.0)));
   coche->agregar(scale(vec3(0.5,0.5,0.25)));
   coche->agregar(new Cubo());

   agregar(coche); 

   pm_coche = leerPtrMatriz(j);
   pm_pos_coche = leerPtrMatriz(k);


}

unsigned Coche::leerNumParametros() const
{
   return num_params;
}

void Coche::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{

      switch (iParam)
      {
      case 0:
      
         *pm_ruedas = rotate(float(5.0*360.0*t_sec),vec3(0.0,0.0,1.0));
         break;

      case 1:
         establecerMovi(v_angu_coche,t_sec);
         break;

      case 2:
         establecerGiroCoche(t_sec);
         break;
      
      }
}

void Coche::establecerMovi(const float v_angular,const float t_sec )
{
   const float radio = 5.0f;
   // Calcular la nueva posición del palo en función del tiempo
   float nuevaPosX = radio * cos(v_angular * t_sec);
   float nuevaPosZ = radio * sin(v_angular * t_sec);
   // Construir la nueva posición en el espacio 3D
   vec3 nuevaPosicion = vec3(0.0, 0.0, 0.0) + vec3(nuevaPosX, 0.0f, nuevaPosZ);

   *pm_coche = translate(nuevaPosicion);

}

void Coche::establecerGiroCoche(const float t_sec)
{
   *pm_pos_coche = rotate(radians(-10.0f*t_sec), vec3(0.0, 1.0, 0.0));
}


//-----------------------------------------------------------------------------------
// PRÁCTICA 4
// --> NodoCubo24
//-----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Clase 'NodoGrafoCubo24

NodoGrafoCubo24::NodoGrafoCubo24() {

   ponerNombre( std::string("Grafo Cubo24") );

   agregar(new Material(new Textura("window-icon.jpg"), 0.2,0.4,0.4,20));
   agregar(new Cubo24());
}

//-----------------------------------------------------------------------------------
// PRÁCTICA 4
// --> NodoDiscoP4 (EJERCICIO ADICIONAL)
//-----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Clase 'NodoDiscoP4

NodoDiscoP4::NodoDiscoP4()
{
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   agregar( new Material(new Textura("ea-textura-cuadricula.jpeg"), 0.2,0.4,0.4,20));
   agregar( new MallaDiscoP4() );
}

//-----------------------------------------------------------------------------------
// PRÁCTICA 5
// --> GrafoEsferaP5 (EJERCICIO ADICIONAL 1)
//-----------------------------------------------------------------------------------

MiEsferaE1::MiEsferaE1(unsigned i, unsigned j)
{
   fila = i;
   num_esfera = j;

   agregar( new Esfera(50,50));
}

bool MiEsferaE1::cuandoClick(const glm::vec3 & centro_wc)
{
   std::cout << "Se ha seleccionado la esfera número " << num_esfera << " de la fila "<< fila << std::endl;
   return true;
}

// -----------------------------------------------------------------------------
// Clase 'NodoDiscoP4
GrafoEsferasP5::GrafoEsferasP5()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 0.4/n_esferas_x_fila ;

   agregar( scale(vec3( e,e,e )));
   
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
   

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE1 * esfera = new MiEsferaE1(i,j) ;
         esfera->ponerIdentificador(n_filas_esferas*i+j+1);
         fila_esferas->agregar( translate(vec3( 2.2, 0.0, 0.0 )));
         fila_esferas->agregar( esfera );
      }
      agregar( fila_esferas );
      agregar( translate(vec3( 0.0, 0.0, 5.0 )));
   }
}


//-----------------------------------------------------------------------------------
// PRÁCTICA 5
// --> MiEsfera2 (EJERCICIO ADICIONAL 2)
//-----------------------------------------------------------------------------------

MiEsferaE2::MiEsferaE2()
{

   agregar( new Esfera(50,50));
  

}

bool MiEsferaE2::cuandoClick(const glm::vec3 & centro_wc)
{
   
   if (tieneColor())
   {
      if (leerColor() == vec3(1.0,1.0,1.0))
         ponerColor(vec3(1.0,0.0,0.0));
      else if (leerColor() == vec3(1.0,0.0,0.0))
         ponerColor(vec3(1.0,1.0,1.0));
   }

   else ponerColor(vec3(1.0,0.0,0.0));
   
   return true;
}


GrafoEsferasP5_2::GrafoEsferasP5_2()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float e = 2.5/n_esferas_x_fila ;

   agregar (scale(vec3( e, e, e )));

   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      fila_esferas->agregar( translate(vec3( 3.0, 0.0, 0.0 )));
   

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE2 * esfera = new MiEsferaE2() ;
         esfera->ponerIdentificador(n_filas_esferas*i+j+1);
         fila_esferas->agregar( translate(vec3( 2.5, 0.0, 0.0 )));
         fila_esferas->agregar( esfera );
      }

   agregar( fila_esferas );
   agregar( rotate( radians(360.0f/n_filas_esferas), vec3( 0.0, 1.0, 0.0 ))); 

   }
}