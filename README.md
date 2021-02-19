# C-Onjunto
Uma linguagem derivada da linguagem C com suporte a conjuntos.

## Dependências

*flex*

```
sudo apt install flex
```

## Executando

```
flex sintaxe.l
gcc lex.yy.c -o lexer -lfl
cat subset_sum.conj | ./lexer
```

## TODO

[ ] expressão vazia no for
