package com.chirico;
import java.util.Date;
import java.util.Calendar;
import java.text.SimpleDateFormat;
public class MyForm {
	MyForm() {


	}

        String pr() {
	    Calendar now = Calendar.getInstance();
	    SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy hh:mm");
	    String s="<form name='input'  method='post'> Date:<br><input type='text' name='date' value='";
            s=s+formatter.format(now.getTime());
	    s=s+"' />";
	    s=s+"<br>Hrs:<br> <input type='text' name='hrs' value='10'";
	    s=s+"<br>End Hours:<br> <input type='text' name='etime' value='18:00'";
	    s=s+"<br>Pay Period:<br> <input type='text' name='payp' value='14'";
	    s=s+"<br>Notes:<br> <input type='text' name='notes' value='Notes   here'";
	    s=s+"<br><input type='submit' value='Submit' /></form>";
	return s;
    }
    }

