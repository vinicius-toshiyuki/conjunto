# C-Onjunto

Uma linguagem derivada da linguagem C com suporte a conjuntos.

## Dependências

- `flex`
- `bison`
- `gcc`
- `make`
- `autoreconf`

```bash
sudo apt install flex bison gcc make autoconf
```

## Executando

```bash
autoreconf --install
./configure
make
./src/parser test/subset_sum1.conj
```

O `./configure` aceita as opções `--with-unicode` e `--with-truecolor`
que habilitam a impressão das árvores com caracteres Unicode e a impressão com
cores de 24 bits, respectivamente, se o seu terminal suportar.

`src/parser` aceita as opções `-C` e `-S` para inibir a impressão da árvore de
contexto e árvore sintática abstrata, respectivamente, e a opção `-h` e
deve receber o nome de um arquivo para ser usado como entrada.

## TODO

- [x] Árvore de contexto / tabela de símbolos
- [x] Arrumar a documentação
- [x] Não alocar a mesma coisa um milhão de vezes
- [x] Parar de imprimir o erro quebrado
- [x] Usar yyerror() no léxico também
- [ ] Mudar o YYLTYPE
- [x] Passas os negócios para o configure
- [x] Arrumar as referências
- [x] Arrumar a gramática
- [x] Avaliar uma expressão (tipo, depois valor?)
- [ ] Parar de criar tags no léxico
- [x] Para de usar o yyerror()
- [ ] Tratar in-expression
- [ ] Mudar os caracteres unicode para os códigos
- [ ] Usar wchar?
- [ ] Ver redefinições de funções
- [ ] Ver se chamadas de funções são para funções
