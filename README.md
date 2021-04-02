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

## TODO

- [x] Árvore de contexto / tabela de símbolos
- [ ] Arrumar a documentação
- [ ] Não alocar a mesma coisa um milhão de vezes
- [ ] Parar de imprimir o erro quebrado
- [x] Passas os negócios para o configure
- [ ] Arrumar as referências
- [ ] Arrumar a gramática
