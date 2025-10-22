# 🤖 RoboNavigator - Simulador de Navegación Autónoma en C

**RoboNavigator** es una aplicación desarrollada en lenguaje **C (C11)** que simula la navegación autónoma de un robot en un entorno mapeado. El proyecto forma parte de la asignatura **Algoritmos y Estructuras de Datos – 2025**, de la carrera **Ingeniería en Sistemas de Información**.

El objetivo principal es aplicar estructuras de datos y algoritmos aprendidos en clase para resolver un problema de planificación de rutas en presencia de obstáculos.

---

## 📌 Objetivo General

Desarrollar una aplicación en lenguaje C que simule la navegación autónoma de un robot en un entorno mapeado, capaz de:

- Recibir comandos de destino.
- Detectar obstáculos.
- Planificar la ruta más corta o eficiente hacia su objetivo.

---

## 🎯 Objetivos Específicos

- ✅ Diseñar algoritmos que permitan descubrir rutas óptimas.
- ✅ Utilizar al menos tres estructuras de datos vistas en clase (matrices, colas, listas, pilas, etc.).
- ✅ Modelar un entorno con obstáculos estáticos y/o dinámicos.
- ✅ Procesar comandos del usuario de forma robusta.
- ✅ Documentar y presentar el desarrollo mediante un informe técnico y un video explicativo.

---

## 🧠 Contenidos Técnicos

- **Lenguaje**: C (C11)
- **Estructuras de datos utilizadas**:
  - Matrices para representación del entorno.
  - Colas (por ejemplo, para BFS).
  - Listas enlazadas o pilas para representar rutas, historial, etc.
- **Algoritmos de planificación**:
  - Búsqueda en anchura (BFS).
  - Posibilidad de implementar A* o Dijkstra (opcional).

---

## 🧭 Descripción del Entorno

- Entorno: cuadrícula bidimensional (20x20 por defecto).
- Celdas del mapa:
  - `░`: espacio libre
  - `█`: obstáculo
  - `R`: robot
  - `X`: destino
  - `.`: camino recorrido
- El usuario puede:
  - Ingresar manualmente coordenadas de destino.
  - Visualizar la ruta calculada.
  - Reconfigurar el mapa.
- El sistema verifica errores como:
  - Coordenadas inválidas.
  - Destinos inaccesibles.

---

## 🖥️ Interfaz de Usuario

La aplicación se ejecuta por **consola**, utilizando **arte ASCII** para representar visualmente el mapa y el recorrido del robot.  
Ejemplo:

░░░░█░░░░░░█░░░    
░░░░░░░█░░░░░░X    
░░█░░█░░█░░█░░░    
░░█░░█░░█░░█░█░    
░R░░░░░░░░░░░░░    


---

## 🚀 Cómo ejecutar el proyecto

### 1. Compilar

```bash
make
```
Esto generará el ejecutable programa.

### 2. Ejecutar
```bash
./programa
```

### 🧹 Limpieza
```bash
make clean
```

---

## 📁 Estructura del proyecto
```
.
├── src/
│   ├── main.c
│   ├── mapa.c / mapa.h
│   ├── interfaz.c / interfaz.h
├── build/        # Archivos objeto generados automáticamente
├── programa      # Ejecutable principal
├── README.md
├── Makefile
```

---

## 💡 Funcionalidades futuras (opcional)

Obstáculos móviles.

Terrenos de alto costo.

Múltiples robots en el mismo entorno.

---

## 👨‍💻 Autores

Proyecto desarrollado por estudiantes de la carrera Ingeniería en Sistemas de Información – 2025
Asignatura: Algoritmos y Estructuras de Datos

---

## 📽️ Presentación

Se adjuntará un video demostrativo y un informe técnico como parte del entregable final del proyecto.

---

## ⚠️ Requisitos

Sistema operativo compatible con compilación C (Linux, WSL, etc.)

Compilador GCC (C11)

make instalado

---

## Licencia

Este proyecto es exclusivamente educativo y no está licenciado para uso comercial.