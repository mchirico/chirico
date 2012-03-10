package testL0;

import com.google.appengine.api.labs.taskqueue.Queue;
import com.google.appengine.api.labs.taskqueue.QueueFactory;
import static com.google.appengine.api.labs.taskqueue.TaskOptions.Builder.*;

import java.util.Date;

public class QueueAdder {

	public QueueAdder(String s) {
		// Queue queue = QueueFactory.getDefaultQueue();
		Queue queue = QueueFactory.getQueue("background-processing");
		queue.add(url("/task/q0").param("key", s));

	}

	public void blaster(String s) {
		Queue queue = QueueFactory.getDefaultQueue();
		// Queue queue = QueueFactory.getQueue("background-processing");
		queue.add(url("/task/q0").param("key", s ));

	}

}
