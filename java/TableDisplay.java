


import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import javax.swing.*;
import javax.swing.table.*;
 
public class TableDisplay extends JFrame implements ActionListener, Runnable {
 
    private static final long serialVersionUID = 1L;
    private JTable myTable;
    private JButton startButton = new JButton("Start Thread to Update Table");
    private JButton stopButton = new JButton("Stop Thread for Update Table");
    private int count = 0;
    private int delay = 3;
    private javax.swing.Timer timer = null;
    private boolean runProcess;
    private int row = 0;
    private int column = 0;
    private String value = "Test";
 
    public TableDisplay() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        String[] head = {"One", "Two", "Three", "Four", "Five", "Six"};
        String[][] data = new String[25][6];
        myTable = new TableBackroundPaint(data, head);
        myTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        myTable.setGridColor(Color.blue);
        final TableCellRenderer cellRendener = myTable.getTableHeader().getDefaultRenderer();
        myTable.getTableHeader().setDefaultRenderer(new TableCellRenderer() {
 
            @Override
            public Component getTableCellRendererComponent(JTable table, Object value,
                    boolean isSelected, boolean hasFocus, int row, int column) {
                JLabel label = (JLabel) cellRendener.getTableCellRendererComponent(
                        table, value, isSelected, hasFocus, row, column);
                label.setBackground(Color.YELLOW);
                label.setForeground(Color.blue);
                label.setPreferredSize(new Dimension(100, 20));
                label.setFont(new Font("SansSerif", Font.BOLD, 12));
                label.setBorder(BorderFactory.createCompoundBorder(label.getBorder(),
                        BorderFactory.createEmptyBorder(0, 5, 0, 0)));
                label.setHorizontalAlignment(SwingConstants.LEFT);
                return label;
            }
        });
        //myTable.setFillsViewportHeight(true); // apply paintComponent for Viewport
        add(new JScrollPane(myTable), BorderLayout.CENTER);
        add(new GraphCanvas(Color.yellow), BorderLayout.EAST);
        startButton.addActionListener(this);
        add(startButton, BorderLayout.NORTH);
        startButton.setEnabled(false);
        stopButton.addActionListener(this);
        add(stopButton, BorderLayout.SOUTH);
        stopButton.setEnabled(false);
        setLocation(100, 100);
        setSize(600, 300);
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
        count = 1;
        Random random = new Random();
        while (runProcess) {
            row = random.nextInt(myTable.getRowCount());
            column = random.nextInt(myTable.getColumnCount());
            SwingUtilities.invokeLater(new Runnable() {
 
                @Override
                public void run() {
                    try {
                        myTable.setValueAt(new String(value), row, column);
                        //myTable.setValueAt(new Integer(1), row, column); 
                        // please uncoment for generate type error on EDT 
                        myTable.changeSelection(row, column, false, false);
                    } catch (Exception e) {
                        runProcess = false;
                        System.out.println("Error for update JTable cell");
                        e.printStackTrace();
                    }
                }
            });
            try {// Chirico - this is second update
                Thread.sleep(200);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
 
    public Action updateCol() {
        return new AbstractAction("text load action") {
 
            private static final long serialVersionUID = 1L;
 
            @Override
            public void actionPerformed(ActionEvent e) {
                //System.out.println("updating row " + (count + 1));
                TableModel model = myTable.getModel();
                int cols = model.getColumnCount();
                int row = 0;
                for (int j = 0; j < cols; j++) {
                    row = count;
                    myTable.changeSelection(row, 0, false, false);
                    try {
                        Thread.sleep(10);
                    } catch (Exception e1) {
                        e1.printStackTrace();
                    }
                    Object value = "row " + (count + 1) + " item " + (j + 1);
                    model.setValueAt(value, count, j);
                }
                count++;
                if (count >= myTable.getRowCount()) {
                    timer.stop();
                    myTable.changeSelection(0, 0, false, false);
                    //System.out.println("update cycle completed");
                    try {
                        Thread.sleep(30);
                    } catch (Exception e2) {
                        e2.printStackTrace();
                    }
                    myTable.clearSelection();
                    startButton.setEnabled(true);
                }
            }
        };
    }
 
    private void start() {
    	// Chirico adjusted from 100 to 1
        timer = new javax.swing.Timer(delay * 1, updateCol());
        timer.start();
    }
 
    public static void main(String args[]) {
        new TableDisplay();
    }
}
 
class TableBackroundPaint extends JTable {
 
    private static final long serialVersionUID = 1L;
 
    public TableBackroundPaint(Object[][] data, Object[] head) {
        super(data, head);
        setOpaque(false);
        ((JComponent) getDefaultRenderer(Object.class)).setOpaque(false);
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
            g2.setPaint(new GradientPaint(start.x, 0, controlColor, (int) 
                    ((end.x + end.width - start.x) * 1.25), 0, Color.blue));
            g2.fillRect(start.x, start.y, end.x + end.width - start.x, start.height);
        }
        super.paintComponent(g);
    }
}


class GraphCanvas extends Component {

    public GraphCanvas(Color faceColor) {
        setForeground(faceColor);
    }

    public Dimension getPreferredSize() {
        return new Dimension(300,300);
    }

   /*
    * Paint when the AWT tells us to...
    */
    public void paint(Graphics g) {
        // Dynamically calculate size information
        // (the canvas may have been resized externally...)
        Dimension size = getSize();
        int d = Math.min(size.width, size.height); // diameter
        int ed = d/20; // eye diameter
        int x = (size.width - d)/2;
        int y = (size.height - d)/2;

        // draw head (color already set to foreground)
        g.fillOval(x, y, d, d);
        g.setColor(Color.black);
        g.drawOval(x, y, d, d);

	g.drawLine(x,y,d,d);
        // draw eyes
        //g.fillOval(x+d/3-(ed/2), y+d/3-(ed/2), ed, ed);
        //g.fillOval(x+(2*(d/3))-(ed/2), y+d/3-(ed/2), ed, ed);

        //draw mouth
	// g.drawArc(x+d/4, y+2*(d/5), d/2, d/3, 0, -180);
    }
}
