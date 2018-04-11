#include <iostream>
#include "includes/S_List.h"
#include "includes/Scoope.h"
#include <regex>
#include<string>


using namespace std;
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




string const ptrn_declaracionGeneral_v0 =               "\\s*(int|long|char|float|double|struct)(\\s*\\*+\\s*|\\*+\\s*|\\s*\\*+|\\s+)((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\']*)\\s*\\;";
regex const rgx_DG(ptrn_declaracionGeneral_v0);


string const ptrn_asignacionGeneral_v1 =                "\\s*((?!.*?[\\&]{2})[^\\s0-9A-z]*)\\s*((?!(int|long|char|float|doble)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=|\\+=|\\-=)\\s*(?:(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\'\\;]*))|\\.)\\s*\\;";
regex const rgx_AG_v1(ptrn_asignacionGeneral_v1);


//Cuando supuestamente hay una operacion
string const ptrn_asignacionGeneral_v2 =                "^\\s*((?!.*?[\\&]{2})[^\\s0-9A-z]*)\\s*((?!(int|long|char|float|doble|struct)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=|\\+=|\\-=)\\s*(?:(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&\\'\\;]*))|\\.)\\s*\\;";
regex const rgx_AG_v2(ptrn_asignacionGeneral_v2);


string const ptrn_declaracion_AsignacionGeneral_v2 =    "\\s*(int|long|char|float|double)(?:\\s*(\\*+)\\s*|(\\*+)\\s*|\\s*(\\*+)|(\\s+))((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[^\\s\\*\\.\\-\\/\\+\\&]*)\\s*(=)\\s*(?:(\\d+)|(\\'.\\')|(\\\".[^\\\"]*\\\")|(\\\"\\\")|(\\d+\\.\\d+)|((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*\\;";
regex const rgx_DAG_v1(ptrn_declaracion_AsignacionGeneral_v2);


string const ptrn_operacionAritmetica_v4 =             "\\s*(?:(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*([\\+]{2}|[\\-]{2})|([A-z]+|\\d+))\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*([\\+]{2}|[\\-]{2})|([A-z]+|\\d+))|((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*([A-z]+)|([A-z]+)\\s*((?:[\\+]{2}|[\\-]{2})))\\s*\\;";
regex const rgx_OA_v0(ptrn_operacionAritmetica_v4);


string const ptrn_operacionAritmetica_v5 =             "\\s*(?:([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+|\\d+\\.\\d+)|)\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)(\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+))|((?:[\\+]{2}\\s*|[\\-]{2}\\s*)+)\\s*(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*((?:[\\+]{2}|[\\-]{2})))\\s*";
regex const rgx_OA_v1(ptrn_operacionAritmetica_v5);


string const ptrn_operacionAritmetica_v6 =             "\\s*(?:([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+|\\d+\\.\\d+)|)\\s*([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))\\s*(?:\\s((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)(\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))|((?!.*?[\\&]{2})[\\*\\&]+)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)\\s*([\\+]{2}|[\\-]{2})|((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)\\s*([\\+]{2}|[\\-]{2})|\\'[^\\']+\\'|\\d+)|((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z][A-z\\d\\_]*)|((?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)?\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z][A-z\\d\\_]*)\\s*((?:[\\+]{2}|[\\-]{2})))\\s*";
regex const rgx_OA_v2(ptrn_operacionAritmetica_v6);


string const ptrn_operador_variable_v0 =             "\\s*(?:([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))([\\+\\-])?\\s*(?:((?:[\\+]{2}\\s*|[\\-]{2}\\s*|(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]+)*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})|(((?!.*?[\\&]{2})[\\*\\&]*)\\s*((?!(int|long|char|float|double)[\\;|\\s])[A-z]+[A-z\\d\\_]*)|\\d+)))";
regex const rgx_OV_v0(ptrn_operador_variable_v0);

