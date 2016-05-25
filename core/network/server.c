#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define ERROR(X) { perror(X); exit(1); }
#define PORT 2048
int *clients;

/* L'initialisation du serveur. Le nombre total de joueur doit etre
   indiqué.  Cette fonction ne retourne que lorsque tous les clients
   sont connectés et que le serveur leur a renvoyé leur numero et le
   nombre de joueurs.
 */
void initServer(int nplayers) {
  int sock;
  int i;
  int t[2];
  struct sockaddr_in server;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) ERROR("socket");
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(PORT);
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1) ERROR("bind");
  if (listen(sock, nplayers) == -1) ERROR("listen");
  clients = (int *)malloc(sizeof(int)*nplayers);
  for (i=0; i<nplayers; i++) {
    if ((clients[i] = accept(sock,0, 0)) == -1) ERROR("accept");
    printf("Player %d connected.\n",i);
  }
  close(sock);
  printf("All connected.\n");
  /* Tout le monde est connecté. Maintenant, envoie à chaque client le nombre de joueurs et son numero */
  for (i=0; i<nplayers; i++) {
    t[0]=nplayers;/* Le nombre de joueurs */
    t[1]=i; /* Le numero du client */
    write(clients[i],&t,sizeof(int)*2); /* Envoie le tout (2 entiers) */
  }
}
/* Envoie les memes données à tous les clients connectés.
   data: les données à envoyer
   size: la taille des données, en octets
   nplayers: le nombre de joueurs
*/
void broadcast(void *data, size_t size,int nplayers) {
  int i;
  for (i=0; i<nplayers; i++) {
    write(clients[i],data,size);
  }
}
/* Recoit des données de tous les joueurs. Ces données sont rangées dans le tableau data
   data: un tableau à une dimension, dont chaque élément est de taille size
   size: la taille d'une donnée envoyée par un client
   nplayers: le nombre de joueurs
*/
void gather(void *data, size_t size,int nplayers) {
  int i;
  for (i=0; i<nplayers; i++) {
    read(clients[i],data+size*i,size) ;
  }
}
/* Termine le serveur */
void closeServer() {
  free(clients);
}

/* Fonction principale du serveur
   A COMPLETER
 */
int main(int argc, char *argv[]) {
  if (argc<2) {
    printf("Le nombre de joueurs doit être indiqué.\nSyntaxe: %s [nombre de joueurs]\n",argv[0]);
    exit(1);
  }
  /* Lit le premier parametre de la ligne de commande */
  int nplayers=atoi(argv[1]);
  initServer(nplayers);

  /* A COMPLETER */


  return 0;
}
