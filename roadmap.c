/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:30:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/19 20:30:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Em C, a leitura dos ficheros (fd) é feita através da função read(). Esta função permite ao programador
ler blocos de memória, mas não fornece nenhum mecanismo automático para detetar onde termina uma linha,
nem para guardar o que foi lido caso a linha seja incompleta. 
A função get_next_line, a cada chamada, deve ler uma linha completa (até encontrar uma newline '\n' ou
até atingir o fim do ficheiro EOF) e devolver essa linha. 
Este comportamente deve repetir-se sem perder o rasto do que já foi lido, até que não haja mais nada a ler
(altura em que a função retorna NULL). 

Explicação detalhada da leitura: read(fd, buffer, BUFFER_SIZE)

A função read é uma função que lê os dados diretamente de um file descriptor.
O fd identifica o ficheiro a partir de onde vamos ler.
O buffer é ponteiro para o bloco de memória onde os dados lidos serão armazenados. 

> File descriptor (fd): É um número inteiro retornado pela função open(). Ele identifica o ficheiro que
                        queremos ler.

Exemplo: int fd = open("texto.txt", O_RDONLY);

> Buffer (buffer): É um array de caracteres (geralmente estático na get_next_line) onde serão armazenados
                   os dados lidos do ficheiro.

Exemplo: static char buffer[BUFFER_SIZE + 1]; // +1 para espaço para '\0'

> BUFFER_SIZE: É o tamanho do bloco de leitura. Define quantos bytes queremos ler de uma vez.

Por exemplo: #define BUFFER_SIZE 5

ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);

O que acontece neste momento?

    O sistema lê até BUFFER_SIZE bytes do ficheiro identificado por fd.
    Esses bytes são armazenados no array buffer.
    O valor retornado pela função read() é a quantidade de bytes lidos.
    Se o ficheiro tiver menos bytes do que BUFFER_SIZE, só esses serão lidos.



	

O projeto get_next_line tem como principal objetivo a implementação de uma função que permite ler, de forma
controlada e precisa, uma linha de cada vez a partir de um ficheiro (fd).

Mas o que significa “ler linha a linha”? Ler linha a linha = Ler o texto até encontrar uma newline \n. 

Um ficheiro de texto, como este: Linha 1: Olá mundo
                                 Linha 2: Bem-vindo à 42
                                 Linha 3: get_next_line

Na verdade, é uma sequência de caracteres, onde cada fim de linha é representado por um caractere especial \n 
(nova linha).
A função get_next_line deve, ao ser chamada repetidamente, devolver uma string com o conteúdo de cada linha, 
incluindo o \n se ele estiver presente.
Ou seja, a cada chamada, deve devolver a próxima linha disponível no fluxo de entrada, sem perder o contexto da
leitura anterior.

O que significa “linha”, neste contexto? Uma "linha" é considerada como uma sequência de caracteres terminada
por um caractere de newline (\n). 
Assim, o projeto define "linha" como:

	> Uma sequência de 1 ou mais caracteres seguida de um \n;
      OU o final do ficheiro, mesmo que não haja \n no fim.

Comportamento da get_next_line em relação À newline \n

	A função get_next_line só retorna uma string terminada com \n se esse caractere realmente existir no conteúdo 
	do ficheiro.
	Ou seja:

      > Se a linha termina com \n, ele devolve a string incluindo esse \n;
	  > Se a linha não termina com \n (por exemplo, a última linha do ficheiro), então não vai adicionar um \n 
	    artificialmente;

    Portanto, a última linha de um ficheiro normalmente não tem \n, e get_next_line devolve apenas os caracteres 
	que foram lidos até o EOF.

	Por que get_next_line não adiciona o \n? Porque isso estaria a falsificar o conteúdo original do ficheiro.
	O projeto pede que get_next_line devolva exatamente o que está no ficheiro, linha a linha, respeitando as
	newlines '\n' originais. 
	Adicionar um \n onde não existe violaria o princípio da fidelidade à fonte original, poderia causar problemas 
	em programas que dependem exatamente do conteúdo lido e iria contra a especificação esperada da função.

	Como confirmar se a última linha tem \n?

	Para verificar se a última linha do ficheiro tem \n, basta usar o comando cat -e no terminal: cat -e dados.txt

	Saída possível: Linha 1: olá mundo$
	                Linha 2: viva a 42$
                    Linha 3: get_next_line

    Se o $ não aparece no fim da última linha, é porque ela não termina com \n.


A função get_next_line() deve obedecer aos seguintes princípios:

1. Ler até encontrar uma nova linha (\n) ou EOF:

   A função get_next_line deve ler o conteúdo do ficheiro em blocos (definidos pelo BUFFER_SIZE) até que:

		> Encontre um caractere de newline (\n): o que indica o fim de uma linha, ou seja, neste caso, a linha 
		                                         está completa e pode ser devolvida;
    	> Chega ao fim do ficheiro (EOF) sem encontrar um \n: mesmo assim, deve devolver o que foi lido até então, 
		                                                      pois trata-se da última linha.

   Este comportamento é essencial para permitir a leitura correta de ficheiros mesmo quando a última linha não termina 
   com \n, algo que acontece com frequência em ficheiros escritos manualmente.

   Ambos os casos devem levar à devolução de uma linha completa, mas com uma nuance muito importante:
	
   Situação com \n:
   
   Se o conteúdo for, por exemplo: Primeira linha\nSegunda linha\nTerceira

   Na 1ª chamada a função deve devolver: "Primeira linha\n"
   Na 2ª chamada: "Segunda linha\n"
   Na 3ª chamada: "Terceira" (mesmo sem \n, ela deve ser devolvida porque é o resto do ficheiro).

   Por que isso é importante? Em muitos casos reais, a última linha não termina com \n, especialmente se foi escrita 
   manualmente. Se a função ignorasse essa linha final por não ter \n, parte do conteúdo seria perdido, o que é 
   inaceitável na leitura de dados.
   
   Requisitos técnicos: > A função não deve parar de ler prematuramente;
						> Deve continuar a juntar blocos até encontrar o \n;
						> E no fim do ficheiro, deve devolver o que foi acumulado, mesmo sem \n.

						
