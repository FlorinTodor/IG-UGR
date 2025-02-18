// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C


#include "examen-ec-p45.h"

PiramideCuadrada::PiramideCuadrada()
  : MallaInd("Pirámide con vértices compartidos")
{
   // (1) VÉRTICES ---------------------------------------
   vertices = {
      {-1.0f, 0.0f, -1.0f}, // v0: base frontal izquierda
      {+1.0f, 0.0f, -1.0f}, // v1: base frontal derecha
      {+1.0f, 0.0f, +1.0f}, // v2: base trasera derecha
      {-1.0f, 0.0f, +1.0f}, // v3: base trasera izquierda
      { 0.0f, 2.0f,  0.0f}  // v4: ápice (compartido)
   };

   // (2) TRIÁNGULOS -------------------------------------
   triangulos = {
      {0, 1, 2},  // Base - Triángulo 1
      {0, 2, 3},  // Base - Triángulo 2

      {0, 1, 4},  // Cara frontal
      {1, 2, 4},  // Cara derecha
      {2, 3, 4},  // Cara trasera
      {3, 0, 4}   // Cara izquierda
   };

   // (3) COORDENADAS DE TEXTURA -------------------------
   cc_tt_ver = {
      // Coordenadas de la base (plano cuadrado)
      {0.0, 1.0}, // v0
      {0.0, 0.0}, // v1
      {1.0, 0.0}, // v2
      {1.0, 1.0}, // v3

      // Coordenada del ápice (se comparte para todas las caras laterales)
      {0.5f, 0.5f}  // v4
   };

   // (4) Cálculo de normales ----------------------------
   calcularNormales(); // Recalcula las normales para iluminación correcta
}



NodoPiramide::NodoPiramide()
{
   // Cargar la textura desde el archivo
   Textura* textura = new Textura("window-icon.jpg");

   // Configurar el material (difuso, especular, brillo, etc.)
   Material* material = new Material(textura, 0.7f, 0.5f, 0.2f, 30.0f);

   // Agregar material al nodo
   agregar(material);

   // Agregar la geometría de la pirámide
   agregar(new PiramideCuadrada());
}



// EJERCICIO 2



Triangulo::Triangulo( glm::vec3 v1,  glm::vec3 v2,  glm::vec3 v3)
{
    // (1) VÉRTICES
    vertices = { v1, v2, v3 };

    // (2) TRIÁNGULOS 
    triangulos = { {0, 1, 2} };

    // (3) Cálculo de normales ----------------------------
   calcularNormales();
    

    // (4) Punto central ----------------------------------
    glm::vec3 punto_central = (v1 + v2 + v3) / 3.0f;

    // (5) Color inicial ----------------------------------
      for ( const auto & v: vertices){
         col_ver.push_back({1.0f, 1.0f, 1.0f});
      }
}

NodoPiramideConTriangulos::NodoPiramideConTriangulos()
{
    // Crear los vértices de la pirámide
    glm::vec3 v0(-1.0f, 0.0f, -1.0f);
    glm::vec3 v1(1.0f, 0.0f, -1.0f);
    glm::vec3 v2(1.0f, 0.0f, 1.0f);
    glm::vec3 v3(-1.0f, 0.0f, 1.0f);
    glm::vec3 v4(0.0f, 2.0f, 0.0f);

    // Crear los triángulos y agregarlos al grafo de escena
    agregar(new Triangulo(v0, v1, v2)); // Base - Triángulo 1
    agregar(new Triangulo(v0, v2, v3)); // Base - Triángulo 2
    agregar(new Triangulo(v0, v1, v4)); // Cara frontal
    agregar(new Triangulo(v1, v2, v4)); // Cara derecha
    agregar(new Triangulo(v2, v3, v4)); // Cara trasera
    agregar(new Triangulo(v3, v0, v4)); // Cara izquierda
}

void NodoPiramideConTriangulos::cambiarColorTriangulo(int id)
{
    // Cambiar el color del triángulo con el identificador dado
   // Me falta solamente seleccionar el nodo con dicho id, pero son las y 31 no me da tiempo
         /*
    if (this != nullptr)
    {
         if (this->colores[0] == glm::vec3(1.0f, 1.0f, 1.0f))
         {
             triangulo->colores = { {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} };
         }
         else
         {
             triangulo->colores = { {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
         }
    } */
}

bool NodoPiramideConTriangulos::procesarClick(int id)
{
    cambiarColorTriangulo(id);
    std::cout << "Nombre: Triangulo " << id << std::endl;
    centrarCamaraEnPunto(nodos[id]->punto_central);
    return true;

    nodos[id]  
}