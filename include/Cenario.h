
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cenario.h
 * Author: jrmou
 *
 * Created on 21 de Março de 2018, 17:45
 */

#ifndef CENARIO_H
#define CENARIO_H

#include <string>
#include <iostream>
#include <fstream>


class Cenario {
public:
    
    virtual ~Cenario(){}

    virtual void executar(std::string caminho, unsigned int nrCementes){
                
        this->nrCementes = nrCementes;
        
        rotina();        
                
        if(this->getResultado()!= ""){
            std::cout << "Salvando resultados referentes ao Cenário " 
                << this->id << " em "<< getNomeArquivoSaida() << " ..." << std::endl;
            salvarResultado(caminho);
        }       
        
        
        if(this->getResultadoPlot()!= ""){
            std::cout << "Salvando resultados referentes ao Cenário " 
                << this->id << " em "<< getNomeArquivoPlot() << " ..." << std::endl;
            salvarResultadoPlot(caminho);
        }
        
        if(this->getResultadoCsv()!=""){
            std::cout << "Salvando resultados referentes ao Cenário " 
                << this->id << " em "<< getNomeArquivoCsvSaida() << " ..." << std::endl;
            salvarResultadoCsv(caminho);
        }
        
        std::cout << "Imprimindo resultado referente ao Cenário " << this->id << " ..." << std::endl;
        std::cout << std::endl << (*this) << std::endl;
    }
    
       
    friend std::ostream& operator<<(std::ostream& os, const Cenario& obj) {
        os << obj.getResultado();
        return os;
    }
    
    virtual void salvarResultado(std::string caminho = ""){
        std::ofstream ofs;
        
        ofs.open(this->getNomeArquivoSaida(caminho));
        
        if(ofs.is_open()){
            ofs << this->getResultado();
            ofs.close();
        }
    }
    
    virtual void salvarResultadoPlot(std::string caminho = ""){
        std::ofstream ofs;
        
        ofs.open(this->getNomeArquivoPlot(caminho));
        
        if(ofs.is_open()){
            ofs << this->getResultadoPlot();
            ofs.close();
        }
    }
    
    virtual void salvarResultadoCsv(std::string caminho = ""){
        std::ofstream ofs;
        
        ofs.open(this->getNomeArquivoCsvSaida(caminho));
        
        if(ofs.is_open()){
            ofs << this->getResultadoCsv();
            ofs.close();
        }
    }
    
    virtual void salvar(std::string arquivo, std::string dados){
        std::ofstream ofs;
        
        ofs.open(arquivo);
        
        if(ofs.is_open()){
            ofs << dados;
            ofs.close();
        }
    }
    
    const unsigned int getId() const {
        return id;
    }

    
protected:
    
    const unsigned int id;
    unsigned int nrCementes = 0;
    
    std::string descricao;
    
    Cenario(unsigned int id, 
            std::string descricao,
            unsigned vetorN[],
            unsigned tamVetorN) :  id(id), 
                                descricao(descricao),
                                vetorN(vetorN),
                                tamVetorN(tamVetorN){ }
    
    std::string getNomeArquivoSaida(std::string caminho = "")const{
        return caminho + "cenario_" + std::to_string(id) + ".txt";
    }
    
    std::string getNomeArquivoPlot(std::string caminho = "")const{
        return caminho + "cenario_plot" + std::to_string(id) + ".txt";
    }
    
    std::string getNomeArquivoCsvSaida(std::string caminho = "")const{
        return caminho + "cenario_" + std::to_string(id) + ".csv";
    }
    
    std::string getDescricao() const {
        return descricao;
    }

    void setDescricao(std::string descricao) {
        this->descricao = descricao;
    }

    unsigned int getNrCementes() const {
        return nrCementes;
    }

    void setNrCementes(unsigned int nrCementes) {
        this->nrCementes = nrCementes;
    }
    
    virtual void rotina(){
        
        std::cout << "Cenario" << id <<": ";
        std::cout << descricao << std::endl;
        
        this->emRotina(true);

        for (size_t i = 0; i < this->tamVetorN; i++)
        {
            
            
            std::cout << std::endl << "Amostragem: " << this->vetorN[i] << std::endl << std::endl;
                       
            this->emRotinaAmostragem(this->vetorN[i], true);
                
            for(int j = 0; j < this->nrCementes; j++){
                
                std::cout << std::endl << "Cemente:" << j + 1 << std::endl << std::endl;

                this->emRotinaCemente(this->vetorN[i], j);
                                
            }  
            
            this->emRotinaAmostragem(this->vetorN[i], false);
            
                        
        };  
        
        this->emRotina(false);
    }


private:   

    unsigned *vetorN;
    unsigned tamVetorN;
       
    
    virtual std::string getResultado() const{
        return "";
    }
    
    virtual std::string getResultadoPlot() const{
        return "";
    }
    
    virtual std::string getResultadoCsv() const {
        return "";
    }
    
    
    
    virtual void emRotinaCemente(unsigned int amo, unsigned int cem) {}
    virtual void emRotinaAmostragem(unsigned int amo, bool inicio) {
        if(inicio){
        }else{            
        }
    }
    virtual void emRotina(bool inicio) {
        if(inicio){
        }else{            
        }
    }
    
};


#endif /* CENARIO_H */

