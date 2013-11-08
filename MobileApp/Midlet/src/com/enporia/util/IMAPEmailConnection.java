/*
 * 19.9.2008, J.V.
 */

package com.enporia.util;

import java.io.*;
import java.util.*;

import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;
import javax.microedition.io.SecureConnection;
import javax.microedition.io.SocketConnection;

public class IMAPEmailConnection
{
	class DateC
	{
		public int day = 0;
		public int month = 0;
		public int year = 0;
		public int hour = 0;
		public int min = 0;
		public int sec = 0;

		DateC() {}
		
		DateC(int day, int month, int year, int hour, int min, int sec)
		{
		this.day = day;
		this.month = month;
		this.year = year;
		this.hour = hour;
		this.min = min;
		this.sec = sec;
		}
		
		public int compare(DateC date1,  DateC date2)
		{ // returns: -1=date1 is less (older), 0=dates are equal, 1=date1 is greater (newer)
			if(date1.year > date2.year) return 1;
			if(date1.year < date2.year) return -1;

			if(date1.month > date2.month) return 1;
			if(date1.month < date2.month) return -1;

			if(date1.day > date2.day) return 1;
			if(date1.day < date2.day) return -1;
			
			if(date1.hour > date2.hour) return 1;
			if(date1.hour < date2.hour) return -1;
			
			if(date1.min > date2.min) return 1;
			if(date1.min < date2.min) return -1;
			
			if(date1.sec > date2.sec) return 1;
			if(date1.sec < date2.sec) return -1;
			
			return 0;
		}
		
