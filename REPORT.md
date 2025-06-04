# Report: Building a search engine like Google

> [!NOTE]  
> Complete the report in this file before delivering the project.
> The lab guide has a list of the questions you must answer.

<table>
  <tr>
   <td><strong>Descripción</strong>
   </td>
   <td><strong>Big-O</strong>
   </td>
   <td><strong>Justificación</strong>
   </td>
  </tr>
  <tr>
   <td><strong>Parsing a document into the struct (including adding the links to the list)</strong>
   </td>
   <td>O(n + m)
   </td>
   <td>Recorrer <code>n</code> palabras y <code>m</code> enlaces para insertarlas en listas por operación.
   </td>
  </tr>
  <tr>
   <td><strong>Parsing a query into the struct</strong>
   </td>
   <td>O(k)
   </td>
   <td>Recorre cada una de las <code>k</code> palabras del query y las agrega a una estructura lineal.
   </td>
  </tr>
  <tr>
   <td><strong>Counting the neighbours in the graph</strong>
   </td>
   <td>O(1) or O(d)
   </td>
   <td>Al guardar el número de vecinos la complejidad es O(1), mientras que si recorre la lista de enlaces es O(d).
   </td>
  </tr>
  <tr>
   <td><strong>Counting the neighbours of a document in the graph</strong>
   </td>
   <td>O(d)
   </td>
   <td>Al recorrer los enlaces salientes del documento, evalúa el grado de salida <code>d</code>.
   </td>
  </tr>
  <tr>
   <td><strong>Finding documents that contain a keyword in the reverse-index</strong>
   </td>
   <td>O(1)
   </td>
   <td>No se encuentra complejidad para acceder a estos apartados.
   </td>
  </tr>
  <tr>
   <td><strong>Finding the documents that match all keywords in the query</strong>
   </td>
   <td>O(k·d)
   </td>
   <td>Para <code>k</code> keywords, se interceptan listas de hasta <code>d</code> documentos por cada una.
   </td>
  </tr>
  <tr>
   <td><strong>Sorting the documents according to the relevance score</strong>
   </td>
   <td>O(n log n)
   </td>
   <td>Se ordenan <code>n</code> documentos por su puntaje usando un algoritmo como mergesort o quicksort, haciendo así que la complejidad sea la esmentada.
   </td>
  </tr>
</table>

Representa gráficamente el tiempo de búsqueda **con/sin** el índice inverso para conjuntos de datos de diferentes tamaños y discute los resultados (**2 frases**).

1. A medida que utilizas el reverse index reduces significativamente el tiempo de búsqueda, especialmente en relación con el crecimiento del tamaño del conjunto de datos.

2. Sin el index nos encontramos que el tiempo de búsqueda crece en relación al número de documentos, mientras que con el reverse index se mantiene constante.

<p align="center">
  <img src="graficas/grafica1.png" alt="Gráfica 1" width="500">
</p>

---

Representa gráficamente el tiempo de inicialización para diferentes configuraciones del número de slots en el hashmap y discute los resultados (**2 frases**).

1. Si augmentamos el número de slots iniciales del hashmap haces una reducción del tiempo de inicialización para evitar colisiones y redimensionamientos.

2. Sin embargo, el tiempo se estabiliza o incluso aumenta ligeramente linealmente al coste de reservar memoria innecesaria.

<p align="center">
  <img src="graficas/grafica2.png" alt="Gráfica 2" width="500">
</p>

---

Representa gráficamente el tiempo de búsqueda para diferentes configuraciones del número de slots en el hashmap y discute los resultados (**2 frases**).

1. A la que hay un mayor número de slots en el hashmap mejora el rendimiento de la búsqueda, ya que reduce las colisiones.

2. Si elaboras un número excesivo de slots puedes causar un aumento del coste de acceso a memoria sin mejoras sustanciales en el rendimiento.

<p align="center">
  <img src="graficas/grafica3.png" alt="Gráfica 3" width="500">
</p>


Describe una mejora del índice inverso para mejorar la velocidad de búsqueda e inicialización. \
 ¿Requeriría la misma, menor o mayor cantidad de memoria en general?

Requeriría más memoria inicialmente debido a estructuras adicionales como bucketing adaptativo y compresión, pero podría utilizar menos memoria total al escalar, gracias a la compresión de las listas de documentos.

 \
 ¿Y cuál sería la complejidad temporal (Big-O)?

**Inicialización**: sigue siendo **O(n·k)**, donde *n* es el número de documentos y *k* el número de palabras por documento. 


**Búsqueda por palabra**: se mantiene en **O(1)** si se usa un `hashmap`. 


**Intersección de documentos por múltiples palabras**: mejora en la práctica por listas comprimidas y ordenadas, aunque el peor caso sigue siendo **O(k·d)**.

 \
 ¿Tardaría lo mismo, menos o más tiempo en ejecutarse?

**Inicialización**: **más lenta**, por la compresión y el manejo de estructuras adicionales. 


**Búsqueda**: **más rápida**, especialmente en consultas frecuentes o con palabras muy comunes. 


**En general**: **más eficiente al escalar** a grandes volúmenes de datos.
