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

Podem ser passadas as macros `PARSER_UNICODE_SUPPORT` e
`PARSER_TRUE_COLOR_SUPPORT` para o `make` com `CFLAGS="-D PARSER_XXX_SUPPORT"`
para habilitar a impressão das árvores com caracteres Unicode e a impressão com
cores de 24 bits, respectivamente, se o seu terminal suportar.

## TODO

- [x] Àrvore de contexto / tabela de símbolos
- [ ] Arrumar a documentação
- [ ] Não alocar a mesma coisa um zilhão de vezes
