import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class HelloFrame1 extends JFrame {
  public static void main(String[] args) {
    new HelloFrame1();
  }

  public HelloFrame1() {
    this.setSize(800, 200);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setTitle("New1!");
    this.setVisible(true);
  }
}
