/*Aluno(N USP)
*   -Vitor Alexandre Garcia Vaz (14611432)
*/

#include <iostream>
#include <string>
#include <iomanip>

#define MAX 999999999   // maior número póssível de 9 dígitos
#define PMAX 1000000000  // maior número após os 9 dígitos
#define DEBUG 0          // DEBUG <-> 1 para debugar / DEGUG <-> 0 para não debugar

// completa string de número até atingit os 9 dígitos (necessário nas somas/subtrações)
std::string completa_str(std::string str){
    
    std::string cmp;                // string de retorno
    
    int len = str.size();           // obtem tamanho da string a ser completada
    cmp.append(str);                // string de retorno recebe string a ser completada em seu final
    for(int i = len; i < 9; i++){
        cmp = "0" + cmp;            // completa string com os "0" necessários
    }
    
    return cmp;                     // retorna string completa (com 9 dígitos)
}

// função que retira os zeros a esquerda de uma string
std::string retirar_zeros_esquerda(std::string str){
    int i= 0, mode = 0;
    int cnt_zeros=0;                        // contador de zeros na string
    std::string cmp;                        // string de retorno

    int len = str.size();                   // obtem tamanho da string q tem zeros a esquerda
    
    if(str[0] == '-') {
        i=1;
        cmp = "-";
    }

    for(i, mode; i < len; i++){
        if(mode) cmp.push_back(str[i]);     // adiciona ao final da string de retorno somente elementos após os zeros a esquerda
        else
        {
            if(str[i] != '0'){              // indentificação do primeiro elemento diferente de zero
                cmp.push_back(str[i]);      // primeiro elemento diferente de zero é adicionado na string
                mode = 1;                   // após isso todos os elementos são adicionados na string de retorno
            }

            else cnt_zeros++;
        }
    }

    if(str[0] == '-') len--;

    if(cnt_zeros == len) return "0";        // se a string só tiver zeros, retorna zero

    return cmp;
}   


class BigInt{
    int *_partes;
    int _npartes;
    bool _positivo;
public:

    BigInt(std::string numero);                                             // construtor por string de número
    BigInt(int num, bool eh_num);                                           // construtor por número inteiro
    BigInt();                                                               // construtor padrão
    BigInt(BigInt &&a);                                                     // construtor de movimento
    ~BigInt();                                                              // destrutor
    bool positivo() const;                                                  // verificador de número positivo
    BigInt& operator=(const BigInt &a);                                     // atribuição (cópia por atribuição)
    BigInt abs() const;                                                     // retorna um BigInt módulo da instância atual
    friend bool operator ==(const BigInt &a, const BigInt &b);              // igualdade de BigInt
    friend bool operator >(const BigInt &a, const BigInt &b);               // comparaçãod e BigInts
    friend BigInt operator +(const BigInt &a, const BigInt &b);             // soma de BigInts
    friend BigInt operator -(const BigInt &a, const BigInt &b);             // subtração de BigInts
    BigInt operator -() const;                                              // inversor de sinal de BigInt
    friend BigInt operator *(const BigInt &a, const BigInt &b);             // multiplicação de BigInts
    BigInt operator /(int b) const;                                         // divisão de um BigInt por um inteiro
    friend BigInt operator ^(const BigInt &a, const BigInt &b);             // elevação de um BigInt por outro
    friend std::ostream& operator <<(std::ostream &out, const BigInt &a);   // Impressão de um Big Int na sua forma inteira

};

