# Métodos Numéricos II (CK0048)

Projetos da disciplina de Métodos Numéricos II (CK0048) da UFC.

## Dependências

É necessário utilizar alguma distribuição Linux como sistema operacional e ter o programa [make](https://www.gnu.org/software/make/) instalado para compilar o código. Além disso, é necessário ter instalado a biblioteca [OpenCV](https://opencv.org/) para utilizar os headers de processamento de imagens.

## Build

Para compilar o código, basta utilizar o comando **make** na pasta raíz do projeto indicando o arquivo que contém a função main, como no exemplo a seguir:
```console
make MAIN="src/arquivo.cpp"
```
Se não for indicado o arquivo com a função main, o make irá procurar pelo arquivo padrão "src/main.cpp".
**Obs.:** O arquivo contendo a função main **deve** estar dentro da pasta "src/".

É possível compilar os arquivos de forma concorrente utilizando o comando **make -j** (**make -j4** para compilar 4 arquivos por vez), como no exemplo a seguir:
```console
make MAIN="src/arquivo.cpp" -j4
```

## Executando

Para executar o código compilado, basta executar o seguinte comando na pasta raíz do projeto:
```console
./main
```
**Obs.:** Independente do nome arquivo usado como main, o executável **sempre** será gerado com o nome "main".