2. Devolver uma linha completa como uma string terminada por \0: 

   Em C, toda a string é um array de caracteres terminado por \0. Isso permite que as funções saibam onde a string 
   termina.

   Ao detetar uma linha (com ou sem \n), a função deve:

		> Alocar memória dinamicamente com malloc() para guardar essa linha (que será devolvida);
		  O tamanho deve ser exatamente o necessário para os caracteres lidos mais o \0 no final;
		> Copiar os caracteres (vindos do buffer e/ou de leituras parciais) para esta nova memória;
		> Incluir o \n se ele existir no conteúdo original;

   Garantir que a string termina com \0 (o terminador nulo da linguagem C).
   Isto significa que a função não modifica nem omite partes da linha: a função não deve omitir o \n. Ela deve 
   manter a fidelidade ao conteúdo lido.
	
3. Manter o estado entre as chamadas (com uso de static):

   Uma das partes mais importantes é garantir que a função "lembra-se" de onde parou da última vez que foi chamada.
   
   Vamos supor que lêmos com um BUFFER_SIZE de 10, e o ficheiro contém: "Linha longa com \n próxima"

   Na primeira leitura, com read(fd, buffer, 10), vamos obter: "Linha lon"

   Mas ainda não encontramos o \n. 
   
   Na próxima leitura: "ga com \n ". Agora sim: o \n apareceu no meio do buffer. 
   
   A função deve: > Juntar tudo o que foi lido antes + até ao \n;
                  > Guardar o que veio depois do \n (a parte " próxima");
                  > Usar esse resto na próxima chamada, sem reler o ficheiro.

   Como isso é feito? Usa-se uma variável static, que é inicializada apenas uma vez.

    
	O que é guardado? O conteúdo que sobrou no buffer depois do \n, que ainda não foi devolvido. 
	Este conteúdo é preservado na memória estática, para ser usado como início da leitura da próxima linha.

   Para isso, é necessário:

   		> Guardar o conteúdo que sobrou da leitura anterior (por exemplo, o que vem depois do \n);
    	> Evitar ler novamente desde o início, o que causaria perda de desempenho e inconsistência nos dados;
    	> Utilizar uma variável static para manter esses dados em memória entre múltiplas execuções da função.

	Esta capacidade de manter o contexto entre as chamadas.
	
4. Funcionar com diferentes tamanhos de buffer:

   A função deve ser escrita de forma a que o seu comportamento não dependa de um tamanho específico de buffer. 
   Isso significa que:

    > Ela deve funcionar corretamente se o BUFFER_SIZE for 1 (um caractere de cada vez);
	> Também deve funcionar com valores grandes de BUFFER_SIZE, como 1000 ou mais;
    > A leitura deve ser feita em blocos sucessivos, até que a linha esteja completa.


EM SUMA: O projeto get_next_line propõe a criação de uma função que, quando chamada repetidamente, lê de um ficheiro 
(file descriptor) uma linha de cada vez — ou seja, a função deve:

    > Ler o conteúdo do ficheiro até encontrar um caractere de nova linha \n ou até chegar ao fim do ficheiro (EOF);
    > Devolver essa linha completa como uma string terminada por \0;
    > Manter o estado entre as chamadas, ou seja, lembrar-se de onde parou na leitura anterior, sem ler novamente
	  desde o início;
    > Funcionar corretamente com diferentes tamanhos de buffer e diferentes ficheiros simultâneos (bónus).

	
