package testL0;

import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.users.User;

import java.util.Date;
import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.PrimaryKey;

@PersistenceCapable
public class DatabasePeople {
	@PrimaryKey
	@Persistent(valueStrategy = IdGeneratorStrategy.IDENTITY)
	private Key key;

	@Persistent
	private String id;

	@Persistent
	private String fn;

	@Persistent
	private String ln;

	@Persistent
	private String desc;

	@Persistent
	private Date date;

	@Persistent
	private String remoteAddr;

	public DatabasePeople(String id, String fn, String ln, String desc) {
		this.id = id;
		this.fn = fn;
		this.ln = ln;
		this.desc = desc;
	}

	public DatabasePeople(String id, String fn, String ln, String desc,
			Date date, String remoteAddr) {
		this.id = id;
		this.fn = fn;
		this.ln = ln;
		this.desc = desc;
		this.date = date;
		this.remoteAddr = remoteAddr;
	}

	public Key getKey() {
		return key;
	}

	public String getId() {
		return id;
	}

	public String getDesc() {
		return desc;
	}

	public String getFn() {
		return fn;
	}

	public String getLn() {
		return ln;
	}

	public String getRemoteAddr() {
		return remoteAddr;
	}

	public Date getDate() {
		return date;
	}

	public void setId(String id) {
		this.id = id;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public void setFn(String fn) {
		this.fn = fn;
	}

	public void setDate(Date date) {
		this.date = date;
	}

	public void setRemoteAddr(String remoteAddr) {
		this.remoteAddr = remoteAddr;
	}

}
