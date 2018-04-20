//
// Created by fmurillom on 30/03/18.
//

#include <fstream>
#include <cstring>
#include "../includes/memBlock.h"
#include "../includes/cajun/json/reader.h"
#include "../includes/cajun/json/writer.h"
#include "../includes/S_List.h"

using namespace json;
/*!
 * Metodo constructor encargado de reservar el bloque de memoeria a utilizar por el servidor de memoria y separar este bloque en datos y os.
 * @param size tamaño crear el blouque.
 */
memBlock::memBlock(std::size_t size){
    os = (char *) malloc(size);
    first = (block *) os + 600;
    current = (char *) first;
    free = size;
    last = (block *) os + size;
    memBlock::size = size;
}

bool memBlock::searchMem(std::string id) {
    block *aux = first;
    while(aux != NULL){
        if(aux->id == id && aux->used){
            return true;
        }else{
            aux = aux->next;
        }
    }
    return false;
}


/*!
 * Agrega datos n memoria
 * @param jsonStr informacion de datos a agregar.
 */
void memBlock::addToMem(std::string jsonStr){
    std::stringstream jsonSS;
    jsonSS << jsonStr;
    Object jSonIn;
    Reader::Read(jSonIn, jsonSS);

    String typetemp = jSonIn["type"];
    String idtemp = jSonIn["id"];

    if(searchMem(idtemp.Value())){
        return;
    }
    Boolean localTemp = jSonIn["local"];

    block *aux = first;

    block *temp = new (os) block;
    if(typetemp.Value() != "reference"){
        temp->data = new (current + sizeof(*temp)) char;
    }

    if(typetemp.Value() == "str" | typetemp.Value() == "char"){
        String dataTemp = jSonIn["value"];
        strcpy(temp->data, dataTemp.Value().c_str());
    }
    if(typetemp.Value() == "int" | typetemp.Value() == "double"){
        Number dataTemp = jSonIn["value"];
        std::string numtemp = std::to_string(dataTemp.Value());
        strcpy(temp->data, numtemp.c_str());
    }
    if(typetemp.Value() == "float"){
        std::stringstream fs;
        Number datatemp = jSonIn["value"];
        fs << datatemp.Value();
        std::string dataTemp = fs.str();
        strcpy(temp->data, dataTemp.c_str());
    }
    if(typetemp.Value() == "bool"){
        Boolean dataTemp = jSonIn["value"];
        *temp->data = (char) dataTemp.Value();
    }

    if(typetemp.Value() == "reference"){
        String datatemp = jSonIn["value"];
        if(datatemp.Value() == "NULL"){
            temp->data = NULL;
        }else{
            block *aux = first;
            while(aux != NULL){
                if(aux->id == datatemp.Value() && aux->used){
                    break;
                }else{
                    aux = aux->next;
                }
            }
            temp->data = aux->data;
        }
    }

    if((sizeof(*temp) + sizeof(*temp->data) < free)){
        while(aux != NULL) {
            if ((!aux->used) && (aux->next == NULL | (((const char *) aux->next - (const char *) aux) >= sizeof(*temp->data)))) {

                aux->used = true;
                aux->type = typetemp;
                aux->id = idtemp;
                aux->data = temp->data;
                aux->next = aux + sizeof(*aux) + sizeof(*aux->data);
                free -= (sizeof(*aux) + sizeof(*aux->data));
                current = (char *) aux->next + sizeof(*aux->data);
                break;
            }else{
                aux = aux + sizeof(*aux) + sizeof(*aux->data);
            }
        }
    }else{
        std::string save = first->next->id;
        saveBlock(save);
        addToMem(jsonStr);

    }
}

/*!
 * Guarda un bloque de memoria en disco.
 * @param id identificador del bloque de memoria que se desea guardar.
 */

void memBlock::saveBlock(std::string id){
    block *aux = first;
    block *before = aux;
    while(aux != NULL){
        if(aux->used && aux->id == id){
            break;
        }else{
            before = aux;
            aux = aux->next;
        }
    }

    block *temp = new (os) block;
    temp->data = new (os + sizeof(*temp)) char;
    strcpy(temp->data, aux->data);
    temp->id = aux->id;
    temp->used = aux->used;
    temp->type = aux->type;
    temp->next = NULL;
    std::string name = id;
    name.append(".bin");
    std::string direccion = "../data";
    if(aux != NULL){
        std::ofstream os(direccion.append(name), std::ios::binary);
        os.write(reinterpret_cast<char*>(&*temp), sizeof(*temp));
        os.close();
    }
}

