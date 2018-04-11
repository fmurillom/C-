
// Created by fmurillom on 30/03/18.
//

#ifndef MSERVER_MEMBLOCK_H
#define MSERVER_MEMBLOCK_H


#include <cstddef>
#include <iostream>

struct block{
    std::string id;
    char *data;
    std::string type;
    bool used;
    block *next = NULL;
};

class memBlock {
private:
    block *first;
    block *last;
    char *os;
    std::size_t size;
    std::size_t free;
    char *current;
    void defragMem();


    int toString(int number);


public:

    memBlock(std::size_t size);

    std::string toJson();

    void addToMem(std::string jsonStr);

    void delFromMem(std::string jsonIn);

    void releaseMem();

    void saveBlock(std::string id);

    void loadBlock(std::string id);

    std::size_t getFreeSpace();

    void receiver(std::string in);

    std::string inMem(std::string id);

};


#endif //MSERVER_MEMBLOCK_H
