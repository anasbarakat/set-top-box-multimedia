//pour l'interface graphique
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

//pour le client
import java.io.*;
import java.net.*;


public class ClientSwing extends JFrame  {

    private static final long serialVersionUID = 1L;
    
    //pour le client
    static final String DEFAULT_HOST = "localhost";
    static final int DEFAULT_PORT = 3330;
    private Socket sock;
    private BufferedReader input;
    private BufferedWriter output;
    
    //true pour jouer et false pour chercher un multimédia
    //son état change selon les clicks sur les jradiobuttons présentés dans la suite
    private boolean operation;
    
    //pour l'interface graphique
    
    ///de l'étape 1
    private JTextArea texte = null;
    
    //champ de recherche
    private JTextField champ = new JTextField();
    
    String request = null;
    String response = null;
    
    //On a besoin de pouvoir récupérer l'état de ces JRadioButtons dans d'autres boutons
    private JRadioButton searchop = null;
    private JRadioButton playop = null;
    
    static {
        System.setProperty("apple.laf.useScreenMenuBar", "true");
    }
    
    public ClientSwing(String host, int port) throws UnknownHostException, IOException {
        
        //appel du constructeur de Frame avec le titre "Télécommande"
        super("Télécommande");
        
        
        /// Initialise la connexion
        /// Renvoie une exception en cas d'erreur
        try {
            sock = new java.net.Socket(host, port);
        }
        catch (java.net.UnknownHostException e) {
            System.err.println("Client: Couldn't find host "+host+":"+port);
            throw e;
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't reach host "+host+":"+port);
            throw e;
        }
        
        try {
            input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't open input or output streams");
            throw e;
        }
        
        ///Interface graphique
        
        JPanel panel = new JPanel();
    
        JButton button1 = new JButton("ajout texte 1");
        JButton button2 = new JButton("ajout texte 2");
        JButton button3 = new JButton("Quitter");
        texte = new JTextArea(10,30);
        JScrollPane sTexte = new JScrollPane(texte);
        
        JMenuBar menubar = new JMenuBar();
        JMenu menu = new JMenu("Menu");
        JToolBar toolbar = new JToolBar();
        
        // 2 possibilités: jouer ou chercher un multimédia
        JRadioButton searchop = new JRadioButton("Chercher");
        searchop.setForeground(Color.RED);
        searchop.addActionListener(new ChercherJRadio( ));
        JRadioButton playop = new JRadioButton("Jouer");
        playop.setForeground(Color.BLUE);
        playop.addActionListener(new JouerJRadio( ));
        //pour qu'une seule option soit choisie à la fois
        ButtonGroup group = new ButtonGroup();
        group.add(searchop);
        group.add(playop);
        
        
        champ.setColumns(10);// taille du champ de texte de recherche
        
        //Le conteneur JPanel contient les boutons
        panel.add(new JLabel("Boutons"));
        panel.add(button1);
        panel.add(button2);
        panel.add(button3);
        
        //pour une disposition verticale des éléments dans le panel de recherche
        JPanel panelSearch = new JPanel();
        panelSearch.setLayout(new BoxLayout(panelSearch, BoxLayout.Y_AXIS));
        panelSearch.add(new JLabel("Nom du multimedia"));
        panelSearch.add(champ);
        //ajout des JRadioButton au panel de droite de l'interface graphique
        panelSearch.add(searchop);
        panelSearch.add(playop);
        

        //Création des actions partagées par la barre d'outils et la barre de menu
        SendRequest sendreq =   new SendRequest(  "Lancer",null,
                                 "Pour jouer le multimédia rentré ou le rechercher dans la base de données ",
                                 new Integer(KeyEvent.VK_L));
        NewRequest newreq = new NewRequest("nouvelle requête",null,
                               "Pour une nouvelle requête",
                               new Integer(KeyEvent.VK_M));
        Close close =  new Close( "Quitter",null,
                           "pour fermer l'application",
                           new Integer(KeyEvent.VK_R));

        //ajout d'items au menu
        menu.add(sendreq);
        menu.add(newreq);
        menu.addSeparator(); //séparateur dans le menu
        menu.add(close);
        

        //Ajout des 3 boutons à la barre d'outils
        JButton buttont1 = new JButton(sendreq);
        toolbar.add(buttont1);
        JButton buttont2 = new JButton(newreq);
        toolbar.add(buttont2);
        JButton buttont3 = new JButton(close);
        toolbar.add(buttont3);

        //barre de menu ajoutée à la barre de menu
        menubar.add(menu);
        
        //barre de menu ajoutée à la fenêtre
        setJMenuBar(menubar);
        
        //Disposition spatiale
        ///JPanel placé au sud de la fenêtre principale
        add(BorderLayout.SOUTH, panel);
        /*JFrame par défaut associé à un LayoutManager de type BorderLayout,
        un positionnement des enfants de type "points cardinaux"*/
        ///JScrollPane construit à partir de JTextArea placé au centre de la fenêtre principale
        JPanel ptextarea = new JPanel();
        ptextarea.setLayout(new BorderLayout());
        ptextarea.add(BorderLayout.NORTH, new JLabel("Affichage du résultat"));
        ptextarea.add(BorderLayout.CENTER, sTexte);
        ptextarea.setVisible(true);
        
        add(BorderLayout.CENTER, ptextarea);
        
        ///Barre d'outils placée au nord de la fenêtre principale
        add(BorderLayout.NORTH, toolbar);
        
        add(BorderLayout.WEST, panelSearch);
        
        
        button1.addActionListener(new AddTextLine1( ));
        button2.addActionListener(new AddTextLine2( ));
        button3.addActionListener(new CloseListener( ));
        
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Client Java Swing");
        pack(); // calcule la disposition spatiale
        setVisible(true); // fait apparaître l’interface
    }
    
