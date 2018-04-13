#include <iostream>
#include "includes/S_List.h"
#include "includes/Scoope.h"
#include <regex>
#include<string>


using namespace std;
/*
         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47

Example cout << "\033[11;31mbold red text\033[0m\n";

reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27

*/





//string const ptrn_signos = "=(?!.*?[\\-]{2})(?!.*?[\\+]{2})[\\+\\-\\s]*";//patron de +'s y -'s exectuando 2 +'s seguidos o 2 -'s seguidos
//string const ptrn_asignacionGeneral_v0 =                "^\\s*((?!.*?[\\&]{2})[^\\s0-9{int}{long}{char}{float}{double}]*)\\s*((?!(int|long|char|float|doble)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=)\\s*(\\d+|\\'.\\'|\\\".[^\\\"]*\\\"|\\\"\\\"|\\d+\\.\\d+|((?!.*?[\\&]{2})[^\\s0-9]*)(?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\']*)\\s*\\;";
//regex const rgx_AG_v0(ptrn_asignacionGeneral_v0);
//string const ptrn_declaracion_AsignacionGeneral_v1 =    "\\s*(int|long|char|float|double)(\\s*\\*+\\s*|\\*+\\s*|\\s*\\*+|\\s+)((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=)\\s*(\\d+|\\'.\\'|\\\".[^\\\"]*\\\"|\\\"\\\"|\\d+\\.\\d+|((?!.*?[\\&]{2})[^\\s0-9]*)(?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\']*)\\s*\\;";
//regex const rgx_DAG_v1(ptrn_declaracion_AsignacionGeneral_v1);
string const ptrn_nombre_v                  =           "(?!(int|long|char|float|double|struct)[\\;|\\s])[A-z][A-z\\d\\_]*";
string const ptrn_las_weas_de_antes_de_v    =           "(?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*";
string const ptrn_weas_v                    =           "\\s*((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[A-z\\d\\_]*)\\s*";
string const ptrn_struct                    =           "(?:(struct)\\s*([A-z][A-z\\d\\_]*)\\s*(\\{)\\s*((?![\\{\\}])\\s*(?:[^\\{\\}]|\\s)+)\\s*(\\})\\s*((?:[A-z][A-z\\d\\_]*\\s*\\,?\\s*)*\\s*\\;))";
regex const rgx_struct_v0(ptrn_struct);
string const ptrn_hmmm                      =           "(\\{)\\s*((?![\\{\\}])\\s*(?:[^\\{\\}]|\\s)+)\\s*(\\})";
string const ptrn_print                     =           "\\s*(Hable)\\(\\s*(\\\"[^\\\"]*\\\"|(?:(?!(int|long|char|float|double|struct)[\\;\\s\\)])[A-z][A-z\\d\\_]*))\\s*\\)\\s*\\;";
regex const rgx_print_v0(ptrn_print);


string const ptrn_getAddr                   =           "\\s*(getAddr)\\(\\s*((?!(int|long|char|float|double|struct)[\\;\\s\\)])[A-z][A-z\\d\\_]*)\\s*\\)\\s*\\;";
regex const rgx_getAddr = regex(ptrn_getAddr);


string const ptrn_getValue                   =           "\\s*(getValue)\\(\\s*((?!(int|long|char|float|double|struct)[\\;\\s\\)])[A-z][A-z\\d\\_]*)\\s*\\)\\s*\\;";
regex const rgx_getValue = regex(ptrn_getValue);



regex const rgx_arreglar_espaciado_llaves = regex("\\s{2,}|\\{|\\}");//Dos o mas espacios juntos o las llaves
regex const rgx_arreglar_espaciado = regex("\\s{2,}");//Dos o mas espacios juntos o las llaves



//string const ptrn_declaracionGeneral_v0 =               "\\s*(int|long|char|float|double|struct)(\\s*\\*+\\s*|\\*+\\s*|\\s*\\*+|\\s+)((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\']*)\\s*\\;";//con * como punteros
//regex const rgx_DG(ptrn_declaracionGeneral_v0);

string const ptrn_declaracionGeneral_v1 =               "\\s*(int|long|char|float|double|struct)\\s*((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z][A-z\\d\\_]*)\\s*\\;|\\s*(reference)\\s*\\<(int|long|char|float|double)\\>\\s+((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z][A-z\\d\\_]*)\\;";
regex const rgx_DG(ptrn_declaracionGeneral_v1);//Nuevo

//string const ptrn_asignacionGeneral_v1 =                "\\s*((?!.*?[\\&]{2})[^\\s0-9A-z]*)\\s*((?!(int|long|char|float|doble)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=|\\+=|\\-=)\\s*(?:(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\'\\;]*))|\\.)\\s*\\;";
//regex const rgx_AG_v1(ptrn_asignacionGeneral_v1);


