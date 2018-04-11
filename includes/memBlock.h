
// Created by fmurillom on 30/03/18.
//

#ifndef MSERVER_MEMBLOCK_H
#define MSERVER_MEMBLOCK_H


#include <cstddef>
#include <iostream>


struct block{
    /*!
     * Estructura creada para almacenar en memoria los datos de cada variable que entre en memoria
     */
    std::string id;
    char *data;
    std::string type;
    bool used;
    block *next = NULL;
};

class memBlock {
    /*!
     * Clase encargada de manejar todo lo que suceda en memoria.
     */
private:
    /*!
     * Puntero a la direccion de memoria inicial del bloque de memoria a utilizar.
     */
    block *first;
    /*!
     * Puntero a la siguiente direccion de memoria despues del bloque.
     */
    block *last;
    /*!
     * puntero de reserva los primeros 600 bytes del bloque para utilizar en swaps y asignacion de variables temporales
     */
    char *os;
    /*!
     * Guardara el tamaño total del bloque de memoria a utilizar
     */
    std::size_t size;
    /*!
     * Guardara el tamaño libre que le queda a la memoria en bytes.
     */
    std::size_t free;
    /*!
     * puntero que señala la siguiente direccion de memoria libre en el bloque.
     */
    char *current;
    /*!
     * Funcion encargada de desfragmentar la memoria despues de alguna eliminacion.
     */
    void defragMem();


public:


    /*!
     * Constructor de la clase.
     * @param size memoria en bytes que se desea resrvar para la ejecucion.
     */
    memBlock(std::size_t size);

    /*!
     * Funcion que convierte todos los datos en memoria en un solo string json para enviar el IDE
     * @return string con todos los datos en memoria para enviar al IDE
     */

    std::string toJson();

    /*!
     * Funcion para agregar un nuevo dato en memoria.
     * @param jsonStr json que contiene los datos a agregar, su formato se puede observar en el archivo jsonSend.
     */

    void addToMem(std::string jsonStr);

    /*!
     * Elimina el dato deseado.
     * @param jsonIn String de json con la informacion para eliminar una variable, su formato se puede obsevar en jsonSend
     */

    void delFromMem(std::string jsonIn);

    /*!
     * Funcion para eliminar y liberar toda la memoria resrvada para el servidor.
     */

    void releaseMem();

    /*!
     * Guarda en disco un archivo .bin que contiene la informacion de la variable dumpeada
     * @param id id de la variable que se desea almacenar en disco
     */

    void saveBlock(std::string id);

    /*!
     * Carga el bloque especificado desde el disco duro y lo inseta en la memoria.
     * @param id el id del bloque que se desea cargar.
     */

    void loadBlock(std::string id);

    /*!
     * Retorna la cantidad de espacio que queda disponible.
     * @return tamaño en bytes que queda disponible.
     */
    std::size_t getFreeSpace();

    /*!
     * Funcion para identificar que se debe hacer, si agregar a memoria o eliminar segun el comando que venga especificado en el jSon.
     * @param in sring de Json identificando que se debe hacer y los datos con que hacerlo, tiene la misma estructura que el de agregar memoria.
     */

    void receiver(std::string in);

    /*!
     * Funcion que determina si la variable especificada se encuentra en memoria.
     * @param id identificador de variable que se desea buscar.
     * @return json que indica el nombre y si si encontro la variable deseada. Estructura del mensaje en jsonSend.
     */

    std::string inMem(std::string id);

};


#endif //MSERVER_MEMBLOCK_H
