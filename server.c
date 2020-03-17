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

	/*
	*	Struct com os dados do cliente
	*/
	struct sockaddr_in caddr;
	int caddr_size = sizeof(caddr);

	/*
	*	Struct com os dados do servidor
	*/
	struct sockaddr_in saddr = {

		/*
		*	AF_INET especifica que sera utilizado
		*	IPv4 no socket
		*/
		.sin_family = AF_INET,

		/*
		*	SINADDR_ANY especifica que podera ser
		*	aceito qualquer endereço passado para
		*	o socket
		*/
		.sin_addr.s_addr = htonl(INADDR_ANY),

		/*
		*	Especifica a porta utilizada pelo socket
		*/
		.sin_port        = htons(5000) 
	};

	/*
	*	Inicializa o socket
	*/
	int server = socket(AF_INET, SOCK_STREAM, 0);

	/*
	*	Vincula o socket a struct saddr
	*/
	bind(server, (struct sockaddr *) &saddr, sizeof(saddr));

	/*
	*	Permite que socket receba conexões
	*	No caso permite no maximo 1 conexão
	*/
	listen(server, 1);

	/*
	*	Aceita a conexão com o cliente e armazena os dados
	*	na struct caddr
	*/
	int client = accept(server, (struct sockaddr *) &caddr, &caddr_size);

	/*
	*	Armazena os dados recebidos do cliente
	*/
	char buff[129];

	while(1){

		/*
		*	Recebe os dados do servidor e armazena o valor
		*	na variável buff 
		*/
		recv(client, buff, sizeof(buff), 0);
		printf("%s\n", buff);
		
	}	

	/*
	*	Encerra a conexão com o cliente
	*/
	close(client);
	return 0;
}