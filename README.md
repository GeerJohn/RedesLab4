# Redes y Sistemas Distribuidos - 2022

# Laboratorio 4: Capa de red

### Autores: 

- **German John (germanjohn13@outlook.es)**


### Introducción

Tenemos un modelo de anillos de 8 nodos, cada uno con dos interfaces de comunicación full-duplex con dos posibles vecinos.
La estructura interna de cada nodo cuenta con dos capas de enlace (lnk, una con cada vecino), una capa de red (net) y una capa de aplicación (app). La capa de aplicación y la capa de enlace implementan generadores de tráfico y buffers respectivamente.
Cada paquete que reciben los nodos son evaluados para determinar si el nodo local es el destino final del mismo. En caso de que lo sea, el paquete es enviado a la capa de aplicación local. En caso de que el paquete esté destinado a otro nodo se elige una interface para re-transmitirlo.
Dividiremos en dos partes el informe, una **Parte 1** sobre Análisis de datos y una **Parte 2** sobre Diseño de Algoritmo de enrutamiento. Teniendo en cuanta dos casos, **Caso 1** y **Caso 2**. 


### Capa de red

**Propósito de la capa de red:**

- Llevar paquetes de un host de origen a uno de destino siguiendo una ruta conveniente.

**Asuntos de los que se encarga la capa de red:**

- o Almacenamiento y reenvío
- o Enrutamiento
- o Control de congestión
- o Conectar redes de distintas tecnologías
- o Fragmentación

### Modelo de Anillo

![ScreenShot](/Parte I/img/Caso 1/modeloAnillo.png)

### Metodologia de trabajo

Usamos simulación discreta por eventos, que es una tecnica informática de modelado dinamico de sistemas. Permite un control en la variable del tiempo que permite avanzar sobre este en función de la planificación de ocurrencia de ciertos eventos a un tiempo futuro, que se organizan en forma de cola. Estos eventos van a ir organizando una cronología sobre qué es lo que va a ir ocurriendo a lo largo de la simulación, y suceden en momentos discretos de tiempo. 
Un requisito para aplicar esta técnica es que las variables que definen el sistema no cambien su comportamiento durante el intervalo simulado, tal com ose espera para los dos casos planteados más adelante.


# Parte 1: Análisis de datos

## Metricas Particulares

Usamos metricas para la cantidad de paquetes en el buffer de cada enlace (lkn), el delay(seg) en llegar los paquetes al nodo destino, cantidad de saltos del paquete, promedio del delay y cantidad de paquetes entregados al nodo destino. 

## Caso de estudio 1

 - **Nodos Generadores:** Nodo 0 y Nodo 2.
 
 - **Destino:** Nodo 5
 
 - **Datarate entre nodos:** 1Mbps bidireccional

Cada uno de los nodos generadores, van entregando paquetes a la capa de red con el mismo intervalo de generacion (exponential(1)), y los paquetes siempre se envian hacia los demas nodos por el link 0 en sentido horario hasta el nodo destino.

**Nodo 0**

En este grafico podemos ver como se comporta el buffer del Nodo[0]

![ScreenShot](/Parte I/img/Caso 1/bufNodo0.png)

Es uno de los nodos de origen, gracias al modelo duplex, recibe paquetes de su capa de aplicación y paquetes producidos por el nodo 2, que pasan por el nodo 1 primero. Debido a esto, vemos que se genera congestión y el buffer de lkn[0] termina muy lleno.

- **Paquetes en buffer congestionados: 188

**Delay Nodo 5**

![ScreenShot](/Parte I/img/Caso 1/delayNode5.png)

Ahora vemos que la demora de cada paquete en llegar al nodo 5 es cada mas grande, por culpa de la congestión que se genera en el nodo 0.

**Nodo 1, 6 y 7**

![ScreenShot](/Parte I/img/Caso 1/bufNodo1.png)

Los bufferes para estos tres nodos estarán siempre oscilando entre 0 y 1, ya que la velocidad con que los reciben y despachan es constante e igual para los tres.

**Nodo 2**

![ScreenShot](/Parte I/img/Caso 1/bufNodo2.png)

En el nodo 2 vemos que hay cambios constantes en el buffer, eso es porque la generación de paquetes que tiene la capa de aplicación es exponencial y la velocidad de envio a otros nodos es constante.

![ScreenShot](/Parte I/img/Caso 1/avgDelay-NumberofPacketsNode5.png)

- Acá mostramos el promedio del delay de llegadas de paquetes al destino: 51,16.
- Y la cantidad de paquetes que llegaron: 196.

**Saltos**

![ScreenShot](/Parte I/img/Caso 1/hopsNode5.png)

- En este gráfico podemos ver la cantidad de saltos que hacen los paquetes hasta que llegan al nodo destino, estos oscilan entre 3 y 5. Esto se debe a que los nodos generadores son el 2 y 0, entonces del nodo 2 al 5 tenemos 5 saltos y del nodo 0 al 5 tenemos 3 saltos.

## Preguntas interesantes

