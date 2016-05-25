#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

/* Fonctions a appeler dans le main, dans tank.c */
int openConnection(const char *host,int *id,int *nplayers);
void closeConnection(int sock);
void sendData(int sock,void *data, size_t size);
void *receiveData(int sock, void *data, size_t size);


#endif // CLIENT_H_INCLUDED
