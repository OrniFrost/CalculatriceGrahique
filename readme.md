# Calculatrice Graphique
## Présentation
Pour ce projet, j'ai créé une calculatrice graphique en C++ en utilisant le framework Qt 5. 
Elle permet d'afficher une fonction mathématique en fonction de la valeur de x. Ainsi que de
pouvoir régler l'intervalle de x.
## Installation
Pour éxecuter le programme, il faut être sûr d'avoir cmake d'installer et télecharger les fichiers
présent sur mon [GitHub](https://github.com/OrniFrost/CalculatriceGrahique). Ensuite, il faut ouvrir un terminal et se placer dans le dossier du projet.
Puis exécuter les commandes suivantes:
```bash
   #Si pas déjà installé, pour les grphiques Qt
   sudo apt install libqt5charts5-dev
   
   cd [dossier du projet]
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ./CalculatriceGraphique
```
## Utilisation
L'application est simple d'utilisation.
Vous pouvez entrer une fonction mathématique dans la zone de texte, sont compris les opérateurs :
> **+** , **-** , __*__ , **/** et **^**.

Pour l'inconnue, veuillez utiliser **x**.
Vous pouvez également régler l'intervalle de x les zones de textes **Min x** et **Man x**.


## Description technique
Pour ce projet, l'utilisation du C++ et du framework Qt 5 était une découverte. 
C'était donc une difficulté de base.
l'aspect le plus utilisé de Qt 5 dans ce projet est le **QChart**. Il permet d'afficher des graphiques.
Mais également la classe **QSplineSerie** qui permet d'afficher une belle courbe en donnant des coordonnées de points.
J'ai donc bouclé sur l'intervalle servant d'abscisse et calculé la valeur de l'ordonnée avec la fonction mathématique pour chaque valeur de x.

Ce qui fait lien avec la seconde dificulté, l'**analyseur** (ou **parser** en anglais) de fonction mathématique.
J'ai trouvé un code source simple d'utilisation qui répondait à mes besoins (disponible [ici](https://www.daniweb.com/programming/software-development/code/217180/simple-equation-solver-in-c)).
Cependant, il ne permet l'utilisation d'autres opérateurs mathématiques tels que **sin**, **cos**, **tan**, **log**, **ln** et **sqrt** par exemple.

M'ont également aidé les sites suivants: 
- [StackOverflow](https://stackoverflow.com/questions/11703082/parsing-math-expression-in-c)
- [Documentation Qt - QChart](https://doc.qt.io/qt-5/qchart.html)
- [Documentation Qt - QSplineSerie](https://doc.qt.io/qt-5/qtcharts-splinechart-example.html)

## Amélioration
Avec plus de temps, j'aurai d'abord aimé pouvoir faire **l'analyseur** cela auurait été une fonctionnalité intéressante.
De plus j'aurai aimé implémenter d'autres types de graphique comme les graphiques polaires.

