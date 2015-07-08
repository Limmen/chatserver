package view;
//import net.miginfocom.swing.MigLayout;
import net.miginfocom.swing.MigLayout;
import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author kim
 */

public class Connect_GUI extends JFrame
{
    JPanel container;
    JLabel txt;
    JButton btn;
    JTextField ip;
    JTextField port;
    private Font Italic = new Font("Serif", Font.ITALIC, 12);
    private Font Plain = new Font("Serif", Font.PLAIN, 12);
    private Font IBold = Italic.deriveFont(Italic.getStyle() | Font.BOLD);
    private Font PBold = Plain.deriveFont(Plain.getStyle() | Font.BOLD);
    private Menu_Panel menu;
    public Connect_GUI(){
        super("Connect to chatserver");

        menu = new Menu_Panel();
        this.setLayout(new MigLayout());
        startup();
        addWindowListener(new java.awt.event.WindowAdapter() {
                @Override
                public void windowClosing(java.awt.event.WindowEvent windowEvent) 
                {
                    //cleanUp();
                    System.exit(0);
                }
            });
        pack();
        setLocationRelativeTo(null);    // centers on screen
        setVisible(true);
    }
    public void startup()
    {
        container = new JPanel(new MigLayout("wrap 2"));
        setJMenuBar(menu.getMenu());
        menu.getHelp().addActionListener(new ActionListener() 
            {
                public void actionPerformed(ActionEvent arg0) 
                {
                    Help();
                }
            });
        menu.getAbout().addActionListener(new ActionListener() 
            {
                public void actionPerformed(ActionEvent arg0) 
                {
                    About();
                }
            });
        txt = new JLabel("Connect to a chatserver");
        txt.setFont(Plain);
        container.add(txt, "span 2, align center");
        txt = new JLabel("IP adress ");
        txt.setFont(Plain);
        container.add(txt, "span 1");
        ip = new JTextField(30);
        ip.setFont(Plain);
        container.add(ip, "span 1");
        txt = new JLabel("Port");
        txt.setFont(Plain);
        container.add(txt, "span 1");
        port = new JTextField(30);
        port.setFont(Plain);
        container.add(port, "span 1");
        btn = new JButton("Connect");
        btn.setFont(PBold);
        btn.addActionListener(new ActionListener() 
            {
                public void actionPerformed(ActionEvent arg0) 
                {
                     try {
                         new Chat_GUI(ip.getText(), Integer.parseInt(port.getText()));
                         ip.setText("");
                         port.setText("");
                     }
                     catch(Exception e)
                     {
                         ip.setText("Could not connect");
                         port.setText("Could not connect");
                     }

                    pack();
                }
            });
        container.add(btn, "span 2, gaptop 10");
        txt = new JLabel("Copyright \u00a9 Kim Hammar all rights reserved");
        txt.setFont(Plain);
        container.add(txt, "span 2, gaptop 20");
        add(container, BorderLayout.CENTER);
    }
    public void About()
    {
        new About();
    }
    public void Help()
    {
        new Help();
    }
}
    