1) get_next_line - char *get_next_line(int fd)

   	char	*get_next_line(int fd)
	{
		static char	buffer[BUFFER_SIZE + 1];
		char		*result_line;
		size_t		read_idx;
		size_t		write_idx;
		int			newl;

		if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);
		result_line = NULL;
		newl = 0;
		while (!newl && (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0)))
		{
			result_line = join_till_nl(result_line, buffer);
			read_idx = 0;
			write_idx = 0;
			while (buffer[read_idx] != '\0')
			{
				if (newl)
					buffer[write_idx++] = buffer[read_idx];
				if (buffer[read_idx] == '\n')
					newl = 1;
				buffer[read_idx++] = '\0';
			}
		}
		return (result_line);
	}

	A função get_next_line tem como objetivo ler uma linha de um ficheiro (fd) de forma contínua,
	devolvendo uma linha de cada vez, até que o final do ficheiro seja antigido. 
	A função guarda os dados restantes entre as sucessivas chamadas utilizando o static buffer, o 
	que permite continuar a leitura no momento em que parou.
	A função get_next_line é chamada repetidamente para ler uma linha de cada vez, ou seja, a cada 
	chamada à função get_next_line é apenas devolvida uma linha, em que nessa linha, inclui o
	caractere '\n' (caso ele exista e se não estiver no fim do ficheiro). Assim, é garantido que as
	leituras parciais (quando a linha não cabe toda no buffer) sejam tratadas corretamente.
	Quando não houver mais linhas para serem lidas, a função retorna NULL. 


	1.1) Variáveis: 

	> static char  buffer[BUFFER_SIZE + 1]: É o buffer de leitura, com tamanho BUFFER_SIZE + 1, que
	                                        armazena temporariamente os dados lidos do fd.
											A adição do +1 é muito importante, para garantir que a
											string seja terminada com o caractere nulo '\0'.
											A função read() pode preencher até BUFFER_SIZE bytes, mas precisamos
											de 1 byte extra para colocar o '\0' no final.

											O tipo static significa que: 

											> A memória dessa variável é alocada apenas uma vez, durante toda a 
											  execução do programa.
											> Ela mantém o seu valor entre as diferentes chamadas da função.
											> Ela não é destruída quando a função termina. 
    										> Só é visível dentro da função get_next_line, mas o valor persiste
											  entre as chamadas.

											Na função get_next_line, significa que:
											
											> O buffer é um array de caracteres com espaço para BUFFER_SIZE bytes
											  mais o caractere '\0'.
											> Esse buffer é criado uma só vez e mantém o conteúdo entre as chamadas
											  à função get_next_line. Ou seja, a função, com ajuda do buffer estático,
											  vai se lembrar do que sobrou da leitura anterior. 
											  Assim, ele vai armazenar os dados não processados (as "sobras") de uma leitura
											  anterior para serem utilizados na próxima chamada. Isto é essencial porque:
											  
											  	> um ficheiro pode conter linhas maiores do que o tamanho do BUFFER_SIZE. 
												> uma linha pode ser lida em partes, e o restante da linha é guardado no
												  buffer.
												> quando voltarmos a chamar a função, ela continua a leitura a partir do
												  conteúdo restante no buffer. 
												  
											Portanto, o buffer vai funcionar como uma "memória intermediária" entre as
											chamadas à função get_next_line, permitindo ler aos poucos o ficheiro e 
											continuar no momento onde parou. 

											Sem o static, o buffer seria apagado cada vez que a função termina
											— o que inviabilizaria continuar a ler corretamente uma linha grande
											ou várias chamadas sucessivas.
											
											O tipo static conserva os dados, ou seja, garante que o 
											valor do buffer não se perde entre as chamadas consecutivas 
											da função get_next_line, o que evita releituras desnecessárias,
											pois se uma leitura anterior terminou antes da newline '\n', o
											que sobra fica guardado para a próxima leitura. 

											Suponhamos:

    										BUFFER_SIZE = 5

    										Conteúdo do ficheiro: Olá\nMundo\n42

											Primeira chamada a get_next_line(fd):

    										buffer está vazio: read(fd, buffer, 5) lê "Olá\nM".

    										join_till_nl junta "Olá\n" na result_line.

    										Sobra "M" após o \n, ela é mantida no buffer (usando read_idx/write_idx).

    										Retorna: "Olá\n"

											Segunda chamada:

    										buffer já contém "M", não faz read ainda.

    										Completa a linha: read(fd, buffer + 1, 4) lê "undo\n", formando "Mundo\n"

    										Retorna: "Mundo\n"

											Terceira chamada:

    										buffer vazio, lê "42" (últimos caracteres).

    										Não tem \n, então result_line = "42"

    										Retorna: "42"

											Quarta chamada:

    										read retorna 0, buffer[0] == '\0' → função retorna NULL.
											 
											
	> char *result_line: É a string final que vai armazenar (acumular) a linha que está a ser construída
	                     durante a função get_next_line.
						 Ela vai guardar o conteúdo (da linha atual que estamos a ler do ficheiro) que será
						 devolvido pela função.
						 Em conjunto com a função join_till_nl, ela junta os fragmentos dos textos lidos do
						 ficheiro até formar uma linha completa, terminada por uma newline '\n' ou pelo fim
						 do ficheiro (EOF).
						 
						 Ela começa com NULL, pois ainda não há nenhuma linha alocada (ou a ser formada).
						 Esta abordagem é importante porque permite informar a função join_till_nl de que
						 está a começar construir uma nova linha e que não está a juntar com uma anterior. 
						 Quando join_till_nl vê que o primeiro argumento é NULL, não tenta fazer uma concatenação,
						 mas sim, cria uma nova string a partir do buffer.

						 // Primeira chamada:
						 result_line = NULL;
						 result_line = join_till_nl(result_line, buffer); // cria nova string

						 // Segunda chamada:
						 result_line != NULL;
						 result_line = join_till_nl(result_line, buffer); // concatena
						 
						 Á medida que os novos dados vão sendo lidos do ficheiro, result_line cresce 
						 progressivamente de modo a armazenar os novos fragmentos de texto da linha
						 até que esta esteja completa.
						 Quando encontrar uma newline ('\n') ou o quando chegar ao fim do ficheiro (EOF),
						 result_line contém a linha completa e é então devolvida. 
						 
						 Assim, result_line cresce dinamicamente:
						 
						 > Se a linha for longa, várias leituras são feitas.
						 > Cada fragmento novo obriga a criar uma nova string com o tamanho aumentado.

						 Exemplo:

						 Se tivermos BUFFER_SIZE = 4 e a linha no ficheiro for "Cadeia muito longa\n":

    					 1ª leitura: "Cade" → cria "Cade"
    					 2ª leitura: "ia m" → junta → "Cadeia m"
    					 3ª leitura: "uito" → junta → "Cadeia muito"
    					 4ª leitura: " lon" → junta → "Cadeia muito lon"
    					 5ª leitura: "ga\n" → junta → "Cadeia muito longa\n" → encontrou \n e retorna

						 A cada passo, é feito:

						 malloc(novo_tamanho);
						 strcpy(novo, antigo);
						 strcat(novo, novo_conteúdo);
						 free(antigo);

						 A construção de result_line para quando um caractere \n é encontrado no buffer (indicando
						 o fim da linha), ou o read() retorna 0 (fim do ficheiro).
						 Neste ponto, result_line contém toda a linha com o \n incluído (caso ele exista), e a função
						 get_next_line retorna-a.

						 O que acontece se não houver \n? Se o ficheiro terminar sem uma newline, mas com texto, 
						 get_next_line ainda retorna esse conteúdo como a última result_line.

						 Exemplo: 
						 
						 Ficheiro contém: "linha final sem newline"
						 A result_line final será "linha final sem newline" e será retornada sem \n.

	> size_t read_idx: é o índice de leitura, utilizado para percorrer o conteúdo do buffer após a leitura feita com a
	                   função read(). Ela é utilizada no loop interno da função para examinar cada caractere do buffer, 
					   identificando onde está o caractere newline '\n' e reorganizando os dados conforme necessário. 

	> size_t write_idx: é o índice de escrita utilizado para reorganizar o conteúdo do buffer após a leitura de uma linha.
	                    Ela serve para preservar os dados que vêm depois de uma newline (ou seja, preserva a parte da próxima
						linha) e coloca-os no ínicio do buffer, para que possam ser utilizados na próxima chamada da função. 
						
						Por que isso é necessário?

						A função get_next_line utilizada a função read() para ler em blocos (BUFFER_SIZE).
						É possível que um read() leia mais do que uma linha, por vez.
						Como a função devolve uma linha por chamada, ela precisa guardar o que sobra para depois.
						Ao utilizar write_idx, o buffer pode ser reutilizado com os caracteres da próxima linha.
	        
	1.2) Verificação de erro

	if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);

	Este if tem a função de verificar se é seguro continuar a execução da função.
	O seu objetivo é garantir que os parâmetros recebidos são válidos e seguros,
	antes de tentar ler o ficheiro, com a função read(). 
	O if vai verificar duas condições importantes logo no começo do get_next_line e
	se qualquer uma delas for verdadeira: 
	
	> o fd for inválido.
	> ou o tamanho do buffer (BUFFER_SIZE) não for positivo. 

	A função interrompe imediatamente a execução e retorna NULL, indicando que não é
	possível continuar. 

	int fd: É um número inteiro atribuído pelo sistema operativo quando se abre um ficheiro.
	        
	fd < 0: Verifica se o file descriptor é inválido.

			Como se obtém um fd? Ao abrir um ficheiro com open(): int fd = open("ficheiro.txt", O_RDONLY);

    		> Se o ficheiro for aberto com sucesso, open() devolve um número inteiro (normalmente ≥ 3).
			> Se houver erro, open() devolve -1.
	        
			Ex.: 0 → stdin, 1 → stdout, 2 → stderr.

        	Normalmente, um fd >= 3 corresponde a ficheiros abertos por open().

    		Quando fd < 0? Significa que o ficheiro não foi aberto corretamente (por exemplo, 
			falha no open()).

    		Isso pode acontecer se:  > O caminho do ficheiro está errado.

									   Ex: int fd = open("inexistente.txt", O_RDONLY); // fd == -1

                                     > Não há permissões para ler o ficheiro.

									   Ex: int fd = open("/etc/shadow", O_RDONLY); // acesso negado → fd == -1
									   
                                     > O ficheiro não existe.

			Porque se devolve NULL? Se o fd for inválido, chamar read(fd, ...) causaria comportamento
			indefinido (por exemplo, erro de leitura ou até crash). Devolver NULL evita isso.

	BUFFER_SIZE <= 0: Verifica se o tamanho do buffer é válido.
					  O BUFFER_SIZE é uma macro definida no tempo da compilação.
					  Define quantos bytes serão lidos do ficheiro por cada chamada da função read().

					  Quando BUFFER_SIZE <= 0? 
					  Pode acontecer se:

        			  > Foi definido como zero (#define BUFFER_SIZE 0)
					  > Foi definido com valor negativo (em implementações incorretas)
					  > Não foi definido (dependendo do compilador, pode assumir 0)

					  Por que isso é um problema?

    				  read(fd, buffer, BUFFER_SIZE) com BUFFER_SIZE <= 0 é inválido, porque:

        			  > read() espera um número positivo de bytes.
        			  > Um BUFFER_SIZE de 0 significaria: “ler zero bytes”, o que é inútil.
        			  > Um valor negativo pode causar erros mais graves (overflow, falhas de segmentação).

	1.3) Loop externo

	newl = 0;
	result_line = NULL;
	while (!newl && (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0)))

	newl = 0: A variável newl atua como uma flag de controlo para saber se já foi encontrada uma newline durante
	          a leitura atual.
			  Começar com 0 significa que ainda não foi encontrada nenhuma newline na linha.

	result_line = NULL: Inicializa a string result_line com NULL, o que indica que ainda não foi alocado espaço
	                    para guardar a linha.

						Por que isso é importante? Isso informa à função auxiliar join_till_nl() que ainda não há 
						dados anteriores.

    					A função join_till_nl() irá:  > Detetar que result_line == NULL.
													  > Fazer o primeiro malloc com base no conteúdo do buffer.
													  > Começar a construir a linha do zero.

						A string result_line vai crescer dinamicamente a cada fragmento lido do ficheiro. 
						A cada chamada de join_till_nl, a result_line é realocada (com malloc + free interno) até 
						conter a linha completa.

	O loop while vai executar o ciclo de leitura e de construção da linha enquanto não encontrarmos uma newline '\n'
	e enquanto temos dados no buffer ou conseguimos ler mais do ficheiro.
	
	> !newl: Vai continuar a ler enquanto não for encontrada uma newline. 
	         Assim que a newline for detetada no buffer, newl será definida como 1 e o loop termina.

	> buffer[0]: verifica se o buffer ainda contém dados não processados de uma chamada anterior da função.
                 Isto acontece porque o buffer é static, e os caracteres após o \n da linha anterior são mantidos.
				 Se buffer[0] != '\0', significa que ainda temos algo para analisar antes de fazer nova leitura.

    > read(fd, buffer, BUFFER_SIZE) > 0: se o buffer estiver vazio (buffer[0] == '\0'), então vai tentar ler novos
	                                     dados do ficheiro.

        								 A função read() devolve o número de bytes lidos:

                						 - 0: foram lidos dados → podemos continuar

            							 - == 0: chegou ao EOF → sair do loop

            							 - < 0: erro de leitura (não tratado diretamente aqui, mas o loop termina
										        porque a condição falha).

	Suponhamos que um ficheiro contém este conteúdo:

	Olá mundo\n
	Esta é a linha 2\n

	E BUFFER_SIZE = 5
    
	1) result_line = NULL.
	2) buffer[0] == '\0', então faz read(fd, buffer, 5) → lê "Olá m"
    3) join_till_nl() cria "Olá m"
    4) buffer é limpo até ao \n (não foi encontrado ainda), então continua.
    5) read() lê "undo\n"
    6) join_till_nl() junta "undo\n" a "Olá m" → linha completa.
    7) newl = 1 → sai do loop.
    8)Devolve "Olá mundo\n"

    Na próxima chamada de get_next_line(), o buffer conterá "Esta " (porque o \n já foi processado)

	1.4) result_line = join_till_nl(result_line, buffer);

	Esta linha é responsável por construir ou continuar a construção da linha atual (até encontrar a newline ou
	chegar ao fim do ficheiro), juntando o conteúdo atual do buffer ao que já foi acumulado na string result_line.

	> result_line: É a linha em construção.
				   Pode:  - Ser NULL, se ainda estamos no início da leitura da nova linha.
                          - Já conter parte da linha lida em chamadas anteriores do loop.

	> buffer: Contém os dados acabados de ler do ficheiro.
			  Pode conter: - Um pedaço da linha atual.
						   - A linha completa (com \n).
						   - Parte de uma linha e parte da seguinte.

	join_till_nl() é uma função que:  > Concatena result_line com o conteúdo do buffer, até ao primeiro \n ou 
	                                    fim de string.
                                      > Faz uma alocação dinâmica (malloc) para criar uma nova string com o conteúdo 
									    combinado.
    								  > Se result_line já tinha conteúdo (de chamadas anteriores), ele é copiado para
									    a nova string, seguido do que for necessário do buffer.
									  > Liberta a memória antiga de result_line (se necessário).

	Observações importantes:

    > join_till_nl() não copia o que está após o \n — esse conteúdo permanece no buffer para a próxima chamada 
	  de get_next_line.
	> Esta abordagem garante que a função devolve apenas uma linha por chamada.

	
	[JOIN_TILL_NL]: 

		char	*join_till_nl(char *line, char *buffer)
		{
			char	*new_line;
			size_t	line_idx;
			size_t	buffer_idx;

			if (!buffer)
				return (NULL);
			new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
			if (!new_line)
				return (NULL);
			line_idx = 0;
			while (line && line[line_idx] != '\0')
			{
				new_line[line_idx] = line[line_idx];
				line_idx++;
			}
			buffer_idx = 0;
			while (buffer[buffer_idx] != '\0')
			{
				new_line[line_idx++] = buffer[buffer_idx];
				if (buffer[buffer_idx++] == '\n')
					break ;
			}
			new_line[line_idx] = '\0';
			free(line);
			return (new_line);
        }

		Tem como objetivo criar uma nova string (new_line) que junta os novos caracteres do buffer à string line
		(segmento da linha já lida em chamadas anteriores) até encontrar a primeira newline '\n'.
		Esta função é responsável por construir (e continuar a construir) a linha final completa, lendo os
		caracteres do buffer e devolvendo uma nova string com os dados combinados.

		1) Variáveis: 

  			> char *line: É uma string que representa a parte da linha que já foi construída até ao momento, com base 
			              nos dados lidos anteriormente do ficheiro (fd) e passados à função join_till_nl.

						  Se line == NULL, significa que ainda não começámos a construir a linha ou é o ínicio da leitura
						  de uma nova linha. 
						  Se line != NULL, significa que line contém parte da linha lida anteriormente mas que ainda está 
						  incompleta porque a newline (\n) ainda não foi encontrada.

				          Ela guarda progressivamente os caracteres da linha que estamos a construir até encontrarmos a
				          newline ('\n') ou chegarmos ao fim do ficheiro ('\0' no buffer).
						  Tudo o que já foi lido e que ainda não terminou com a newline '\n' está guardado aqui, em line.
 
						  Quando a linha não cabe na totalidade no buffer (ex: BUFFER_SIZE pequeno), line acumula temporáriamente
						  os segmentos já lidos em chamadas anteriores da função join_till_nl, até que se complete uma linha com '\n'. 
						  
						  A string line é a base sobre a qual os novos dados do buffer são adicionados. Isto garante a concatenação
						  correta dos segmentos da linha, mesmo que ela seja muito longa e tenha de ser lida em múltiplas iterações.
	
						  Por que é essencial?

						  O read() pode ler apenas parte de uma linha, especialmente se:

        				  	> A linha no ficheiro for maior que o BUFFER_SIZE,
						    > Ou o \n ainda não tiver sido alcançado.

    					  Assim, line mantém os fragmentos parciais da linha atual entre as leituras, permitindo que ela continue a 
						  ser construída de forma correta.

						  Exemplo:

						  BUFFER_SIZE = 5
						  conteúdo do ficheiro: "Olá mundo\nBoa noite\n"

						  1ª leitura → buffer = "Olá m"  → line = "Olá m"
						  2ª leitura → buffer = "undo\n" → line = "Olá mundo\n" (linha pronta para retornar)

    					  O buffer tem tamanho limitado: só contém uma parte dos dados lidos do ficheiro numa dada iteração.
                          A string line permite juntar essas partes (segmentos) em sequência, até que uma linha completa seja formada.
						  Quando a linha fica completa (porque foi encontrado uma newline, '\n'), a line final é retornada pela
						  função get_next_line.
				
  			> char *buffer: É um bloco temporário de memória (com tamanho fixo BUFFER_SIZE) utilizada para armazenar os novos caracteres 
			                lidos diretamente do ficheiro (fd) através da função read(fd, buffer, BUFFER_SIZE), em blocos com tamanho definido
							por BUFFER_SIZE.
							É uma variável que recebe os próximos caracteres do ficheiro (a partir de onde a leitura parou) e é passada para a
							função join_till_nl, para copiar os dados que acabaram de ser lidos. 
							A função read escreve no buffer os próximos caracteres do ficheiro, começando exatamente onde parou
							na última leitura. 

							Durante a execução da função get_next_line, temos um while que continua enquanto houver dados no buffer 
							ou se o bufer estiver vazio, tentamos ler mais com o read(): while (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0))

    						A cada iteração:

        					> Os dados do buffer são passados para a função join_till_nl.
        					> Essa função percorre os caracteres do buffer até encontrar uma newline '\n' ou o caractere nulo '\0',
							  e junta esses dados à line (a linha em construção).
        					> Se encontrar a newline '\n', a leitura para, e o restante do buffer (o que vem depois do \n) fica intacto 
							  para a próxima chamada.
							
							O buffer atua como um intermediário entre o ficheiro e a linha final que a função get_next_line vai 
							devolver. A função join_till_nl então utiliza este buffer para construir (ou continuar a construir)
							uma linha até que encontre o caractere da newline ('\n') ou o fim (caractere '\0' no buffer). 
							
							O buffer armazena segmentos da linha (ou de múltiplas linhas) para que depois, esses segmentos sejam 
							transferidos para a variável result_line (ou line, dentro da função join_till_nl).

  			> char *new_line: Representa a nova linha alocada, construída a partir da concatenação do conteúdo atual de line
			                  (linha anterior, acumulada até agora) com os novos caracteres do buffer até encontrar uma newline 
							  ('\n') ou o fim da string ('\0').
							  É a nova versão da linha que está a ser construída, que contém tudo o que já foi lido (line) e 
							  tudo o que foi recentemente lido (buffer) até ao primeiro '\n'. 
							  Esta variável garante que temos uma nova string com todo o conteúdo atualizado da linha em construção. 
							  Torna-se a nova versão da line, e a line antiga é libertada com free().
                    		  
  			> line_idx: É o índice utilizado para percorrer a string line original, que contém os caracteres previamente lidos
			            do ficheiro (ou uma string vazia, caso seja a primeira chamada).
						Vai permitir copiar o conteúdo da line antiga para a new_line, caractere a caractere, para
						depois concatenar os caracteres novos do buffer. 
			  
  			> buffer_idx: É o índice utilizado para percorrer o conteúdo do buffer e copiar caractere a caractere
			              para o final da new_line, até encontrar a newline '\n' (ou o caractere nulo '\0'), 
						  garantindo que apenas uma linha é construída a cada chamada à função get_next_line .
						  
						  Lê os novos caracteres armazenados temporariamente no buffer,
						  E junta-os à linha que está a ser construída (new_line),
						  Mas para no primeiro \n (se houver), pois o objetivo da get_next_line é retornar apenas 
						  uma linha por chamada.
						  
						  Comportamento especial:

						  if (buffer[buffer_idx++] == '\n')
						  	  break;

    					  Assim que o \n é encontrado e copiado, o loop interrompe imediatamente, deixando qualquer conteúdo 
						  posterior no buffer para a próxima chamada de get_next_line.

						  Exemplo:

						  buffer = "linha1\nlinha2"
						  → Copia: 'l', 'i', 'n', 'h', 'a', '1', '\n'
						  → Depois para! 'linha2' será processada apenas na próxima chamada.


		2) Alocação de memória para a new_line

		new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
		if (!new_line)
			return (NULL);

		Nesta parte da função join_till_nl, estamos a preparar uma nova string (new_line) que será o resultado da 
		concatenação da string atual line com parte do conteúdo do buffer, até encontrarmos um \n ou o fim.

        Como line é uma string em construção (incompleta) e o buffer contém novos caracteres lidos do ficheiro, 
		precisamos de alocar espaço para os dois conteúdos juntos, mais o espaço para o caractere nulo '\0'.

    	> ft_strlen(line): calcula o comprimento da string line, ou seja, o número de caracteres já acumulados da linha 
		                   que estamos a construir.

		> ft_strlen(buffer): calcula o comprimento total do conteúdo atual do buffer.
							 Mesmo que não se vá usar tudo (por exemplo, se houver uma newline pelo meio), por precaução, 
							 aloca-se espaço para todo o conteúdo.
							 Mais tarde, no loop da cópia, só serão usados os caracteres até \n ou \0.

		Exemplo: 

		line = "Hello, ";
		buffer = "World\nresto do buffer";

    	ft_strlen(line) = 6
    	ft_strlen(buffer) = 21

    	Total a alocar = 6 + 21 + 1 = 28 bytes

		Mesmo que só parte do buffer vá ser usada (até ao \n), o malloc aqui antecipa o pior caso, garantindo que há
		espaço para todos os dados.

		Nota: Mesmo que o buffer seja grande, só uma parte dele será usada. A alocação reserva o espaço
	      	  todo, mas o while só copia até ao \n.

		Esta parte da função:

		Garante que há memória suficiente para juntar line + buffer + \0
		Protege o programa caso malloc falhe
		Prepara o espaço onde será criada a nova linha (new_line) que irá substituir line

		4) Cópia da line para new_line: 

		while (line && line[line_idx] != '\0')
		{
			new_line[line_idx] = line[line_idx];
			line_idx++;
		}
		Este while copia os dados antigos (já lidos anteriormente) da string line para a nova string new_line,
		antes de começarmos a adicionar os novos dados do buffer. Isto é feito para preservar a parte anterior
		da linha que ainda não foi terminada (ou seja, que ainda não contém \n), pois o buffer foi insuficiente
		para concluir a leitura da linha numa chamada anterior.
		A ideia é construir uma nova linha (new_line) contendo: 
		
		> A parte anterior da linha (armazenada em line de chamadas anteriores).
		> A parte nova da linha (vinda do buffer no loop atual).

		Por que copiar line para new_line?

		A função join_till_nl tem o papel de concatenar. Ela junta o que já foi lido (line) com o que foi acabado
		de ler (buffer). No entanto, como as strings em C são imutáveis em tamanho, não podemos simplesmente "aumentar"
		a string line. Precisamos de:

    		> Criar uma nova string maior (new_line);
			> Copiar o conteúdo antigo (line);
			> Juntar os dados novos (buffer).

		line && ... : Verifica se a string line não é NULL.
		              Isto pode acontecer na primeira chamada a join_till_nl, quando ainda ainda não foi lido nada
					  do ficheiro, ou seja, quando ainda não há nenhuma linha construída.
					  Se line for NULL, não há nada para copiar, e o loop não será executado, evitando comportamento 
					  indefinido ao aceder line. 

		Esta verificação ocorre logo no início da função join_till_nl, cuja objetivo é concatenar o conteúdo 
		atual do buffer à string line — a linha que está a ser construída.

		No entanto, há situações em que a line ainda não existe, ou seja, line é NULL. Isto normalmente acontece
		na primeira vez que a get_next_line chama join_till_nl, quando ainda não foi lido nada do ficheiro.
		Esta verificação é responsável por garantir que a line esteja corretamente inicializada para que possamos
		começar a construir a nova linha.

		new_line[line_idx] = line[line_idx]: Copia o caractere atual da line para a new_line na mesma posição.
											 Isto garante que a ordem e o conteúdo da parte previamente lida da linha
											 (em line) seja preservada na nova construção (new_line).
											 A new_line vai sendo construída, posição a posição, até conter a mesma parte 
											 inicial da line.

		Este passo garante que, se a line já tinha dados (parte de uma linha anterior que ainda não terminou), eles não são perdidos.

		Por que este passo é fundamental?

    	  > Evita perda de dados: Se line já contém parte de uma linha anterior (porque a linha era maior que 
		    o BUFFER_SIZE), esses dados precisam de ser preservados.
    	  > Constrói a nova linha de forma segura: Copia com segurança os dados antigos para uma string nova com 
		    espaço suficiente.
    	  > Controla o fluxo de concatenação: Permite que a linha seja montada progressivamente, com dados acumulados
		    em cada chamada à função.
    	  > Evita erros de acesso à memória: Ao verificar se line não é NULL, evita segmentation fault.

		Suponhamos que um ficheiro tem o seguinte conteúdo:

		"Olá, este é um teste\nSegunda linha\n"

		Agora imaginemos que:

    	BUFFER_SIZE = 10 (ou seja, conseguimos ler apenas 10 caracteres por chamada de read)

    	O ficheiro será lido em blocos de 10 caracteres.
		Queremos construir a primeira linha completa: "Olá, este é um teste\n"

		Iteração 1 — Leitura inicial: 
		
		read(fd, buffer, 10) → lê: "Olá, este ".
		Assim, buffer contém "Olá, este ".
		line neste momento é NULL (primeira chamada)
    	Aloca espaço para new_line: strlen(line) é 0 (porque line == NULL)
    								strlen(buffer) é 10
    								→ malloc(11) para new_line

    	Loop de cópia: while (line && line[line_idx] != '\0') // não entra, pois line é NULL

    	Cópia do buffer: new_line = "Olá, este "   // '\n' ainda não apareceu

    	Resultado: return new_line; // contém: "Olá, este "
				   Este valor é atribuído a result_line ou line para a próxima chamada.
		
    	join_till_nl vai construir new_line com o conteúdo do buffer, pois ainda não há \n

		Iteração 2 — Continuação da leitura:

    	read(fd, buffer, 10) → lê: "é um test"
		Assim, buffer contém "é um test"
		line agora contém "Olá, este "
		Vamos criar new_line com tamanho suficiente para armazenar: strlen(line) + strlen(buffer até '\n' ou '\0') + 1
																	=> 10 (de "Olá, este ") + 9 (de "é um test") + 1 = 20

		Agora entra este loop:

		while (line && line[line_idx] != '\0')
		{
			new_line[line_idx] = line[line_idx];
			line_idx++;
		}

		O que ele faz aqui:

    	Copia cada caractere de "Olá, este " da line antiga para a new_line.
		Isto preserva o conteúdo lido na chamada anterior.
		Depois disso, os novos caracteres de buffer são copiados a seguir.

		Resultado após a 2ª iteração: new_line contém: "Olá, este é um test"  (\n ainda não foi encontrado → continuar leitura)
	
		Iteração 3 — Leitura final da linha:

    	read(fd, buffer, 10) → lê: "e\nSegunda"
		Assim, buffer contém "e\nSegunda" → temos finalmente o \n
		line agora contém "Olá, este é um test"

		Vamos alocar new_line com: strlen(line) + número de caracteres até o \n (inclusive) + 1
									=> 19 + 2 + 1 = 22

		Entramos novamente no loop:

		while (line && line[line_idx] != '\0')
		{
			new_line[line_idx] = line[line_idx];
			line_idx++;
		}

		O que acontece:

    	Copia novamente "Olá, este é um test" para a new_line.
		Depois, os dois novos caracteres do buffer são adicionados: "e\n"
    	A leitura termina no \n, como é regra na get_next_line.

		Resultado final de get_next_line nesta chamada: "Olá, este é um teste\n"

		EM SUMA: 

		> A cada chamada de join_till_nl, line acumula os pedaços lidos anteriormente e constrói uma nova string maior.
		> O conteúdo da line antiga é copiado primeiro para essa nova string.
		> Só depois os dados novos do buffer são adicionados.
		> Isso permite acumular e construir a linha progressivamente, mesmo que a BUFFER_SIZE seja pequena.
		> No final, depois de encontrar a '\n', a construção da linha finaliza e temos uma string new_line com todos os 
		  pedaços da linha unidos corretamente.

		5)  Cópia do buffer até ao \n ou \0

		buffer_idx = 0;
		while (buffer[buffer_idx] != '\0')
		{
			new_line[line_idx++] = buffer[buffer_idx];
			if (buffer[buffer_idx++] == '\n')
				break ;
		}
				
		Este loop copia os novos caracteres lidos do ficheiro (armazenados no buffer) para a newline que está a ser
		construída, até encontrar '\n' ou chegar ao fim do buffer '\0'. Ou seja, copiamos o conteúdo do buffer até
		encontrarmos o caractere '\n' (que representa o fim de uma linha de texto). 
		Isto permite construir a linha completa lida do ficheiro sem ultrapassar o final da linha.

		Quando encontramos \n, saímos do loop imediatamente.

		Porquê? A função get_next_line deve retornar uma linha completa de cada vez.
				Ao encontrar \n, significa que já temos uma linha completa.
				Portanto, não devemos continuar a copiar mais caracteres do buffer nesta chamada.
				Se não encontrarmos \n, o loop continua até ao fim do buffer.

		7) Termina a nova string com \0

		new_line[line_idx] = '\0';

    	Coloca o caractere nulo no fim da new_line, para garantir que é uma string válida em C.

		8)  Liberta a antiga line

		free(line);

    	A line anterior já foi copiada para new_line, por isso pode ser libertada para evitar leaks
		de memória.

		

  	1.5 )
	
	while (buffer[read_idx] != '\0')
	{
		if (newl)
			buffer[write_idx++] = buffer[read_idx];
		if (buffer[read_idx] == '\n')
			newl = 1;
		buffer[read_idx++] = '\0';
	}

	Este loop tem o objetivo de gerir o conteúdo remanescente no buffer após termos copiado os caractere até à \n
	(ou até ao fim da string) para a result_line. 

	Por outras palavras:

    > Ele limpa o buffer à medida que processa os caracteres.
    > Ele preserva os dados que aparecem após o \n, porque esses serão necessários para a próxima chamada de 
	  get_next_line.
    > Ele remove os dados que já foram processados, substituindo por \0.
   
	
	> if (newl): O newl serve como um sinalizador: foi encontrado um \n?

    Antes do \n: newl == 0, então não entra neste if.
				 Nenhum caractere é preservado.

    Depois do \n: newl == 1, então preservamos todos os caracteres seguintes, copiando-os para o início do buffer, 
	              através de write_idx.
                  Isto move os dados restantes (após o \n) para o início do buffer, permitindo que estejam prontos 
				  para a próxima chamada a get_next_line.

	> buffer[write_idx++] = buffer[read_idx]: Quando estamos após o \n (newl == 1) copiamos o caractere atual de 
	                                          read_idx para a posição write_idx e depois, incrementamos write_idx.
											  Ou seja, estamos a reutilizar o buffer, deslocando para a frente apenas
											  os caracteres que ainda não foram usados.
	> if (buffer[read_idx] == '\n'): Aqui verificamos se o caractere atual é um \n.
									 Se for, atualizamos newl para 1.
									 A partir deste ponto, o if (newl) passará a ser verdadeiro, e os caracteres seguintes 
									 serão preservados.
	> buffer[read_idx++] = '\0': Esta é uma ação de limpeza: estamos a esvaziar o conteúdo processado do buffer.
								 O caractere atual em read_idx é substituído por \0, que em C marca o fim de uma string.



