# criptografia-simetrica-com-hash
Garantia de identidade usando criptografia simétrica com Hash. Exemplo didático feito na disciplina de Auditoria de SI.

Esse código simula uma comunicação entre 2 clientes, onde o primeiro cliente gera o hash da mensagem a ser enviada e depois criptografa o Hash com uma chave simétrica, para que seja garantida a identificação do cliente A. Quando cliente B recebe a mensagem + hash criptografado, ele descriptografa o Hash e compara com o hash gerado da mensagem.

Para executar os códigos compilados, basta abrir o terminal linux e digitar "./exec1". Observe as saídas do terminal. Após isso, execute o cliente 2, com o comando "./exec2" no terminal.
    ./exec1
    ./exec2

Os códigos sem compilar são os arquivos "cliente1.c" e "cliente2.c". Caso queira compilar novamente, é só usar os seguintes comando:
    gcc -o exec1 cliente1.c
    gcc -o exec2 cliente2.c
