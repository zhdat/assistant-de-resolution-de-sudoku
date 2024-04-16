# Rapport Aide Sudoku

## Introduction

Notre projet, "Aide Sudoku", est un logiciel développé dans l'environnement Qt Creator, conçu pour offrir une assistance intelligente aux amateurs de Sudoku. En combinant la simplicité des règles du jeu avec les capacités de l'informatique moderne, notre objectif est de simplifier la résolution des grilles tout en enrichissant l'expérience de jeu. Ce rapport présente les fonctionnalités clés de notre application, démontrant comment elle peut améliorer la jouabilité et stimuler l'intérêt pour ce jeu de réflexion classique.

## Fonctionnalités Marquantes

### Fenêtre de Login

- Permet l'accès au classement par niveau de difficulté(classement en local), aux réglages de volume et de VFX, ainsi qu'à la personnalisation du pseudo et de la difficulté de la grille.
- Offre une interface conviviale pour une expérience utilisateur optimale.

### Fenêtre Principale de Jeu

- Affiche deux grilles : une grille de jeu à remplir et une grille d'aide pour suivre les choix effectués.
- Interface claire et intuitive pour une concentration maximale sur le jeu.

### Toolbar Intuitive

- Fournit un accès rapide aux fonctionnalités essentielles via les menus Fichier, Options et Aide.
- Facilite la navigation et l'utilisation du logiciel.

### Options de Personnalisation

- Permet aux utilisateurs de changer de thème et de difficulté pour une expérience de jeu personnalisée.

### Feedback Visuel et sonore

- Barre de progression et timer offrant un feedback visuel sur la progression du joueur et le temps écoulé.
- Renforce l'immersion et l'engagement du joueur dans le jeu.
- Effets sonores permettant un feedback auditif contextuel.

### Fenêtre de Victoire

- Affiche une fenêtre de victoire une fois la partie terminée avec succès.
- Confirme la réussite du joueur et ajoute une dimension gratifiante à l'expérience de jeu.

### Langues et Internationalisation

- Prise en Charge de l'Internationalisation : L'application prend en charge le français et l'anglais en fonction de la langue par défaut de l'ordinateur.

## Perspective d'évolution

### Adapdation sur mobile

- L'UI utilisée étant le style "Bento UI" nous n'aurions aucun mal à le transposer sur mobile (en retirant la fenêtre de prévisualisation à droite afin d'éviter de surcharger)

- Compatibilité avec les Plateformes Mobiles : Le choix du langage C++ offre une bonne compatibilité pour l'adaptation de l'application sur les plateformes mobiles telles qu'Android et iOS.

- Utilisation de Qt : En utilisant Qt, la transition vers les appareils mobiles est facilitée grâce à sa capacité à compiler le même code source sur différentes plateformes.

### Mise en place de différent niveau d'aide

- Une désactivation des aides
- Une vérification colonne/ligne
- Une vérification du carré
- Une vérification des trois
- Une vérification des trois + indicateur coloré s'il reste une unique possibilité dans la case

## Structure du Code

- Modèle-Vue-Présentateur (MVP) : Le code suit une architecture MVP pour une séparation claire des préoccupations.

- Classes pour les Vues : Chaque vue est représentée par une classe distincte, facilitant la gestion de l'interface utilisateur.

- Classe "Tools" : Gère les thèmes de base, les options de musique et la gestion des fichiers comme le leaderboard.

- Widget Personnalisé pour la Grille : Un widget personnalisé représente la grille de droite, offrant une expérience visuelle dynamique.

## Outils Utilisés

- Qt Creator : Utilisé pour le développement du code de l'application, offrant un environnement de développement intégré (IDE) adapté à qt.

- Qt Designer : Employé pour concevoir les vues de l'interface utilisateur de manière visuelle et intuitive, facilitant ainsi le processus de conception.

- Git : Utilisé comme gestionnaire de version pour le suivi des modifications, la collaboration et la gestion du code source du projet.

- Linguist : Mis en œuvre pour la mise en place de l'internationalisation, permettant la traduction et l'adaptation de l'application dans différentes langues.

## Conclusion

Le projet "Aide Sudoku" réalisé dans Qt Creator offre une expérience de jeu riche, intuitive et personnalisée. Les fonctionnalités marquantes telles que la fenêtre de login, la toolbar intuitive et les options de personnalisation contribuent à rendre le jeu de Sudoku accessible et gratifiant pour tous les utilisateurs.

## A Propos

Ce projet a été développé par Jantet Clément & Ravix Calliste et est distribué sous licence MIT.
