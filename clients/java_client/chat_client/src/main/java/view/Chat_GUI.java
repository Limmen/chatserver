package view;
//import net.miginfocom.swing.MigLayout;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.Action;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import model.Client;
import net.miginfocom.swing.MigLayout;

/**
 *
 * @author kim
 */


public class Chat_GUI extends JFrame
{
    private String host;
    private int port;
    private Client client;
    private JPanel container;

    private Font Italic = new Font("Serif", Font.ITALIC, 12);
    private Font Plain = new Font("Serif", Font.PLAIN, 12);
    private Font IBold = Italic.deriveFont(Italic.getStyle() | Font.BOLD);
    private Font PBold = Plain.deriveFont(Plain.getStyle() | Font.BOLD);
    
    private JPanel chatpanel;
    private JScrollPane chat_scroll;
    private JScrollPane message_scroll;
    private JTextArea entry;
    private JTextField enter_msg;
    private JPanel input;
    public Chat_GUI(String host, int port) throws Exception{
        super("Chat client" + host + " " + port);
        this.host = host;
        this.port = port;
        this.client = new Client(host, port, this);

        startup();
        
        addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent windowEvent)
            {
                cleanUp();                
            }
        });
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

        client.start();

        
    }
    public void startup(){
        
        Action action = new AbstractAction()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                client.sendMsg(enter_msg.getText());
                enter_msg.setText("");
            }
        };
        
        
        input = new JPanel(new MigLayout("wrap 2"));
        JLabel txt = new JLabel(">");
        input.add(txt, "span 1");
        enter_msg = new JTextField(30);
        enter_msg.addActionListener(action);
        input.add(enter_msg);
        
        container = new JPanel(new MigLayout("wrap 4"));
        String title = "Connected to chat-server on "+ host + " " + port;
        txt = new JLabel(title);
        txt.setFont(Plain);
        container.add(txt, "span, align center");
        chatpanel = new JPanel(new MigLayout("wrap 1"));
        chat_scroll = new JScrollPane(chatpanel);
        chat_scroll.setPreferredSize(new Dimension(500, 300));
        container.add(chat_scroll, "span");
        
        add(container, BorderLayout.CENTER);
        enter_msg.requestFocusInWindow();
        
    }
    
    public void newMsg(String msg){
        JLabel txt = new JLabel(msg);
        JPanel p = new JPanel(new MigLayout("wrap 2"));
        p.add(txt, "span");
        chatpanel.remove(input);
        chatpanel.add(p, "span");
        chatpanel.add(input);
        enter_msg.requestFocusInWindow();
        pack();
    }
    public void cleanUp(){
        try{
            client.socket.close();
        }
        catch(Exception e){
            
        }
    }
    
}
