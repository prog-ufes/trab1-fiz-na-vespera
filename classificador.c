#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void dimensao_matriz(FILE *p,int *u,int *v)
{
    char det_TAM[25000];
    while ((fgets(det_TAM, 25000, p)) != NULL)
    {
        *u++;
    }
    *v = (strlen(det_TAM) + 1) / 5;
}

float maximo_vetor(float *p, int n)
{
    float m = p[0];
    for (int i=0;i<(n-1);i++)
    {
        if (m < p[i+1])
        {
            m = p[i+1];
        }
    }
    return m;
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
    FILE *config;
    config = fopen("config.txt","r");
    char sconfig[600];
    int i = 0;
    
    while ((sconfig[i] = fgetc(config)) != EOF)
    {
        i++;
    }
    fclose(config);
    sconfig[i] = '\0';
    
    // Caminho treino: 
    char ctreino[50];
    i = 0;
    while ((ctreino[i] = sconfig[i]) != '\n')
    {
        i++;
    }
    ctreino[i] = '\0';
    
    // TREINO:

    FILE *treino;
    treino = fopen(ctreino,"r");
    if (treino == NULL)
    {
        printf("Erro na abertura de arquivo! Programa terminado ...");
        exit(1);
    }
    
    char det_TAM[25000];
    int u=0,v=0;
    while ((fgets(det_TAM, 25000, treino)) != NULL)
    {
        u++;
    }
    v = (strlen(det_TAM) + 1) / 5;
    
    fclose(treino);
    treino = fopen(ctreino,"r");
    

    float q[u][v];
    int j,l;
    for (j=0;j<u;j++)
    {
        for (l=0;l<v;l++)
        {   
            fscanf(treino,"%f,", &q[j][l]);
        }
    }
    fclose(treino);
    printf("%.2f\n",q[4][4]);
    
    //Caminho de Teste:
    char cteste[50];
    i++; //Tirando o i da posição \n do config
    j=0;
    while ((cteste[j] = sconfig[i]) != '\n')
    {
        /*if (cteste[j] == '/')
        {
            cteste[j] = '\\';
        }*/
        i++;
        j++;
    }
    cteste[j] = '\0';

    // TESTE:

    FILE *teste;
    teste = fopen(cteste,"r");
    if (teste == NULL)
    {
        printf("Erro na abertura de arquivo! Programa terminado ...");
        exit(1);
    }

    int w=0;
    while ((fgets(det_TAM, 25000, teste)) != NULL)
    {
        w++;
    }
    
    fclose(teste);
    teste = fopen(cteste,"r");

    float t[w][v];
    for (j=0;j<w;j++)
    {
        for (l=0;l<v;l++)
        {
            fscanf(teste,"%f,", &t[j][l]);
        }
    }
    fclose(teste);
    printf("%.2f ",t[4][4]);

    // Caminho das predições:
    char cpredicao[50];
    i++; //Tirando o i da posição \n do config
    j=0;
    while ((cpredicao[j] = sconfig[i]) != '\n')
    {
        /*if (cpredicao[j] == '/')
        {
            cpredicao[j] = '\\';
        }*/
        i++;
        j++;
    }
    cpredicao[j] = '\0';

    // Calculando N predições:
    // Leu 3, E. Logo:
    int b = 0;
    float resultados[w][u]; // u = 105 e w = 45
    for (j=0;j<u;j++)
    {
        for (l=0;l<w;l++)
        {
            if (distanciaEuclidiana(q[j],t[l],(v-1)) <= 4) // 5 são as colunas de teste/treino e 4 = 5 - 1 (que é o tipo das amostras).
            {
                resultados[l][b] = q[j][v-1];
                b++;
            }
        }
    }
    print("%d", resultados[0][0]);
    
    printf("\n");
    return 0;
}