//Cuando supuestamente hay una operacion
//string const ptrn_asignacionGeneral_v2 =                "^\\s*((?!.*?[\\&]{2})[^\\s0-9A-z]*)\\s*((?!(int|long|char|float|doble|struct)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=|\\+=|\\-=)\\s*(?:(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\'\\;]*))|\\.)\\s*\\;";
//regex const rgx_AG_v2(ptrn_asignacionGeneral_v2);


string const ptrn_asignacionGeneral_v3 =                "\\s*((?!(int|long|char|float|doble)[\\;|\\s])[A-z][A-z\\d\\_]*)\\s*(=|\\+=|\\-=)\\s*(?:(?:(\\+|\\-)?\\s*(\\d+))|(\\'.\\')|(\\\"[^\\\"]*\\\")|(\\d+\\.\\d+)|(\\+|\\-)?\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;|\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;|\\s])[A-z][A-z\\d\\_]*)|((?!(int|long|char|float|doble|struct)[\\;\\s\\+])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))))\\s*\\;";
regex const rgx_AG_v3(ptrn_asignacionGeneral_v3);//Nuevo

string const ptrn_declaracion_AsignacionGeneral_v2 =    "\\s*(?:(reference\\<(?:int|long|char|float|double)\\>)|(int|long|char|float|double))(?:\\s*(\\*+)\\s*|(\\*+)\\s*|\\s*(\\*+)|(\\s+))((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=)\\s*(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*\\;";
regex const rgx_DAG_v1(ptrn_declaracion_AsignacionGeneral_v2);


//string const ptrn_operacionAritmetica_v4 =             "\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*([\\+]{2}|[\\-]{2})|([A-z]+|\\d+))\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*([\\+]{2}|[\\-]{2})|([A-z]+|\\d+))|((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*((?:[\\+]{2}|[\\-]{2})))\\s*\\;";
//regex const rgx_OA_v0(ptrn_operacionAritmetica_v4);


//string const ptrn_operacionAritmetica_v5 =             "\\s*(?:([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+|\\d+\\.\\d+)|)\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)(\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+))|((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*((?:[\\+]{2}|[\\-]{2})))\\s*";
//regex const rgx_OA_v1(ptrn_operacionAritmetica_v5);

string const ptrn_operacionAritmetica_v5 =             "\\s*(?:(?:(?:(\\+|\\-)?\\s*(\\d+))|(\\'.\\')|(\\\"[^\\\"]*\\\")|(\\d+\\.\\d+)|(\\+|\\-)?\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;\\s])[A-z][A-z\\d\\_]*)|((?!(int|long|char|float|doble|struct)[\\;\\s\\+\\-])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))))\\s*(|\\+|\\-|\\*|\\/)\\s*(?:(?:(\\+|\\-)?\\s*(\\d+))|(\\'.\\')|(\\\"[^\\\"]*\\\")|(\\d+\\.\\d+)|(\\+|\\-)?\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;\\s])[A-z][A-z\\d\\_]*)|((?!(int|long|char|float|doble|struct)[\\;\\s\\+\\-])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))))|(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;\\s\\+\\-])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))))\\s*";
regex const rgx_OA_v1(ptrn_operacionAritmetica_v5);//Nuevo


//string const ptrn_operacionAritmetica_v6 =             "\\s*(?:([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+|\\d+\\.\\d+)|)\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)(\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|((?!.*?[\\&]{2})[\\*\\&]+)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)\\s*([\\+]{2}|[\\-]{2})|((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)\\s*([\\+]{2}|[\\-]{2})|\\'[^\\']+\\'|\\d+)|((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z][A-z\\d\\_]*)|((?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)?\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2})))\\s*";
//regex const rgx_OA_v2(ptrn_operacionAritmetica_v6);

string const ptrn_operacionAritmetica_v7 =              "\\s*(|\\+|\\-|\\*|\\/)\\s*(?:(?:(\\+|\\-)?\\s*(\\d+))|(\\'.\\')|(\\\"[^\\\"]*\\\")|(\\d+\\.\\d+)|(\\+|\\-)?\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;\\s])[A-z][A-z\\d\\_]*)|((?!(int|long|char|float|doble|struct)[\\;\\s\\+\\-])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))))\\s*";
regex const rgx_OA_v2(ptrn_operacionAritmetica_v7);//Nuevo


string const ptrn_operador_variable_v0 =             "\\s*(?:([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+)))";
regex const rgx_OV_v0(ptrn_operador_variable_v0);
//Nuevo//"\\s*(?:([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))([\\+\\-])?\\s*(\\+|\\-)?\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)(?!(int|long|char|float|doble|struct)[\\;\\s])([A-z][A-z\\d\\_]*))|((?!(int|long|char|float|doble|struct)[\\;\\s\\+\\-])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2}))|((?!(int|long|char|float|doble|struct)[\\;\\s])[A-z][A-z\\d\\_]*)))";


