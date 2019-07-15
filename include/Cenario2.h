#ifndef CENARIO2_H
#define CENARIO2_H

#include <vector>
#include "Cenario.h"
#include "QuickSort.h"

class Cenario2 : public Cenario
{
public:
    Cenario2(   unsigned vetorN[],
                unsigned tamVetorN,
                float mistura) : Cenario(
                                            2,
                                            "Comparação do Quicksort:Insert - Escolha de Pivô",
                                            vetorN,
                                            tamVetorN),                                      
                                            mistura(mistura){}

    virtual ~Cenario2() {}

private:
    
    
    float mistura;
    QuickSort<unsigned> quick;

    double t1 = 0, t2 = 0, t3 = 0, t4 = 0;

    std::string resultado, resultadoPlot;

    virtual std::string getResultado() const
    {
        return resultado;
    }

    virtual std::string getResultadoPlot() const
    {
        return resultadoPlot;
    }

    virtual void emRotina(bool inicio)
    {
        if (inicio)
        {

            quick.setTipo(QuickSort<unsigned>::Tipo::insercao);

            resultado += "Cenario" + std::to_string(this->id) + ": " + this->descricao + "\n";
        }
    }

    virtual void emRotinaAmostragem(unsigned int amo, bool inicio)
    {

        if (inicio)
        {

            resultado += "Amostragem: " + std::to_string(amo) + "\n";
            t1 = t2 = t3 = t4 = 0;
        }
        else
        {

            resultado += "\n";
            std::cout << std::endl;
            if (this->getNrCementes() > 0)
            {
                t1 /= this->getNrCementes();
                t2 /= this->getNrCementes();
                t3 /= this->getNrCementes();
                t4 /= this->getNrCementes();
            }
            resultadoPlot += std::to_string(amo) + "\t" +
                             std::to_string(t1) + "\t" +
                             std::to_string(t2) + "\t" +
                             std::to_string(t3) + "\t" +
                             std::to_string(t4) + "\n";
        }
    }

    virtual void emRotinaCemente(unsigned int amo, unsigned int cem)
    {
        resultado += "\nCemente: " + std::to_string(cem + 1) + "\n";

        std::cout << "Preparando vetor de backup ..." << std::endl;
        
        unsigned *backup = new unsigned[amo];
        unsigned *util = new unsigned[amo];

        for (size_t i = 0; i < amo; i++)
        {
            backup[i] = i;
        } 

        Ordenacao<unsigned>::aplicarMistura(backup, amo, this->mistura); 
       

        std::cout << "Executando QuickSort - Pivô Randômico..." << std::endl;

        std::cout << "Preparando vetor ..." << std::endl;

        for (size_t i = 0; i < amo; i++)
        {
            util[i] = backup[i];
        }

        quick.setEscolha(QuickSort<unsigned>::Escolha::random);

        t1 = quick.executar(util, amo);

        resultado += (quick.resultado() + "\n");

        std::cout << "Executando QuickSort - Pivô Média de três..." << std::endl;

        std::cout << "Preparando vetor ..." << std::endl;

        for (size_t i = 0; i < amo; i++)
        {
            util[i] = backup[i];
        }

        quick.setEscolha(QuickSort<unsigned>::Escolha::media);

        t2 = quick.executar(util, amo);

        resultado += (quick.resultado() + "\n");

        std::cout << "Executando QuickSort - Pivô Achado..." << std::endl;

        std::cout << "Preparando vetor ..." << std::endl;

        for (size_t i = 0; i < amo; i++)
        {
            util[i] = backup[i];
        }

        quick.setEscolha(QuickSort<unsigned>::Escolha::achaPivo);

        t3 = quick.executar(util, amo);

        resultado += (quick.resultado() + "\n");

        std::cout << "Executando QuickSort - Pivô Mediana..." << std::endl;

        std::cout << "Preparando vetor ..." << std::endl;

        for (size_t i = 0; i < amo; i++)
        {
            util[i] = backup[i];
        }

        quick.setEscolha(QuickSort<unsigned>::Escolha::mediana);

        t4 = quick.executar(util, amo);

        resultado += (quick.resultado() + "\n");
       

        delete[] backup;
        delete[] util;
    }
};

#endif /* CENARIO2_H */
