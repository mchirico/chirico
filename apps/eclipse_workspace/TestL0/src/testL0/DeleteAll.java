package testL0;



import testL0.Database;
import testL0.PMF;

import java.io.IOException;
import java.util.Date;

import javax.jdo.PersistenceManager;
import javax.servlet.http.*;

@SuppressWarnings("serial")
public class DeleteAll extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp)
	throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");
		
		stuff0 s0 = new stuff0(req,resp);
		s0.pt("Test here");
		
		PrBev p = new PrBev(req,resp);
		
		Beverage beverage = new Espresso();
        p.pr(beverage);
        beverage = new Mocha(beverage);
        p.pr(beverage);
        beverage = new Mocha(beverage);
        p.pr(beverage);
        p.totals();
        
        p.prData(beverage, "Wow Test0");		
		p.prdate();      
        p.deleteAll(); 
        
		
	}
}