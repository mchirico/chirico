import javax.swing.JFrame;

public class HelloFrame extends JFrame {
  public static void main(String[] args) {
    new HelloFrame();
  }

  public HelloFrame() {
    this.setSize(200, 100);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setTitle("Hello World!");
    this.setVisible(true);
  }
}
