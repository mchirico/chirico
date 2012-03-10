package testL0;

import testL0.Database;
import testL0.PMF;

import java.io.IOException;
import java.util.Date;

import javax.jdo.PersistenceManager;
import javax.servlet.http.*;

import com.google.appengine.api.users.User;
import com.google.appengine.api.users.UserService;
import com.google.appengine.api.users.UserServiceFactory;

@SuppressWarnings("serial")
public class QueueWorker0 extends HttpServlet {

	public void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		UserService userService = UserServiceFactory.getUserService();

		String data = req.getParameter("key");
		Date date = new Date();

		PrBev p = new PrBev(req, resp);

		Beverage beverage = new Espresso();
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		p.totals();

		p.prDataPeople("3", "Bob", "Don", "Sample");

		String remoteAddr = req.getRemoteAddr();
		p.prData(beverage, data, remoteAddr);
		p.prdate();
		p.deleteAll();
		p.deleteAllPeople();

	}

}
