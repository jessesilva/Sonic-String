# Sonic String

Simple library for manipulating text.
- Autor: Constantine / jessesilvabr1994@gmail.com


### Reference...

- Language: Portuguese Brazilian
- Nome: Sonic String
- Descrição: Pequeno conjunto de funções para manipulação de texto.
- Data: 27 de setembro de 2014
- Autor: Constantine / jessesilvabr1994@gmail.com


###Sumário
- 0x00 - value
- 0x01 - string
- 0x02 - length
- 0x03 - concat
- 0x04 - compare
- 0x05 - search
- 0x06 - tolower
- 0x07 - toupper
- 0x08 - position
- 0x09 - is_char
- 0x10 - is_numeric
- 0x11 - revert
- 0x12 - delete
- 0x13 - zero
- 0x14 - error


### 0x00 - value
- Função responsável por setar novo valor da string.

		Protótipo:
		 unsigned char * this.value (this, "Olá mundo!");
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x01 - string
- Função responsável por retornar a string atual.

		Protótipo:
		 unsigned char * this.string (this);
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x02 - length
- Função responsável por retornar tamanho da string atual.

		Protótipo:
		 unsigned int this.length (this);
		 
		Retorno: Tamanho da string atual.

		
### 0x03 - concat
- Função responsável por concatenar texto ao final da string atual.

		Protótipo:
		 unsigned char * this.concat (this, "Texto que será concatenado ao final da string atual");
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x04 - compare
- Função responsável por comparar se duas strings são identicas.

		Protótipo:
		 unsigned int this.comparar (this, "String a ser comparada com a string atual");
		 
		Retorno: SS_EQUAL se strings forem iguais e SS_NOT_EQUAL caso contrário.


### 0x05 - search
- Função responsável por buscar determinada string dentro da string atual.

		Protótipo:
		 unsigned char * this.search (this, "string a ser procurada");
		 
		Retorno: Ponteiro para inicio da string se for encontrada e NULL caso contrário.

		
### 0x06 - tolower
- Função responsável por converter todos os caracteres da string atual para minúsculo.
		
		Protótipo:
		 unsigned char * this.tolower (this);
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x07 - toupper
- Função responsável por converter todos os caracteres da string atual para maiúsculo.
		
		Protótipo:
		 unsigned char * this.toupper (this);
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x08 - position
- Função responsável por retornar posição da primeira ocorrência do delimitador encontrado na string atual.
		
		Protótipo:
		 unsigned int this.position (this, "delimitador");
		 
		Retorno: Posição na string atual em que o delimitador foi encontrado.

		
### 0x09 - is_char
- Função responsável por verificar se caracter é uma consoante ou vogal.
		
		Protótipo:
		 unsigned int this.is_char (this, 'a');
		 
		Retorno: TRUE se for consoante  ou vogal e FALSE caso contrário.

		
### 0x10 - is_numeric
- Função responsável por verificar se caracter é um número decimal.
		
		Protótipo:
		 unsigned int this.is_numeric (this, '1');
		 
		Retorno: TRUE se for número decimal e FALSE caso contrário.

		
### 0x11 - revert
- Função responsável por inverter ordem dos caracteres da string atual.
		
		Protótipo:
		 unsigned int this.revert (this);
		 
		Retorno: Ponteiro para inicio da string.

		
### 0x12 - delete
- Função responsável por deletar string da memória.
		
		Protótipo:
		 void this.delete (this);
		 
		Retorno: Sem retorno.

		
### 0x13 - zero
- Função responsável por setar todos os caracteres da string atual para '\0'.
		
		Protótipo:
		 void this.zero (this);
		 
		Retorno: Sem retorno.

		
### 0x14 - error
- Função responsável por retornar último código de erro.
		
		Protótipo:
		 unsigned int this.error (this);
		 
		Retorno: Valor do último código de erro.

		
