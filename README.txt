Anas BARAKAT 


######################################
PROCEDURE DE TEST
######################################

- Lancer le serveur: make run dans le répertoire cpp
- Lancer le client: make run dans le répertoire swing 
(L’ordre de ces 2 étapes est important)

AVEC L’INTERFACE GRAPHIQUE UNIQUEMENT
——————————————————————————————————————

-Tester la recherche d’objets:  Des objets multimedia ont été créés dans le main pour tester, 
————taper par exemple oss7 (ou “oss117” ou “Paris” ou même n’importe quel string et dans ce cas renvoie objet non trouvé) dans la barre de recherche 
————appuyer sur le radiobouton “chercher” 
———-appuyer sur le bouton “Lancer”, 
les attributs de cet objet s’affichent sur le JTextArea.

-Tester la lecture d’objets:
————taper par exemple MyVideo ou MyPhoto dans la barre de recherche
————appuyer sur le radiobouton “jouer” 
————le multimédia est alors joué (lancé) sur le serveur avec gnome -open sur linux (machine de l’école) qui permet d’ouvrir n’importe quel fichier avec l’application par défaut associée. 

AVEC LE MAIN DE database.cpp 
————————————————————————————

Des blocs de tests commentés permettent de tester notamment la sérialisation et désérialisation qui fonctionnent. 


Remarque: le code a été commenté dans un des styles de commentaires supportés par Doxygen. Le texte de génération automatique de documentation a été fait avec l’application Doxygen directement en donnant juste la directory cpp contenant tous les fichiers C++, on obtient deux dossiers: un HTML et un Latex avec la documentation. Je ne les ai pas mis dans le rendu pour ne pas alourdir le dossier de rendu de TP de HTML … inutilement 


######################################
REPONSES AUX QUESTIONS ET REALISATION
######################################

——————————————————————————————
TP C++
——————————————————————————————

4ème étape : Photos et videos
------------------------------

La méthode playMultimedia pour jouer l'objet multimedia est une
méthode abstraite. La déclaration de cette méthode se fait comme suit:

  virtual void playMultimedia() const = 0;

dans le header.

Il ne sera plus possible d'instancier des objets de la classe de
base car celle-ci est incomplète: elle est abstraite, les méthodes
abstraites ne sont pas implémentées.


5ème étape : Traitement générique
----------------------------------

C'est le polymorphisme de type qui permet de faire cela, grâce à la liaison
dynamique ou tardive.
Il est nécessaire dans le cas du C++ d'utiliser des tableaux de pointeurs
vers les objets de type Video ou Photo. Les éléments du tableau sont de type
pointeurs vers des objets Photo ou Video.

Sinon, on n’a pas de liaison dynamique. 

Java fonctionne sur le même principe avec les références Java mais ceci
reste plus opaque au programmeur.

6ème étape : Films et tableaux
-------------------------------

L'utilisation du mot clé const pour l'accesseur empêche de modifier l'objet.

Avec le mot clé const avant le int* pour le type de retour de l'accesseur, on empêche
la modification du pointeur renvoyé par l'accesseur.

7ème étape: Destruction et copie d'objets
------------------------------------------

Il faut modifier la classe film qui a des variables d'instances qui pointent vers des
objets ou des tableaux comme par exemple Film.

Aussi, quand on fait la copie d'un objet, il faut faire delete de l'ancien après la copie
par exemple dans le cas de la modification du tableau de durées de la classe Film.

8ème étape: Créer des groupes
------------------------------

Si la liste n'est pas une liste de pointeurs d'objets mais une liste d'objets,
ces objets seraient détruits à la destruction de la liste alors qu'un objet peut
appartenir à plusieurs groupes alors qu'on ne veut supprimer que l'une des listes sans supprimer l’objet qui peut appartenir à une autre liste.


9ème étape: Gestion automatique de la mémoire
---------------------------------------------
traitée

10ème étape: Gestion cohérente des données
------------------------------------------

On déclare le constructeur de Multimedia private
et les autres constructeurs protected (ceux des classes qui en héritent) et on donne le droit d'accès
friend à la classe Database sur la classe Multimedia. Remarque: comme les constructeurs sont chaînés,
même si on ne met pas de protected pour les constructeurs des sous-classes, l'utilisation posera problème
puisque le constructeur de la classe Multimedia sera aussi appelé.

11ème étape: Client/serveur
---------------------------

Le serveur est implémenté dans le database.cpp qui est aussi la classe pour la gestion cohérente de données (la map). 

Sachant que la méthode processRequest peut appartenir à n'importe quelle classe, on peut l'implémenter dans
la classe DataBase pour qu'elle ait accès aux données de cette classe de manière automatique.

12ème étape: Sérialisation/Désérialisation 
——————————————————————————————————————————

Comme vu en cours, j’ai implémenté les deux fonctions read (avec getline) et write en puis deux fonctions load et save pour lire depuis un fichier et écrire sur un fichier. 
Pour le respect de l’orienté objet, les méthodes read et write sont implémentées dans Multimédia puis redéfinies dans ses différentes sous-classes. C’est donc l’objet lui-même qui écrira sur le fichier et lira depuis le fichier. 

On écrit en avec une ligne par attribut pour éviter les ambiguïtés. 

Dans le main, la sérialisation est testée en écrivant des un fichier testSerialize.txt qui est alors créé dans le même répertoire. 

De même, la désérialisation a été testée, en lisant à partir d’un fichier testSerialize.txt puis en accédant aux objets multimédias qui venaient d’être créés. 

——————————————————————————————
TP Java/Swing 
——————————————————————————————

1ère étape: Fenêtre principale et quelques interacteurs
———————————————————————————————————————————————————————

Il y a à chaque fois besoin de retailler la fenêtre pour voir le texte qui a été inséré grâce aux boutons 1 et 2 quand le JTextArea est plein et qu’il n’y a pas de JScrollPane. 

2ème étape: Menus, barre d'outils et actions 
————————————————————————————————————————————

J’ai opté pour la 2ème solution (conseillée) utilisant les Actions. 
Remarque: dans le code, il y a les classes imbriquées permettant de répondre à l’étape 1 que j’ai gardées même si j’aurai pu les remplacer par les sous-classes de AbstractAction pour alléger le code. J’ai conscience que cette partie est redondante, 
mais je les ai gardées volontairement pour suivre la progression de l’énoncé.

3ème étape: Interaction client/serveur
——————————————————————————————————————
Le client est implémenté dans la même classe ClientJavaSwing.java en intégrant le code du client donné. 


4ème étape: Créer un Makefile
——————————————————————————————————————

J’ai modifié le nom du programme pour qu'il corresponde au fichier ClientSwing.java qui contient le main() et le fichier source pour y mettre ClientSwing.java.


