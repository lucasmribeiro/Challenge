# Challenge
Desafio de programação para seleção no LIS

Para a resolução do desafio, primeiramente foi identificado como funciona o processo de criptografia e descriptografia da mensagem. Após isso, seguindo a ideia do algoritmo da cifra de Cesar foram definidos os métodos de criptografar e descriptografar mensagens. Finalizado esta etapa foi verificado todos os valores possíveis de chave e encontrado qual é a que decodifica a mensagem corretamente. 
No entanto, esta verificação da mensagem era manual, o não é o esperado. Desta forma, foi elaborado um algoritmo para checar a autenticidade da mensagem lida é válida, mais especificamente se os conceitos da mensagem são válidos. Com base nisso utilizando do arquivo Dictionary.txt foi verificado se cada palavra contida na mensagem era legítima. Então ao calcular quantas palavras são válidas por mensagem, foi possível definir a que tem maior incidência de palavras.   

# How it's works

O programa faz a leitura de um arquivo txt que contém a mensagem criptograda e a decodifica utilizando todas as chaves possíveis. Então ele analisa a veracidade das mensagens decodificadas e elege a chave que tem maior acertividade de palavras e indica a chave e a mensagem.

# Requirements
- CodeBlocks com MinGW

# How to use

- Abrir o projeto Challenge.cbp no CodeBlocks.
- No menu Project selecionar Set programs'arguments...
- Na caixa de texto Program arguments informar: './SecretMessage.txt'
- Compilar e executar o programa.

# References

- [Wikipedia](https://pt.wikipedia.org/wiki/Cifra_de_C%C3%A9sar)
- [Dictionary](https://github.com/dwyl/english-words/blob/master/words_alpha.txt)