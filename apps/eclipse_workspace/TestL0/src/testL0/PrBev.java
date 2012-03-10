package testL0;
import java.io.IOException;

import javax.jdo.PersistenceManager;
import javax.servlet.http.*;
import java.util.Arrays;
import java.util.List;
import java.util.Date;


public class PrBev  {
    Beverage beverage;
    Integer orders;
    Double total_sell;
	private HttpServletRequest req;
	private HttpServletResponse resp;
	

    public PrBev (HttpServletRequest req, HttpServletResponse resp) {
        this.orders=0;
        this.total_sell=0.0;
        this.req=req;
        this.resp=resp;
        

    }

    public void pt(String s) throws IOException {
		resp.getWriter().println(s);
			
	}
    
    
    public void pr(Beverage beverage) throws IOException {
        this.beverage = beverage;
        this.orders+=1;
        this.total_sell+=beverage.cost();
        pt("\n"+beverage.getDescription()
                           + " $" + beverage.cost());
    }
    
    public String prs(Beverage beverage)  {
        this.beverage = beverage;
        this.orders+=1;
        this.total_sell+=beverage.cost();
        return ("\n"+beverage.getDescription()
                           + " $" + beverage.cost());
    }
    

    
    
    
    
    
    public void prData(Beverage beverage,String content) {
        
        Date date = new Date();
        Database database = new Database(this.prs(beverage), content, date, "prData 2 param");

        
     	
        PersistenceManager pm = PMF.get().getPersistenceManager();
        try {
       
            pm.makePersistent(database);
        } finally {
            pm.close();
        }       
    	
    }
    
    
    
    public void prDataPeople(String id,String fn,String ln, String desc) {
        
        Date date = new Date();
        DatabasePeople database = new 
            DatabasePeople(id, fn, ln, desc);

        
     	
        PersistenceManager pm = PMF.get().getPersistenceManager();
        try {
       
            pm.makePersistent(database);
        } finally {
            pm.close();
        }       
    	
    }    
    
    

    public void prData(Beverage beverage,String content, String remoteAddr) {
        
        Date date = new Date();
        Database database = new Database(this.prs(beverage), 
        		content, date, "prData",remoteAddr);

        
     	
        PersistenceManager pm = PMF.get().getPersistenceManager();
        try {
       
            pm.makePersistent(database);
        } finally {
            pm.close();
        }       
    	
    }
    
    
    public void prdate() throws IOException 
    {
    	
    	PersistenceManager pm = PMF.get().getPersistenceManager();
    	String query = "select from " + Database.class.getName();
    	List<Database> database = (List<Database>) pm.newQuery(query).execute();
        
        for (Database d : database) {
        	pt(d.getDate().toString());
        	
        }
    }
    
    
    public void deleteAll() throws IOException
    {
    	PersistenceManager pm = PMF.get().getPersistenceManager();
    	String query = "select from " + Database.class.getName();
    	pm.newQuery(query).deletePersistentAll();
        
       
    }
    
    
    public void deleteAllPeople() throws IOException
    {
    	PersistenceManager pm = PMF.get().getPersistenceManager();
    	String query = "select from " + DatabasePeople.class.getName();
    	pm.newQuery(query).deletePersistentAll();
        
       
    }
    
    

    public void totals() throws IOException
    {

        pt("\n\n************* Totals **************\n");
        pt("orders:\t"+ orders +"\nSales: \t"+ total_sell +"\n");

    }

}


