/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Ordena.h
 * Author: jrmou
 *
 * Created on 17 de Março de 2018, 06:49
 */

#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <random>
#include <ctime>
#include <ratio>
#include <chrono>

template <class T>
class Ordenacao
{

public:

    double executar(T vetor[], unsigned int tam){

        nrRegistros = tam;

        tempo = this->aplicarAlgoritmo(vetor, tam);

        return tempo;
    }

    static void trocar(T vetor[], unsigned int ind1, unsigned int ind2)
    {
        T aux = vetor[ind1];
        vetor[ind1] = vetor[ind2];
        vetor[ind2] = aux;
    }

    static double aplicarMistura(T vetor[], unsigned int tam, const float &fatorMistura = 1.0f)
    {
        std::chrono::high_resolution_clock::time_point t1, t2;
        t1 = std::chrono::high_resolution_clock::now();

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(0, tam - 1);

        int n = (int)(fatorMistura * tam);

        for (int i = 0; i < n; i++)
        {
            Ordenacao::trocar(vetor, dis(gen), dis(gen));
        }

        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = t2 - t1;
        return time_span.count();
    }

    static double aplicarMistura(T vetor[], unsigned int tam, const float &fatorMistura, std::mt19937 *gen)
    {
        std::chrono::high_resolution_clock::time_point t1, t2;
        t1 = std::chrono::high_resolution_clock::now();

        std::uniform_int_distribution<> dis(0, tam - 1);

        int n = (int)(fatorMistura * tam);

        for (int i = 0; i < n; i++)
        {
            Ordenacao::trocar(vetor, dis(*gen), dis(*gen));
        }

        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = t2 - t1;
        return time_span.count();
    }

    virtual ~Ordenacao() {}

    virtual std::string resultado() const
    {
        return this->getAlgortimo() + 
               " / reg: " + std::to_string(nrRegistros) +
               " / t(s): " + std::to_string(tempo);
    }

    virtual std::string resultadoCsv() const
    {
        return this->getAlgortimo() +
               ";" + std::to_string(nrRegistros) +
               ";" + std::to_string(tempo);
    }

    virtual std::string titleCsv() const
    {
        return "Algoritmo;Nr Registros;Tempo";
    }

    static T select(T vetor[], int ini, int fim, int ind){

        if(ini == fim)
            return vetor[ini];
        int q = Ordenacao<T>::pivotear(vetor, ini, vetor[fim], fim);
        int k = q - ini + 1;
        if(ind == k)
            return vetor[q];
        else if(ind < k)
            return select(vetor, ini, q - 1, ind );
        else
            return select(vetor, q + 1, fim, ind - k);        
    }

    static T achaPivo(T vetor[], int ini, int fim){
        
        int pos = ini + 1;
        if(pos > fim)
            return vetor[ini];
        
        if(vetor[pos] < vetor[pos - 1])
            return vetor[pos];
        else if(vetor[pos] > vetor[pos - 1])
            return vetor[pos - 1];
 
        return Ordenacao<T>::achaPivo(vetor, pos, fim);
    }

    

    static T select(T vetor[], int ini, int fim, int ind, std::mt19937 *gen){

        if(ini == fim)
            return vetor[ini];

        std::uniform_int_distribution<> dis(ini, fim);
        int q = Ordenacao<T>::pivotear(vetor, ini, vetor[dis(*gen)], fim);
        int k = q - ini + 1;
        if(ind == k)
            return vetor[q];
        else if(ind < k)
            return select(vetor, ini, q - 1, ind );
        else
            return select(vetor, q + 1, fim, ind - k);        
    }

    static double insertSort(T vetor[], int ini, int fim)
    {
        std::chrono::high_resolution_clock::time_point t1, t2;
        t1 = std::chrono::high_resolution_clock::now();
        for (int j = ini + 1; j <= fim; ++j)
        {
            T aux = vetor[j];
            int i = j - 1;
            for (; i >= ini && vetor[i] > aux; --i)
            {
                vetor[i + 1] = vetor[i];
            }
            vetor[i + 1] = aux;
        }
        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = t2 - t1;
        return time_span.count();
    }

    static int pivotear(T vetor[], int ini, T pivo, int fim)
    {

        int indEsq = ini, indDir = fim;

        while (true)
        {

            while (indEsq < fim && vetor[indEsq] < pivo){
                indEsq++;
            }

            while (indDir > ini && vetor[indDir] > pivo){
                indDir--;
            }

            if (indEsq >= indDir)
                break;
            else
                Ordenacao<T>::trocar(vetor, indEsq, indDir);
        }

        return indEsq;
    }

protected:

    Ordenacao(const std::string &algoritmo) : algoritmo(algoritmo), nrRegistros(0) {}

    virtual const std::string getAlgortimo() const
    {
        return algoritmo;
    }

    unsigned int nrRegistros;

    const std::string algoritmo;

private:

    virtual double aplicarAlgoritmo(T vetor[], unsigned int tam) = 0;

    double tempo = 0;
};

#endif /* ORDENA_H */