//Globales
S_List<Scoope> * VG_scoopes = new S_List<Scoope>;



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
    {
        if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
        {
            //i = regex_replace(i, regex("\\s"), "");//Borra los espacios innecesarios
            if(i != groups[0])
            {
                tokens->add(i);
            }
        }
    }
    /*
    if(regex_search(tokens->getLast()->data, regex(regex("[\\&\\*]"))))//Esto arregla los grupos si el ultimo es un puntero
    {
        string ultimo = tokens->getLast()->data;
        string penultimo = tokens->get(tokens->getSize()-2);
        tokens->edit(ultimo, tokens->getSize()-2);
        tokens->edit(regex_replace(penultimo, regex("[\\&\\*]"), ""), tokens->getSize()-1);
    }
    */
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
        {
            tokens->del(i);
        }
    }
}
bool getTokensOperacion(string str, S_List<string> *tokens)
{
    smatch groups;
    int cantidad_a_cortar = 0;
    if(regex_search(str, groups, rgx_OA_v2))
    {
        //cout << "str: [" << str << "]" << endl;
        for(int x=0; x < groups.size(); x++)
        {
            string i = groups[x];
            if(x==0)
            {
                cantidad_a_cortar += i.length();
            }
            //cout << "   i: [" << i << "]" << endl;
            if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
            {
                //i = regex_replace(i, regex("\\s"), "");//Borra los espacios innecesarios
                if(x!=0)
                    tokens->add(i);
            }
        }
        //tokens->add(":v");
        //cout << "cantidad a cortar: " << cantidad_a_cortar << endl;
        str = str.substr(cantidad_a_cortar, str.size());
    }
    while(str != ";" && str != "")
    {
        cantidad_a_cortar = 0;
        if(regex_search(str, groups, rgx_OV_v0) || regex_search(str, groups, regex("\\s*(?:([\\+\\-\\*\\/]|(?:[\\+\\-]\\s+(?![\\+\\-]{2}))*(?:[\\+\\-](?![\\+\\-]{2}))|\\-\\+|\\+\\-|\\/\\+|\\/\\-|\\*\\+|\\*\\-|\\%|(?:\\+\\-\\s*)*(?:\\+\\-))([\\+\\-])?\\s*(?:(?:(?:(?![\\*\\&\\s]*?[\\&]{2})[\\*\\&\\s]*)\\s*((?!(int|long|char|float|double|struct)[\\;|\\s])[A-z]+[A-z\\d\\_]*))\\s*([\\+]{2}|[\\-]{2})\\s*|(\\d+)))\\s*")))
        {
            //cout << "str: [" << str << "]" << endl;
            for(int x=0; x < groups.size(); x++)
            {
                string i = groups[x];
                if(x==0)
                {
                    cantidad_a_cortar += i.length();
                }
                //cout << "   i: [" << i << "]" << endl;
                if(!regex_match(i, regex("\\s*")))//Si el group solo es \s lo omite
                {
                    //i = regex_replace(i, regex("\\s"), "");//Borra los espacios innecesarios
                    if(x!=0)
                        tokens->add(i);
                }
            }
            //tokens->add(":v");
            //cout << "cantidad a cortar: " << cantidad_a_cortar << endl;
            str = str.substr(cantidad_a_cortar, str.size());
        }
        else
        {
            int veces = tokens->getSize();for(int a=0; a < veces; a++)tokens->delFirst();
            return false;
        }

    }
    eliminarEspacios(tokens);
    return true;
    //tokens->show2ln();
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

    smatch groups;
    //S_List<string> *tokens = new S_List<string>;
    if(regex_match(instruccion, groups, rgx_DG))//Declaracion
    {
        getTokens(groups, tokens);
        eliminarEspacios(tokens);
        //cout << "Declaracion" << endl;
        return 1;
    }
    else if(regex_match(instruccion, groups, rgx_DAG_v1))//Asignacion Declaracion
    {
        getTokens(groups, tokens);
        //cout << "Declaracion-Asignacion" << endl;

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
        //cout << "Declaration Tokens: " << endl;
        //declaration_tokens->show2ln();
        //cout << "Asignation Tokens: " << endl;
        //asignation_tokens->show2ln();

        for(int i=0; i < asignation_tokens->getSize(); i++)
            declaration_tokens->add(asignation_tokens->get(i));
        tokens = declaration_tokens;
        return 3;
    }
    else if(regex_match(instruccion, groups, rgx_AG_v1))//Asignacion simple
    {
        getTokens(groups, tokens);
        //cout << "Asignacion" << endl;
        return 2;
//        if(regex_search(instruccion, groups, rgx_OA_v1))
//        {
//            cout << "con Operacion" << endl;
//        }
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

        if(regex_match(antes_de, grupos_antes_de, regex(ptrn_weas_v)))
        {
            getTokens(grupos_antes_de, tokens_antes_de);
            //cout << "tokens_antes_de->show2ln(): ";
            //tokens_antes_de->show2ln();
        }
        else
        {
            string wawa = antes_de + ";";
            if(regex_match(wawa, grupos_antes_de, rgx_DG))
            {
                getTokens(grupos_antes_de, tokens_antes_de);
                return 5;
                //cout << "tokens_antes_de->show2ln(): ";
                //tokens_antes_de->show2ln();
            }
            else
            {
                return -1;
            }
        }
        if(regex_search(despues_de, grupos_despues_de, rgx_OA_v1))
        {
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
        return 4;
    }
    else if(regex_search(instruccion, groups, rgx_OA_v1) && getTokensOperacion(instruccion, tokens))
    {
        //cout << "Operacion" << endl;
        return 6;
    }
    else
    {
        return -1;
    }
    cout << "Tokens: " << endl;
    tokens->show2ln();
    cout << "tokens->getSize(): " << tokens->getSize() << endl;
    return true;
}

void printScoopes()
{
    for(int i=0; i < VG_scoopes->getSize(); i++)
    {
        cout << "Scoope: " << VG_scoopes->get(i).getString() << endl;
    }
}

void readCode(string text)
{
    //Sacar lista de orden de declaraciones




















    S_List<S_List<string>> * matriz_de_tokens = new S_List<S_List<string>>;

    int numero_de_linea = 0;


    string segmento;
    stringstream stringstream(text);
    S_List<string> *list_de_instrucciones = new S_List<string>;
    while(std::getline(stringstream, segmento, ';'))
    {
        string instruccion = segmento + ";";
        list_de_instrucciones->add(instruccion);
        cout << instruccion << endl;
    }
    //list_de_instrucciones->show2ln();
    //cout<< "_________________________________\n" <<endl;
    for(int i=0; i < list_de_instrucciones->getSize(); i++)
    {

        string instruccion = list_de_instrucciones->get(i);
        S_List<string> * tokens = new S_List<string>;

        cout << "Instruccion: ";
        switch(readInstruction(instruccion, tokens))
        {

            case 1://Declaracion
                cout << "Declaracion" << endl;
                switch(tokens->getSize())
                {
                    case 2:
                        cout <<">>> Mandar JSON: {\"Tipo\" : "<<tokens->get(0)<<" , "<<"\"Nombre\""<<" : "<<tokens->get(1)<<" }"<<endl;
                        break;

                    case 3:
                        cout << ">>> Mandar JSON: { " << "\"Tipo\"" << " : " << tokens->get(0) << tokens->get(1) << ", " << "\"Nombre\"" << " : " << tokens->get(2) << " }" << endl;
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

            default:
                cout << "C mamo :v (Oasease, Error de Syntaxis)" << endl;
                break;
        }
        tokens->show2ln();
        matriz_de_tokens->add(*tokens);
        cout << "tokens->getSize(): " << tokens->getSize() << endl;
        cout << "_____________________________________________________________________________________________\n\n" << endl;

        for(int i=0; i < matriz_de_tokens->getSize(); i++)
        {
            matriz_de_tokens->get(i).show2ln();
        }

    }
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

int main()
{
    cout << "_____________________________________________________________________________________________" << endl;
    string text = //"int a; {int b;{int bb;}} int c;";
            "int a;"
            "{"
            "   {"
            "       int b;"
            "       {"
            "           int c;"
            "           int d;"
            "           {"
            "               int e;"
            "           }"
            "           int f;"
            "       }"
            "       int g;"
            "       {"
            "           {"
            "               {"
            "                   int h;"
            "                   {"
            "                       int i;"
            "                       int ii;"
            "                       {"
            "                           {"
            "                               int iii;"
            "                           }"
            "                       }"
            "                   }"
            "                   int j;"
            "               }"
            "               int k;"
            "           }"
            "           int l;"
            "       }"
            "       int m;"
            "   }"
            "   int n;"
            "}"
            "int o;"
            "{"
            "   int x;"
            "   int y;"
            "   int z;"
            "}"
            ;


    string text2 =
            "a\n"
                    "{\n"
                    "\t{\n"
                    "\t\tb\n"
                    "\t\t{\n"
                    "\t\t\tc\n"
                    "\t\t\td\n"
                    "\t\t\t{\n"
                    "\t\t\t\tstruct Books\n"
                    "\t\t\t\t{\n"
                    "\t\t\t\t\tint a;\n"
                    "\t\t\t\t}a,b,c;\n"
                    "\t\t\t\te\n"
                    "\t\t\t}\n"
                    "\t\t\tf\n"
                    "\t\t}\n"
                    "\t\tg\n"
                    "\t\t{\n"
                    "\t\t\t{\n"
                    "\t\t\t\t{\n"
                    "\t\t\t\t\th\n"
                    "\t\t\t\t\t{\n"
                    "\t\t\t\t\t\ti\n"
                    "                        struct SHETS\n"
                    "                        {\n"
                    "                            int shet;\n"
                    "                        }sh;\n"
                    "\n"
                    "\t\t\t\t\t}\n"
                    "\t\t\t\t\tj\n"
                    "\t\t\t\t}\n"
                    "\t\t\t\tk\n"
                    "\t\t\t}\n"
                    "\t\t\tl\n"
                    "\t\t}\n"
                    "\t\tm\n"
                    "\t}\n"
                    "\tn\n"
                    "}\n"
                    "o";

    string text3 = "int i =0;struct Books{int a;}book;float r;";
                           //9                   29
    //readCode(text);



    string _text = text;
    //string const ptrn_shaves = "(\\{)\\s*((?![\\{\\}])\\s*(?:[^\\{\\}]|\\s)+)\\s*(\\})";
    smatch grupishos;
    regex rgx("(\\{)\\s*[^\\{\\}]*\\s*(\\})");


    cout << "Text: " << text << endl;
    cout << "_____________________________________________________________________________________________" << endl;

    while(regex_search(_text, grupishos, rgx))
    {
        _text = regex_replace(_text, regex("\\n|\\t|\\r"), "");
        cout <<  "text:" << _text << endl;
        cout << "_____________________________________________________________________________________________" << endl;
        cout <<  "grupo:" << grupishos[0] << endl;

        int profundidad = 0;
        string segmento;
        stringstream stringstream(_text.substr(0, grupishos.position(0)));
        //S_List<string> *list_de_instrucciones = new S_List<string>;
        while(std::getline(stringstream, segmento, '{'))
        {
            profundidad++;
        }




        string partes[2];
        extraerString(_text, partes, rgx);
        cout << "partes[0]: " << partes[0] << endl;
        cout << "partes[1]: " << partes[1] << endl;




        VG_scoopes->add(*new Scoope(profundidad, partes[1]));
        _text = partes[0];
    }
    if(_text != "")
    {
        VG_scoopes->add(*new Scoope(0, _text));
    }



    cout << "_____________________________________________________________________________________________" << endl;
    printScoopes();
    /*
    //string const ptrn = "(?:(struct)\\s*([A-z][A-z\\d\\_]*)\\s*(\\{)\\s*((?![\\{\\}])\\s*(?:[^\\{\\}]|\\s)+)\\s*(\\})\\s*((?:[A-z][A-z\\d\\_]*\\s*\\,?\\s*)+\\s*\\;))";
    smatch grupishos2;
    if(regex_search(text3, grupishos2, rgx_struct_v0))
    {
        //string partes[2];
        //array[0] = s.substr(0, g.position(1)) + s.substr(g.position(g.size()-1)+1, s.size());
        //array[1] = g[0];
        //cout << partes[0] << endl;
        //cout << partes[1] << endl;
        cout << "text3: [" << text3 << "]" << endl;
        for(string i : grupishos2)
        {
            cout << "i: [" << i << "]" << endl;
        }

        int index_i = grupishos2.position(0);
        int index_f = index_i + grupishos2[0].length();

        cout << "struct\ni->[" << index_i << "]\nf->[" << index_f << "]" << endl;
        string _text3 = text3.substr(0, index_i) + text3.substr(index_f, text3.length()-1);
        cout << "texto sin ESE struct: [" << _text3 << "]" << endl;
        cout << "solo ESE struct: [" << text3.substr(index_i, index_f) << "]" << endl;
    }
    else
    {
        cout << "C Marmota" << endl;
    }
    cout << "_____________________________________________________________________________________________" << endl;

    cout << "Codigo: " << text << endl;
    readCode(text);
    cout << "_____________________________________________________________________________________________" << endl;


    */






























    //readInstruction(instruccion);
    //cout << "____________________________________" << endl;

    /*
    string instruccion = "int i=a;";
    cout << "Instruccion: " << instruccion << endl;

    /*
    //cout << "ptrn_declaracionGeneral_v0: " << ptrn_declaracionGeneral_v0 << endl;


    string ptrn_D_int_v0 = "\\s*int\\s+[A-z]+[^\\s]*\\s*\\;";
    //cout << "ptrn_declaracionInt_v0: " << ptrn_D_int_v0 << endl;

    string ptrn_D_long_v0 = "\\s*long\\s+[A-z]+[^\\s]*\\s*\\;";
    //cout << "ptrn_declaracionInt_v0: " << ptrn_D_long_v0 << endl;

    string ptrn_D_char_v0 = "\\s*char\\s+[A-z]+[^\\s]*\\s*\\;";
    //cout << "ptrn_declaracionInt_v0: " << ptrn_D_char_v0 << endl;

    string ptrn_D_float_v0 = "\\s*float\\s+[A-z]+[^\\s]*\\s*\\;";
    //cout << "ptrn_declaracionInt_v0: " << ptrn_D_float_v0 << endl;

    string ptrn_D_double_v0 = "\\s*double\\s+[A-z]+[^\\s]*\\s*\\;";
    //cout << "ptrn_declaracionInt_v0: " << ptrn_D_double_v0 << endl;


    regex regex1(ptrn_D_int_v0);
    regex regex2(ptrn_D_long_v0);
    regex regex3(ptrn_D_char_v0);
    regex regex4(ptrn_D_float_v0);
    regex regex5(ptrn_D_double_v0);


    bool match_D = regex_match(string1, regex_DG);
    bool match_D_int = regex_match(string1, regex1);
    bool match_D_long = regex_match(string1, regex2);
    bool match_D_char = regex_match(string1, regex3);
    bool match_D_float = regex_match(string1, regex4);
    bool match_D_double = regex_match(string1, regex5);


    cout << "Declaracion? : " <<        (match_D? "True" : "Nope") << endl;
    cout << "Declaracion int? : " <<    (match_D_int? "True" : "Nope") << endl;
    cout << "Declaracion long? : " <<   (match_D_long? "True" : "Nope") << endl;
    cout << "Declaracion char? : " <<   (match_D_char? "True" : "Nope") << endl;
    cout << "Declaracion float? : " <<  (match_D_float? "True" : "Nope") << endl;
    cout << "Declaracion double? : " << (match_D_double? "True" : "Nope") << endl;
    */
    /*
    cout<<"is D-A: "<<          regex_match(instruccion, regex_DAG) << endl;
    cout<<"is Asignation: "<<   regex_match(instruccion, regex_AG)  << endl;
    cout<<"is Declaration: "<<  regex_match(instruccion, regex_DG)  << endl;
    cout<<"getTypeDataDeclaration: "<< getTypeDataDeclaration(instruccion) <<endl;








    cout << "\n\n\n\n\n\n" << endl;

    std::stringstream test
            (
                "int a = 500;"
                "char c = 'x';"
                "a = 40;"
                "double ****** sss;"
            );



    std::regex spli_by_rgx("()");
    std::sregex_token_iterator iter(instruccion.begin(), instruccion.end(), spli_by_rgx, -1);
    std::sregex_token_iterator end;
    for ( ; iter != end; ++iter)
        std::cout << *iter << '\n';




/*
    std::string s{R"(
tХB:Username!Username@Username.tcc.domain.com Connected
tХB:Username!Username@Username.tcc.domain.com WEBMSG #Username :this is a message
tХB:Username!Username@Username.tcc.domain.com Status: visible
)"};

    regex rgx("WEBMSG #([a-zA-Z0-9]+) :(.*)");
    smatch matches;

    if(std::regex_search(s, matches, rgx))
    {
        std::cout << "Match found\n";

        for (size_t i = 0; i < matches.size(); ++i)
        {
            std::cout << i << ": '" << matches[i].str() << "'\n";
        }
    } else {
        std::cout << "Match not found\n";
    }

    return 0;
*/
    /*
    for(auto i : sm)
    {
        cout << i << endl;
    }
    cout << "____________________________________" << endl;
    */
}
