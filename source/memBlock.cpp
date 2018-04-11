//
// Created by fmurillom on 30/03/18.
//

#include <fstream>
#include <cstring>
#include "../includes/memBlock.h"
#include "../includes/cajun/json/reader.h"
#include "../includes/cajun/json/writer.h"

using namespace json;

memBlock::memBlock(std::size_t size){
    os = (char *) malloc(size);
    first = (block *) os + 600;
    current = (char *) first;
    free = size;
    last = (block *) os + size;
    memBlock::size = size;
}

void memBlock::addToMem(std::string jsonStr){
    std::stringstream jsonSS;
    jsonSS << jsonStr;
    Object jSonIn;
    Reader::Read(jSonIn, jsonSS);

    String typetemp = jSonIn["type"];
    String idtemp = jSonIn["id"];
    Boolean localTemp = jSonIn["local"];

    block *aux = first;

    block *temp = new (os) block;
    temp->data = new (current + sizeof(*temp)) char;

    if(typetemp.Value() == "str"){
        String dataTemp = jSonIn["value"];
        strcpy(temp->data, dataTemp.Value().c_str());
    }
    if(typetemp.Value() == "int" | idtemp.Value() == "float" | idtemp.Value() == "double"){
        Number dataTemp = jSonIn["value"];
        std::string numtemp = std::to_string(dataTemp.Value());
        strcpy(temp->data, numtemp.c_str());
    }
    if(typetemp.Value() == "bool"){
        Boolean dataTemp = jSonIn["value"];
        *temp->data = (char) dataTemp.Value();
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
                current = (char *) aux->next;
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
    std::string direccion = "/home/fmurillom/CLionProjects/mServer/";
    if(aux != NULL){
        std::ofstream os(direccion.append(name), std::ios::binary);
        os.write(reinterpret_cast<char*>(&*temp), sizeof(*temp));
        os.close();
    }
    delFromMem(id);
}

void memBlock::loadBlock(std::string id){
    block *aux = new (os) (block);
    std::string name;
    name = id;
    name.append(".bin");
    std::string direccion = "/home/fmurillom/CLionProjects/mServer/";
    std::ifstream inputFile;
    inputFile.open(direccion.append(name), std::ios::in | std::ios::binary);
    inputFile.read(reinterpret_cast<char *>(&*aux), sizeof(*aux));
    inputFile.close();
    Object jsonAdd;
    jsonAdd["id"] = String(aux->id);
    jsonAdd["type"] = String(aux->type);
    jsonAdd["local"] = Boolean(aux->used);
    if(aux->type == "str"){
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

void memBlock::defragMem(){
    block *aux = first;
    block *before = aux;
    while(aux != NULL){
        block *between = aux + sizeof(*aux) + sizeof(*aux->data);
        if(aux->next != between  && !between->used && aux->next != NULL){
            block *aux2 = aux + sizeof(*aux) + sizeof(*aux->data);
            aux2->id = aux->next->id;
            aux2->used = true;
            aux2->type = aux->next->type;
            strcpy(aux2->data, aux->next->data);
            aux2->next = aux->next->next;
            before->next = aux2;
            aux->next->next->used = false;
            before = aux2;
            aux = aux + (sizeof(*aux) + sizeof(*aux->data));
        }else{
            aux = aux->next;
        }
    }
    current = (char *) before->next;
}

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
        before->next = aux->next;
        free += (sizeof(*aux) + sizeof(*aux->data));
        if(aux->next->next == NULL){
            return;
        }
        defragMem();
    }else{
        std::cout << "Value not Found" << std::endl;
    }
}

std::string memBlock::toJson(){
    Object varJson;
    Array variableArray;
    block *aux = first;
    while(aux != NULL){
        if(aux->used){
            Object variableData;
            variableData["id"] = String(aux->id);
            if(aux->type == "str"){
                variableData["value"] = String(aux->data);
            }
            if(aux->type == "int" | aux->type == "float" | aux->type == "double"){
                variableData["value"] = Number(atoi(aux->data));
            }
            if(aux->type == "bool"){
                variableData["value"] = Boolean((bool) aux->data);
            }
            variableData["type"] = String(aux->type);
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

void memBlock::releaseMem(){
    delete[] os;
}

std::size_t memBlock::getFreeSpace(){
    return free;
}

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
}

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
