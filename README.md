# Laboratorio 3: Programación Concurrente con Pthreads

[![Linux](https://img.shields.io/badge/OS-Linux-blue?logo=linux)](https://www.linux.org/)
[![C](https://img.shields.io/badge/Language-C-A8B9CC?logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Pthreads](https://img.shields.io/badge/API-POSIX_Threads-green)](https://en.wikipedia.org/wiki/Pthreads)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

##  Autores

**Juan Camilo Avendano Rodriguez**  
**Jose Fernando Waldo Rojas**  

##  Descripción

Implementación y análisis de programas multihilo en C utilizando la API POSIX Threads (pthreads). Este laboratorio explora:

- **Paralelización** de aplicaciones compute-bound
- **Sincronización** de hilos mediante `pthread_join()`
- **Análisis de rendimiento** con métricas Speedup y Eficiencia
- **Patrones de diseño** para programación concurrente

##  Objetivos

1.  Aplicar conceptos de creación y sincronización de hilos POSIX
2.  Paralelizar una aplicación serial (Cálculo de π)
3.  Implementar generación concurrente de datos (Fibonacci)
4.  Medir y analizar el impacto del paralelismo en rendimiento

## Estructura del Proyecto
```
SO-Lab3-20252/
├── pi.c                  # Versión serial del cálculo de π
├── pi_p.c                # Versión paralela del cálculo de π
├── fibonacci.c           # Generador concurrente de Fibonacci
├── analisis.ipynb        # Análisis detallado con gráficos
├── README.md             # Este archivo
└── .gitignore
```

##  Compilación y Ejecución

### Prerrequisitos
```bash
# Fedora/RHEL/CentOS
sudo dnf install gcc python3-jupyter-notebook

# Ubuntu/Debian
sudo apt install build-essential python3-notebook

# Verificar instalación
gcc --version
jupyter --version
```

### Compilar programas
```bash
# Versión serial de π
gcc -o pi_s pi.c -lm

# Versión paralela de π
gcc -o pi_p pi_p.c -lpthread -lm

# Generador de Fibonacci
gcc -o fibonacci fibonacci.c -lpthread
```

### Ejecutar
```bash
# Cálculo serial de π (n=2 billones de intervalos)
./pi_s 2000000000

# Cálculo paralelo con 4 hilos
./pi_p 2000000000 4

# Generar primeros 15 números de Fibonacci
./fibonacci 15
```

### Análisis de resultados
```bash
# Iniciar Jupyter Notebook
jupyter notebook analisis.ipynb
```

##  Resultados Experimentales

### Sistema de Pruebas
- **SO:** Fedora 42 (Kernel 6.17.5)
- **CPU:** 4 núcleos físicos (8 lógicos con HT)
- **Compilador:** GCC 14.x

### Métricas Clave

| Hilos | Tiempo (s) | Speedup | Eficiencia |
|-------|-----------|---------|-----------|
| Serial | 6.748 | 1.00x | 100% |
| 1      | 7.690 | 0.88x | 88% |
| 2      | 3.444 | 1.96x | 98% |
| 4      | 2.171 | 3.11x | 78% |
| **8**  | **1.875** | **3.60x** | **45%** |
| 16     | 1.986 | 3.40x | 21% |
| 32     | 2.039 | 3.31x | 10% |

**Punto óptimo:** 8 hilos con un speedup de 3.6x (90% del teórico en 4 núcleos)



##  Conceptos Clave Implementados

### 1. Data Parallelism (Cálculo de π)
```c
// Cada hilo procesa un sub-rango del bucle
for (int i = data->start; i < data->end; i++) {
    fX = fH * ((double)i + 0.5);
    fSum += f(fX);
}
```

### 2. Producer-Consumer (Fibonacci)
```c
// Main produce el arreglo, Worker lo consume
pthread_create(&worker_thread, NULL, GenerateFibonacci, &data);
pthread_join(worker_thread, NULL);  // Sincronización implícita
```

### 3. Agregación de Resultados Parciales
```c
// Sin mutexes - Agregación al final
for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
    total_sum += thread_data[i].sum;  //  No race condition
}
```

##  Lecciones Aprendidas

###  Buenas Prácticas
- Minimizar memoria compartida entre hilos
- Evitar mutexes dentro de loops críticos
- Adaptar #hilos al hardware disponible
- Medir rendimiento, no asumir

###  Errores Comunes
- Sobresuscripción (más hilos que núcleos)
- Compartir variables sin sincronización
- Ignorar overhead de creación de hilos
- Asumir escalabilidad lineal infinita

##  Análisis Detallado

Ver [`analisis.ipynb`](analisis.ipynb) para:
-  Gráficos interactivos de Speedup y Eficiencia
-  Tablas de resultados completas
-  Interpretación de métricas
-  Análisis de overhead y limitaciones
-  Conclusiones y recomendaciones

##  Referencias

- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [Operating Systems: Three Easy Pieces - Threads](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf)
- [Amdahl's Law](https://en.wikipedia.org/wiki/Amdahl%27s_law)
- [False Sharing](https://mechanical-sympathy.blogspot.com/2011/07/false-sharing.html)

##  Autores

**Juan Camilo Avendano Rodriguez**  
**Jose Fernando Waldo Rojas**  

Universidad de Antioquia - Sistemas Operativos 2025-2

---

## 📄 Licencia

Este proyecto es material académico para el curso de Sistemas Operativos.

---

##  Contribuciones

Este es un trabajo académico grupal. Las sugerencias y mejoras son bienvenidas mediante issues.



