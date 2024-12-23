// Avisa que houve click
function eventoClick (){ 
    alert("Houve click"); // alerta de que houve click
    document.body.style.backgroundColor = "yellow"; // mudança de cor do background
}

// Avisan que houve clique duplo
function eventoDbClick(){
    alert("Houve doble click"); // alerta de que houve duplo click
    document.body.style.backgroundColor = "blue"; // mudança de cor do background
}

// Muda cor da div se mouse estiver sobre ela
function eventoMouseOver(){
    let div = document.getElementById("onMouseTemplate1"); // obtém determinado elemento do documento pelo seu id
    div.style.backgroundColor = "rgb(0,0,0)" // muda background do elemento cujo id foi obtido
}

// Retorna a cor da div se o mouse sair dela
function eventoMouseOut(){
    let div = document.getElementById("onMouseTemplate1"); // obtém determinado elemento do documento pelo seu id
    div.style.backgroundColor = "rgb(0,0,255)" // muda background do elemento cujo id foi obtido

}

// Avisa que mouse se moveu na div (aviso no console)
function eventoMouseMove(){
    console.log("Mouse se moveu");
}

// Muda cor da div se o click estiver ativo em cima da div
function eventoMouseDown(){
    let div = document.getElementById("onMouseTemplate2");
    div.style.backgroundColor = "rgb(0,0,0)";
}

// Volta cor da div normal e compartila aviso quando o usuaŕio para de clicar me cima da div
function eventoMouseUp(){
    alert("soltou o mouse");
    let div = document.getElementById("onMouseTemplate2");
    div.style.backgroundColor = "rgb(255,255,255)";
}

// Limpa o texto já presente no input antes do onFocus
function onFocus(){
    document.getElementById("input1").value="";
}

// Avisa quando o conteúdo do imput muda (pode ser muito utilizado para select)
function onChange(){
    console.log("Conteúdo do input mudou");
}

// Avisa quando o input sai de foco
function onBlur(){
    alert("Input saiu de foco");
}

// Quando uma tecla é apertada, mostra o conteúdo atual do input
function onKeyDown(){
    console.log("Conteúdo input 2: " + document.getElementById("input2").value);
}

// Quando uma tecla é pressionada, mostra o conteúdo atual do input
function onKeyPress(){
    console.log("Conteúdo input 3: " + document.getElementById("input3").value);
}

// Quando uma tecla é solta, mostra conteúdo atual do input
function onKeyUp(){
    console.log("Conteúdo input 4: " + document.getElementById("input4").value);
}

// Quando a página é carregada, avisa
function onLoad(){
    alert("Página carregada");
}

// Quando a página é redimensionada, avisa
function onResize(){
    alert("Página redimensionada");
}