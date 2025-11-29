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
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Función f(x) = 4/(1+x^2)
double f(double x) {
    return (4.0 / (1.0 + x * x));
}

// Función para calcular π
double CalcPi(int n) {
    const double fH = 1.0 / (double)n;
    double fSum = 0.0;
    double fX;
    
    for (int i = 0; i < n; i++) {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }
    
    return fH * fSum;
}

// Función para obtener el tiempo actual
double GetTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_intervalos>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n <= 0) {
        printf("Error: El número de intervalos debe ser positivo\n");
        return 1;
    }
    
    printf("Calculando π con n=%d (versión serial)...\n", n);
    
    double start_time = GetTime();
    double pi = CalcPi(n);
    double end_time = GetTime();
    
    printf("π ≈ %.15f\n", pi);
    printf("Tiempo de ejecución: %.6f segundos\n", end_time - start_time);
    
    return 0;
}