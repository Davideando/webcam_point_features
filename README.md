# webcam_point_features
Detection of ORB features from online webcam imges.

La dirección donde se explican las funcionalidades del detector de puntos ORB (Oriented FAST and Rotated BRIEF)

http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html

Referencia de la wikipedia

https://en.wikipedia.org/wiki/ORB_(feature_descriptor)

El paper que hablo por primera vez del algoritmo ORB

http://www.vision.cs.chubu.ac.jp/CV-R/pdf/Rublee_iccv2011.pdf

Explicación de los distintos tipos de filtros

https://moodle2015-16.ua.es/moodle/pluginfile.php/105463/mod_page/content/43/3%20Caracteristicas%20y%20segmentacion.pdf

Analisis de eficiencia de algoritmos de reconocimiento

http://repositorio.espe.edu.ec/bitstream/21000/7770/1/AC-SI-ESPE-047430.pdf

Un detector de esquinas ORB utiliza las caracteristicas de dos filtros, el filtro FAST y el filtro BRIEF, utilizando las ventajas 
que proporciona el filtro BRIEF en fácilidad de computo y la detección del filtro Fast para mejorar el tiempo de computación.

El filtro ORB utiliza un sistema de pixeles vecinos para detectar las esquinas, utiliza un algoritmo para detectar donde se producen estos 
cambios en la imagen para prooponer las esquinas. Además de la detección de las esquinas, se utilizan los momentos para calcular la orientación del punto. Por otro lado, se calculan los descriptores de la imagen utilizando el filtro BRIEF, pero se ha mejorado con un calculo de pares, de tal manera que con este calculo se consigue que la detección sea inmune a la rotación, y por tanto, da igual donde esté apuntando, que detectará el punto.

El código lo he hecho con una mascará configurable, pero no he notado que hayan más o menos detecciones cuando he aplicado el filtro, no se si he hecho alguna cosa mal...

