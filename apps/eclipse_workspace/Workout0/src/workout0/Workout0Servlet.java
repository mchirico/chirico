package workout0;

import java.io.IOException;
import javax.servlet.http.*;

@SuppressWarnings("serial")
public class Workout0Servlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");
		PrettyPrint p = new PrettyPrint();
		p.doStuff(req, resp, "This is stuff");
	}
}