/*!
 * Carga un bloque de memori de disco a memoria RAM.
 * @param id identificador del bloque que se desea cargar.
 */

void memBlock::loadBlock(std::string id){
    block *aux = new (os) (block);
    std::string name;
    name = id;
    name.append(".bin");
    std::string direccion = "../data";
    std::ifstream inputFile;
    inputFile.open(direccion.append(name), std::ios::in | std::ios::binary);
    inputFile.read(reinterpret_cast<char *>(&*aux), sizeof(*aux));
    inputFile.close();
    Object jsonAdd;
    jsonAdd["id"] = String(aux->id);
    jsonAdd["type"] = String(aux->type);
    jsonAdd["local"] = Boolean(aux->used);
    if(aux->type == "str" ||  aux->type == "char"){
        jsonAdd["value"] = String(aux->data);
    }
    if(aux->type == "int" | aux->type == "float" | aux->type == "double"){
        jsonAdd["value"] = Number(atoi(aux->data));
    }
    if(aux->type == "bool"){
        jsonAdd["value"] = Boolean((bool) aux->data);
    }

    std::string *jsonSend = new (os + sizeof(*aux)) std::string;
    std::stringstream *ss = new (os + sizeof(*aux) + sizeof(*jsonSend)) std::stringstream;
    Writer::Write(jsonAdd, *ss);
    *jsonSend = ss->str();
    addToMem(*jsonSend);
}

/*!
 * Metodo encargado de desfragmentar la memoria
 */

void memBlock::defragMem(){
    block *aux = first;
    block *aux2 = aux + sizeof(*aux) + sizeof(*aux->data);
    block *auxNext = aux->next;
    current = (char *) aux;
    while(aux != NULL){
        if(!aux2->used && aux2->next != NULL){
            auxNext = aux2->next;
            block *temp = new (aux2) block;
            char *data = new (aux2 + sizeof(*aux2)) char;
            temp->id = auxNext->id;
            temp->type = auxNext->type;
            temp->used = auxNext->used;
            strcpy(data, auxNext->data);
            temp->data = data;
            temp->next = auxNext->next;
        }
        aux = aux->next;
        if(aux != NULL){
            auxNext = aux->next;
            aux2 = aux + sizeof(*aux) + sizeof(*aux->data);
        }
    }
}

/*!
 * Elimina el dato deseado de la memoria.
 * @param jsonIn datos de memoria que se desean eliminar.
 */

void memBlock::delFromMem(std::string jsonIn){
    std::stringstream ss;
    ss << jsonIn;
    Object jSon;
    Reader::Read(jSon, ss);
    std::string id = String(jSon["id"]);
    block *aux = (block *) first;
    block *before = aux;
    while(aux != NULL){
        if(aux->id == id){
            break;
        }else{
            before = aux;
            aux = aux->next;
        }
    }
    if(aux != NULL){
        aux->used = false;
        free += (sizeof(*aux) + sizeof(*aux->data));
        if(aux->next->next == NULL){
            if(aux == first){
                current = (char *) first;
                return;
            }
            current = (char *) before->next;
            return;
        }
        defragMem();
    }else{
        std::cout << "Value not Found" << std::endl;
    }
}

/*!
 * Convierte el estado de la memoria incluidos sus datos a un jsonstring para poder ser enviada utilizando sockets.
 * @return
 */

std::string memBlock::toJson(){
    Object varJson;
    Array variableArray;
    block *aux = first;
    while(aux != NULL){
        if(aux->used){
            Object variableData;
            variableData["id"] = String(aux->id);
            if(aux->type == "str" | aux->type == "char"){
                variableData["value"] = String(aux->data);
            }
            if(aux->type == "int" | aux->type == "double" | aux->type == "long"){
                variableData["value"] = Number(atoi(aux->data));
            }
            if(aux->type == "float"){
                std::string::size_type sz;
                variableData["value"] = Number(std::atof(aux->data));
            }
            if(aux->type == "bool"){
                variableData["value"] = Boolean((bool) aux->data);
            }
            if(aux->type == "reference"){
                std::stringstream ssData;
                ssData << aux->data;
                variableData["value"] = String(ssData.str());
            }
            variableData["type"] = String(aux->type);
            std::stringstream ss;
            ss << &aux->data;
            variableData["pointer"] = String(ss.str());
            variableArray.Insert(variableData);
            aux = aux->next;
        } else{
            aux = aux->next;
        }
    }
    varJson["size"] = Number(variableArray.Size());
    varJson["variables"] = variableArray;
    std::stringstream sendStream;
    Writer::Write(varJson, sendStream);
    return sendStream.str();
}

