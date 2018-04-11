//
// Created by fmurillom on 30/03/18.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "includes/memBlock.h"
#include "includes/cajun/json/reader.h"
#include "includes/cajun/json/writer.h"
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void recieveData (int sock, memBlock *server)
{
    using namespace json;
    int n;
    char buffer[256];

    Object JsonIn;
    std::stringstream ss;

    bzero(buffer,256);
    n = read(sock,buffer,255);
    std::cout << n << std::endl;
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    ss << buffer;
    Reader::Read(JsonIn, ss);
    std::string command = String(JsonIn["command"]);
    if(command == "srch"){
        n = write(sock, server->inMem(String(JsonIn["id"])).c_str(), server->inMem(String(JsonIn["id"])).size());
        if (n < 0) error("ERROR writing to socket");
    }else{
        server->receiver(buffer);
        std::string state = server->toJson();
        n = write(sock, state.c_str(), state.size());
        if (n < 0) error("ERROR writing to socket");
    }
}

void sockServer(memBlock *server, int portIn){
    int sockfd, newsockfd, port, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    port = portIn;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1) {
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        recieveData(newsockfd, server);
        std::cout << server->toJson() << std::endl;

    }
    close(sockfd);
}


int main(int argc, char *argv[])
{
    memBlock *mServer = new memBlock(100000);
    sockServer(mServer, atoi(argv[1]));
}
