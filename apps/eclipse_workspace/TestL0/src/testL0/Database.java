package testL0;

import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.users.User;

import java.util.Date;
import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

@PersistenceCapable
public class Database {
    @PrimaryKey
    @Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
    private Key key;

    @Persistent
    private String item;

    @Persistent
    private String content;
    
    @Persistent
    private String stuff;
    
    @Persistent
    private String remoteAddr;

    @Persistent
    private Date date;

    public Database(String item, String content, Date date, String stuff) {
        this.item = item;
        this.content = content;
        this.date = date;
        this.stuff = stuff;
    }
    
    public Database(String item, String content, Date date, 
    		String stuff,String remoteAddr ) {
        this.item = item;
        this.content = content;
        this.date = date;
        this.stuff = stuff;
        this.remoteAddr=remoteAddr;
    }
    
    

    public Key getKey() {
        return key;
    }

    public String getItem() {
        return item;
    }

    
    public String getContent() {
        return content;
    }

    public String getStuff() {
        return stuff;
    }
    public String getRemoteAddr(){
        return remoteAddr;
     }
    
    
    
    public Date getDate() {
        return date;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public void setDate(Date date) {
        this.date = date;
    }
    
    public void setRemoteAddr(String remoteAddr){
        this.remoteAddr=remoteAddr;
     }
    
}
