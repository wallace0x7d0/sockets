#include <stdio.h>

/*
*	Utilizado para fechar uma struct
*	com a função close()
*/
#include <unistd.h>

/*
*	Utilizados para usar funções e constantes
*	referentes a sockets
*/
#include <sys/types.h>
#include <sys/socket.h>

/*
*	Para utilizar a função htons()
*/
#include <arpa/inet.h>

int main(){
	char ip[] = "127.0.0.1";
	int port  = 5000;

	/*
	*	Struct com dados do servidor
	*/
	struct sockaddr_in saddr;
	int saddr_size = sizeof(saddr);

	/*
	*	Struct com os dados do cliente
	*/
	struct sockaddr_in caddr = {

		/*
		*	AF_INET especifica que sera utilizado
		*	IPv4 no socket
		*/
		.sin_family = AF_INET,

		/*
		*	inet_addr transforma um char em um
		*	endereço ip válido para a requisição
		*/
		.sin_addr.s_addr = inet_addr(ip),

		/*
		*	Especifica a porta utilizada pelo socket
		*/
		.sin_port = htons(port) 
	};

	/*
	*	Inicializa o socket
	*/
	int client = socket(AF_INET, SOCK_STREAM, 0);

	/*
	*	Realiza uma tentativa de conexão com o servidor
	*/
	if(connect (client, (struct sockaddr *)&caddr, sizeof (caddr)) != 0){
		printf("Servidor não encontrado!\n");
	}else {

		while(1){
			char buff[129];
			scanf("%s", buff);

			/*
			*	Envia dados para o servidors
			*/
			send(client, buff, sizeof(buff), 0);
		}
		
		close(client);
	}

	return 0;
}