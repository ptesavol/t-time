package com.enporia.util;

import java.io.*;
import javax.microedition.io.*;

public class HttpEmailConnection implements EmailConnection
{
private String url="";
public void open(String url, String localhost) throws IOException, EmailException
	{
	this.url=url;
	}
public void close()
	{}	 
public void sendEmail(String from, String to, String subject, byte[] payload)	throws IOException, EmailException 
	{ 
	HttpConnection c = null;
	InputStream is = null;
	OutputStream os = null;

	try 	{	 
		c = (HttpConnection)Connector.open("http://"+url);
		ByteArrayHolder holder=new ByteArrayHolder(to.getBytes());
		UrlEncoder.encode(holder);
		String eto=new String(holder.data);
		holder.data=subject.getBytes();
		UrlEncoder.encode(holder);
		String esubject=new String(holder.data);
		holder.data=payload;
		UrlEncoder.encode(holder);
		System.gc();
		
		String params=	"to="+eto+"&"+"subject="+esubject+"&"+
				"message=";
		
		
		c.setRequestProperty("Content-Length",""+params.length()+holder.data.length);
		c.setRequestMethod(HttpConnection.POST);
		c.setRequestProperty("User-Agent","Profile/MIDP-1.0 Configuration/CLDC-1.0");
		c.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
		
		
		// Getting the output stream may flush the header
	
		
		os = c.openOutputStream();
		//os.write(params.getBytes());
		os.write(params.getBytes());
		os.write(holder.data);
		holder.data=null;
		holder=null;
		System.gc();
		//os.flush();                
		// Optional, openInputStream will flush

		// Opening the InputStream will open the connection
		// and read the HTTP headers. They are stored until
		// requested.
		is = c.openInputStream();
		if (is==null)
			throw new IOException();
			
		
		// Get the length and process the data
		int len = (int)c.getLength();
		String ret="";
		if (len > 0) 
			{
                	byte[] data = new byte[len];
                	//int actual = is.read(data);
                	ret=new String(data);
            		} 
		else 	{
                	int ch;
                	while ((ch = is.read()) != -1) 
				{
                    		ret+=((char)ch);
                		}
            		}
		
		if (c.getResponseCode()!=200)
			{
			throw new EmailException(ret);
			}	
        	if (ret.length()>1 && !ret.startsWith("OK"))
			{
			throw new EmailException(ret);
			}
		} 
	finally {
            	if (is != null)
                	is.close();
            	if (os != null)
                	os.close();
            	if (c != null)
                	c.close();
        	}
    
	}
	
	
}
