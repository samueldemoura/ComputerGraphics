# Trabalho Individual I
![Triangles](/images/triangle.png)

## Introdução
A atividade proposta requer a implementação de 3 funções: PutPixel, DrawLine e DrawTriangle. Todas elas devem ser implementadas manuseando somente os bytes RGBA de uma textura que será mapeada na janela do programa.

## PutPixel
A função mais trivial de ser implementada. Recebe uma coordenada X, uma coordenada Y e um objeto da classe color, que por sua vez contem 4 ints representando os valores R, G, B e A desejados.

A implementação é bastante simples: para cada unidade da coordenada x, devemos andar 4x para encontrar o endereço de memória do proximo pixel. E para cada unidade da coordenada y, devemos andar IMAGE_WIDTH*4*y já que as linhas estão dispostas uma após a outra na memória.

## DrawLine
A função mais complexa a ser implementada neste trabalho. Ela utiliza o algoritmo de Bresenham, com algumas alterações para funcionar em todos os 8 octantes e interpolar as cores iniciais e finais da linha.

Primeiro, a função determina a qual dos 8 octantes a linha de entrada pertence. Os pontos da linha são então jogados para o primeiro quadrante, e começamos o algoritmo de Bresenham. A cada iteração do laço, as coordenadas geradas pelo algoritmo são então devolvidas ao seus quadrantes originais e passadas para dentro da função PutPixel.

A interpolação de cor acontece de forma relativamente simples: primeiro calculamos o tamanho total da linha. Em seguida, encontramos a variação entre as cores finais e iniciais para cada componente RGBA. Essa variação agora é dividida pelo tamanho total calculado previamente, o que nos dá um número que representa a variação de cor que deve acontecer a cada vez que nos afastamos do ponto inicial. Finalmente, ao desenhar o pixel, pegamos a cor inicial e acrescentamos: esse valor númerico vezes a quantidade de pixels que já andamos no algoritmo.

## DrawTriangle
Também uma função trivial de ser implementada. Recebe 3 cores e 6 coordenadas, representando 3 vértices. Assim, basta chamar a função DrawLine para desenhar linhas do ponto A ao B, B ao C e C ao A. Como a própria DrawLine já faz a interpolação de cores, basta repassar as 3 cores recebidas que o triângulo será desenhado com a interpolação entre as cores dos vértices.

## Conclusão