BigInt::BigInt(std::string numero){
    int i, j, aux;
    char c;

    // retira zeros a esquerda da string
    numero = retirar_zeros_esquerda(numero);

    // obtenção do tamanho da string de número
    int size = numero.size();

    // inicialmente o número de partes é 0
    _npartes = 0;
    
    c = numero[0];
    // se for um número negativo
    if(c == '-'){
        // cálculo do número de partes
        _npartes = (size-1)/9;
        aux = (size-1)%9;
        if(aux != 0) _npartes++;
        
        // definição de sinal
        _positivo = false;
        j = 1;
    }

    // se for um número positivo
    else{
        // cálculo do número de partes
        _npartes = (size)/9;
        aux = (size)%9;
        if(aux != 0) _npartes++;

        // definição de sinal
        _positivo = true;
        j = 0;
    }

    // alocação do vetor de partes
    _partes = new int[_npartes];
    
    // inclusção de partes com nove dígitos ou menos dígitos
    if(aux != 0)    // se há parte com menos de 9 dígitos
    {
        for(i = 0; i < _npartes; i++){
            if(i == 0)         
                _partes[i] = std::stoi(numero.substr(j, aux));                  // pega numero[j]:numero[aux] e passa para _partes[0] como inteiro 
            else
                _partes[i] = std::stoi(numero.substr((i-1)*9 + j + aux, 9));    // pega numero[(i-1)*9+j+aux]:numero[i*9+j+aux] e passa para _partes[i] como inteiro
        }
    }
    else            // todas as partes tem 9 dígitos                                                                        
    {
        for(i = 0; i < _npartes; i++){
            _partes[i] = std::stoi(numero.substr(i*9 + j, 9));                  // pega numero[i*9+j]:numero[(i+1)*9+j] e passa para _partes[i] como inteiro
        }
    }

}

BigInt::BigInt(int num, bool eh_num=true){
    
    // se é um número, adiciona-se esse mesmo número inteiro na forma de string
    if(eh_num){
        int i, j, aux;
        char c;
        
        // monta-se string do número dado
        std::string numero = std::to_string(num);

        // obtenção do tamanho da string de número
        int size = numero.size();

        // inicialmente o número de partes é 0
        _npartes = 0;

        c = numero[0];
        // se for um número negativo
        if(c == '-'){
            // cálcculo do número de partes
            _npartes = (size-1)/9;
            aux = (size-1)%9;
            if(aux != 0) _npartes++;

            // definição de sinal
            _positivo = false;
            j = 1;
        }

        // se for um número positivo
        else{
            // cálculo do número de partes
            _npartes = (size)/9;
            aux = (size)%9;
            if(aux != 0) _npartes++;

            // definição de sinal
            _positivo = true;
            j = 0;
        }

        // alocação do vetor de partes
        _partes = new int[_npartes];

        // inclusção de partes com nove dígitos ou menos dígitos
        if(aux != 0)
        {
            for(i = 0; i < _npartes; i++){
                if(i == 0)         
                    _partes[i] = std::stoi(numero.substr(j, aux));                  // pega numero[j]:numero[aux] e passa para _partes[0] como inteiro 
                else
                    _partes[i] = std::stoi(numero.substr((i-1)*9 + j + aux, 9));    // pega numero[(i-1)*9+j+aux]:numero[i*9+j+aux] e passa para _partes[i] como inteiro
            }
        }
        else
        {
            for(i = 0; i < _npartes; i++){
                _partes[i] = std::stoi(numero.substr(i*9 + j, 9));                  // pega numero[i*9+j]:numero[(i+1)*9+j] e passa para _partes[i] como inteiro
            }
        }
    }

    // caso contrário, adiciona-se uma quantidade num de zeros
    else{
        _positivo = true;
        _npartes = num;
        _partes = new int[num];
        for(int i = 0; i < num; i++) _partes[i] = 0;
    }
}

// coloca-se um zero em BigInt
BigInt::BigInt(){
    _positivo = true;
    _npartes = 1;
    _partes = new int[1];
    _partes[0] = 0;
}

// cópia de movimento 
BigInt::BigInt(BigInt &&b): _npartes(b._npartes), _positivo(b._positivo) 
{
    _partes = std::move(b._partes);
}

// destruidor do BigInt (desaloca vetor *_partes)
BigInt::~BigInt(){
    delete [] _partes;             // desaloca vetor de partes
}

// retorna se o BigInt é positivo
bool BigInt::positivo() const{
    return _positivo;           
}

