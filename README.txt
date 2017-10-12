Author: Anas BARAKAT 


######################################
TESTING PROCEDURE
######################################

1° Launch the server: 'make run'command in the cpp directory
2° Launch the client: 'make run' command in the swing directory


WITH THE GRAPHICAL INTERFACE ONLY
——————————————————————————————————————

-Testing searching objects:  Multimedia objects have been created in the main for testing purposes, 
————type for example oss7 (or “oss117” or “Paris” or whenever string you want and you get in this case dans ce cas "non found object") in the research bar
————click  “chercher” (search) button
———-click  “Lancer” (launch) button, 
The attributes of the object appear in the JTextArea. 

-Testing reading objects:
————type for example MyVideo or MyPhoto in the research bar. 
————click the "jouer" (play) radiobutton.  
————the corresponding multimédia is played (launched) on the server with gnome -open with linux which allows to open whenever file you want with the corresponding default applicaiton.

In the main of database.cpp 
————————————————————————————

Commented testing blocks can test the serialization and deserialization of objects.