EXEMPLO PRÁTICO MUITO DETALHADO: 

Conteúdo do ficheiro: "Primeira linha\nSegunda linha\nTerceira"

Definições: BUFFER_SIZE = 8
            Chamaremos get_next_line(fd) várias vezes.

1ª CHAMADA: get_next_line(fd)
 
  > Etapa 1: inicialização

	static char buffer[BUFFER_SIZE + 1]; // todos os bytes estão com '\0'
	char *result_line = NULL;
	int newl = 0;

  > Etapa 2: buffer[0] == '\0', então faz-se leitura: read(fd, buffer, 8);

	Dados lidos: "Primeira" (8 caracteres)
	buffer = ['P','r','i','m','e','i','r','a']
	Ainda não lemos o \n.

  > Etapa 3: join_till_nl(NULL, buffer)

    Vai copiar até \0 ou \n (mas não há \n)
    Copia: "Primeira"
    Aloca: result_line = "Primeira"

  > Etapa 4: processar e preservar o buffer

	read_idx = 0;
	write_idx = 0;

	Como não há \n, nenhuma parte do buffer é preservada. Todos os caracteres são esvaziados:

	while (buffer[read_idx] != '\0')
	{
    	if (newl) // false
        	buffer[write_idx++] = buffer[read_idx];
    	if (buffer[read_idx] == '\n') // nunca acontece
        	newl = 1;
    	buffer[read_idx++] = '\0'; // apaga cada caracter
	}

	buffer agora: ['\0','\0','\0','\0','\0','\0','\0','\0','\0']
	
	Novo loop: read(fd, buffer, 8)
	Próximo trecho: " linha\nS"
	buffer = [' ','l','i','n','h','a','\n','S']

  > join_till_nl("Primeira", buffer)

	Vai copiar até \n: Encontra espaço + "linha\n" → total de " linha\n"
	Concatena com "Primeira": result_line = "Primeira linha\n"

  > Processamento para preservar o buffer

	read_idx	buffer[read_idx]	Ação		write_idx
		0				' '			 -	        	-
		1				'l'			 -	        	-
		2				'i'	         -	        	-
		3				'n'			 -				-
		4				'h'			 -				-
		5				'a'			 -				-
		6				'\n'		newl = 1		-
		7				'S'	 guardado → buffer[0]	1