- #  ¿Cómo es el uso de los recursos de la red?

Por lo que vimos en las metricas obtenidas anteriormente, el nodo 3 y 4 no aparecen, y eso es porque no se estan usando. Por lo que hay un desperdicio de los recursos de la red. 

- #  ¿Se puede mejorar?

Sí, cambiando el algoritmo de enrutamiento por uno que busque el camino mas corto. Es una de las opciones para mejorar el uso de los recursos de la red.
Otra opción es que elijan la salida al azar por donde mandar los datos.  

## Caso de estudio 2

 - **Nodos Generadores:** Nodo {0,1,2,3,4,6,7}.
 
 - **Destino:** Nodo 5
 
 - **Datarate entre nodos:** 1Mbps bidireccional

En este caso, todas las capas de aplicacion de los nodos generan paquetes. Se utiliza el mismo intervalo de generacion exponential(1).

- **Nodos 0, 1, 2, 3, 6 y 7**

![ScreenShot](/Parte I/img/Caso 2/bufNodos.png)

Ahora ocurren problemas de congestión en todos los nodos, de igual manera que ocurria con el Nodo 0. El unico que no sufre de tanta congestión es el Nodo 4 ya que por mas que tambien genere, no recibe paquetes (el nodo anterior es el destino).

![ScreenShot](/Parte I/img/Caso 2/bufNodo4.png)

- **Delay Nodo 5**

![ScreenShot](/Parte I/img/Caso 2/delayNode5.png)

El delay crece constantemente, en este caso son 200s pero en una simulacion con tiempo mayor, el delay no dejaria de crecer.

![ScreenShot](/Parte I/img/Caso 2/avgDelayNode5.png)

- El promedio del delay de llegadas de paquetes al destino ahora es de: 36,37.
- Y la cantidad de paquetes que llegaron: 381.

**Saltos**

![ScreenShot](/Parte I/img/Caso 2/hopsNode5.png)

Ahora los paquetes pueden hacer como minimo 1 salto y maximo 7, 7 saltos hace cuando el paquete se genera en el nodo 4. 

## Pregunta interesante

### ¿A partir de qué valor de interArrivalTime se puede garantizar un equilibrio o estabilidad en la red?

Buscando la respuesta a la pregunta, nos encontramos que con **interArrivalTime** = 7.2, ya se genera un equilibrio en la red.

- **Nodos 0, 1, 2, 3 y 4**

![ScreenShot](/Parte I/img/interArrivalTime7/bufNodos.png)

Ahora vemos que los nodos 0, 1, 2, 3 y 4 no crecen constantemente, si no que se mantienen entre 0 y 1 la mayor parte del tiempo.

- **Nodos 6 y 7**

![ScreenShot](/Parte I/img/interArrivalTime7/bufNodos67.png)

Los nodos 6 y 7 crecen un poco pero no tanto como antes y no es constante. 

- **Delay**

![ScreenShot](/Parte I/img/interArrivalTime7/delayNode5.png)

El delay ahora se mantiene en un rango estable, ya no crece de manera constante.

![ScreenShot](/Parte I/img/interArrivalTime7/avg.png)

El promedio de delay es de: 8,40.
Y la cantidad de paquetes que llegaron son 213.

- **Saltos**

![ScreenShot](/Parte I/img/interArrivalTime7/hopsNodo5.png)

En cuando a los saltos no hay mucho cambio ya que los paquetes viajan la misma ruta que antes.

# Parte 2: Diseño de Algoritmo de enrutamiento

### Azar

El azar es un término utilizado para calificar aquellos eventos impredecibles. Es decir, eventos que no se pueden anticipar utilizando la lógica o cualquier tipo de análisis.

### Diseño

La idea fue diseñar un algoritmo azar, que cada nodo envie los paquetes por el enlace 0 o 1 al azar. 
Para eso implementamos una forma de crear numeros aleatoreamente, numeros entre 0 o 1, entonces cada vez que un nodo tiene que enviar un paquete a otro nodo, se envia por un enlace aleatorio. 
Esta idea no hace que la red sea eficiente, pero da uso a todos los nodos de la red, por lo tanto se utilizan los recursos de la red. Y usando las metricas que usamos en la **Parte 1**, nos trae unas estadisticas interensates para estudiarlas.

## Caso de estudio 1

 - **Nodos Generadores:** Nodo 0 y Nodo 2.
 
 - **Destino:** Nodo 5
 
 - **Datarate entre nodos:** 1Mbps bidireccional

Lo mismo que en la **Parte 1 Caso 1**.

- **Nodos 4 y 6**

![ScreenShot](/Parte II/img/Caso 1/bufNode46.png)

En los nodos 4 y 6 (vecinos del nodo destino) notamos que el buffer no tiene congestión y se mantiene entre 0 y 1 la carga de paquetes en sus respectivos bufferes de sus dos enlaces (lkn[0] y lnk[1]).

- **Nodos 3 y 7**

![ScreenShot](/Parte II/img/Caso 1/bufNode37.png)

