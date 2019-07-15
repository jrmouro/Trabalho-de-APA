
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <random>
#include <ctime>
#include <algorithm>
#include "Ordenacao.h"

template <class T>
class QuickSort : public Ordenacao<T>
{
public:

    class EscolhaPivo
    {
    public:
        virtual T getPivo(T vetor[], int ini, int fim) = 0;
    };

    class RandomPivo : public EscolhaPivo
    {
    private:
        std::mt19937 *gen;

    public:
    
        RandomPivo(){
            std::random_device rd;
            this->gen = new std::mt19937(rd());
        }

        ~RandomPivo(){
            delete this->gen;
        }

        virtual T getPivo(T vetor[], int ini, int fim){
            std::uniform_int_distribution<> dis(ini, fim);
            return vetor[dis(*gen)];
        }

    };

    class MediaPivo : public EscolhaPivo{
    public:
        virtual T getPivo(T vetor[], int ini, int fim){
            //return (vetor[ini] + vetor[fim] + vetor[(int)(fim - ini) / 2]) / 3;
            return (vetor[ini] + vetor[fim]) / 2;
        }
    };

    class AchaPivo : public EscolhaPivo{
    public:
        virtual T getPivo(T vetor[], int ini, int fim){
            return Ordenacao<T>::achaPivo(vetor, ini, fim);
        }
    };

    class MedianaPivo : public EscolhaPivo{

    private:
        std::mt19937 *gen;
                
    public:

        MedianaPivo(){
            std::random_device rd;
            this->gen = new std::mt19937(rd());
        }

        ~MedianaPivo(){
            delete this->gen;
        }

        virtual T getPivo(T vetor[], int ini, int fim){
            int m = (fim - ini + 1)/2;
            return Ordenacao<T>::select(vetor, ini, fim, m, this->gen);
        }
        
    };

    enum Tipo
    {
        recursivo,
        insercao
    };
    enum Escolha
    {
        random,
        media,
        mediana,
        achaPivo
    };

    QuickSort(const std::string &nome = "QuickSort",
              const QuickSort<T>::Tipo &tipo = QuickSort<T>::Tipo::recursivo,
              const QuickSort<T>::Escolha &escolha = QuickSort<T>::Escolha::media,
              unsigned int tamInsercao = 10) : Ordenacao<T>(nome),
                                               tipo(tipo),
                                               escolha(escolha),
                                               tamInsercao(tamInsercao)
    {
        this->setEscolha(escolha);
    }

    void setEscolha(const QuickSort<T>::Escolha &escolha){

        this->escolha = escolha;

        if(this->escolhaPivo)
            delete this->escolhaPivo;

        switch (escolha)
        {
            case Escolha::media:
                this->escolhaPivo = new MediaPivo();
                break;
            case Escolha::mediana:
                this->escolhaPivo = new MedianaPivo();
                break;
            case Escolha::achaPivo:
                this->escolhaPivo = new AchaPivo();
                break;
            case Escolha::random:
                this->escolhaPivo = new RandomPivo();
                break;
        }
    }

    virtual ~QuickSort()
    {
        delete this->escolhaPivo;
    }

    unsigned int getTamInsercao() const
    {
        return tamInsercao;
    }

    void setTamInsercao(unsigned int tamInsercao)
    {
        this->tamInsercao = tamInsercao;
    }

    Tipo getTipo() const
    {
        return tipo;
    }

    void setTipo(Tipo tipo)
    {
        this->tipo = tipo;
    }

private:

    Tipo tipo;
    Escolha escolha;

    unsigned int tamInsercao;

    EscolhaPivo *escolhaPivo = NULL;

    virtual const std::string getAlgortimo() const
    {
        return this->nomeTipo();
    }

    std::string nomeTipo() const
    {
        switch (this->tipo)
        {
        case Tipo::insercao:
            return "insercao:" + std::to_string(tamInsercao) + "-" + this->nomeEscolha();
        }
        return "recursivo-" + this->nomeEscolha();
    }

    std::string nomeEscolha() const
    {
        switch (this->escolha)
        {
            case Escolha::media:
                return "media:";
            case Escolha::mediana:
                return "mediana:";
            case Escolha::achaPivo:
                return "achaPivo:";
        }
        return "random";
    }

    
    virtual double aplicarAlgoritmo(T vetor[], unsigned int tam)
    {

        std::chrono::high_resolution_clock::time_point t1, t2;
        t1 = std::chrono::high_resolution_clock::now();

        switch (this->tipo)
        {
        case Tipo::insercao:
            quickSortInsercao(vetor, 0, tam - 1);
            break;
        case Tipo::recursivo:
            quickSortRecursivo(vetor, 0, tam - 1);
            break;
        }

        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = t2 - t1;

        return time_span.count();
    }
    
    void quickSortRecursivo(T vetor[], int ini, int fim)
    {
        if (fim - ini <= 0)
        {
            return;
        }
        else
        {
            T pivo = this->escolhaPivo->getPivo(vetor, ini, fim);
            int i = Ordenacao<T>::pivotear(vetor, ini, pivo, fim);
            quickSortRecursivo(vetor, ini, i - 1);
            quickSortRecursivo(vetor, i + 1, fim);
        }
    }
    

    void quickSortInsercao(T vetor[],  int ini, int fim)
    {
        int x = fim - ini;
        if (x <= 0)
        {
            return;
        }
        else
        {
            if (x <= this->tamInsercao)
            {
                Ordenacao<T>::insertSort(vetor, ini, fim);
            }
            else
            {
                T pivo = this->escolhaPivo->getPivo(vetor, ini, fim);
                int i = Ordenacao<T>::pivotear(vetor, ini, pivo, fim);
                quickSortInsercao(vetor, ini, i - 1);
                quickSortInsercao(vetor, i + 1, fim);
            }
        }
    }

    

    
};

#endif /* QUICKSORT_H */
