import java.io.File;
public class FileCopier {

    public static void main(String args[]) throws Exception {
        File inboxDirectory = new File("data/inbox");
        File outboxDirectory = new File("data/outbox");
	outboxDirectory.mkdir();

    }
}