Cuando nos alejamos un poco del nodo destino empezamos a ver que los bufferes de los nodos se empiezan a llenar de a momentos.

- **Nodos 0, 1 y 2**

![ScreenShot](/Parte II/img/Caso 1/bufNode012.png)

En este grafico notamos como los nodos generadores(0 y 2) tienen congestión en sus bufferes. El nodo 1 no se ve tan afectado como los nodos generadores pero igual tiene congestión.

- **Delay**

![ScreenShot](/Parte II/img/Caso 1/delayNode5.png)

El delay tiene un comportamiento extraño, va aumentando pasando el tiempo pero no es constante.

- **Saltos**

![ScreenShot](/Parte II/img/Caso 1/hops.png)

Ahora tenemos saltos muy diversos, algunos superan los 20 saltos.

![ScreenShot](/Parte II/img/Caso 1/avg.png)

El promedio de delay es de: 49,9.
Y la cantidad de paquetes que llegaron son: 128.

## Comparación Parte 2 con Parte 1 en el Caso 1

Viendo las metricas y los graficos obtenidos con el algoritmo implementado, podemos ver que ahora tenemos congestión en varios nodos, en cambio en la parte 1 solo teniamos congestión en el nodo 0, pero ahora usamos todos los recursos de la red.
El cambio mas grande es el de los saltos, en la parte 1 oscilaban entre 3 y 5 saltos, ahora tenemos un minimo de 3 saltos y un maximo de 25, que puede ser diferente cada vez que hacemos la simulacion discreta.

Esto se debe a que se elije de forma aleatoria la salida del paquete por cualquiera de los enlaces del nodo y de esta manera cada paquete puede ir y volver de un nodo al otro varias veces antes de llegar al destino.

En cuando a el delay promedio, bajo de 51,16 a 49,9.
Y la cantidad de paquetes que llegaron, tambien bajo de 196 a 128.


## Caso de estudio 2 intervalArrivalTime = 1

 - **Nodos Generadores:** Nodo {0,1,2,3,4,6,7}.
 
 - **Destino:** Nodo 5
 
 - **Datarate entre nodos:** 1Mbps bidireccional

Usamos lo mismo que en la **Parte 1 Caso 2**
Primero observaremos los bufferes de los nodos

- **Nodos 4 y 6**

![ScreenShot](/Parte II/img/Caso 2/bufNode46.png)

En los bufferes de los nodos 4 y 6 vemos que tiene un poco de congestión. 

- **Nodos 0, 1, 2, 3 y 7**

![ScreenShot](/Parte II/img/Caso 2/bufNode12370.png)

Acá tenemos a todos los nodos con una congestión visible que crece constantemente con el tiempo.

- **Delay**

![ScreenShot](/Parte II/img/Caso 2/delay.png)

El grafico de delay es parecido al de la parte 1, pero el promedio del delay es totalmente distinto.

![ScreenShot](/Parte II/img/Caso 2/avg.png)

El promedio del delay de la **Parte 1 Caso 2** es de: 36,37 seg. Y con el algoritmo tenemos un promedio de 20 seg.
Y la cantidad de paquetes que llegaron fue de : 381 de la parte 1 contra 555 de la parte 2.

- **Saltos**

![ScreenShot](/Parte II/img/Caso 2/hops.png)

Hay oscilaciones de saltos entre 1 y 13.

## Comparación Parte 2 con Parte 1 en el Caso 2

Ahora seguimos teniendo congestion en los bufferes 0, 1, 2, 3 y 7 pero no tanto como en la Parte 1. Crece constantemente pero no tan rápido.
En la Parte 1 teniamos el nodo 4 que no sufria de congestion como los demas nodos, con el algoritmo azar, el nodo 4 y el nodo 6 tampoco sufren como los demas. Esto se debe a que son vecinos del nodo destino y ahora los nodos envian por las dos salidas que tienen.

Los mayores cambios se ven en el delay promedio y en la cantidad de paquetes que llegaron al nodo destino.
Con el algoritmo implementado llegan mas paquetes al destino porque se envian paquetes por los dos enlaces (lkn[0] y lkn[1]).
Y los saltos que hace son muchos mas, por el echo que explicamos más arriba (en la comparación de la Parte 2 con la Parte 1 Caso 1).

## Preguntas interesantes

### ¿Cuánto mejoran las métricas?

En el **Caso 1** no mejoran las metricas, de echo empeoran, se usa mejor los recursos de la red al usar todos los nodos pero no es eficiente el algoritmo azar.

###  ¿Por qué?

Porque al elegir la salida al azar, los paquetes pueden ir y volver al mismo nodo. 

###  ¿Hay loops de enrutamiento?

Si.

###  ¿Ve alguna manera de mejorar más aún su diseño?

Se podría hacer otro algoritmo. Una opción puede ser hacer un algoritmo de enrutamiento estatico, o uno dinamico que encuentre el camino mas corto de cada nodo al nodo destino.

## Referencias:
- Omnet++ Manual
- Stackoverflow
- Videos de clases sincronicas del laboratorio




