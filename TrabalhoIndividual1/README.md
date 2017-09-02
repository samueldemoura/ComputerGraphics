# Trabalho Individual I
![Triangles](/TrabalhoIndividual1/images/triangle.png)

## Introdução
A atividade proposta requer a implementação de 3 funções: PutPixel, DrawLine e DrawTriangle. Todas elas devem ser implementadas manuseando somente os bytes RGBA de uma textura que será mapeada na janela do programa.

## PutPixel
A função mais trivial de ser implementada. Recebe uma coordenada X, uma coordenada Y e um objeto da classe color, que por sua vez contem 4 ints representando os valores R, G, B e A desejados.

A implementação é bastante simples: para cada unidade da coordenada x, devemos andar 4x para encontrar o endereço de memória do proximo pixel. E para cada unidade da coordenada y, devemos andar IMAGE_WIDTH*4*y já que as linhas estão dispostas uma após a outra na memória.

## DrawLine
![Line](/TrabalhoIndividual1/images/line.png)
```c++
DrawLine(vect2d(IMAGE_WIDTH / 3, IMAGE_HEIGHT * 2/3),
		 vect2d(IMAGE_WIDTH * 2/3, IMAGE_HEIGHT / 3),
		 color(255, 0, 0, 255),
		 color(110, 110, 255, 255)
		);
```

A função mais trabalhosa de ser implementada neste trabalho. Ela utiliza o algoritmo de Bresenham, com algumas alterações para funcionar em todos os 8 octantes e interpolar entre as cores iniciais e finais da linha.

Primeiro, a função determina a qual dos 8 octantes a linha de entrada pertence. Os pontos da linha são então jogados para o primeiro quadrante, e começamos o algoritmo de Bresenham. A cada iteração do laço, as coordenadas geradas pelo algoritmo são então devolvidas ao seus quadrantes originais e passadas para dentro da função PutPixel.

## Obs: Interpolação de cores
![Interpolation](/TrabalhoIndividual1/images/interp.png)
```c++
for (int i = 0; i < IMAGE_HEIGHT; ++i)
{
	DrawLine(vect2d(0, i),
			 vect2d(IMAGE_WIDTH, i),
			 color( (float)i * 255/512, 255 - (float)i * 255/512, 100 + i/512, 255 ),
			 color( 0, (float)i * 255/512, 255 - (float)i * 255/512, 255));
}
```

O algoritmo inicial acontece da seguinte forma: Encontramos a variação entre as cores finais e iniciais para cada componente RGBA. Essa variação agora é dividida pela quantidade de pixels que vamos desenhar (representada por dx), o que nos dá um número representante da variação de cor que deve acontecer a cada iteração. Finalmente, ao desenhar o pixel, pegamos a cor prévia e acrescentamos esse valor.

## DrawTriangle
![Triangles](/TrabalhoIndividual1/images/triangle.png)
```c++
for (int padding = IMAGE_HEIGHT/4; padding < IMAGE_HEIGHT/2; padding += 4)
{
	DrawTriangle(vect2d(padding, IMAGE_HEIGHT - padding),
				 vect2d(IMAGE_WIDTH / 2, padding),
				 vect2d(IMAGE_WIDTH - padding, IMAGE_HEIGHT - padding),
				 color(255, 0, 0, 255),
				 color(0, 255, 0, 255),
				 color(0, 0, 255, 255));
}
```

Também uma função trivial de ser implementada. Recebe 3 cores e 6 coordenadas, representando 3 vértices. Assim, basta chamar a função DrawLine para desenhar linhas do ponto A ao B, B ao C e C ao A. Como a própria DrawLine já faz a interpolação de cores, basta repassar as 3 cores recebidas que o triângulo será desenhado com a interpolação entre as cores dos vértices.

## Conclusão
Todas as funções apresentadas na proposta do projeto foram implementadas com a funcionalidade adequada. Ainda assim, foi possível fazer algumas alterações:
- O algoritmo de interpolação de cores ainda é razoavelmente ineficiente, mas foi possível melhorar-lo. Inicialmente, os valores RGBA eram guardados em ints, logo não era possível acrescentar valores decimais a eles. Assim, para cada pixel a ser desenhado durante o algoritmo de Bresenham, era preciso calcular partindo da cor inicial, pegando quantos pixels já foram andados e finalmente multiplicando com o valor que representa a variação de cor que deve acontecer por pixel.
Ao armazenar os valores de RGBA em floats, tornou-se possível simplesmente começar com a cor inicial e acrescentar a variação de cor em cada iteração do laço.
- Ainda falando sobre o algoritmo de interpolação de cores: seria possível deixar-lô com uma aparência mais natural. Como visto nas imagens anteriores, as cores aparentam escurecer/esclarecer e desbotar durante a interpolação. Isso pode ser resolvido se, antes de passar pelo algoritmo, as cores fossem convertidas para o espaço de cor HSV, interpoladas e depois convertidas de volta para RGB para desenhar na tela. Isso acontece pois o espaço HSV tem elementos separados para cor, saturação e luminosidade, permitindo a alteração de cada um de forma individual.
- Para generalizar o algoritmo de Bresenham, determinamos a qual octante a linha pertence, transformamos ela em uma linha do primeiro octante, rodamos uma iteração do algoritmo, convertemos a saída do algoritmo de volta para o octante original e finalmente a desenhamos na tela. Inicialmente, a checagem do octante ocorria através de 8 ifs com 3 condições cada. Foi possível re-estruturar de forma que a checagem precisa passar somente por 3 ifs de condição única.
Além disso, no final de cada iteração a função entrava em um switch-case para armazenar as coordenadas x,y em duas novas variáveis com as devidas alterações de maneira que a linha fosse desenhada no octante correto. Foi possível remanejar o código para que a função PutPixel fosse chamada diretamente dentro dos cases do switch-case, com as devidas inversões já feitas, evitando declarar duas novas variáveis.