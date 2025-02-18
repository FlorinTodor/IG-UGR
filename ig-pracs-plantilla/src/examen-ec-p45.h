// Nombre: Florin Emanuel Apellidos: Todor Gliga Titulación: GIADE
// email: flotodor@correo.ugr.es, DNI o pasaporte: 74049463C


#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "malla-ind.h"
#include "grafo-escena.h"
class PiramideCuadrada : public MallaInd{
   public:
      PiramideCuadrada();
};

class NodoPiramide : public NodoGrafoEscena
{
public:
   NodoPiramide();
};

// Crea una clase derivada de NodoGrafoEscenam que tenga un material con textura y una instancia de la pirámide. El material debe tener

//Añadele a la mirame una tabla de coordenadas de textura en su constructor, de forma que la textura se repite en cada una de las 4 caras laterales de la pirámide (centrada y recortada) y en la base (completa). La textura no debe aparecer invertida ni en horizontal ni en vertical (sus letras se leen bien).


class Triangulo: public MallaInd{
   public:
   Triangulo(glm::vec3 vec1,glm::vec3 vec2,glm::vec3 vec3);
};


class NodoPiramideConTriangulos: public NodoGrafoEscena{
   public:
   NodoPiramideConTriangulos();
   void cambiarColorTriangulo(int id);
   bool cuandoClick(int id) override;
};
#endif