package com.enporia.util;

import java.io.*;
import javax.microedition.io.*;

 public class SmtpEmailConnection implements EmailConnection
 {
 private InputStream input=null;
 private OutputStream output=null;
 private StreamConnection connection=null;
 private byte[] buffer=new byte[256];
 private static final byte[] CRLF = new byte[] {13, 10};

 public void open(String url, String localhost) throws IOException, EmailException
	 {
	 try	{
		 connection=(StreamConnection)Connector.open("socket://"+url+":25",Connector.READ_WRITE, true);
        	 output = connection.openOutputStream();
		 input = connection.openInputStream();
		 this.say(null);
		 this.say("HELO "+localhost);
		 }
	 catch (IOException e)
		 {
		 this.close();
		 throw e;
		 }
	 }

 public void close()
	 {
	 if (connection!=null)
		 {
		 try 	{
		 	this.say("QUIT");
			}
		catch (Exception e) {}	
		 try	{
			 
			 connection.close();
			 }
		 catch (Exception e) 	
		 	{
		 	return;
			} 	
		 connection=null;
		 input=null;
		 output=null;
		 }
	 }

 public void sendEmail(String from, String to, String subject, byte[] payload) throws IOException, EmailException 
	{
	this.say("MAIL FROM: <"+from +">");
	this.say("RCPT TO: <"+to+">");
	this.say("DATA");
	this.sendAsLines(payload);
	this.say(".");
	}


 public void sendAsLines(byte[] data) throws IOException
	 {
	
	 if (data.length>0)
		 {
		 int start=0;
		 int end=0;
		System.gc();
		 while (start<data.length)
			 {
			 end=start;
			 while(end<data.length && data[end]!=13 &&  data[end]!=10)
				 end++;
			 output.write(data, start, end-start);
			 output.write(CRLF);
			 if ((start%100)==0)
			 	{
				output.flush();
			 	System.gc();
				}
			 if (end<(data.length-1) && data[end]==13 &&  data[end+1]==10)
				 end++;
			 start=end+1;
			 }
		 }
	 else	{
		 output.write(CRLF);
		 }
	 }

 // Reads until a line break or EOF

 public String readLine() throws IOException
	 {
	 int offset=0;
	 int retcode=0;
	 String ret="";
	 do	{
		 offset=0;
		 while (true)
			 {
			 retcode=input.read(buffer,offset,1);

			 if (retcode==0)
				 {
				 try 	{
					 Thread.yield();
					 }
				 catch (Exception e) {}
				 continue;
				 }

			 if (retcode==-1)
				 {
				 try 	{
					 close(); 
					 }
				 catch (Exception e) {}
				 throw new IOException("Read returned -1");
				 }

			 if (buffer[offset]==10 || buffer.length==(offset+1) )	//line break read
				 break;
			 offset++;
			 }
		 ret+=new String(buffer,0,offset);
		 }
	 while (buffer.length==offset);
	 return ret;		
	 }

 public void say(String command) throws IOException, EmailException
	 {
	 System.out.println(command);
	 if (command!=null)
		 this.sendAsLines(command.getBytes());

	 String line=this.readLine();	
	 String result=line;
	 while (line.length()>3 && line.charAt(3)=='-')
		 line=this.readLine();
	 if (result.charAt(0)=='4' || result.charAt(0)=='5')
		throw new EmailException(result);
	  System.out.println(result);
	  }
 }
