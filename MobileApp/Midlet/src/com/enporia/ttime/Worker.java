package com.enporia.ttime;

import com.enporia.util.*;
import com.enporia.util.*;
import javax.microedition.lcdui.Image;
import java.io.*;

public class Worker extends DataObject implements Saveable
{
private static Worker _instance=null;
private String email="";
private String emailserver="";
private String emailproxy="";
private String imapserver=""; // 17.9.2008, J.V.
private String imapport=""; // 4.11.2009, J.V.
private boolean useimapencrypted=false; // 4.11.2009, J.V.
private boolean useproxy=false;
private boolean namefirst=true;
private boolean roundtonearest=true;
private long rounding=0;
private int stringItemMode = 0;

public static Worker instance()
	{
	if (_instance==null)
		{
		DataObject tobj=WorkerStore.instance().getSavedObject();
		if (tobj==null)
			_instance=new Worker();
		else _instance=(Worker)tobj;
		}
	return _instance;
	}
	
public Worker()
	{}

public Worker(String name)
	{
	this.name=name;
	}

public Worker(String name, String email, String emailserver, String emailproxy, String imapserver, String imapport, boolean useproxy)
	{
	this.name=name;
	this.email=email;
	this.emailserver=emailserver;
	this.emailproxy=emailproxy;
	this.imapserver=imapserver;
	this.imapport=imapport;
	this.useproxy=useproxy;
	}
/*
public Worker(String name, int id)
	{
	this.name=name;
	this.id=id;
	}
*/	
		
public void setEmail(String email)
	{
	this.email=email;
	}

public void setEmailServer(String emailserver)
	{
	this.emailserver=emailserver;
	}

public void setEmailProxy(String emailproxy)
	{
	this.emailproxy=emailproxy;
	}

public void setIMAPServer(String imapserver) // 17.9.2008, J.V.
{
this.imapserver=imapserver;
}

public void setIMAPPort(String imapport) // 4.11.2009, J.V.
{
this.imapport=imapport;
}

public void setUseIMAPEncrypted(boolean useimapencrypted) // 4.11.2009, J.V.
{
this.useimapencrypted=useimapencrypted;
}

public void setUseProxy(boolean useproxy)
	{
	this.useproxy=useproxy;
	}	

public void setNameFirst(boolean first)	
	{
	this.namefirst=first;
	}

public void setRoundToNearest(boolean val)
	{
	this.roundtonearest=val;
	}	

public void setRounding(long val)
	{
	this.rounding=val;
	}
public void setStringItemMode(int val)
	{
	this.stringItemMode = val;
	}

public String getEmail()
	{
	return this.email;
	}

public String getEmailServer()
	{
	return this.emailserver;
	}
	
public String getEmailProxy()
	{
	return this.emailproxy;
	}

public String getIMAPServer() // 17.9.2008, J.V.
{
return this.imapserver;
}

public String getIMAPPort() // 4.11.2009, J.V.
{
return this.imapport;
}

public boolean useIMAPEncrypted() // 4.11.2009, J.V.
{
return this.useimapencrypted;
}

public boolean useProxy()
	{
	return this.useproxy;
	}

public boolean isNameFirst()
	{
	return this.namefirst;
	}
	
public boolean isRoundToNearest()
	{
	return this.roundtonearest;
	}
	
public long getRounding()
	{
	return this.rounding;
	}
public int getStringItemMode()
	{
	return this.stringItemMode;
	}

public byte[] getBytes()
	{
	byte[] data=null;
	try	{
		super.output.writeUTF(this.name);
		super.output.writeUTF(this.email);
		super.output.writeUTF(this.emailserver);
		super.output.writeUTF(this.emailproxy);
		super.output.writeUTF(this.imapserver); // 17.9.2008, J.V.
		super.output.writeUTF(this.imapport); // 4.11.2009, J.V.
		super.output.writeBoolean(this.useimapencrypted); // 4.11.2009, J.V.
		super.output.writeBoolean(this.useproxy);	
		super.output.writeBoolean(this.namefirst);
		super.output.writeBoolean(this.roundtonearest);
		super.output.writeLong(this.rounding);
		super.output.writeInt(this.stringItemMode);
		super.output.flush(); 
		data=super.byteoutput.toByteArray(); 
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}
	super.byteoutput.reset();	
	return data;
	} 

public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		this.name=dinput.readUTF();
		this.email=dinput.readUTF();
		this.emailserver=dinput.readUTF();
		this.emailproxy=dinput.readUTF();
		this.imapserver=dinput.readUTF(); // 17.9.2008, J.V.
		this.imapport=dinput.readUTF(); // 4.11.2009, J.V.
		this.useimapencrypted=dinput.readBoolean(); // 4.11.2009, J.V.
		this.useproxy=dinput.readBoolean();
		this.namefirst=dinput.readBoolean();
		this.roundtonearest=dinput.readBoolean();
		this.rounding=dinput.readLong();
		this.stringItemMode=dinput.readInt();
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}	
	}
/*
public String getRenderingName()
	{
	return null;
	}
	
public Image getRenderingImage()
	{
	return null;
	}
*/	
public void save()
	{
	WorkerStore.instance().saveObject(this);
	_instance=this;
	}
}
