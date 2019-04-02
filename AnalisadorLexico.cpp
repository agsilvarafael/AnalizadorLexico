#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> identificadores= {"Program","Var","Const","Begin"};
FILE *fp;

bool identificaSinal(char c);
char lerLetras(char c);
char lerNumeros(char c);
char lerCoisaEstranha(string s);

int main(int argc, char const *argv[]){
	char *nomeArq,c;

    cout << "Digite o nome do arquivo"<< endl;
    cin >> nomeArq;

	fp = fopen(nomeArq, "r");
	
	c = getc(fp);
    while(c!=EOF){
        //ignora espaços e quebras de linha
        if(c!=' '&& c>13){
            if(!identificaSinal(c)){
                if(c==':'){
                    c = getc(fp);
                    if(c=='='){
                        cout << "O sinal de atribuicao [:=]" << endl;
                      c = getc(fp);
                    }else{
                        cout << "O sinal de dois pontos [:]" << endl;
                    }
                }else if(c>47&&c<58){
                    c = lerNumeros(c);
                }else if((c>64&&c<92) || (c>96&&c<122) ){
                    c = lerLetras(c);
                }else {
                    string s;
                    s.push_back(c);
                    c = lerCoisaEstranha(s);
                }
            }else{
                c = getc(fp);
            }
        }else{
            c = getc(fp);
        }
    }
    

	return 0;
}

bool identificaSinal(char c){
    switch (c)
        {
            case '+': cout << "O sinal de adicao [+]" << endl; return true;
            case '*': cout << "O sinal de multiplicacao [*]" << endl; return true;
            case '/': cout << "O sinal de divisao [/]" << endl; return true;
            case '-': cout << "O sinal de subtracao [-]" << endl; return true;
            case '=': cout << "O sinal de igualdade [=]" << endl; return true;
            case '(': cout << "O sinal de abre parenteses [(]" << endl; return true;
            case ')': cout << "O sinal de fecha parenteses [)]" << endl; return true;
            case ',': cout << "O identificador de virgula [,]" << endl; return true;
            case '.': cout << "O identificador de fim de programa (ponto final) [.]" << endl; return true;
            case ';': cout << "O identificador de fim de comando (ponto e virgula) [;]" << endl; return true;
            default: return false;
        }
}

char lerLetras(char c){
    string s;
    s.push_back(c);
    c = getc(fp);
    //Se for letra
    while((c>64&&c<92) || (c>96&&c<122)){
        s.push_back(c);
        c = getc(fp);
    }
    //se numero
    if(c>47&&c<58){
        s.push_back(c);
        c = getc(fp);
        //se letra ou numero
        while((c>64&&c<92) || (c>96&&c<122) || (c>47&&c<58)){
            s.push_back(c);
            c = getc(fp);
        }
        //Se for fim, espaço ou sinal
        if(c==' ' || c<=13 || identificaSinal(c) || c == ':' ){
            cout << "A variavel " << s << endl;
            return c;
        }
    }
    else{
        //Se for fim, espaço ou sinal
        if(c==' ' || c<=13 || identificaSinal(c) || c == ':' ){
            for(string st: identificadores){
                if(!s.compare(st)){
                cout << "Um identificador da linguagem - " << s << endl;
                return c;
                }
            }
            cout << "A variavel " << s << endl;
            return c;
        }
    }
    return lerCoisaEstranha(s);
}

char lerNumeros(char c){
    int n = 0;
    //enquanto numero
    while(c>47&&c<58){
        n = n*10 + c-48;
        c = getc(fp);
    }
    //Se for fim, espaço ou sinal
    if(c==' ' || c<=13 || identificaSinal(c) || c == ':' ){
        cout << "O Numero " << n << endl;
        return c;
    }
    string s = to_string(n);
    s.push_back(c);
    return lerCoisaEstranha(s);
}

char lerCoisaEstranha(string s){
    char c = getc(fp);
    //Se nao for fim, espaço ou sinal
    while(c!=' ' && c>13 && !identificaSinal(c) && c != ':' ){
        s.push_back(c);
        c = getc(fp);
    }
    cout << "Identificador desconhecido ou fora da linguagem [" << s << "]" << endl;
    return c;
}