// Nombre: Quintín, Apellidos: Mesa Romero, Titulación: GIM.
// email: quintinmr@correo.ugr.es, DNI o pasaporte: 78006011Q
// *********************************************************************

#include "latapeones.h"
#include <iostream>

#include "objeto3d.h"
#include "aplicacion-ig.h"  
#include "seleccion.h"
#include "camara.h"

using namespace glm;

Lata::Lata(const std::string& archivoTextura)
{
    NodoGrafoEscena * base_inferior = new NodoGrafoEscena();
    NodoGrafoEscena * cilindro_lata = new NodoGrafoEscena();
    NodoGrafoEscena * base_superior = new NodoGrafoEscena();

    Material * material_bases = new Material(0.1,0.6,2.0,50);
    base_inferior->agregar(material_bases);
    base_superior->agregar(material_bases);

    Material * material_cilindro = new Material(new Textura(archivoTextura),0.5,3.0,3.0,50);
    cilindro_lata->agregar(material_cilindro);
    base_inferior->agregar(new MallaRevolPLY("lata-pinf.ply",50));
    agregar(base_inferior);
    base_superior->agregar(new MallaRevolPLY("lata-psup.ply",50));
    agregar(base_superior);
    cilindro_lata->agregar(new MallaRevolPLY("lata-pcue.ply",50));
    agregar(cilindro_lata);

    ponerNombre("Lata");
}

LataCoca::LataCoca()
{
    agregar(new Lata("lata-coke.jpg"));
    ponerNombre("Lata de Coca-Cola");
    ponerIdentificador(1);

}

LataPepsi::LataPepsi()
{
    agregar(new Lata("lata-pepsi.jpg"));
    ponerNombre("Lata de Pepsi");
    ponerIdentificador(2);

}

LataUGR::LataUGR()
{
    agregar(new Lata("window-icon.jpg"));
    ponerNombre("Lata de la UGR");
    ponerIdentificador(3);

}

PeonMadera::PeonMadera()
{
    ponerNombre("Peón de madera");
    
    Textura * madera = new Textura("text-madera.jpg");
    agregar(scale(vec3(0.2,0.2,0.2)));
    unsigned i = agregar(translate(vec3(0.0,1.35,0.0)));
    agregar( new Material(madera, 0.25, 0.75, 3.0, 20));
    agregar( new MallaRevolPLY("peon.ply",50));

    pm_madera = leerPtrMatriz(i);

    ponerIdentificador(4);
}

/* unsigned PeonMadera::leerNumParametros() const
{
    return num_params;
}

void PeonMadera::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros()-1);
    switch (iParam)
    {
    case 0:
        if (cuandoClick(leerCentroOC()))
            *pm_madera = translate(vec3(0.0,0.0,3.0));
        break;
    
    default:
        break;
    }
}
*/

bool PeonMadera::cuandoClick(const glm::vec3 & centro_wc)
{
       
   *pm_madera = translate(vec3(0.0,0.0,3.0*contador));
    contador++;

   return true;
    
} 



PeonBlanco::PeonBlanco()
{
    ponerNombre("Peón blanco");

    agregar(scale(vec3(0.2,0.2,0.2)));
    unsigned i = agregar(translate(vec3(0.0,1.35,0.0)));
    agregar( new Material(0.25,0.8,0.1,30));
    agregar( new MallaRevolPLY("peon.ply",50));

    pm_blanco = leerPtrMatriz(i);
    ponerIdentificador(5);

}

bool PeonBlanco::cuandoClick(const glm::vec3 & centro_wc)
{
       
   *pm_blanco = translate(vec3(0.0,0.0,3.0*contador));
    contador++;
   return true;
    
} 


PeonNegro::PeonNegro()
{
    ponerNombre("Peón negro");

    agregar(scale(vec3(0.2,0.2,0.2)));
    unsigned i = agregar(translate(vec3(0.0,1.35,0.0)));
    agregar( new Material(0.1,0.25,0.8,20));
    agregar( new MallaRevolPLY("peon.ply",50));

    pm_negro = leerPtrMatriz(i);
    ponerIdentificador(6);

}

bool PeonNegro::cuandoClick(const glm::vec3 & centro_wc)
{
       
   *pm_negro = translate(vec3(0.0,0.0,3.0*contador));
    contador++;
   return true;
    
} 

Latas::Latas()
{
    ponerNombre("Latas");
    agregar(new LataCoca());
    agregar(translate(vec3(1.0,0.0,0.0)));
    agregar(new LataPepsi);
    agregar(translate(vec3(1.0,0.0,0.0)));
    agregar(new LataUGR);

    
}

Peones::Peones()
{
    agregar(translate(vec3(0.0, 0.0, 1.0)));
    madera = agregar(new PeonMadera());
    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(new PeonBlanco());
    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(new PeonNegro());

    ponerNombre("Peones");

}

/* unsigned Peones::leerNumParametros() const
{
    return num_params;
}


void Peones::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
        ((PeonMadera*)(entradas[madera].objeto))->actualizarEstadoParametro(iParam,t_sec);
        break;
    
    default:
        break;
    }
} */


LataPeones::LataPeones()
{
    NodoGrafoEscena * lata = new NodoGrafoEscena();
    lata->agregar(new Lata("lata-coke.jpg"));
    agregar(lata);
    agregar(translate(vec3(0.0, 0.0, 1.0)));
    agregar(new PeonMadera());
    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(new PeonBlanco());
    agregar(translate(vec3(0.5, 0.0, 0.0)));
    agregar(new PeonNegro());
    ponerNombre("Lata y peones");
}

VariasLataPeones::VariasLataPeones()
{
    agregar(new Latas());
    agregar(new Peones());

    ponerNombre("Varias latas y peones");
}

/* unsigned VariasLataPeones::leerNumParametros() const
{
    return num_params;
}

void VariasLataPeones::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam <= leerNumParametros()-1);

    switch (iParam)
    {
    case 0:
        ((Peones*)(entradas[madera].objeto))->actualizarEstadoParametro(iParam,t_sec);
        break;
    
    default:
        break;
    }
} */

