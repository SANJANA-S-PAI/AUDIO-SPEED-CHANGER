#include <math.h> 
#include <stdio.h> 
#define N 8 
#define M 2 
#define L 2 
#define NI ((N-1)*L + 1) 
#define PI 3.141592653589793 
/* Input signal */ 
float input_signal[N] = {0,1,2,3,4,5,6,7}; 
/* Decimation & Interpolation */ 
float decimated_signal[N/M]; 
float interpolated_signal[NI]; 
/* FFT buffers */ 
float real[N]; 
float imag[N]; 
float magnitude[N]; 
int i, j, k; 
void main(void){ 
    /* -------- DECIMATION -------- */ 
    for(i = 0, j = 0; i < N; i += M, j++){ 
        decimated_signal[j] = input_signal[i]; 
    } 
    /* -------- ZERO INSERTION -------- */ 
    for(i = 0; i < NI; i++){ 
        interpolated_signal[i] = 0.0; 
    } 
    /* -------- INTERPOLATION -------- */ 
    for(i = 0; i < N; i++){ 
        interpolated_signal[i * L] = input_signal[i]; 
    } 
    /* -------- COPY INPUT TO FFT REAL PART -------- */ 
    for(i = 0; i < N; i++){ 
        real[i] = input_signal[i]; 
        imag[i] = 0.0; 
    } 
    /* -------- DFT (Frequency Domain) -------- */ 
    for(k = 0; k < N; k++){ 
        real[k] = 0.0; 
        imag[k] = 0.0; 
        for(i = 0; i < N; i++){ 
            real[k] += input_signal[i] * cos(2 * PI * k * i / N); 
            imag[k] -= input_signal[i] * sin(2 * PI * k * i / N); 
        } 
        magnitude[k] = sqrt((real[k] * real[k]) + (imag[k] * imag[k])); 
    } 
    /* -------- PRINT RESULTS -------- */ 
    printf("Input Signal:\n"); 
    for(i = 0; i < N; i++){ 
        printf("%f ", input_signal[i]); 
    } 
    printf("\n\nDecimated Signal:\n"); 
    for(i = 0; i < N/M; i++){ 
        printf("%f ", decimated_signal[i]); 
    } 
    printf("\n\nInterpolated Signal:\n"); 
    for(i = 0; i < NI; i++){ 
        printf("%f ", interpolated_signal[i]); 
    } 
    printf("\n\nProgram Completed\n"); 
    /* Infinite loop for CCS graph */ 
    while(1); 
}