//Globales
S_List<Scoope> * VG_scoopes = new S_List<Scoope>;
S_List<S_List<string>> * VG_structs = new S_List<S_List<string>>;


char getTypeDataDeclaration(std::string instruccion);
char getTypeDataDeclaration(std::string instruccion)
{
    if(regex_match(instruccion, rgx_DG))
    {

        if(regex_search(instruccion, regex("int")))
            return 'i';
        if(regex_search(instruccion, regex("long")))
            return 'l';
        if(regex_search(instruccion, regex("char")))
            return 'c';
        if(regex_search(instruccion, regex("float")))
            return 'f';
        if(regex_search(instruccion, regex("double")))
            return 'd';
    }
    else
        return 'n';
}

void getTokens(smatch groups, S_List<string> *tokens)
{
    for(string i : groups)
        if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
            if(i != groups[0])
                tokens->add(i);
}

void eliminarEspacios(S_List<string> *tokens)
{
    for(int i=0; i < tokens->getSize(); i++)
    {
        string s = tokens->get(i);
        if(!regex_match(s, regex("\\s*")))//Si el group solo es \s lo omite
        {
            s = regex_replace(s, regex("\\s"), "");//Borra los espacios innecesarios
            tokens->edit(s, i);
        }
        else
            tokens->del(i);
    }
}

bool getTokensOperacion(string str, S_List<string> *tokens)
{
    smatch groups;
    int cantidad_a_cortar = 0;
    if(regex_search(str, groups, rgx_OA_v2))
    {
        for(int x=0; x < groups.size(); x++)
        {
            string i = groups[x];
            if(x==0)
                cantidad_a_cortar += i.length();
            if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
                if(x!=0)
                {
                    tokens->add(i);
                }

        }
        str = str.substr(cantidad_a_cortar, str.size());

    }
    while(str != ";" && str != "")
    {
        cantidad_a_cortar = 0;
        if(regex_search(str, groups, rgx_OV_v0) || regex_search(str, groups, regex("\\s*(?:([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))([\\+\\-])?\\s*(?:(?:(?:(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]*)\\s*((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})\\s*|(\\d+)))\\s*")))
        {
            for(int x=0; x < groups.size(); x++)
            {
                string i = groups[x];
                if(x==0)
                    cantidad_a_cortar += i.length();
                if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
                    if(x!=0)
                        tokens->add(i);
            }
            str = str.substr(cantidad_a_cortar, str.size());
        }
        else
        {
            int veces = tokens->getSize();
            for(int a=0; a < veces; a++)
                //tokens->delFirst();
            return false;
        }

    }
    eliminarEspacios(tokens);
    return true;
}

S_List<string> * parsear(string str, char c)
{
    string segmento;
    stringstream stringstream(str);
    S_List<string> *segmentos = new S_List<string>;

    while(std::getline(stringstream, segmento, c))
        segmentos->add(segmento);

    return segmentos;
}


