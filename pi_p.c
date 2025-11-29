/*
 *  OpenMP lecture exercises
 *  Copyright (C) 2011 by Christian Terboven <terboven@rz.rwth-aachen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Estructura para pasar datos a cada hilo
typedef struct {
    int start;      // Índice inicial del rango
    int end;        // Índice final del rango
    int n;          // Total de intervalos
    double sum;     // Suma parcial (resultado)
} ThreadData;

// Función f(x) = 4/(1+x^2)
double f(double x) {
    return (4.0 / (1.0 + x * x));
}

// Función que ejecutará cada hilo
void* CalcPiThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    const double fH = 1.0 / (double)data->n;
    double fSum = 0.0;
    double fX;
    
    // Cada hilo calcula su rango asignado
    for (int i = data->start; i < data->end; i++) {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }
    
    // Guardamos el resultado en la estructura
    data->sum = fSum;
    
    pthread_exit(NULL);
}

// Función para obtener el tiempo actual
double GetTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero_intervalos> <numero_hilos>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);           // Número de intervalos
    int num_threads = atoi(argv[2]); // Número de hilos
    
    if (num_threads <= 0 || n <= 0) {
        printf("Error: Los valores deben ser positivos\n");
        return 1;
    }
    
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData* thread_data = malloc(num_threads * sizeof(ThreadData));
    
    // Calculamos cuántas iteraciones le tocan a cada hilo
    int chunk_size = n / num_threads;
    int remainder = n % num_threads;
    
    printf("Calculando π con n=%d usando %d hilos...\n", n, num_threads);
    
    double start_time = GetTime();
    
    // Crear los hilos
    int offset = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].n = n;
        thread_data[i].start = offset;
        
        // Distribuimos el remainder en los primeros hilos
        int current_chunk = chunk_size + (i < remainder ? 1 : 0);
        thread_data[i].end = offset + current_chunk;
        offset += current_chunk;
        
        thread_data[i].sum = 0.0;
        
        pthread_create(&threads[i], NULL, CalcPiThread, &thread_data[i]);
    }
    
    // Esperar a que terminen todos los hilos y sumar resultados
    double total_sum = 0.0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
    }
    
    double end_time = GetTime();
    
    // Calcular π
    const double fH = 1.0 / (double)n;
    double pi = fH * total_sum;
    
    printf("π ≈ %.15f\n", pi);
    printf("Tiempo de ejecución: %.6f segundos\n", end_time - start_time);
    
    // Liberar memoria
    free(threads);
    free(thread_data);
    
    return 0;
}