# C-Onjunto
Uma linguagem derivada da linguagem C com suporte a conjuntos.

## Dependências

- flex
- gcc

```
sudo apt install flex
```

## Executando

```
flex sintaxe.l
gcc lex.yy.c -lfl
./a.out subset_sum1.conj
```
