import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JApplet;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JTextField;



public class SimpleMenus extends JApplet {
    private JTextField t = new JTextField(15);

    private ActionListener al = new ActionListener() {
	    public void actionPerformed(ActionEvent e) {
		t.setText(((JMenuItem) e.getSource()).getText());
	    }
	};

    private JMenu[] menus = { new JMenu("Winken"), new JMenu("Blinken"),
			      new JMenu("Nod") };

    private JMenuItem[] items = { new JMenuItem("Fee"), new JMenuItem("Fi"),
				  new JMenuItem("Fo"), new JMenuItem("Zip"), new JMenuItem("Zap"),
				  new JMenuItem("Zot"), new JMenuItem("Olly"), new JMenuItem("Oxen"),
				  new JMenuItem("Free") };

    public void init() {
	for (int i = 0; i < items.length; i++) {
	    items[i].addActionListener(al);
	    menus[i % 3].add(items[i]);
	}
	JMenuBar mb = new JMenuBar();
	for (int i = 0; i < menus.length; i++)
	    mb.add(menus[i]);
	setJMenuBar(mb);
	Container cp = getContentPane();
	cp.setLayout(new FlowLayout());
	cp.add(t);
    }

    public static void main(String[] args) {
	run(new SimpleMenus(), 600, 400);
    }

    public static void run(JApplet applet, int width, int height) {
	JFrame frame = new JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.getContentPane().add(applet);
	frame.setSize(width, height);
	applet.init();
	applet.start();
	frame.setVisible(true);
    }
} 