		public boolean zero()
		{
			if(this.day == 0 && this.month == 0 && this.year == 0 && this.hour == 0 && this.min == 0 && this.sec == 0)
				return true;

			return false;
		}
	}
	
private InputStream input = null;
private OutputStream output = null;
private StreamConnection connection = null;
private SecureConnection secconnection = null;

private static final int READSIZE = 256;
private byte[] buffer = new byte[READSIZE];
private ByteArrayOutputStream readbuffer = new ByteArrayOutputStream(READSIZE);
private ByteArrayOutputStream lineread = new ByteArrayOutputStream(READSIZE);

public static final String CONNECT = "CONNECT";
private static final String LOGIN = "LOGIN";
private static final String SELECT = "SELECT";
private static final String SEARCH = "SEARCH";
private static final String FETCH = "FETCH";
private static final String FETCH_INTERNALDATE = "FETCH_INTERNALDATE";
private static final String FETCH_MAIL = "FETCH_MAIL";
//private static final String STORE = "STORE";

private static final int  FIND_APP_HEADER = 0;
//private static final int  EXAMINE_HEADER = 1;
private static final int  GET_ATTACHMENT = 2;
private static final int  PROCESS_ATTACHMENT = 3;

public static final byte[] CRLF = {13, 10};
public static final String[] SPACE = {" "};
public static final String[] REGX = {";", ":", "="};
public static final String[] OCTS = {" ", "{", "}" };
public static final String[] SPLITDATE = {"-", ":", " "};
public static final String[] QUOTE = {"\""};
public static final char[] IGNORENONE = {};
public static final char[] IGNORESPACE = {32};
public static final String UNTAGGED = "*";
public static final String OK = "OK";
public static final String NO = "NO";
public static final String BAD = "BAD";
public static final String READWRITE = "[READ-WRITE";
public static final String READONLY = "[READ-ONLY]";

private int prefix = 1;
private String prefixStr = "";
private String fetch_result = "";
private String search_result = "";
ByteArrayOutputStream attachment_data = new ByteArrayOutputStream(READSIZE);
private String attachment_name = "";
private String content_transfer_encoding = "";

private Vector boundaries = new Vector();

private int oct_pos;
private int octet_count;

private static final Boolean DEBUG = false;

public void open(String url, String localhost, String port, boolean useEncryption) throws IOException, EmailException
	{
	 try	{		 
		 if(useEncryption == false)
		 	{
			 connection=(StreamConnection)Connector.open("socket://"+url+":"+port,Connector.READ_WRITE, true);
			 output = connection.openOutputStream();
			 input = connection.openInputStream();
		 	}
		 else
		 	{
			 secconnection = (SecureConnection)Connector.open("ssl://"+url+":"+port,Connector.READ_WRITE, true);
			 //SecurityInfo info = sconnection.getSecurityInfo();
			 //boolean isTLS = (info.getProtocolName().equals("TLS"));
			 //sconnection.setSocketOption(SocketConnection.LINGER, 5);
			 output = secconnection.openOutputStream();
			 input = secconnection.openInputStream();
		 	}
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
		 try
		 {
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
	 
	 if (secconnection!=null)
	 {
		 try
		 {
		 secconnection.close();
		 }
		 catch (Exception e) 	
		 {
		 return;
		 }

		 secconnection=null;
		 input=null;
		 output=null;
	 }
}

private byte[] getAllBytes(int mode) throws IOException
	{
	byte[] bytes = null;
	String rstr = "";
	String[] split = null;

	this.readbuffer.reset();                     // clear read buffer
	
	// Read data one line at a time. Break when line length equals zero.
	while(true)
	{
		readLine();                              // read line
		bytes = this.lineread.toByteArray();

		if(bytes.length == 0) continue;          // store line: only if something to store, otherwise continue reading
		this.readbuffer.write(bytes);            
		this.readbuffer.write(10);               // + LF to complete line with CRLF instead of just CR

		if(checkOctets(bytes))                   // check if there's octets defined on this line (more bytes to come :)) -> add the bytes to 'readBuffer'
			readBytes(this.octet_count);

		rstr = this.lineread.toString();         // wait for the last line, line that has current 'prefixStr' on it
		if(mode == 1) break;                     // mode = 1 -> server greetings: no 'prefixStr', only untagged * response
		split = GetLine.splitLine(rstr, SPACE, IGNORENONE, 0);       // split, wait for current 'prefixStr'
		if(split.length > 0)
		{
			if(split[0].equals(prefixStr))
				break;
		}
	}

	bytes = null;
	System.gc();	
	return this.readbuffer.toByteArray();
	}

public void readLine() throws IOException
{
	int offset=0;
	int retcode=0;
	//String ret="";
	this.lineread.reset();
	do	{
		offset=0;
		while (true)
		{
			retcode=input.read(buffer,offset,1);

			if (retcode==0)
			{
				try { Thread.yield(); }
				catch (Exception e) {}
				continue;
			}
			
			if (retcode==-1)
			{
				throw new IOException("Read returned -1");
			}

			if (buffer[offset]==10 || buffer.length==(offset+1) )	//line break read
				break;
			offset++;
		}

		//ret+=new String(buffer,0,offset);
		this.lineread.write(buffer, 0, offset);
	}
	while (buffer.length==offset);

	//return ret;
}

public void readBytes(int size) throws IOException
	{
	int read;
	int insize = 0;

	// get some defined amount of bytes
	while(size > 0)
	{
		if(size > READSIZE) read = READSIZE;
		else read = size;

		if((insize = input.read(this.buffer, 0, read)) > 0)
			this.readbuffer.write(this.buffer, 0, insize);

		size -= insize;
	}
	}

public void writeBytes(String out) throws IOException
	{
	String data = makePrefix() + out;
	byte[] bytes = data.getBytes(/*"US-ASCII"*/);

	output.write(bytes, 0, bytes.length);
	output.write(CRLF);
	output.flush();
	}

public void login(String username, String password, OwnStringItem statusItem) throws CustomException, IOException
	{
	//byte bytes[] = null;
	String ret;
	String split[] = null;

	String stext = new String(statusItem.getText()); // debug
		
	// Connect - confirm connection with an IMAP-server
	if(DEBUG) { stext += ">CON"; statusItem.setText(stext); } // debug
	if((ret = checkResponse(getAllBytes(1), CONNECT)) != "")
		throw new CustomException(Props.get("getlists_noresponse"));
	
	// LOGIN
	if(DEBUG) { stext += ">LGI"; statusItem.setText(stext); } // debug
	writeBytes(" LOGIN " + username + " " + password);	
	if((ret = checkResponse(getAllBytes(-1), LOGIN)) != "")
		throw new CustomException(Props.get("getlists_loginfail") + "\n" + ret);
	
	// SELECT inbox
	if(DEBUG) { stext += ">SEL"; statusItem.setText(stext); } // debug
	writeBytes(" SELECT INBOX");
	if((ret = checkResponse(getAllBytes(-1), SELECT)) != "")
		throw new CustomException(Props.get("getlists_selfail") + "\n" + ret);

	// SEARCH the inbox for all the messages having known identifier in their subject field
	if(DEBUG) { stext += ">SEA"; statusItem.setText(stext); } // debug
	search_result = "";
	writeBytes(" SEARCH SUBJECT \"" + Props.get("lists_identifier") + "\"");
	if((ret = checkResponse(getAllBytes(-1), SEARCH)) != "")
		throw new CustomException(Props.get("getlists_searchfail") + "\n" + ret);

	// Separate search results
	if((split = GetLine.splitLine(search_result.trim(), SPACE, IGNORENONE, 0)).length == 0)
		throw new CustomException(Props.get("getlists_searchnone"));

	// Find the latest date
	if(DEBUG) { stext += ">INT"; statusItem.setText(stext); } // debug
	String msg = split[0];
	DateC date = new DateC(0, 0, 0, 0, 0, 0);
	DateC date_new = new DateC();
	for(int i=0; i<split.length; i++)
	{
		fetch_result = "";
		writeBytes(" FETCH " + split[i] + " INTERNALDATE");
		if((ret = checkResponse(getAllBytes(-1), FETCH_INTERNALDATE)) != "")
			throw new CustomException(Props.get("getlists_fetchfail") + "\n" + ret);
		
		if((date_new = parseDate(fetch_result)).zero()) continue;
		
		if(date.compare(date_new, date) > 0)
		{
			date = date_new;
			msg = split[i];
		}
	}
	
	// FETCH the latest mail
	if(DEBUG) { stext += ">FET"; statusItem.setText(stext); } // debug

	attachment_data.reset();
	attachment_name = "";
	content_transfer_encoding = "";

	writeBytes(" FETCH " + msg + " BODY[TEXT]");
	if((ret = checkResponse(getAllBytes(-1), FETCH_MAIL)) != "")
		throw new CustomException(Props.get("getlists_fetchfail") + "\n" + ret);
	if(Attachments.instance().getSize() == 0)
		throw new CustomException(Props.get("getlists_fetchfail_att") + "\n" + ret);

	// STORE +flags \deleted
	//writeBytes(" STORE " + split[i] + " +FLAGS.SILENT \\DELETED");
	//if((ret = checkResponse(getAllBytes(-1), STORE)) != "")
		//throw new CustomException(Props.get("getlists_fetchfail") + "\n" + ret);
	
	// LOGOUT
	if(DEBUG) { stext += ">LGO"; statusItem.setText(stext); } // debug
	writeBytes(" LOGOUT");
	}

public String checkResponse(byte[] bytes, String mode) throws IOException
	{
	int state = FIND_APP_HEADER, li;
	String line[] = null;
	String tokens[] = null;
	String temp;
	boolean boundary;

    GetLine gl = new GetLine(bytes, CRLF);
    while((line = gl.getNextLine()) != null)
	{
//System.out.println(line[0]);
    	// Tokenize
    	tokens = GetLine.splitLine(line[0], SPACE, IGNORENONE, GetLine.TOUPPER);

    	// error handling
    	if(tokens.length >= 2)
    	{
    		// protocol-level and server internal failures => BAD
    		if(tokens[1].equals(BAD)) return makeString(tokens, 1);
    		
    		// unsuccessful completion of an associated command  
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(NO)) return makeString(tokens, 1);
    	}

    	// All the necessary modes when communicating with an IMAP-server
    	if(mode.equals(CONNECT) && tokens.length >= 2)
    	{ // search * OK from the beginning of a line -> IMAP-server ready to receive commands
    		if(tokens[0].equals(UNTAGGED) && tokens[1].equals(OK)) return "";
		}
    	if(mode.equals(LOGIN) && tokens.length >= 2)
    	{ // wait for successful login
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    	}
    	if(mode.equals(SELECT) && tokens.length >= 2)
    	{ // wait for successful inbox selection
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    	}
    	if(mode.equals(SEARCH) && tokens.length >= 2)
    	{ // wait for successful search, store search result
    		if(tokens[0].equals(UNTAGGED) && tokens[1].equals(SEARCH)) search_result += makeString(tokens, 2);
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    	}
    	if(mode.equals(FETCH_INTERNALDATE) && tokens.length >= 2)
    	{ // wait for successful search, store search result
    		if(tokens[0].equals(UNTAGGED) && tokens[2].equals(FETCH)) fetch_result = line[0];
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    	}
    	if(mode.equals(FETCH_MAIL))
    	{ // get the attachment, wait for successful operation
    		// Was fetch successful
    		if(tokens.length >= 2)
    		{
    		    if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    		}

    		// Store all the unique mime boundaries - used when storing the actual attachment data
    		boundary = checkBoundary(line[0]);
    		
    		// Examine attachment - "state machine"
    		if(state == FIND_APP_HEADER)
    		{ // find: content-type: attachment/tta or similar headers
    			temp = line[0].toLowerCase();

    			//OLD FIND_APP_HEADER->EXAMINE_HEADER 1/2 SEE BELOW FOR PART 2/2
    			//if(temp.indexOf("content-type") != -1 && temp.indexOf("application") != -1 /*&& temp.indexOf("tta") != -1*/)
    				//state = EXAMINE_HEADER;

    			if(temp.indexOf("content-type") != -1 && temp.indexOf("application") != -1 /*&& temp.indexOf("tta") != -1*/)
    			{
        			temp = "";								// 15.8.2010, J.V. Make one big string of the attachment header
    				do {
    					temp += line[0] + " ";
    				    line = gl.getNextLine();
    				} while(!line[0].equals(""));

					Vector fvect = new Vector();				// Separate the fields
    				do
    				{
    					li = temp.lastIndexOf(':');
    					li = temp.lastIndexOf(' ', li);
    					if(li != -1)
    					{
    						fvect.addElement(temp.substring(li).trim());
							temp = temp.substring(0, li);
    					}
    				} while(li != -1);
					fvect.addElement(temp.trim());

					for(int v=0; v<fvect.size(); v++)			// Get parameters
					{
		    			if((tokens = GetLine.splitLine((String)fvect.elementAt(v), REGX, IGNORENONE, GetLine.TRIMSPACE|GetLine.TRIMQUOTE)).length == 0) continue;

		    	        if(tokens[0].equalsIgnoreCase("content-type") || tokens[0].equalsIgnoreCase("content-disposition"))
		    	        {
		    	          for(int i=2; i<tokens.length; i+=2)
		    	          { if(tokens[i].equalsIgnoreCase("name") || tokens[i].equalsIgnoreCase("filename")) attachment_name = tokens[i + 1]; }
		    	        }

		    	        if(tokens[0].equalsIgnoreCase("content-transfer-encoding"))
		    	        	content_transfer_encoding = tokens[1];
					}

    				state = GET_ATTACHMENT;						// Continue with the attachment data
    			}
    		}

			//OLD FIND_APP_HEADER->EXAMINE_HEADER 2/2 SEE ABOVE FOR PART 1/2
    		/*if(state == EXAMINE_HEADER)
    		{ // extract all the info from the header
    			if(line[0].equals("")) { state = GET_ATTACHMENT; continue; } // header ends with an empty line

    			if((tokens = GetLine.splitLine(line[0], REGX, IGNORENONE, GetLine.TRIMSPACE|GetLine.TRIMQUOTE)).length == 0) continue;

    	        if(tokens[0].equalsIgnoreCase("content-type") || tokens[0].equalsIgnoreCase("content-disposition"))
    	        {
    	          for(int i=2; i<tokens.length; i+=2)
    	          { if(tokens[i].equalsIgnoreCase("name") || tokens[i].equalsIgnoreCase("filename")) attachment_name = tokens[i + 1]; }
    	        }

    	        if(tokens[0].equalsIgnoreCase("content-transfer-encoding"))
    	        	content_transfer_encoding = tokens[1];
    		}*/

    		if(state == GET_ATTACHMENT)
    		{ // get the attachment data
    			if(boundary) state = PROCESS_ATTACHMENT;
    			if(!boundary && !line[0].equals("") && Base64.check(line[0].getBytes("US-ASCII"))) 
    				{//attachment_data += line[0];
    				attachment_data.write(gl.getPrevLineAsBytes());
    				}    			
    		}

    		if(state == PROCESS_ATTACHMENT)
    		{ // store the attachment and its info
    			if(!Attachments.instance().addAttachment(attachment_data.toByteArray(), attachment_name, content_transfer_encoding, Attachments.DECODE))
    				return Props.get("getlist_addattfail");

    			attachment_data.reset();
    			attachment_name = "";
    			content_transfer_encoding = "";

    			state = FIND_APP_HEADER;                     // allow multiple aplication/x-tta, aplication/octect-stream attachments
    		}
    	}
    	/*if(mode.equals(STORE) && tokens.length >= 2)
    	{ // wait for successful store
    		if(tokens[0].equals(prefixStr) && tokens[1].equals(OK)) return "";
    	}*/
	}

	return Props.get("getlists_unexpected");
	}

private String makePrefix()
	{
	prefixStr = "A";
	if(this.prefix < 100) prefixStr += "0";
	if(this.prefix < 10) prefixStr += "0";
	prefixStr += Integer.toString(this.prefix++);
	
	return prefixStr;
	}

private String makeString(String[] tokens, int index)
	{
	String ret = "";
	for(int i=index; i<tokens.length; i++) ret += tokens[i] + " ";

	return ret;
	}

private boolean checkBoundary(String line)
	{
	int i;
	
    if(line.startsWith("--"))
	{
      line = line.substring(2);                    // Get rid of the leading and trailing "--" hyphens
      if(line.endsWith("--"))
          line = line.substring(0, line.length() - 2);

      for(i=0; i<boundaries.size(); i++)     // only unique boundaries are added to the boundary vector
        if(boundaries.elementAt(i).toString() == line) break;
      if(i == boundaries.size())
		 boundaries.addElement(line);
      return true;
	}

    return false;
	}

private boolean checkOctets(byte[] bytes)
	{ // find: number of octets (located between {} braces followed by a CRLF)
	int state = 0;
	String octets = "";

	for(this.oct_pos=0; this.oct_pos<bytes.length - 2; this.oct_pos++)
	{ 
		if(bytes[this.oct_pos] == 32) continue; // skip white spaces
		
		if(state == 0)      // search for '{'
		{ if(bytes[this.oct_pos] == 123) state = 1; }
		else if(state == 1) // add to octets
		{	
			if(bytes[this.oct_pos] != 125) // not '}'
				octets += (char)bytes[this.oct_pos];
			else
			{
				if(bytes[this.oct_pos + 1] == 13 && bytes[this.oct_pos + 2] == 10)
				{ 
					this.octet_count = Integer.parseInt(octets);
					this.oct_pos += 3; //  += 3 > characters after '}',13,10 sequence
					return true; 
				}
				else { octets = ""; state = 0; }
			}
		}
	}

	return false;
	}

private DateC parseDate(String fetch)
	{
	DateC date = new DateC(0, 0, 0, 0, 0, 0);
	String[] line = null;
	String months = "JanFebMarAprMayJunJulAugSepOctNovDec"; // RFC822 months
	
	// INTERNALDATE format returned by IMAP-server: * 1 FETCH (INTERNALDATE "02-Oct-2008 09:48:31 +0300")
	try
	{
		if((line = GetLine.splitLine(fetch, QUOTE, IGNORENONE, 0)).length < 3) throw new Exception();
		line[1] = line[1].trim();
		if((line = GetLine.splitLine(line[1], SPLITDATE, IGNORENONE, 0)).length < 6) throw new Exception();

		date.day = Integer.parseInt(line[0]);
		date.month = months.indexOf(line[1]) / 3 + 1;
		date.year = Integer.parseInt(line[2]);
		date.hour = Integer.parseInt(line[3]);
		date.min = Integer.parseInt(line[4]);
		date.sec = Integer.parseInt(line[5]);
	}
	catch(Exception e)
	{ return new DateC(0, 0, 0, 0, 0, 0); }

	return date;
	}
}