package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.io.*;
import java.io.*;
import java.util.*;

public class ActivationForm extends Form
{
public static final String STATUS_OK="0";
public static final String STATUS_CODENOTFOUND ="1";
public static final String STATUS_OLDCODE ="2";
public static final String STATUS_DBERROR ="3";
public static final String STATUS_WRONGMODULE="4";
public static final String MODULE_TIME="0";
public static final String MODULE_TRAVEL="1";
public static final String MODULE_STORAGE="2";

class ActivationThread extends Thread
{
private String code="";
private String module="";
private ActivationForm parent=null;

public ActivationThread(ActivationForm parent_, String code_, String module_)
	{
	this.parent=parent_;
	this.code=code_;
	this.module=module_;
	}
public void run()
	{
	//String url=Props.get("activation_url")+"?authcode="+this.code+"&module="+this.module;
	String url = Props.get("activation_url");
	HttpConnection c = null;
	InputStream is = null;
	OutputStream os = null;
	try 	{	 
		parent.reportConnecting();
		c = (HttpConnection)Connector.open("http://"+url);
		
		ByteArrayHolder holder=new ByteArrayHolder(this.code.getBytes());
		UrlEncoder.encode(holder);
		String eauthcode=new String(holder.data);
		
		holder.data=this.module.getBytes();
		UrlEncoder.encode(holder);
		String emodule=new String(holder.data);
		
		String params = "authcode="+eauthcode+"&module="+emodule;
		
		
		c.setRequestProperty("Content-Length",""+params.length());
		c.setRequestMethod(HttpConnection.POST);
		c.setRequestProperty("User-Agent","Profile/MIDP-1.0 Configuration/CLDC-1.0");
		c.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
	
		c.setRequestProperty("Accept","text/plain,text/html,*/*");
		os = c.openOutputStream();
		//os.write(params.getBytes());
		os.write(params.getBytes());
		os.flush();
		
		int responseCode = c.getResponseCode(); 
		
		
		is = c.openInputStream();
		if (is==null)
			throw new IOException();
	
		//String contentType = c.getType();
		//String debug = "ContentType oli: "+contentType+"\n";
		
		// Get the length and process the data
		int len = (int)c.getLength();
		
		//debug +="pituuskentän arvo oli: "+len+"\n";
		String ret = "";
		
		 if (len > 0) 
		 	{
            int actual = 0;
            int bytesread = 0 ;
            byte[] data = new byte[len];
            while ((bytesread != len) && (actual != -1)) 
            	{
                actual = is.read(data, bytesread, len - bytesread);
                bytesread += actual;
            	}
            ret = new String(data,0,bytesread);
		 	}
		else 	
			{
            int ch;
            StringBuffer sBuf = new StringBuffer();
            while ((ch = is.read()) != -1) 
            	{
                sBuf.append((char)ch);
            	}
			ret = sBuf.toString();
			}
        /*
		if (len > 0) 
			{
                	byte[] data = new byte[len];
                	int actual = is.read(data);
                	ret=new String(data);
            		} 
		else 	{
                	int ch;
                	while ((ch = is.read()) != -1) 
				{
                    		ret+=((char)ch);
                		}
            		}
		*/
		//debug+="ResponseCode oli: "+ responseCode+"\n";
		//debug+="Paluustring oli: "+ret;
		//parent.reportDebug(debug);
		
		//if (true)
		//	return;
		
		if (responseCode!=200)
			{
			throw new IOException();
			}	
        if (ret.length()<1 || !ret.startsWith(STATUS_OK))
			{
			parent.reportFailure(ret);
			try 	{
				if (is != null)
                			is.close();
            			if (c != null)
                			c.close();
        			}
			catch (Exception e1) {}
			return;
			}
		parent.reportSuccess();
		}
			
	catch (Exception e)
		{
		parent.reportConnectionFailure(e.toString());
		}	
	finally {
            	try 	{
			if (is != null)
                		is.close();
            		if (c != null)
                		c.close();
        		}
		catch (Exception e1) {}
		}
	}

}

private ActivationThread thread=null;
private boolean activated=false;
private OwnStringItem statusItem=null;
private TextField activationField=null;
private int aIndex=-1;
private static ActivationForm _instance=null;
public static Command ACTIVATIONFORM_OK = new Command(Props.get("common_ok"), Command.OK, 1);
public static Command ACTIVATIONFORM_CANCEL = new Command(Props.get("common_cancel"), Command.CANCEL, 1);
public static Command ACTIVATIONFORM_COMPLETED = new Command(Props.get("common_ok"), Command.OK, 1);
private String module="";

public static ActivationForm instance()
	{
	if (_instance==null)
		_instance=new ActivationForm();
	//_instance.activationField.setString("");
	return _instance;
	}

private ActivationForm()
	{
	super(Props.get("activationform_title"));
	
	this.statusItem=new OwnStringItem("","");
	this.activationField=new TextField("","",6,TextField.NUMERIC);
	
	}
	
public void setPrompt(String prompt)
	{
	this.activationField.setLabel(prompt);
	}
	
public void setModule(String _module)
	{
	this.module=_module;
	this.activated=false;
	if (MODULE_TIME.equals(_module))
		{
		this.setPrompt(Props.get("activationform_timerprompt"));
		}
	if (MODULE_TRAVEL.equals(_module))
		{
		this.setPrompt(Props.get("activationform_travelprompt"));
		}
	if (MODULE_STORAGE.equals(_module))
		{
		this.setPrompt(Props.get("activationform_storageprompt"));
		}
	}	
	
public String getModule()
	{
	return this.module;
	}	
	
public boolean isActivated()
	{
	return this.activated;
	}

public void checkActivationCode()
	{
	this.removeCommand(ACTIVATIONFORM_OK);
	String code=activationField.getString();
	if (code!=null && code!="")
		{
		this.thread=new ActivationThread(this,code,this.module);
		this.thread.start();
		}
	}
	
public void requestActivationCode()
	{
	if (this.aIndex!=-1)
		{
		this.statusItem.deleteFromForm(this);
		this.removeCommand(ACTIVATIONFORM_COMPLETED);
		}
	this.aIndex=this.append(this.activationField);
	this.statusItem.setText("");
	this.activationField.setString("");
	this.addCommand(ACTIVATIONFORM_OK);
	}
		
public void saveActivationInfo()
	{
	if (MODULE_TIME.equals(this.module))
		ProgramState.instance().setTimerActivated(true);
	if (MODULE_TRAVEL.equals(this.module))
		ProgramState.instance().setTravelActivated(true);
	if (MODULE_STORAGE.equals(this.module))
		ProgramState.instance().setStorageActivated(true);
	
	ProgramState.instance().save();
	}
		
private void reportConnecting()
	{
	this.delete(this.aIndex);
	this.statusItem.appendToForm(this);
	this.aIndex=1;
	this.statusItem.setText(Props.get("activationform_connecting"));
	}
			
private void reportSuccess()
	{
	this.activated=true;
	this.statusItem.setText(Props.get("activationform_success"));
	this.addCommand(ACTIVATIONFORM_COMPLETED);
	}
/*
private void reportDebug(String s)
	{
	this.activated=false;
	this.statusItem.setText(s);
	this.addCommand(ACTIVATIONFORM_COMPLETED);
	}
*/

private void reportFailure(String reason)
	{
	String message=Props.get("activationform_dbfailure");
	
	if (reason.length()>0 && reason.startsWith(STATUS_CODENOTFOUND))
		message=Props.get("activationform_codenotfound");
	if (reason.length()>0 && reason.startsWith(STATUS_OLDCODE))
		message=Props.get("activationform_oldcode");
	if (reason.length()>0 && reason.startsWith(STATUS_WRONGMODULE))
		message=Props.get("activationform_wrongmodule");
	
	this.statusItem.setText(message);
	this.addCommand(ACTIVATIONFORM_COMPLETED);
	}

private void reportConnectionFailure(String reason)
	{
	this.statusItem.setText(Props.get("activationform_connectionfailure")+" "+reason);
	this.addCommand(ACTIVATIONFORM_COMPLETED);
	}

}