Novo estado do buffer: buffer = ['S','\0','\0','\0','\0','\0','\0','\0','\0']

Resultado da primeira chamada: return ("Primeira linha\n");

2ª CHAMADA: get_next_line(fd)

  > buffer[0] == 'S' → entra no loop
  > join_till_nl(NULL, buffer)
    Copia "S" até \0 (não tem \n)
    result_line = "S"

  > processa e esvazia buffer (sem preservar nada)

    buffer = ['\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0']

  > Lê mais 8 caracteres
	Dados: "egunda l"
	buffer = ['e','g','u','n','d','a',' ','l']

  > join_till_nl("S", buffer)
    Copia "egunda l"
    Resulta em "Segunda l"

  > Apaga buffer (não há \n):
	buffer = ['\0',...]

  > Lê mais 8 caracteres
	Dados: "inha\nTer"
	buffer = ['i','n','h','a','\n','T','e','r']

  > join_till_nl("Segunda l", buffer)
    Copia até \n: "inha\n"
    Final: "Segunda linha\n"

  > Preserva o que vem após \n: "Ter"
    buffer = ['T','e','r','\0','\0','\0','\0','\0']

  > Retorno da segunda chamada: return ("Segunda linha\n");

3ª CHAMADA

  > buffer contém "Ter"

  > join_till_nl(NULL, buffer) → "Ter"

    read() retorna 0 → fim do ficheiro

    result_line = "Terceira"

Retorno da terceira chamada: return ("Terceira");

4ª CHAMADA

    buffer[0] == '\0' e read() == 0

    Retorna NULL





	    


									 




*/