#include"client_head.h"

void center_ac::set_serverAddress(QHostAddress s){this->serverAddress=s;}
void center_ac::set_serverPort(int p){this->serverPort=p;}

QHostAddress center_ac::get_serverAddress(){return this->serverAddress;}
int center_ac::get_serverPort(){return this->serverPort;}