// cópia por atribuição (funciona melhor para classes que usam recursos)
BigInt& BigInt::operator =(const BigInt &b){
    // número de partes e sinal da instância atual
    _npartes = b._npartes;
    _positivo = b._positivo;

    // estava gerando erros sem essa parte -> aparentemente o copy exige que o vetor de recepção já tenha sido alocado
    delete [] _partes;
    _partes = new int [b._npartes];

    // cópia das partes de b para a istância atual
    std::copy(b._partes, b._partes+b._npartes, _partes); // evita que duas classes tenham termos se referindo ao mesmo endereço
    return *this;
}

// retorno de valor absoluto do BigInt
BigInt BigInt::abs() const{
    std::string str;
    int i =1;   
    
    // copia partes do big int para a string sem considerar o sinal
    str = str + std::to_string(_partes[0]);
    for(i; i < _npartes; i++){

        str.append( completa_str( std::to_string(_partes[i]) ) );
    }

    return BigInt(str); // inicia-se novo BigInt sem o sinal
}

// Operação == entre dois BigInt
bool operator ==(const BigInt &a, const BigInt &b){
    
    std::string str1, str2;

    // transforma BigInt a em string
    if(!a._positivo) str1.append("-");
    for(int i = 0; i < a._npartes; i++){
        str1.append(std::to_string(a._partes[i]));
    }

    // transforma BigInt b em string
    if(!b._positivo) str2.append("-");
    for(int i = 0; i < b._npartes; i++){
        str2.append(std::to_string(b._partes[i]));
    }

    // para serem iguais, strings resultantes devem ter todos os caracteres iguais
    return(str1.compare(str2) == 0);
}

// Operação > entre dois BigInt
bool operator >(const BigInt &a, const BigInt &b){
    int num1, num2;

    // caso tenham sinai diferentes o maior é positivo
    if(a._positivo != b._positivo){
        return (a._positivo) ? true : false;
    }
    
    // caso tenham o mesmo sinal
    else{
        
        // se forem ambos positivos
        if(a._positivo)
        {   
            // se tiverem o mesmo número de partes, o maior é o com o maior número na parte mais significativa
            if(a._npartes == b._npartes)
            {
                for(int i=0; i < a._npartes; i++)               // para comparação nesse caso, considera a parte mais significativa na qual os BigInts se diferenciam
                {
                    num1 = a._partes[i];
                    num2 = b._partes[i];
                    if(num1!=num2) return(num1 > num2);
                }

                return true;
            }

            // se tiverem número diferente de partes retorna o que tiver maior número de partes
            else return (a._npartes > b._npartes) ? true:false;
        }

        // se forem ambos negativos, a lógica é a mesma para o caso de ambos positivos, mas o resultado é invertido
        else
        {
            if(a._npartes == b._npartes)
            {
                for(int i=0; i < a._npartes; i++)       // para comparação nesse caso, considera a parte mais significativa na qual os BigInts se diferenciam
                {
                    num1 = a._partes[i];
                    num2 = b._partes[i];
                    if(num1 != num2) return(num1 < num2);
                }

                return true;
            }

            else return (a._npartes > b._npartes) ? false:true;
        }
    }
}

