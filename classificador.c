#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float moda_nao_nula(float v[],int n)
{
	int i=0, j=0, cont[n];
	float conta=0, moda=0;
	
	for(i=0;i<n && (v[i] != 0);i++)
    {
        for(j=i+1;j<n;j++)
        {
			if(v[i]==v[j])
            {
				cont[i]++;
					if(cont[i]>conta)
                    {
						conta=cont[i];
						moda=v[i];
					}
			}
        }
        cont[i]=0;
    }
	return moda;
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
        if (ctreino[i] == '/')
        {
            ctreino[i] = '\\';
        }
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
    
    //Caminho de Teste:
    char cteste[50];
    i++; //Tirando o i da posição \n do config
    j=0;
    while ((cteste[j] = sconfig[i]) != '\n')
    {
        if (cteste[j] == '/')
        {
            cteste[j] = '\\';
        }
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

    // Caminho das predições:
    char cpredicao[50];
    i++; //Tirando o i da posição \n do config
    j=0;
    while ((cpredicao[j] = sconfig[i]) != '\n')
    {
        if (cpredicao[j] == '/')
        {
            cpredicao[j] = '\\';
        }
        i++;
        j++;
    }
    cpredicao[j] = '\0';

    //Lendo N predições da config:
    i++; //Tirando o i da posição quebra de linha \n
    int b = 0; // B = quantidade de predições impressas
    for (i;sconfig[i] != EOF;i++)
    {
        if (sconfig[i] == '\n')
        {
            b+=1;
        }
    }
   
    int k[b], h;
    float r[b], resultados_parciais[w][u], resultados[w],cont_acertos, cont_erros, acc; // u = 105 e w = 45
    char c[b],auxpredicao[100];
    char gconverte[12];
    strcat(cpredicao,"predicao_");
    FILE *predicao;
    config = fopen("config.txt","r");
    for (i=0;i<3;i++)
    {
        fgets(det_TAM,25000,config); //Colocando config no terceiro paragráfo.
    }

    for(j=0;j<b;j++)
    {
        sprintf(gconverte,"%d",j+1);
        strcpy(auxpredicao,cpredicao);
        strcat(auxpredicao, gconverte);
        strcat(auxpredicao, ".txt");
        printf("%s\n",auxpredicao);
        predicao = fopen(auxpredicao,"w");
        fscanf(config,"%d, %c, %f",&k[j],&c[j],&r[j]);
        switch(c[j])
        {
            case 'M':
                cont_acertos = 0, cont_erros = 0, acc = 0;
                for (i=0;i<w;i++)
                {
                    h = 0;
                    for (l=0;l<u;l++)
                    {
                        if ((distanciaMinkowsky(t[i],q[l],(v-1),r[j])) <= k[j]) // 5 são as colunas de teste/treino e 4 = 5 - 1 (que é o tipo das amostras).
                        {
                            resultados_parciais[i][h] = q[l][v-1];
                            h++;
                        }
                    }

                    resultados[i] = moda_nao_nula(resultados_parciais[i],u);
                    if (resultados[i] == t[i][v-1])
                    {
                        cont_acertos ++;
                    }
                    else
                    {
                        cont_erros ++;
                    }
                }
                acc = 100*(cont_acertos / (cont_erros + cont_acertos));
                fprintf(predicao,"%.2f\n",acc);
                fprintf(predicao,"\n");
                for (l=0;l<3;l++)
                {
                    fprintf(predicao,"\n");
                }
                for (i=0;i<w;i++)
                {
                    fprintf(predicao,"%d\n",(int) resultados[i] -1);
                }
                break;
            
            case 'E':
                cont_acertos = 0, cont_erros = 0, acc = 0;
                for (i=0;i<w;i++)
                {
                    h=0;
                    for (l=0;l<u;l++)
                    {
                        if ((distanciaEuclidiana(t[i],q[l],(v-1))) <= k[j]) // 5 são as colunas de teste/treino e 4 = 5 - 1 (que é o tipo das amostras).
                        {
                            resultados_parciais[i][h] = q[l][v-1];
                            h++;
                        }

                    }
                    
                    resultados[i] = moda_nao_nula(resultados_parciais[i],u);
                    if (resultados[i] == t[i][v-1])
                    {
                        cont_acertos ++;
                    }
                    else
                    {
                        cont_erros ++;
                    }
                }
                acc = 100*(cont_acertos / (cont_erros + cont_acertos));
                fprintf(predicao,"%.2f\n",acc);
                fprintf(predicao,"\n");
                for (l=0;l<3;l++)
                {
                    fprintf(predicao,"\n");
                }
                for (i=0;i<w;i++)
                {
                    fprintf(predicao,"%d\n",(int) resultados[i] -1);
                }
                break;
            
            case 'C':
                cont_acertos = 0, cont_erros = 0, acc = 0;
                for (i=0;i<w;i++)
                {
                    h = 0;
                    for (l=0;l<u;l++)
                    {
                        if ((distanciaEuclidiana(t[i],q[l],(v-1))) <= k[j]) // 5 são as colunas de teste/treino e 4 = 5 - 1 (que é o tipo das amostras).
                        {
                            resultados_parciais[i][h] = q[l][v-1];
                            h++;
                        }
                    }

                    resultados[i] = moda_nao_nula(resultados_parciais[i],u);
                    if (resultados[i] == t[i][v-1])
                    {
                        cont_acertos ++;
                    }
                    else
                    {
                        cont_erros ++;
                    }
                    
                }
                acc = 100*(cont_acertos / (cont_erros + cont_acertos));
                fprintf(predicao,"%.2f\n",acc);
                fprintf(predicao,"\n");
                for (l=0;l<3;l++)
                {
                    fprintf(predicao,"\n");
                }

                for (i=0;i<w;i++)
                {
                    fprintf(predicao,"%d\n",(int) resultados[i] -1);
                }
                break;
        }
        fclose(predicao);
    }
    fclose(config);
    return 0;
}