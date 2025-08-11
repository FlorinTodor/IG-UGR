# Informática Gráfica – Proyecto IG

## 📌 Descripción
Conjunto de prácticas desarrolladas en la asignatura **Informática Gráfica** centradas en la programación con **OpenGL** y **C++** para la construcción de una aplicación gráfica interactiva en 3D.
El objetivo ha sido implementar de forma incremental distintas funcionalidades: visualización de modelos, manejo de cámaras, animaciones jerárquicas, texturizado, iluminación y técnicas de selección.

---

## 📚 Prácticas realizadas

### P1 – Entorno básico y visualización
- Inicialización de OpenGL y GLUT.
- Carga y renderizado de primitivas 3D básicas (cubos, tetraedros).
- Control interactivo de la cámara (vista ortográfica/perspectiva).
- Gestión de eventos de teclado para cambiar modo de visualización.

### P2 – Cámaras y proyecciones
- Implementación de cámara interactiva (rotación, zoom, traslación).
- Definición de proyecciones ortográficas y en perspectiva.
- Movimiento independiente del observador y del objeto.
- Múltiples cámaras con cambio dinámico.

### P3 – Modelos jerárquicos
- Diseño e implementación de un **grafo de escena**.
- Modelado jerárquico de un objeto animado compuesto por subpartes.
- Animaciones articuladas controladas por teclado.
- Transformaciones locales por nodo (traslación, rotación, escalado).

### P4 – Materiales y texturas
- Aplicación de materiales con propiedades **ambient, diffuse, specular**.
- Uso de **iluminación de Phong** y luces posicionales/direccionales.
- Carga y mapeado de texturas en modelos 3D.
- Activación/desactivación de texturas y luces en tiempo real.

### P5 – Identificadores de selección
- Implementación de **picking por color** para seleccionar objetos.
- Asociación de identificadores únicos a cada parte del modelo.
- Resaltado visual del objeto seleccionado.
- Ejecución de acciones específicas al seleccionar elementos.

---

## 🛠 Tecnologías utilizadas
- **Lenguaje**: C++
- **API gráfica**: OpenGL, GLUT/FreeGLUT
- **Bibliotecas**: GLM (matemáticas 3D), SOIL/stb_image (carga de texturas)
- **IDE**: Visual Studio Code
- **Sistema**: Linux y/o Windows (preferiblemente linux)

---

## 📐 Metodología
- Desarrollo incremental: cada práctica amplía las funcionalidades previas.
- Uso de **programación orientada a objetos** para modularidad (clases para cámara, escena, modelo, etc.).
- Gestión de eventos de entrada (teclado, ratón) para control de cámara, animaciones y selección.
- Renderizado en pipeline fijo (OpenGL clásico) para centrarse en conceptos fundamentales.

---


## 🚀 Posibles mejoras
- Migrar a OpenGL moderno (shaders GLSL).
- Añadir animación mediante interpolación y cinemática inversa.
- Implementar carga de modelos desde formatos externos (OBJ, GLTF).
- Integrar soporte para sombras dinámicas y reflejos.
---
## 📂 Estructura del repositorio
```yaml
.
├── P1/           # Visualización básica y control de cámara
├── P2/           # Cámaras y proyecciones
├── P3/           # Modelos jerárquicos
├── P4/           # Materiales y texturas
├── P5/           # Identificadores de selección
└── common/       # Utilidades y clases compartidas