// operação + entre dois BigInts
BigInt operator +(const BigInt &a, const BigInt &b){

    int aux_a, aux_b;   // auxiliares para receberem partes de a e b
    int som = 0;        // resultado de soma de partes
    int fi;             // fator de inversão(usado na subtração)
    int ext;            // extensão da soma/subtração


    // strings usadas na determinação do resultado final
    std::string aux, appd;

    // sinais dos BigInts a e b
    int asig=1, bsig=1;
    asig = (a._positivo) ? 1:-1;
    bsig = (b._positivo) ? 1:-1;

    // ext recebe a maior extensão de BigInt
    ext = (a._npartes > b._npartes) ? a._npartes : b._npartes;
    

    // caso sejam ambos os BigInts positivos ou negativos
    if(a._positivo == b._positivo)
    {
        if(DEBUG) printf("\tSOMA\n");

        // loop de somas de partes e integração dessas somas em uma string
        for(int i = 0, j =0, ka, kb, k; i < ext ; i++)
        {
            // iterador atual das partes
            ka = (a._npartes-1) - i;
            kb = (b._npartes-1) - i;
            k = (ka > kb) ? ka:kb;                      // iterador máximo (referente ao elemento com maior número de partes)

            // Verificação de acesso da lista de inteiros
            aux_a = (i < a._npartes) ? a._partes[ka] : 0;
            aux_b = (i < b._npartes) ? b._partes[kb] : 0;
            if(DEBUG) printf("a._partes[%d] = %d || b._partes[%d] = %d || ",i,aux_a,i,aux_b);

            // Obtenção da soma que será integrada a string de resultado
            som += aux_a + aux_b;
            if(DEBUG) printf("som[%d] = %d || ",i,som);

            // Verificação se há carregamento na soma
            if(som > MAX){                              // com carregamento (para a próxima soma)
                appd = std::to_string(som%PMAX);
                appd = completa_str(appd);
                if(DEBUG) printf("appd[%d] = %s || ",i,appd.data());

                som = 1;
            } 
            else if(som <= MAX){                        // sem carregamento
                appd = std::to_string(som);
                if(k!=0) appd = completa_str(appd);
                if(DEBUG) printf("appd[%d] = %s || ",i,appd.data());

                som = 0;
            }
            
            aux = appd + aux;                           // adiciona nova parte no começo da string
            if(DEBUG) printf("aux[%d] = %s\n",i,aux.data());

        }

        if(som==1) aux = "1" + aux;                     // caso haja carregamento da última soma necessária

                                                    
        if(asig == -1) aux = "-" + aux;                 // caso sejam negativos "-" é considerado no início da string
        
        if(DEBUG) printf("res = %s\n",aux.data());

        return BigInt(aux);                             // retorna BigInt com base na string montada
    }

    // caso possuam sinais diferentes
    else
    {

        if(DEBUG) printf("\tSUBTRAÇÃO\n");


        // determinação do fator de inversão de termos (necessário pois para o cpalculo do módulo da subtração, o termo absolutamente menor estará subtraindo)
        fi = (a.abs() > b.abs()) ? 1:-1;

        if(DEBUG) printf("%d\n",fi);
        
        // loop de somas de partes e integração dessas somas em uma string
        for(int i = 0, ka, kb, k; i < ext ; i++)
        {
            // iterador atual das partes
            ka = (a._npartes-1) - i;
            kb = (b._npartes-1) - i;
            k = (ka > kb) ? ka:kb;                                 // iterador máximo (referente ao elemento com maior número de partes)
            
            // Verificação de acesso da lista de inteiros
            aux_a = (i < a._npartes) ? (a._partes[ka]) : 0;
            aux_b = (i < b._npartes) ? (b._partes[kb]) : 0;
            if(DEBUG) printf("a._partes[%d] = %d || b._partes[%d] = %d ||",i,aux_a,i,aux_b);
            
            // Obtenção da soma que será integrada a string de resultado (considerando sinais)
            som += fi*aux_a - fi*aux_b;
            if(DEBUG) printf("som[%d] = %d\n ||",i,som);

            // Verificação se há carregamento na subtração
            if(som <= MAX & som >= 0){                             // não recebe carregamento da próxima soma
                appd = std::to_string(som);
                if(k!=0) appd = completa_str(appd);
                if(DEBUG) printf("appd[%d] = %s || ",i,appd.data());

                som = 0;
            } 
            else if(som < 0){                                      // recebe carregamento da próxima soma
                
                if(k!=0) // se n for o último elemento
                {
                    som += PMAX;                                    // carregamento
                    appd = std::to_string(som);                    
                    appd = completa_str(appd);
                }

                else{ // caso seja última parte, não há carregamento e nema  string é completada
                    appd = std::to_string(som);
                }
                if(DEBUG) printf("appd[%d] = %s || ",i,appd.data());


                som = -1;
            }
            
            aux = appd + aux;
            if(DEBUG) printf("aux[%d] = %s\n",i,aux.data());
        }

        if(DEBUG) printf("res = %s\n",appd.data());
    
        // se o número que tiver maior módulo for negativo, o resultado é negativo
        if(( (fi==1 && asig==-1) || (fi==-1 && bsig == -1) ) ) aux = "-" + aux;

        return BigInt(aux);                             // retorna BigInt com base na string montada

    }

}

