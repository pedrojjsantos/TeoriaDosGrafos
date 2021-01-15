# TeoriaDosGrafos

Todos os algorítimos recebem grafos com peso não-direcionados
com exceção do *topological_sort* que recebe um digrafo com peso.

A entrada para os códigos devem ser da seguinte forma:
- Na primeira linha:
  >N M

	  Onde N é a quantidade vértices e M é a quantidade de arestas.
- Seguida de M linhas, cada uma com uma aresta do formato:
  > V U W
	
	  onde V e U (numerados a partir de 0) são os extremos da aresta VU com peso W

Ps. para grafos não-direcionados se foi adicionado a aresta VU não se deve adicionar a aresta UV
