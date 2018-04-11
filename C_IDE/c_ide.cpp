#include "c_ide.h"
#include "ui_c_ide.h"
#include<iostream>
#include "includes/cajun/json/reader.h"
#include "includes/cajun/json/writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

std::string socketConnect(){
    int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        char buffer[1000000];
        portno = 51717;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname("localhost");
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");
        std::string send = "{\"command\" : \"info\"}";
        bzero(buffer,1000000);
        n = write(sockfd,send.c_str(),send.size());
        if (n < 0)
            error("ERROR writing to socket");
        bzero(buffer,1000000);
        n = read(sockfd,buffer,1000000);
        if (n < 0)
            error("ERROR reading from socket");
        std::cout << buffer << std::endl;
        close(sockfd);
        shutdown(sockfd, SHUT_WR);
        std::string sending = buffer;
        return sending;
}

C_IDE::C_IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::C_IDE)
{
    ui->setupUi(this);
    this->setWindowTitle("C! IDE");

    this->createUI();
}

C_IDE::~C_IDE()
{
    delete ui;
}

void C_IDE::createUI(){
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Holis"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Prueaba"));
    ui->tableWidget->resizeColumnsToContents();
}



void C_IDE::refreshMem(){
    using namespace json;

    ui->tableWidget->setRowCount(0);
    Object jSonStatus;
    std::string jsonIn = socketConnect();
    std::stringstream ss;
    ss << jsonIn;
    Reader::Read(jSonStatus, ss);
    Array variableArray;
    Number sizeAux = jSonStatus["size"];
    int size = sizeAux.Value();
    variableArray = jSonStatus["variables"];
    for(int i = 0; i < size; i++){
        Object addObject;
        addObject = variableArray[i];
        String idaux  = addObject["id"];
        String pointeraux = addObject["pointer"];
        QString id = QString::fromStdString(idaux.Value());
        QString pointer = QString::fromStdString(pointeraux.Value());
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(id));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(pointer));
    }
    ui->tableWidget->resizeColumnsToContents();
}