// operação - entre dois BiInt (soma do primeiro pelo oposto do segundo)
BigInt operator -(const BigInt &a, const BigInt &b){
    BigInt aux;
    aux = b;
    aux._positivo = !aux._positivo;

    return a+aux;
}

// operação de inversão do BigInt (subtração do elemento nulo pela instância atual)
BigInt BigInt::operator -() const{
    BigInt aux;
    aux = *this;
    if(!(_npartes == 1 && _partes[0] == 0)) aux._positivo = not aux._positivo;
    return aux;
}

// operação de multiplicação de dois BigInt
BigInt operator *(const BigInt &a, const BigInt &b){
    
    unsigned long long mult = 0;     // resultado de b._partes[i] pelas partes de a
    unsigned long long A, B;
    int i, j, k;

    // strings usadas na determinação do resultado final
    std::string aux, appd, strList;

    // sinais dos BigInts a e b
    int asig=1, bsig=1;
    asig = (a._positivo) ? 1:-1;
    bsig = (b._positivo) ? 1:-1;

    // vetor de BigInts que somados formarão o resultado final
    BigInt *list = new BigInt[b._npartes];
    BigInt res;

    if(DEBUG) printf("\tMULTIPLICAÇÃO\n");

    for(i = b._npartes - 1; i >= 0; i--)
    {
        strList = "";                                   // inicialmente, a string referente ao elemento a ser adicionado na lista está vazia
        mult = 0;                                       // o resultado de multiplicação, inicialmente, também é zero                   

        for(j = a._npartes - 1; j >= 0; j--)
        {
            if(DEBUG) printf("carry = %lld || ", mult);
            
            A = a._partes[j]; B = b._partes[i];
            mult += A * B;                              // resultado de multiplicação

            if(DEBUG) printf(" a._parte[%d] = %d || b.parte[%d] = %d || mult = %lld || ",j,a._partes[j],i,b._partes[i],mult);
            
            // se o resultado tiver no máximo 9 dígitos, integramos ele a resposta final
            if(mult < PMAX){     
                appd = std::to_string(mult);            
                if(j!=0) appd = completa_str(appd); 
                mult = 0;
            }
            
            // caso contrário, integramos o resto por PMAX na resposta final e geramos um carregamento para a próxima multiplicação
            else{
                appd = std::to_string(mult%PMAX);
                appd = completa_str(appd);
                mult = mult/PMAX;
            }

            strList = appd + strList;

            if(DEBUG) printf("appd[%d] = %s\n",j,appd.data());
        }

        if(mult !=0) strList = std::to_string(mult) + strList;      // caso haja carregamento final, adiciona na lista                  
        
        for(k = 0; k < (b._npartes - (i+1)); k++){                  // adiciona zeros a direita (mostrar ordem de grandeza)
                strList.append("000000000");
        }

        if(DEBUG) printf("\tBigInt[%d]= %s\n", b._npartes - (1+i),strList.data());

        list[b._npartes - (1+i)] = BigInt(strList);                      // elemento i da lista de BigInts recebe valor 
    }

    for(i=0; i < b._npartes; i++){                      // resultado final como soma de elementos da lista
        res = res + list[i] ;
    }

    delete [] list;                                     // desaloca lista de BigInts a serem somados
    
    if(DEBUG) printf("asig = %d || bsig = %d\n",asig,bsig);

    if(asig != bsig) res = -res;                        // se a e b tiverem sinais diferentes, o resultado é negativo

    return res;
}

