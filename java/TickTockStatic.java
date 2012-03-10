import java.awt.event.*;
import javax.swing.*;

public class TickTockStatic
{
    private static String tickMessage = "Tick...";
    private static String tockMessage = "Tock...";

    public static void main(String[] args)
    {
	TickTockStatic t = new TickTockStatic();
	t.go();
    }

    private void go()
    {
	Timer t = new Timer(1000, new Ticker());
	t.start();

	JOptionPane.showMessageDialog(null, "Click OK to exit program");
	System.exit(0);
    }

    static class Ticker implements ActionListener
    {
	private boolean tick=true;
	public void actionPerformed(ActionEvent event)
	{
	    if (tick)
		{
		    System.out.println(tickMessage);
		}
	    else
		{
		    System.out.println(tockMessage);
		}
	    tick=!tick;
	}
    }
}