import java.awt.*;
import javax.swing.*;
import javax.swing.table.*;
 
public class TablePrepareRenderer extends JFrame
{
    JTable table;
 
    public TablePrepareRenderer()
    {

	Object[] columnNames = {"Type", "Company", "Shares", "Price"};
	Object[][] data =
	{
	    {"Buy", "IBM", new Integer(1000), new Float(80.50)},
	    {"Sell", "MicroSoft", new Integer(2000), new Float(6.25)},
	    {"Sell", "Apple", new Integer(3000), new Float(7.35)},
	    {"Buy", "Nortel", new Integer(4000), new Float(20.00)}
	};
 


	DefaultTableModel model = new DefaultTableModel(data, columnNames);
	table = new JTable( model )
	    {
		//  Returning the Class of each column will allow different
		//  renderers to be used based on Class
		public Class getColumnClass(int column)
		{
		    return getValueAt(0, column).getClass();
		}
 
		public Component prepareRenderer(TableCellRenderer renderer, int row, int column)
		{
		    Component c = super.prepareRenderer(renderer, row, column);
		    if (!c.getBackground().equals(getSelectionBackground()))
			{
			    String type = (String)getModel().getValueAt(row, 0);
			    c.setBackground( type.equals("Buy") ? Color.GREEN : Color.YELLOW );
			}
		    return c;
		}
	    };
	table.setPreferredScrollableViewportSize(table.getPreferredSize());
	JScrollPane scrollPane = new JScrollPane( table );
	getContentPane().add( scrollPane );
    }
 
    public static void main(String[] args)
    {
	TablePrepareRenderer frame = new TablePrepareRenderer();
	frame.setDefaultCloseOperation( EXIT_ON_CLOSE );
	frame.pack();
	frame.setLocationRelativeTo( null );
	frame.setVisible(true);
    }
}
