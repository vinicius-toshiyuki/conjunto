# C-Onjunto

Uma linguagem derivada da linguagem C com suporte a conjuntos.

## Dependências

- `flex`
- `bison`
- `gcc`
- `make`

```bash
sudo apt install gcc
sudo apt install make
sudo apt install flex
sudo apt install bison
```

## Executando

```bash
make
./a.out test/subset_sum1.conj
```

## TODO

- [*] Àrvore de contexto / tabela de símbolos
- [ ] Arrumar a documentação
- [ ] Não alocar a mesma coisa um zilhão de vezes
- [ ] Ver a compilação antes de ter rodado o flex
- [ ] Ver o cmake