    ///
    /// Envoie une requete au serveur et retourne sa reponse.
    /// Noter que la methode bloque si le serveur ne repond pas.
    ///
    public String send(String request) {
        // Envoyer la requete au serveur
        try {
            request += "\n";  // ajouter le separateur de lignes
            output.write(request, 0, request.length());
            output.flush();
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't send message: " + e);
            return null;
        }
        
        // Recuperer le resultat envoye par le serveur
        try {
            return input.readLine();
        }
        catch (java.io.IOException e) {
            System.err.println("Client: Couldn't receive message: " + e);
            return null;
        }
    }

    
    //On utilise ici les classes imbriquées: 3ème stratégie vue en cours
    class AddTextLine1 implements ActionListener{
        //méthode appelée si click sur un bouton
        public void actionPerformed(ActionEvent e) {
            texte.append("Je suis le bouton 1 et voici mon texte\n");
        }
    }
    
    class AddTextLine2 implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            texte.append("Je suis le bouton 2 et voici mon texte\n");
        }
    }
    
    class CloseListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }
    
    class ChercherJRadio implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            operation = false;
        }
    }
    
    class JouerJRadio implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            operation = true;
        }
    }
    
    
    //les classes suivantes (imbriquées) sont dans la classe JavaSwing pour avoir accès aux attributs comme texte
    
    
    //pour chercher ou jouer un multimedia - envoie la requête client et récupère la réponse
    class SendRequest extends AbstractAction {
    
        public SendRequest(String text, ImageIcon icon,
                        String desc, Integer mnemonic) {
            super(text, icon);
            putValue(SHORT_DESCRIPTION, desc);
            putValue(MNEMONIC_KEY, mnemonic);
        }
        public void actionPerformed(ActionEvent e) {
            
            //requête client traitée selon l'état des JRadioButtons
            if(operation == false){
                // la recherche se fait avec la requête suivante spécifiée comme cela dans le serveur cpp
                request = "chercher "+champ.getText().split("\n")[0];
                response = ClientSwing.this.send(request);
            }
            
            if(operation == true){
                request = "jouer "+champ.getText().split("\n")[0];
                response = ClientSwing.this.send(request);
            }
            texte.append(response);
        }
    }
    
    //pour une nouvelle recherche
    class NewRequest extends AbstractAction {
        
        public NewRequest(String text, ImageIcon icon,
                        String desc, Integer mnemonic) {
            super(text, icon);
            putValue(SHORT_DESCRIPTION, desc);
            putValue(MNEMONIC_KEY, mnemonic);
        }
        public void actionPerformed(ActionEvent e) {
            
            //vide la barre de recherche
            texte.setText("");
            champ.setText("");
            
            //Boite de dialogue avec message à l'utilisateur
            JDialog.setDefaultLookAndFeelDecorated(true);
            JDialog d = new JDialog(ClientSwing.this,"Nouvelle opération",true);
            d.setSize(700,100);
            d.setLayout(new FlowLayout());
            d.add(new JLabel("Rentrez un nouveau nom d'objet à rechercher ou à jouer dans la barre de recherche"));
            d.setVisible(true);
            
        }
    }
    

    class Close extends AbstractAction {
        
        public Close(String text, ImageIcon icon,
                     String desc, Integer mnemonic) {
            super(text, icon);
            putValue(SHORT_DESCRIPTION, desc);
            putValue(MNEMONIC_KEY, mnemonic);
        }
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }


    public static void main(String argv[ ]) {
        
        String host = DEFAULT_HOST;
        int port = DEFAULT_PORT;
        if (argv.length >=1) host = argv[0];
        if (argv.length >=2) port = Integer.parseInt(argv[1]);
        
        ClientSwing client = null;
        
        try {
            client = new ClientSwing(host, port);
        }
        catch (Exception e) {
            System.err.println("Client: Couldn't connect to "+host+":"+port + " Lancez d'abord le programme cpp avec le serveur en faisant make run dans le sous répertoire make run");
            System.exit(1);
        }
        
        System.out.println("Client connected to "+host+":"+port);

    }

    
}


