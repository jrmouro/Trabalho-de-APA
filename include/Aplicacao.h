/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aplicacao.h
 * Author: jrmou
 *
 * Created on 28 de MarÃ§o de 2018, 12:08
 */

#ifndef APLICACAO_H
#define APLICACAO_H

#include <stack>
#include <iostream>

#include "Menu.h"

class Aplicacao : private std::stack<Menu*>{
public:
    
    Aplicacao(MenuBuilder *mb = 0, unsigned int linha = 80): linha(linha), idMenus(0){
        if(mb)
            this->abrirMenu(mb);
    }
    
    virtual ~Aplicacao(){}
    
    virtual void rodar(){ 
        this->emIniciar();
        
        if(this->abrir){
            this->push(this->abrir);
            this->abrir = 0;
        }
        
        while(!this->empty()){
            
            Menu *m = this->top();
            
            this->limpar(false);           
            
            this->antesDeExibirMenu(); 
            
            if(m->ativo()){
                std::cout << *m;
                int o = optar(m);
                if(m->executar(o))
                    esperarEnter();

                if(m->fechado()){
                    delete m;
                    this->pop();                    
                }
            }
            
            this->depoisDeExibirMenu();
            
            if(this->abrir){
                this->push(this->abrir);
                this->abrir = 0;
            }       
            
        }
        this->emTerminar();
    }
    
    bool abrirMenu(MenuBuilder *mb){
        if(!abrir){
            this->abrir = mb->get(this, idMenus++, linha);
            return true;
        }
        return false;
    }
    
    void fecharMenuAtual(){
        if(!this->empty()){
            Menu *m = this->top();
            m->fechar();            
        }
    }
    
    void terminar(){
        while(!this->empty()){
            Menu *m = this->top();
            this->pop();
            delete m;
        }
    }
    
    const unsigned int getLinha() const {
        return linha;
    }

    
private:
    
    const unsigned int linha;
    unsigned int idMenus;
    Menu *abrir = 0;
    
    int optar(Menu *m){
        
        std::cout << " Opcao: ";
        int t = m->size();
        
        bool erro = false;
        int o;
        std::string n;
        
        try {            
            std::cin >> n; 
            o = std::stoi(n);
            std::cin.clear();
        }
        catch (const std::invalid_argument& ia) {
            erro = true;
            std::cin.clear();
            std::cerr << "  Argumento invalido: "<< n << " - " << ia.what() << '\n';
        }
        
        while(erro || o < 1 || o > t){
            std::cout << "  Opcao invalida.";
            std::cout << "  Entre com uma opcao valida: ";
            erro = false;
            try {            
                std::cin >> n; 
                o = std::stoi(n);
                std::cin.clear();
            }
            catch (const std::invalid_argument& ia) {
                erro = true;
                std::cin.clear();
                std::cerr << "  Argumento invalido: "<< n << " - " << ia.what() << '\n';
            }
        }
                
        return o;
    }
    
    static void esperarEnter(){
        std::cout << "\n  Tecle Enter para continuar... " << std::endl;
        std::cin.get();
        std::cin.get();
    }
    
    static void limpar(bool esperaEnter){
        
         if(esperaEnter)
             esperarEnter();
        
        #if defined(WIN)  
            std::system("cls"); //limpa a tela   
        #else  
            std::system("clear");
        #endif

    }
    
    virtual void emTerminar(){}
    
    virtual void emIniciar(){}
    
    virtual void antesDeExibirMenu()=0;
    
    virtual void depoisDeExibirMenu(){}
    
        
};

#endif /* APLICACAO_H */