int readInstruction(string instruccion, S_List<string> * tokens)
{
    //1 = Declaracion
    //2 = Asignacion
    //3 = Declaracion-Asignacion
    //4 = Asignacion con operacion
    //5 = Declaracion-Asignacion con operacion
    //6 = Operacion
    //7 = print()
    //8 = getAddr()
    //9 = getValue()

    smatch groups;
    if(regex_match(instruccion, groups, rgx_DG))//Declaracion
    {
        getTokens(groups, tokens);
        eliminarEspacios(tokens);
        return 1;
    }
    else if(regex_match(instruccion, groups, rgx_DAG_v1))//Asignacion Declaracion
    {
        getTokens(groups, tokens);
        S_List<string> *declaration_tokens = new S_List<string>;
        S_List<string> *asignation_tokens = new S_List<string>;

        bool getEqual = false;
        for(int i=0; i < tokens->getSize(); i++)
        {
            string s = tokens->get(i);
            if(s == "=")
                getEqual = true;
            if(getEqual)
                asignation_tokens->add(s);
            else
                declaration_tokens->add(s);
        }
        for(int i=0; i < asignation_tokens->getSize(); i++)
            declaration_tokens->add(asignation_tokens->get(i));
        tokens = declaration_tokens;
        return 3;
    }
    else if(regex_match(instruccion, groups, rgx_AG_v3))//Asignacion simple
    {
        getTokens(groups, tokens);
        return 2;
    }
    else if(regex_search(instruccion, regex("\\=|\\+\\=|\\-\\=")))//Asignacion con operacion
    {
        string antes_de = "";
        string despues_de = "";
        S_List<string> * partes = parsear(instruccion, '=');
        antes_de = partes->getFirst()->data;
        despues_de = partes->getLast()->data;
        //cout << "antes_de: " << antes_de << endl;
        //cout << "despues_de: " << despues_de << endl;
        smatch grupos_antes_de, grupos_despues_de;

        S_List<string> * tokens_antes_de = new S_List<string>;
        S_List<string> * tokens_despues_de = new S_List<string>;

        bool es_declaracion = false;

        if(regex_match(antes_de, grupos_antes_de, regex(ptrn_weas_v)))
        {
            getTokens(grupos_antes_de, tokens_antes_de);
        }
        else
        {
            string wawa = antes_de + ";";
            //cout << "wawa: " << wawa << endl;
            if(regex_match(wawa, grupos_antes_de, rgx_DG))
            {
                getTokens(grupos_antes_de, tokens_antes_de);
                es_declaracion = true;
                //return 5;
            }
            else
            {
                return -1;
            }
        }
        if(regex_search(despues_de, grupos_despues_de, rgx_OA_v1))
        {
            //cout << "despues_de: " << despues_de << endl;
            getTokensOperacion(despues_de, tokens_despues_de);
            //cout << "tokens_despues_de->show2ln(): ";
            //tokens_despues_de->show2ln();
        }
        else
        {
            return -1;
        }

        tokens_antes_de->add("=");
        for(int i=0; i < tokens_despues_de->getSize(); i++)
        {
            tokens_antes_de->add(tokens_despues_de->get(i));
        }


        *tokens = *tokens_antes_de;
        //tokens->show2ln();
        //cout << "Asignacion no simple" << endl;
        if(es_declaracion)
        {
            return 5;
        }
        else
        {
            return 4;
        }

    }
    else if(regex_search(instruccion, groups, rgx_OA_v1) && getTokensOperacion(instruccion, tokens))
    {
        //cout << "Operacion" << endl;
        return 6;
    }
    else if(regex_search(instruccion, groups, rgx_print_v0))
    {
        getTokens(groups, tokens);
        return 7;
    }
    else if(regex_search(instruccion, groups, rgx_getAddr))
    {
        getTokens(groups, tokens);
        return 8;
    }
    else if(regex_search(instruccion, groups, rgx_getValue))
    {
        getTokens(groups, tokens);
        return 9;
    }
    else
    {
        return -1;
    }
}

void printStructs()
{
    for(int i=0; i < VG_structs->getSize(); i++)
    {
        S_List<string> tokens_struct = VG_structs->get(i);
        cout << "Struct: ";tokens_struct.show2ln();
    }
}

void printScoopes()
{
    for(int i=0; i < VG_scoopes->getSize(); i++)
        cout << "Scoope: " << VG_scoopes->get(i).getString() << endl;
}