// operação de divisão de um BigInt por um inteiro normal
BigInt BigInt::operator/(int b) const{

    unsigned long long div;         // resultado  da divisão de _partes[i] pelo inteiro b
    unsigned long long num, denom;  // numerador e denominador da divisão
    unsigned long long parte;       // parte atual  
    int i, j;       // índices
    int cont = 0;   // contador 
    int flag;       // flag de indicação de soma de partes
    
    // strings usadas na determinação do resultado final
    std::string appd, str;

    // sinal da instância atual e do inteiro b
    unsigned long long siga = (_positivo) ? 1:-1;
    unsigned long long sigb = (b>=0) ? 1:-1;

    if(DEBUG) printf("\tMULTIPLICAÇÃO\n");

    // conta de divisão
    div = 0;                                            // inicialmente a divisão é zero
    denom = b;                                          // denominador é igual a b

    if(DEBUG) printf("Denominador = %lld\n", denom);

    for(i = 0; i < _npartes; i++)
    {
        flag = 1;                                       // inicialmente, flag de soma das partes é igual a 1
        num = div + (unsigned long long)_partes[i];     // numerador recebe _partes[i]

        while(flag)                                      
        {   
            if(DEBUG) printf("Num[%d] = %lld\n", i, num);
            
            if(num < (sigb*denom) && (i+1) < _npartes){         // enquanto num < |b|, somo as partes menos significativas a num
                num=PMAX*num+(unsigned long long)_partes[i+1];          
                str = str + "000000000";                        // considero zeros a esquerda no resultado final
                i ++;                                           // vou para próxima parte
            }
            else{

                div = num/(sigb*denom);                        // div = div + quonciente de (num/|b|) 
                appd = std::to_string(div);                     // transformo div para string, recebida por appd
                if(i != 0) appd = completa_str(appd);   
                
                if(DEBUG) printf("div[%d] = %lld || ", i, div);

                div = (num%(sigb*denom))*PMAX;                       // carregamento para próxima parte (igual ao resto da divisão)
                
                if(DEBUG) printf("carry[%d] = %lld\n", i, div);

                flag = 0;
            }             
        }

        if(DEBUG) printf("appd[%d] = %s\n", i, appd.data());

        str.append(appd);                                       // adiciona appd no final da string de resultado final
    }

    if(DEBUG) printf("res = %s\n",str.data());

    if( (siga*sigb) == -1) str = "-"  + str;     // se a e b tiverem sinais diferentes, o retorno é negativo

    return BigInt(str);                                         // retorno da divisão   
}

// operação de elevação de um BigInt (a) por outro (b), ou seja, (a^b)
BigInt operator ^(const BigInt &a, const BigInt &b){
    
    BigInt res, zero;

    if(b._npartes == 1){
        res = a;
        for(int i = 1; i < b._partes[0]; i++){
            res = res * a;
        }
    }

    else
    {
        res = 1;
        for(int i = 0; i < b._npartes; i++)
        {
            for(int j=0; j < b._partes[j] ; j++)    res = res * a;
        }
    }

    return res;
}
 
// impressão de BigInt com std::cout na forma de um número inteiro
std::ostream& operator <<(std::ostream &out, const BigInt &a){
   
    std::string print;

    if(!a._positivo) out << '-';
    
    out << a._partes[0];
    
    for(int i = 1; i < a._npartes; i++){
        print = std::to_string(a._partes[i]);
        print = completa_str(print);
        out << print;
    }

    return out;
}

int main() {
    BigInt a(1769046);
    a = a + BigInt(-359581455);
    std::cout << a.abs() << std::endl;
    a = a - BigInt(-1312384133);
    std::cout << a.abs() << std::endl;
    a = a - BigInt(-549574006);
    std::cout << a.abs() << std::endl;  // 1504145730
    a = a / (-808589206);
    // std::cout << "ETP ERRO 1 : "<< a << std::endl;
    a = a ^ BigInt(26);
    // std::cout << "ETP ERRO 2 : "<< a << std::endl;
    a = a * BigInt(-2886168);
    // std::cout << "ETP ERRO 3 : "<< a << std::endl;
    a = a - BigInt(-1672877545);
    // std::cout << "ETP ERRO 4 : "<< a << std::endl;
    a = a + BigInt(1328378163);
    std::cout << a << std::endl;
    a = a * BigInt(-160854082);
    a = a ^ BigInt(17);
    a = a * BigInt(-405596109);
    std::cout << a.abs() << std::endl;
    std::cout << a << std::endl;
    std::cout << a.abs() << std::endl;
    return 0;
}