/*!
 * Metodo encargado de liberar y borrar todo el bloque de memoria seleccionado.
 */
void memBlock::releaseMem(){
    delete[] os;
}

/*!
 * Retorna la cantidad de espacio libre que le queda a la memoria.
 * @return
 */

std::size_t memBlock::getFreeSpace(){
    return free;
}

/*!
 * Metodo para diferenciar entre agregar y eliminar datos.
 * @param in
 */

void memBlock::receiver(std::string in) {
    Object JsonIn;
    std::stringstream ss;
    ss << in;
    Reader::Read(JsonIn, ss);
    std::string command = String(JsonIn["command"]);
    if(command == "add"){
        addToMem(in);
    }
    if(command == "del"){
        delFromMem(in);
    }
    if(command == "edit"){
        editData(in);
    }
}

/*!
 * Verifica si la variable deseada se encuentra en la memoria.
 * @param id identificador de la variable que desea buscar.
 * @return jsonString que contiene la informacion si esta se encuentra en memoria.
 */

std::string memBlock::inMem(std::string id) {
    block *aux = first;
    while(aux != NULL){
        if(aux->id == id){
            break;
        }else{
            aux = aux->next;
        }

    }
    if(aux != NULL){
        Object JsonOut;
        std::string jsonOuts;
        std::stringstream ss;
        JsonOut["id"] = String(id);
        JsonOut["found"] = Boolean(true);
        if(aux->type == "str" || aux->type == "char"){
            JsonOut["value"] = String(aux->data);
        }
        if(aux->type == "int" | aux->type == "float" | aux->type == "double"){
            JsonOut["value"] = Number(atoi(aux->data));
        }
        if(aux->type == "bool"){
            JsonOut["value"] = Boolean((bool) aux->data);
        }
        JsonOut["type"] = String(aux->type);
        std::stringstream ps;
        ps << &aux->data;
        JsonOut["pointer"] = String(ps.str());
        Writer::Write(JsonOut, ss);
        return ss.str();
    }else{
        Object JsonOut;
        std::string jsonOuts;
        std::stringstream ss;
        JsonOut["id"] = String(id);
        JsonOut["found"] = Boolean(false);
        Writer::Write(JsonOut, ss);
        return ss.str();
    }
}

void memBlock::editData(std::string jsonin) {
    std::stringstream ss;
    ss << jsonin;
    Object jSon;
    Reader::Read(jSon, ss);
    block *aux = first;
    std::string id;
    String idTemp = jSon["id"];
    id = idTemp.Value();
    while(aux != NULL){
        if(aux->id == id){
            break;
        }else{
            aux = aux->next;
        }
    }

    String typetemp = jSon["type"];
    if(aux != NULL){
        if(typetemp.Value() == "str" | typetemp.Value() == "char"){
            String dataTemp = jSon["value"];
            strcpy(aux->data, dataTemp.Value().c_str());
        }
        if(typetemp.Value() == "int" | typetemp.Value() == "double"){
            Number dataTemp = jSon["value"];
            std::string numtemp = std::to_string(dataTemp.Value());
            strcpy(aux->data, numtemp.c_str());
        }
        if(typetemp.Value() == "float"){
            std::stringstream fs;
            Number datatemp = jSon["value"];
            fs << datatemp.Value();
            std::string dataTemp = fs.str();
            strcpy(aux->data, dataTemp.c_str());
        }
        if(typetemp.Value() == "bool"){
            Boolean dataTemp = jSon["value"];
            *aux->data = (char) dataTemp.Value();
        }
        if(typetemp.Value() == "reference"){
            String search = jSon["value"];
            bool foundBool = searchMem(search.Value());
            if(foundBool){
                block *aux2 = first;
                while(aux2 != NULL){
                    if(aux2->id == search.Value() && aux2->used){
                        break;
                    }else{
                        aux2 = aux2->next;
                    }
                }
                aux->data = aux2->data;
            }
        }
    }

}
