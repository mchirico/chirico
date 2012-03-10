//file:	GridBagDev0.java
//package com.cwxstat.dev
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.table.*;




public class GridBagDev0 extends JPanel implements ActionListener, Runnable {
    GridBagConstraints constraints = new GridBagConstraints();
    SpTable spt;
    SpTable spt2;

    public GridBagDev0() {


	String[] head = {"One", "Two", "Three", "Four", "Five", "Six","Seven","Eight","Nine","Ten"};
        String[][] data = new String[20][head.length];

	String[] head2 = {"1", "2", "3", "4", "5", "6"};
        String[][] data2 = new String[20][head2.length];

        spt = new SpTable(head,data);
        spt2 = new SpTable(head2,data2);


        spt.setValue("wow", 1, 1);
        setLayout(new GridBagLayout());
        constraints.weightx	= 1.0;
        constraints.weighty	= 1.0;
        constraints.fill = GridBagConstraints.BOTH;
        int	x, y;  // for clarity
        constraints.gridheight = 2;	// span	two rows
        addGB(new JButton("one"),	x = 0, y = 0);
        constraints.gridheight = 1;	// set it back
        addGB(new JButton("two"),	x = 1, y = 0);
        addGB(new JScrollPane(spt2.getTable()),	x = 2, y = 0);
        constraints.gridwidth = 2; // span two columns

        addGB(new JScrollPane(spt.getTable()),	x = 1, y = 1);
        constraints.gridwidth = 1; // set it back

        spt.setValue("GO", 5, 1);

    }

    void addGB(Component component, int x, int y)	{
        constraints.gridx =	x;
        constraints.gridy =	y;
        add(component, constraints);
    }

    public static	void main(String[] args) {
        (new Thread(new GridBagDev0())).start();

    }





    @Override
    public void run() {
        int j=0;
        String value="stuff";
        JFrame frame = new JFrame("GridBagDev0");
        frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        frame.setSize(800, 400);
        frame.setLocation(200, 200);
        frame.setContentPane(this);
        frame.setVisible(true);

        while (true) {
            try {// Chirico - this is second update
                System.out.println("Did run()\n");
                for (int i=0; i <= 5; ++i) {
                    spt.setValue(value, j, i);
                    spt2.setValue(value, j, i);
		    spt.setColor();
                }
                Thread.sleep(2000);
            } catch (Exception e) {
                e.printStackTrace();
            }
            j=j+1;
            if (value == "stuff") {
                value="Wow";
            } else {
                value="stuff";
            }
            if (j >= 12 ) j=0;
        }
    }


    @Override
    public void actionPerformed(ActionEvent e) {

    }
}


class SpTable {
    private JTable myTable;

    public  SpTable(String[] head, String[][] data) {
	//        String[] head = {"One", "Two", "Three", "Four", "Five", "Six","Seven","Eight","Nine","Ten"};
        //        String[][] data = new String[20][head.length];

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


    }

    public void setColor() {
	myTable.paintImmediately(3, 5, 10,60);
    }


    public void setValue(String value, int row, int column) {
        myTable.setValueAt(new String(value), row, column);
        myTable.changeSelection(row, column, false, false);
    }

    public JTable getTable() {

        return myTable;
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

