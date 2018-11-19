#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
float maximo_vetor(float *p, int n)
{
    int i = 0;
    float m = p[i];
    for (i=0;i<(n-1);i++)
    {
        if (m < p[i+1])
        {
            p[i] = p[i+1];
            m = p[i+1];
        }
    }
}

float distanciaChebyshev(float *p, float *q, int n)
{
    float m = 0;
    float v[n];
    for (int i=0;i<n;i++)
    {
        float s = p[i] - q[i];
        if (s < 0)
        {
            s = (q[i] - p[i]);
        }
        v[i] = s;
    }
    return maximo_vetor(v,n);
}

float distanciaMinkowsky(float *p, float *q, int n, float r)
{
    float m = 0;
    for (int i=0;i<n;i++)
    {
        float s = p[i] - q[i];
        if (s < 0)
        {
            s = (q[i] - p[i]);
        }
        m += pow(s,r);
    }
    return pow(m,(1/r));
}

float distanciaEuclidiana(float *p, float *q, int n)
{
    float m = 0;
    for(int i=0;i<n;i++)
    {
        m += pow((p[i]-q[i]),2);
    }
    return sqrt(m);
}
int main()
{
    // Método KNM :

    //conjunto de dados e saída
    //float k;
    //printf("Informe o valor de k: ");
    //scanf("%f", &k);
    float vet1[2],vet2[2];
    vet1[0] = 0;
    vet1[1] = 0;
    vet2[0] = 4;
    vet2[1] = 5;
    printf("%.2f",distanciaMinkowsky(vet1,vet2,2,2));
    printf("\n%.2f",distanciaEuclidiana(vet1,vet2,2));
    printf("\n%.2f",distanciaChebyshev(vet1,vet2,2));
    printf("\n%.2f",maximo_vetor(vet1,2));
    return 0;
}