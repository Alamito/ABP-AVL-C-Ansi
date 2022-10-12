# 🌳 Árvores Binárias de Pesquisa (ABP & AVL) 🌳
[![NPM](https://img.shields.io/github/license/Alamito/ABP-AVL-C-Ansi)](https://github.com/Alamito/ABP-AVL-C-Ansi/blob/main/LICENCE)
# Sobre o projeto
Este projeto consiste na implementação de árvores binárias de pesquisas na linguagem C Ansi, no qual foi avaliada na disciplina de Estrutura de Dados do Curso de Engenharia da Computação pela UFRGS.
  
Foram implementadas duas árvores: Árvore Binária de Pesquisa (ABP) e Árvore Binária de Busca Balanceada (AVL), onde os códigos podem ser visualizados nos arquivos main_ABP.c e main_AVL.c, respectivamente. A partir disso, o objetivo do projeto visa auxiliar de maneira ficcional uma Nutricionista no controle da dieta de seus clientes. Assim, são armazenados alimentos e suas calorias na árvore, dessa forma anotando o alimento e a quantidade ingerida dele, podemos fazer uma busca binária na árvore e contar quantas calorias foram ingeridas de acordo com os alimentos buscados.

No final, são gerados arquivos texto informando as características da árvore junto com os alimentos buscados.

# Apresentação do projeto
Executando o código main_ABP.exe com os arquivos 1K.csv e day1.csv, no qual o primeiro é referente a lista de alimentos e o segundo é sobre os alimentos ingeridos, é gerado o seguinte arquivo texto.

![abp](https://user-images.githubusercontent.com/102616676/194928208-1fdb176c-b0f6-477c-bd8d-8cc7fcca9efa.png)

Além disso, é informado no prompt de comando informações sobre tempo de execução.

![abp_tempo](https://user-images.githubusercontent.com/102616676/194932731-ad5a266c-6556-4cca-9282-334e28e3fc5f.png)


Utilizando main_AVL.exe com os mesmos arquivos anteriores, temos:

![avl](https://user-images.githubusercontent.com/102616676/194929279-bf1c4621-9354-421f-ba9c-167689860397.png)


![avl_tempo](https://user-images.githubusercontent.com/102616676/194929049-1c3550f6-583e-4525-ac76-020ca373b14f.png)

# Tecnologias Utilizadas
- C Ansi

# Como executar o projeto
```bash
# clonar repositório
git clone https://github.com/Alamito/ABP-AVL-C-Ansi.git

# executar
main_ABP.exe 1K.csv day1.csv <nome de saída>.txt
main_AVL.exe 1K.csv day1.csv <nome de saída>.txt
```
Os arquivos .csv podem ser trocados por outros, desde que sigam o seguinte padrão:

"nome do alimento";"quantidade de caloria por grama" para o arquivo com os alimentos que serão armazenados na árvore.
  
"nome do alimento";"quantidade de gramas ingeridas" para o arquivo com os alimentos que foram ingeridos.

Note que a separação do texto com o número acontece através de um token ; (ponto e vírgula).

Exemplo do arquivo 1K.csv, que contém 1000 alimentos.

![1k](https://user-images.githubusercontent.com/102616676/194931884-ac55ad66-5b1b-4f05-bb5a-723248316fb1.png)

# Autores: 
Alamir Bobroski Filho 
- www.linkedin.com/in/alamirdev

Galeano Folle Domingues 
