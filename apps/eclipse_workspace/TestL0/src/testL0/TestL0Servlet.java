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
public class TestL0Servlet extends HttpServlet {

	public void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		UserService userService = UserServiceFactory.getUserService();

		String content = req.getParameter("content");
		Date date = new Date();

		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");

		stuff0 s0 = new stuff0(req, resp);
		s0.pt(content + " " + date.toString());

		PrBev p = new PrBev(req, resp);

		Beverage beverage = new Espresso();
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		p.totals();

		String data_s = req.getParameter("stuff");
		String remoteAddr = req.getRemoteAddr();
		p.prData(beverage, data_s, remoteAddr);
		p.prdate();

	}

	public void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");

		String remoteAddr = req.getRemoteAddr();

		stuff0 s0 = new stuff0(req, resp);
		s0.pt("Test here");

		PrBev p = new PrBev(req, resp);

		Beverage beverage = new Espresso();
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		beverage = new Mocha(beverage);
		p.pr(beverage);
		p.totals();

		String data_s = req.getParameter("stuff");

		p.prData(beverage, data_s, remoteAddr);
		p.prdate();

		QueueAdder q = new QueueAdder("Test of Q");
		q.blaster("Test of Blaster");

	}
}
