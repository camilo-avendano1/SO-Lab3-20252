#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Estructura para pasar datos al hilo trabajador
typedef struct {
    long long* array;  // Puntero al arreglo compartido
    int n;             // Número de elementos a generar
} FibonacciData;

// Función que ejecutará el hilo trabajador
void* GenerateFibonacci(void* arg) {
    FibonacciData* data = (FibonacciData*)arg;
    
    // Casos base
    if (data->n >= 1) {
        data->array[0] = 0;
    }
    if (data->n >= 2) {
        data->array[1] = 1;
    }
    
    // Generar el resto de la secuencia
    for (int i = 2; i < data->n; i++) {
        data->array[i] = data->array[i-1] + data->array[i-2];
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_elementos>\n", argv[0]);
        printf("Ejemplo: %s 10\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n <= 0) {
        printf("Error: El número de elementos debe ser positivo\n");
        return 1;
    }
    
    // Asignar memoria para el arreglo compartido
    long long* fibonacci_array = malloc(n * sizeof(long long));
    if (fibonacci_array == NULL) {
        printf("Error: No se pudo asignar memoria\n");
        return 1;
    }
    
    // Preparar datos para el hilo trabajador
    FibonacciData data;
    data.array = fibonacci_array;
    data.n = n;
    
    // Crear el hilo trabajador
    pthread_t worker_thread;
    printf("Generando los primeros %d números de Fibonacci...\n", n);
    
    pthread_create(&worker_thread, NULL, GenerateFibonacci, &data);
    
    // Esperar a que el hilo trabajador termine
    pthread_join(worker_thread, NULL);
    
    // Imprimir la secuencia de Fibonacci
    printf("Secuencia de Fibonacci:\n");
    for (int i = 0; i < n; i++) {
        printf("F(%d) = %lld\n", i, fibonacci_array[i]);
    }
    
    // Liberar memoria
    free(fibonacci_array);
    
    return 0;
}