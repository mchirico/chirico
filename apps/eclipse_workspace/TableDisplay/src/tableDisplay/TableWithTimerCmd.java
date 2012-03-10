package tableDisplay;

import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import java.io.*;
import javax.swing.*;
import javax.swing.table.*;

import java.util.ArrayList;
import java.util.List;

public class TableWithTimerCmd extends JFrame implements ActionListener,
		Runnable {

	private static final long serialVersionUID = 1L;
	// private JTable myTable;
	private SpecialJT myTable;
	private JButton startButton = new JButton("Start Thread to Update Table");
	private JButton stopButton = new JButton("Stop Thread for Update Table");
	
	private boolean runProcess;
	
	private CmdExecPy cmd;

	public TableWithTimerCmd() {
		cmd = new CmdExecPy();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		String[] head = { "  ", "   ", "   ", "   ", "   ", "   ", "   ",
				"    ","   "," " };
		String[][] data = new String[800][head.length];
		myTable = new SpecialJT(data, head);

		myTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		myTable.setGridColor(Color.blue);
		myTable.setSize(200, 800);
		System.out.print("Size H:" + myTable.getWidth() + " W:"
				+ myTable.getWidth());
		final TableCellRenderer cellRendener = myTable.getTableHeader()
				.getDefaultRenderer();
		myTable.getTableHeader().setDefaultRenderer(new TableCellRenderer() {

			@Override
			public Component getTableCellRendererComponent(JTable table,
					Object value, boolean isSelected, boolean hasFocus,
					int row, int column) {
				JLabel label = (JLabel) cellRendener
						.getTableCellRendererComponent(table, value,
								isSelected, hasFocus, row, column);
				label.setBackground(Color.white);
				label.setForeground(Color.blue);
				label.setPreferredSize(new Dimension(100, 20));
				label.setFont(new Font("SansSerif", Font.BOLD, 10));
				label.setBorder(BorderFactory.createCompoundBorder(
						label.getBorder(),
						BorderFactory.createEmptyBorder(0, 5, 0, 0)));
				label.setHorizontalAlignment(SwingConstants.LEFT);
				return label;
			}
		});
		// myTable.setFillsViewportHeight(true); // apply paintComponent for
		// Viewport

		add(new JScrollPane(myTable), BorderLayout.CENTER);
		add(new GraphCanvas(Color.yellow), BorderLayout.EAST);

		startButton.addActionListener(this);
		
		startButton.setEnabled(true);
		stopButton.addActionListener(this);
		
		
		JPanel cp = new JPanel();
		LayoutManager layout = new BoxLayout(cp, BoxLayout.X_AXIS);
        cp.setLayout(layout);
		
		cp.add(startButton);
		cp.add(stopButton);
		add(cp,BorderLayout.NORTH);
		
		
		stopButton.setEnabled(false);
		setLocation(100, 100);
		setSize(800,400);
		
		System.out.println("this W:"+this.getWidth()+"this H:"+this.getHeight());
		
		pack();
		setVisible(true);
		start();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == startButton) {
			runProcess = true;
			new Thread(this).start();
			myTable.requestFocus();
			startButton.setEnabled(false);
			stopButton.setEnabled(true);
		} else if (e.getSource() == stopButton) {
			runProcess = false;
			startButton.setEnabled(true);
			stopButton.setEnabled(false);
		}
	}

	@Override
	public void run() {

		while (runProcess) {

			SwingUtilities.invokeLater(new Runnable() {
				@Override
				public void run() {
					try {
						cmd.go(myTable);
						// myTable.setValueAt(new String("here one"), row,
						// column);
						// myTable.setValueAt(new Integer(1), row, column);
						// please uncomment for generate type error on EDT
						// myTable.changeSelection(row, column, false, false);
					} catch (Exception e) {
						runProcess = false;
						System.out.println("Error for update JTable cell");
						e.printStackTrace();
					}
				}
			});
			try {// Chirico - this is second update
				Thread.sleep(5000);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	private void start() {
		// Chirico
		// You may want to enable this:
		// timer = new javax.swing.Timer(delay * 1, updateCol());
		// timer.start();

		// Chirico - taken from above, but you could delete
		runProcess = true;
		new Thread(this).start();
		myTable.requestFocus();
		startButton.setEnabled(false);
		stopButton.setEnabled(true);

	}

	public static void main(String args[]) {
		new TableWithTimerCmd();
	}
}


class Brow {
	private int x;
	private int y;
	private Color c;
	public Brow(int x,int y, Color c)
	{
		this.x=x;
		this.y=y;
		this.c=c;
	}
	public int getX() {
		return x;
	}
	public int getY() {
		return y;
	}
	public Color getC() {
		return c;
	}
}



class SpecialJT extends JTable {

	private static final long serialVersionUID = 1L;
	private List<Brow> l = new ArrayList<Brow>();
	

	public SpecialJT(Object[][] data, Object[] head) {
		super(data, head);
		setOpaque(false);
		((JComponent) getDefaultRenderer(Object.class)).setOpaque(false);

	}

	public void mySet(int a, int b, Color c) {
		l.add(new Brow(a,b,c));
		
	}
	public void myClear(){
		l.clear();
	}

	@Override
	public void paintComponent(Graphics g) {
		Color background = new Color(168, 255, 255);
		Color controlColor = new Color(230, 240, 230);
		int width = getWidth();
		int height = getHeight();
		Graphics2D g2 = (Graphics2D) g;
		Paint oldPaint = g2.getPaint();
		g2.setPaint(new GradientPaint(0, 0, background, width, 0, controlColor));
		g2.fillRect(0, 0, width, height);
		g2.setPaint(oldPaint);
		for (int row : getSelectedRows()) {
			Rectangle start = getCellRect(row, 0, true);
			Rectangle end = getCellRect(row, getColumnCount() - 1, true);
			g2.setPaint(new GradientPaint(start.x, 0, controlColor,
					(int) ((end.x + end.width - start.x) * 1.25), 0, Color.blue));
			g2.fillRect(start.x, start.y, end.x + end.width - start.x,
					start.height);
		}

		for (Brow i: l) {
		
			Rectangle start = getCellRect(i.getX(), 0, true);
			Rectangle end = getCellRect(i.getY(), getColumnCount() - 1, true);
			g2.setPaint(new GradientPaint(start.x, 0, controlColor,
					(int) ((end.x + end.width - start.x) * 0.75), 0, i.getC()));
			g2.fillRect(start.x, start.y, end.x + end.width - start.x,
					start.height);
		}

		super.paintComponent(g);
	}
}

class GraphCanvas extends Component {

	public GraphCanvas(Color faceColor) {
		setForeground(faceColor);
	}

	public Dimension getPreferredSize() {
		return new Dimension(300, 300);
	}

	/*
	 * Paint when the AWT tells us to...
	 */
	public void paint(Graphics g) {
		// Dynamically calculate size information
		// (the canvas may have been resized externally...)
		Dimension size = getSize();
		int d = Math.min(size.width, size.height); // diameter
		int ed = d / 20; // eye diameter
		int x = (size.width - d) / 2;
		int y = (size.height - d) / 2;

		g.setColor(Color.black);
		g.drawLine(x, y + 20, d, y + 20);

		g.setColor(Color.blue);
		g.drawLine(x, y + 100, d, y + 100);
		// draw head (color already set to foreground)
		// g.fillOval(x, y, d, d);
		// g.setColor(Color.black);
		// g.drawOval(x, y, d, d);

		// draw eyes
		// g.fillOval(x+d/3-(ed/2), y+d/3-(ed/2), ed, ed);
		// g.fillOval(x+(2*(d/3))-(ed/2), y+d/3-(ed/2), ed, ed);

		// draw mouth
		// g.drawArc(x+d/4, y+2*(d/5), d/2, d/3, 0, -180);
	}
}

class CmdExecPy {

	public void go(SpecialJT jt) {
		try {
			String line;
			
			Process p = Runtime.getRuntime().exec("./cmdpy.py");
			BufferedReader input = new BufferedReader(new InputStreamReader(
					p.getInputStream()));
			while ((line = input.readLine()) != null) {
				String[] tokens = line.split("[\t]+");
				for (int i = 2; i < tokens.length; ++i) {
					if (Integer.parseInt(tokens[0]) == -1) {
						jt.getColumnModel().getColumn(i - 2)
								.setHeaderValue(tokens[i]);
						jt.getColumnModel().getColumn(i-2).setMinWidth(tokens[i].length()*10);
						
					} else {
						jt.setValueAt(tokens[i], Integer.parseInt(tokens[0]),
								(i - 2));
					}
					// myTable.setValueAt(new String("here one"), row, column);
					if (Integer.parseInt(tokens[1]) == 1) {
						/*
						 * jt.changeSelection(Integer.parseInt(tokens[0]),
						 * Integer.parseInt(tokens[1]), false, false);
						 */
						jt.mySet(Integer.parseInt(tokens[0]),
								Integer.parseInt(tokens[0]), new Color(200, 50, 60));
						// jt.repaint();
						// myTable.changeSelection(row, column, false, false);
					} else {
						jt.mySet(Integer.parseInt(tokens[0]),
								Integer.parseInt(tokens[0]), new Color(255, 255, 255));
						
					}

			

					System.out.print(tokens[i]);
					System.out.print(" ");
				}

				System.out.println("");

			}
			input.close();
		} catch (Exception err) {
			err.printStackTrace();
		}
	}
}