S_List<string> * getScoopeVariables(Scoope scoope)
{
    S_List<string> * ids = new S_List<string>;

    string lines = scoope.lineas;

    string segmento;
    stringstream stringstream(lines);
    S_List<string> *lista_de_instrucciones = new S_List<string>;
    while(std::getline(stringstream, segmento, ';'))
    {
        string instruccion = segmento + ";";
        lista_de_instrucciones->add(instruccion);
    }

    for(int i=0; i < lista_de_instrucciones->getSize(); i++)
    {

        string instruccion = lista_de_instrucciones->get(i);
        S_List<string> * tokens = new S_List<string>;

        S_List<string> * tokens_antes_de_asgnacion = new S_List<string>;
        bool llego_al_igual = false;


        switch(readInstruction(instruccion, tokens))
        {
            case 1://Declaracion
                switch(tokens->getSize())
                {
                    case 2:
                        ids->add(tokens->get(1));
                        break;

                    case 3:
                        ids->add(tokens->get(2));
                        break;

                    default:
                        break;
                }
                break;

            case 3:
                switch(tokens->getSize())
                {
                    case 4:
                        ids->add(tokens->get(1));
                        break;
                    case 5:
                        ids->add(tokens->get(2));
                        break;
                    case 6:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(1) << tokens->get(2) << ", " << "\"Nombre\"" << " : " << tokens->get(3) << " }" << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;


            case 5:
                tokens_antes_de_asgnacion->delAll();
                llego_al_igual = false;
                for(int i=0; i < tokens->getSize(); i++)
                {
                    if(tokens->get(i) == "=")
                    {
                        llego_al_igual = true;
                    }
                    if(!llego_al_igual)
                    {
                        tokens_antes_de_asgnacion->add(tokens->get(i));
                    }
                }
                switch(tokens_antes_de_asgnacion->getSize())
                {
                    case 1:
                        cout << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;
                        break;
                    case 2:
                        ids->add(tokens->get(1));
                        break;
                    case 3:
                        cout << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            default:
                break;
        }
    }
    return ids;
}

bool readLines(string text)
{
    //Sacar lista de orden de declaraciones
    S_List<S_List<string>> * matriz_de_tokens = new S_List<S_List<string>>;

    int numero_de_linea = 0;


    string segmento;
    stringstream stringstream(text);
    S_List<string> *lista_de_instrucciones = new S_List<string>;
    while(std::getline(stringstream, segmento, ';'))
    {
        string instruccion = segmento + ";";
        lista_de_instrucciones->add(instruccion);
    }

    int scoope = 0;

    for(int i=0; i < lista_de_instrucciones->getSize(); i++)
    {

        string instruccion = lista_de_instrucciones->get(i);
        S_List<string> * tokens = new S_List<string>;

        for(char c : instruccion)
        {
            if(c == '}')
            {
                cout << "\033[0;33mCerrar Scoope: " + to_string(scoope) + "\033[0m" << endl;
                S_List<string> * variables_q_pueden_matarse = new S_List<string>;
                variables_q_pueden_matarse = getScoopeVariables(VG_scoopes->get(scoope));
                variables_q_pueden_matarse->show2ln();

                scoope++;
            }
            if(c == '\n')
            {
                numero_de_linea++;
            }
        }
        string _instruccion = instruccion;
        instruccion = regex_replace(instruccion, regex("\\{|\\}"), "");
        if(instruccion == ";" && _instruccion != instruccion)
        {
            cout << "_______________________________________________________________________________________________________________________________\n\n\n" << endl;
            break;
        }


        cout << "Instruccion -> [";
        cout << "\033[0;33m" + instruccion + "\033[0m";
        cout << "] : ";


        S_List<string> * tokens_antes_de_asgnacion = new S_List<string>;
        bool llego_al_igual = false;


        switch(readInstruction(instruccion, tokens))
        {

            case 1://Declaracion
                cout << "Declaracion" << endl;
                switch(tokens->getSize())
                {
                    case 2:
                        if(tokens->get(0) == "struct")
                        {
                            string nombre_del_struct = tokens->get(1);
                            bool existe_este_struct = false;
                            for(int i=0; i < VG_structs->getSize(); i++)
                            {
                                S_List<string> tokens_struct = VG_structs->get(i);
                                if(nombre_del_struct == tokens_struct.get(1))
                                {
                                    existe_este_struct = true;
                                }
                            }
                            if(existe_este_struct)
                            {
                                cout << ">>> Hacer lo q sea q deba hacer cuando hay un struct :v"<<endl;
                            }
                            else
                            {
                                cout << "\033[0;31mError: Struct " + nombre_del_struct + " indefinido :v\033[0m\n" << endl;
                            }

                        }
                        else
                        {
                            Object jsonSend;
                            jsonSend["id"] = String(tokens->get(1));
                            jsonSend["local"] = Boolean(false);
                            jsonSend["command"] = String("add");
                            //{"id" : "a", "value": true, "local": "false", "type" : "bool", "command" : "add"}
                            cout << ">>> Mandar JSON: {\"id\" : \"" << tokens->get(1)<< "\", " << "\"value\"" << " : \"" << 0 << "\", \"local\" : \"false\", \"type\" : \"" << tokens->get(0) << "\", \"command\" : \"add\"}"<<endl;
                            if(tokens->get(0) == "int" | tokens->get(0) == "float" |  tokens->get(0) == "long" | tokens->get(0) == "double"){
                                jsonSend["type"] = String(tokens->get(0));
                                jsonSend["value"] = Number(0);
                            }
                            if(tokens->get(0) == "char" | tokens->get(0) == "string"){
                                jsonSend["type"] = String(tokens->get(0));
                                jsonSend["value"] = String(" ");
                            }
                            Writer::Write(jsonSend, ss);
                            socketConnect(ss.str(), port);
                        }
                        break;

                    case 3:
                        cout << ">>> Mandar JSON: {\"id\" : \"" << tokens->get(2)<< "\", " << "\"value\"" << " : \"" << 0 << "\", \"local\" : \"false\", \"type\" : \"" << tokens->get(0) << tokens->get(1) << "\", \"command\" : \"add\"}"<<endl;
                        break;

                    default:
                        cout << "{Declaracion?}" << endl;
                        break;
                }
                break;

            case 2://Asignacion
                cout << "Asignacion" << endl;
                switch(tokens->getSize())
                {
                    case 3:
                        cout << ">>> Asignar el valor: " << tokens->get(2) << " a: " << tokens->get(0) << endl;
                        Object jsonSend;
                        jsonSend["id"] = String(tokens->get(0));
                        jsonSend["local"] = Boolean(false);
                        jsonSend["command"] = String("edit");
                        Object jsonSRCH;
                        jsonSRCH["command"] = String("srch");
                        jsonSRCH["id"] = String(tokens->get(0));
                        std::stringstream as;
                        Writer::Write(jsonSRCH, as);
                        std::string received = socketConnect(as.str(), port);
                        std::stringstream rs;
                        rs << received;
                        Object jReceived;
                        Reader::Read(jReceived, rs);
                        String typeAux = String(jReceived["type"]);
                        std::string type = typeAux.Value();
                        if(type == "int" | type == "long" | type == "double"){
                            jsonSend["type"] = String(type);
                            jsonSend["value"] = Number(atoi(tokens->get(2).c_str()));
                        }
                        if(type == "float"){
                            jsonSend["type"] = String(type);
                            std::cout << tokens->get(2);
                            float val = std::atof(tokens->get(2).c_str());
                            jsonSend["value"] = Number(val);
                        }
                        if(type == "char" | type == "string"){
                            jsonSend["type"] = String(type);
                            jsonSend["value"] = String(tokens->get(2));
                        }
                        Writer::Write(jsonSend, ss);
                        std::string aux = ss.str();
                        socketConnect(aux, port);
                        break;
                    case 4:
                        if(regex_search(tokens->get(0), regex("\\*|\\&|\\+")))//Si el group solo es \s lo omite
                        {
                            cout << ">>> Asignar el valor: " << tokens->get(3)  << " a: " << tokens->get(0) << tokens->get(1) << endl;
                        }
                        else
                        {
                            cout << ">>> Asignar el valor: " << tokens->get(2) << tokens->get(3) << " a: " << tokens->get(0) << endl;
                        }

                        break;
                    case 5:
                        cout << ">>> Asignar el valor: " << tokens->get(3) << tokens->get(4)  << " a: " << tokens->get(0) << tokens->get(1) << endl;

                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            case 3:
                cout << "Declaracion-Asignacion" << endl;
                switch(tokens->getSize())
                {
                    case 4:
                        cout << ">>> Mandar JSON: { " << "\"Tipo\"" << " : " << tokens->get(0) << ", " << "\"Nombre\"" << " : " << tokens->get(1) << " }" << endl;
                        Object jsonSend;
                        jsonSend["id"] = String(tokens->get(1));
                        jsonSend["local"] = Boolean(false);
                        jsonSend["command"] = String("add");
                        //{"id" : "a", "value": true, "local": "false", "type" : "bool", "command" : "add"}
                        if(tokens->get(0) == "int" | tokens->get(0) == "long" | tokens->get(0) == "double"){
                            jsonSend["type"] = String(tokens->get(0));
                            jsonSend["value"] = Number(atoi(tokens->get(3).c_str()));
                        }
                        if(tokens->get(0) == "float"){
                            jsonSend["type"] = String(tokens->get(0));
                            std::cout << tokens->get(3);
                            float val = std::atof(tokens->get(3).c_str());
                            jsonSend["value"] = Number(val);
                        }
                        if(tokens->get(0) == "char" | tokens->get(0) == "string"){
                            jsonSend["type"] = String(tokens->get(0));
                            jsonSend["value"] = String(tokens->get(3));
                        }
                        Writer::Write(jsonSend, ss);
                        std::string auxsend = ss.str();
                        socketConnect(ss.str(), port);
                        break;
                    case 5:
                        cout << ">>> Mandar JSON: { " << "\"Tipo\"" << " : " << tokens->get(0) << tokens->get(1) << ", " << "\"Nombre\"" << " : " << tokens->get(2) << " }" << endl;
                        cout << ">>> Asignar el valor: " << tokens->get(4) << " a: " << tokens->get(2) << endl;
                        break;
                    case 6:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(1) << tokens->get(2) << ", " << "\"Nombre\"" << " : " << tokens->get(3) << " }" << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            case 4:
                cout << "Asignacion con Operacion" << endl;
                switch(tokens->getSize())
                {
                    case 2:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << ", " << "\"Nombre\"" << " : " << tokens->get(1) << " }" << endl;
                        break;
                    case 3:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << tokens->get(1) << ", " << "\"Nombre\"" << " : " << tokens->get(2) << " }" << endl;
                        break;
                    case 4:
                        cout << ">>>Resolver: " << endl;
                        cout << ">>> Asignar el valor resuelto: " << " a: " << tokens->get(0) << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            case 5:
                cout << "Declaracion-Asignacion con Operacion" << endl;
                tokens_antes_de_asgnacion->delAll();
                llego_al_igual = false;
                for(int i=0; i < tokens->getSize(); i++)
                {
                    if(tokens->get(i) == "=")
                    {
                        llego_al_igual = true;
                    }
                    if(!llego_al_igual)
                    {
                        tokens_antes_de_asgnacion->add(tokens->get(i));
                    }
                }
                switch(tokens_antes_de_asgnacion->getSize())
                {
                    case 2:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << ", " << "\"Nombre\"" << " : " << tokens->get(1) << " }" << endl;
                        break;
                    case 3:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << tokens->get(1) << ", " << "\"Nombre\"" << " : " << tokens->get(2) << " }" << endl;
                        break;
                    case 4:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(1) << tokens->get(2) << ", " << "\"Nombre\"" << " : " << tokens->get(3) << " }" << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            case 6:
                cout << "Operacion" << endl;
                switch(tokens->getSize())
                {
                    case 2:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << ", " << "\"Nombre\"" << " : " << tokens->get(1) << " }" << endl;
                        break;
                    case 3:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(0) << tokens->get(1) << ", " << "\"Nombre\"" << " : " << tokens->get(2) << " }" << endl;
                        break;
                    case 4:
                        //cout << "{ " << "\"Tipo\"" << " : " << tokens->get(1) << tokens->get(2) << ", " << "\"Nombre\"" << " : " << tokens->get(3) << " }" << endl;
                        break;
                    default:
                        //cout << "{Default}" << endl;
                        break;
                }
                break;

            case 7:
                cout << "stdout" << endl;
                switch(tokens->getSize())
                {
                    case 3:
                        if(regex_search(tokens->get(2), regex("\"")))
                        {
                            string s = regex_replace(tokens->get(2), regex("\""), "");
                            cout << "\033[0;35m" + s + "\033[0m\n" << endl;
                        }
                        else
                        {
                            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            cout << "\033[0;35mValor de: " + tokens->get(2) + "\033[0m\n" << endl;
                        }

                        break;
                    default:
                        break;
                }
                break;

            case 8:
                cout << "getAddr()" << endl;
                switch(tokens->getSize())
                {
                    case 3:
                        cout << "\033[0;36m>>>retornar reference<type> de : " + tokens->get(2) + "\033[0m\n" << endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        break;

                    default:
                        break;
                }
                break;

            case 9:
                cout << "getValue()" << endl;
                switch(tokens->getSize())
                {
                    case 3:
                        cout << "\033[0;36m>>>retornar el valor al que hace referencia: " + tokens->get(2) + "\033[0m\n" << endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        break;

                    default:
                        break;
                }
                break;

            default:
                cout << "\033[0;31mC mamo :v (Oasease, Error de Syntaxis)\033[0m\n" << endl;
                return false;
        }
        matriz_de_tokens->add(*tokens);
        tokens->show2ln();
        cout << "tokens->getSize(): " << tokens->getSize() << endl;
        cout << "_______________________________________________________________________________________________________________________________\n\n\n" << endl;
    }
    cout << "\033[0;33mCerrar Scoope: " + to_string(scoope) + "\033[0m" << endl;
    S_List<string> * variables_q_pueden_matarse = new S_List<string>;
    variables_q_pueden_matarse = getScoopeVariables(VG_scoopes->get(scoope));
    variables_q_pueden_matarse->show2ln();
    cout << "_______________________________________________________________________________________________________________________________\n\n\n" << endl;
    return true;
}

void extraerString(string s, string * array, regex r)
{
    smatch g;
    if(regex_search(s, g, r))
    {
        array[0] = s.substr(0, g.position(1)) + s.substr(g.position(g.size()-1)+1, s.size());
        array[1] = g[0];
    }


}

string sin_espacios_innecesarios(string str)
{
    return regex_replace(str, rgx_arreglar_espaciado, " ");
}


void procesar_structs(string * code)
{
    //por si acaso
    VG_structs->delAll();


    *code = sin_espacios_innecesarios(*code);
    smatch grupishos;


    while(regex_search(*code, grupishos, rgx_struct_v0))
    {
        //cout <<  "code:" << *code << endl;
        //cout << "_____________________________________________________________________________________________" << endl;


        S_List<string> *tokens_struct = new S_List<string>;
        tokens_struct->add(grupishos[1]);//struct
        tokens_struct->add(grupishos[2]);//Nombre
        tokens_struct->add(grupishos[3]);//{
        tokens_struct->add(sin_espacios_innecesarios(grupishos[4]));//Lineas
        tokens_struct->add(grupishos[5]);//}
        tokens_struct->add(grupishos[6]);//variables y ;


        *code = (*code).substr(0, grupishos.position(0)) + ((string)grupishos[1] + " " + (string)grupishos[2] + ";") + (*code).substr(grupishos.position(0) + grupishos[0].length(), (*code).size());
        //*code = regex_replace(*code, rgx_struct_v0, ((string)grupishos[1] + " " + (string)grupishos[2] + ";"));
        VG_structs->add(*tokens_struct);
    }
}





bool procesar_Scoopes(string code)
{
    //por si acaso
    VG_scoopes->delAll();

    int cantidad_llaves_abiertas = 0;
    int cantidad_llaves_cerradas = 0;

    for(char c : code)
    {
        if(c == '{')
            cantidad_llaves_abiertas++;
        if(c == '}')
            cantidad_llaves_cerradas++;
    }
    if(cantidad_llaves_abiertas != cantidad_llaves_cerradas)
        return false;

    smatch grupishos;
    regex rgx_llaves_v0("(\\{)\\s*[^\\{\\}]*\\s*(\\})");
    regex rgx_llaves_v1("(\\{)\\s*([^\\{\\}]*)\\s*(\\})");
    regex rgx_arreglar_espaciado_scoope_v0 = regex("(\\{)(\\s*)([\\n\\s\\t]*|.*)(\\;)(\\s*)(\\})");

    while(regex_search(code, grupishos, rgx_llaves_v1))
    {
        int profundidad = 0;
        string code_hasta_scoope = code.substr(0, grupishos.position(2));

        for(char c : code_hasta_scoope)
            if(c == '{')
                profundidad++;

        string partes[2];
        extraerString(code, partes, rgx_llaves_v0);

        smatch grupos_scoope;
        if(regex_search(partes[1], grupos_scoope, rgx_arreglar_espaciado_scoope_v0))
        {
            partes[1] = regex_replace(partes[1], rgx_arreglar_espaciado_llaves, "");
        }
        VG_scoopes->add(*new Scoope(profundidad, partes[1]));
        code = partes[0];
    }
    if(code != "")
        VG_scoopes->add(*new Scoope(0, code));
    return true;
}



void readCode(string code)
{
    string _code = code;

    procesar_structs(&_code);
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\033[0;32m.:Structs:.\033[0m\n" << endl;
    printStructs();
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;


    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\033[0;32m::_code::\033[0m\n" << endl;;
    cout << "(Para revision de Scoopes)\n" << _code << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;


    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    if(procesar_Scoopes(_code))
    {
        cout << "\033[0;32m.:Scoopes:.\033[0m\n" << endl;
        printScoopes();
    }
    else
    {
        cout << "\033[0;31mError: Scoope sin cerrar :v\033[0m\n" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\033[0;31m.:Not C1:.\033[0m" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;
        return;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;


    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\033[0;32m::_code::\033[0m\n" << endl;
    _code = sin_espacios_innecesarios(_code);
    _code = regex_replace(_code, regex("\\;\\s*"), ";");
    cout << "(Para revision de Syntaxis)\n" << _code << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;



    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\033[0;32m.:Lectura de lineas:.\033[0m\n" << endl;

    if(readLines(_code))
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\033[0;34m.:C!:.\033[0m" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;
    }
    else
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\033[0;31m.:Not C1:.\033[0m" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n" << endl;



}


int main()
{
    string text =
            "int a;"
            "reference<int> aa;"
            "reference<int> aaa = 100;"
            "a = 2*a;"
            "{"
            "   {"
            "       int b = 1;"
            "       {"
            "           int c;"
            "           int d;"
            "           ++"
                    ""
                    ""
                    ""
                    ""
                    "\nc;"
            "           {"
            "               int e;"
            "           }"
            "           int f;"
            "       }"
                    "\n"
            "       int"
                    " g;"
            "       {"
            "           {"
            "               {"
            "                   int h ; "
            "                   {"
            "                       int i "
                    " "
                    " "
                    " "
                    " ;     "
            "                       int ii ;    "
            "                       {"
            "                           {"
            "                               int iii;"
            "                               struct "
                    "Book"
            "                               {"
            "                                   int waca;"
            "                               }book1,"
                    "book2; "
            "                           }"
            "                       }"
            "                   }"
            "                   int j "
                    "; "
                    "Hable("
                    " j"
                    " "
                    ");"
            "               } "
                    "getAddr(a);"
            "               int "
                    "k;"
            "               struct "
                    "Pokemon"
            "               {"
            "                   int "
                    "maia;"
            "               }r1;getValue( k ) ; getValue( aa"
                    ");"
            "           }"
            "           int l;"
            "           Hable(\"LALALALALLALALALALALA\");"
            "       }"
            "       reference<char> m;"
            "   }"
            "   int n;"
            "}"
            "int o;"
            "{"
            "   int x;"
            "   int y = a + 3 * 2 / 1;"
            "   int z;"
            "   z = a + 1 + 1 + 1 + 1;"
            "   Hable(\"Holiwis\") ; "
            "}"
            ;

    string text2  =
            "int c = a + b   ;  c =  a + b ;      ";


    string text3  =
            "int a = 500;\n"
            "char c =  'x';\n"
            "struct A\n"
            "{\n"
            "\tint x1;\n"
            "\tint y1;\n"
            "}claseA;\n"
    ;


    readCode(text3);



    //string i = "123456789098765432";


    /*
    string str = "2.5";
    smatch sm;regex_match(str, sm, regex("\\s*(\\d+)\\.(\\d+)"));
    float f
        cout << "C: " << (float)(atoi(((string)sm[1]).c_str()) + ((float)atoi(((string)sm[2]).c_str())/10) ) << endl;

    */





}
