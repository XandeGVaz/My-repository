
/*Objeto em JavaScript
*   Boa Prática: deixar objeto em const -> programadores da linguagem.
*   Objeto-Literal: propriedades bem definidas  -> ha objetos não literais com valores determinados de
*forma dinâmica.
*
*/ 
const carro = {

    // Propriedades (atributos)
    marca: "ford",
    modelo: "ka",
    ano: 2015,
    placa: "ABC-1234",
    
    // Métodos (propriedades com funções dentro)
    buzina: function(){ alert("BIIIIIIIII")},
    completo: function(){
        return "O carro é da marca " + this.marca + " e do modelo " + this.modelo;
    }
};

// Escreve placa no consoleLog
console.log(carro.completo());

// Aplica método de buzinha
carro.buzina();

