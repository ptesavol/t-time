package com.enporia.util;

import java.util.Vector;
import java.io.*;

public class GetLine {
int bufSize = 0;
int bufPos = 0;
int bufPrevPos = 0;
byte[] buf = null;

int eolSize = 0;
byte[] eol = null;

String line[] = new String[] {""};

public static final int TOLOWER = 1;
public static final int TOUPPER = 2;
public static final int TRIMSPACE = 4;
public static final int TRIMQUOTE = 8;
public static final int IGNOREEMPTY = 16;

//private static final String[] PARSEDATE =  {"."};
//private static final String[] PARSETIME =  {":"};
//private static final char[] IGNORENONE =  {};

public GetLine()
	{}

public GetLine(byte[] buf, byte[] eol)
	{
	    this.buf = buf;
	    this.eol = eol;
	    
	    if(buf != null) this.bufSize = buf.length;
	    else this.bufSize = 0;
	    if(eol != null)this.eolSize = eol.length; 
	    else this.eolSize = 0;
	    
	    this.bufPos = 0;
	    this.bufPrevPos = 0;
	}

public String[] getNextLine() throws IOException
	{
	int i;
	byte[] byt = {0};
	ByteArrayOutputStream out = new ByteArrayOutputStream(256);
	
	this.line[0] = "";

	this.bufPrevPos = this.bufPos;
	
	if(this.buf == null || this.eol == null) return null;
	if(this.bufPos == this.bufSize) return null;

	while(this.bufPos < this.bufSize)
	{
		// check eol
		for(i=0; i<this.eolSize; i++)
		{
			if(this.bufPos + i >= this.bufSize) break;               // eol marker extends beyond buffer top?
			if(this.buf[this.bufPos + i] != this.eol[i]) break;      // something else than eol
		}
		if(i == this.eolSize) 
		{ this.bufPos += this.eolSize; break; }

		// add character and get next character
		byt[0] = this.buf[this.bufPos++]; out.write(byt);
	}

	this.line[0] = new String(out.toByteArray());

	return this.line;
	}

public byte[] getPrevLineAsBytes()
	{
	byte bytes[] = null;
	int i, curPos = this.bufPrevPos, endOffs = 0;

	if(this.buf == null || this.eol == null) return null;

	while(curPos < this.bufSize)
	{
		// check eol
		for(i=0; i<this.eolSize; i++)
		{
			if(curPos + i >= this.bufSize) break;
			if(this.buf[curPos + i] != this.eol[i]) break;
		}
		if(i == this.eolSize)
			break;

		// add to offset, increment current position
		endOffs++; curPos++;
	}

	if(endOffs > 0)
	{
	bytes = new byte[endOffs];
	for(i=this.bufPrevPos; i<this.bufPrevPos + endOffs; i++)
		bytes[i - this.bufPrevPos] = this.buf[i];
	}

	return bytes;
}

public static String[] splitLine(String line, String[] markers, char[] ignored, int flags)
	{
	String[] tokens = null;
	String token = "";
	boolean marker_found;
	int i, m, mlen, lpos = 0, llen = line.length();

	Vector vect = new Vector();
	
	while(lpos < llen)
	{
		// Multiple split markers -> check them all against string pos
		marker_found = false;
		for(m=0; m<markers.length; m++)
		{
			mlen = markers[m].length();

			for(i=0; i<mlen; i++)
			{
				if(lpos + i >= llen) break;               // marker extends beyond buffer top?
				if(line.charAt(lpos + i) != markers[m].charAt(i)) break;
			}
			if(i == mlen)                // :: marker found (1.1) - skip marker (increment) + add to vector + reset for next round + set mark found + stop searching for markers
			{ lpos += mlen; addElem(vect, token, flags); token = ""; marker_found = true; continue; }
		}
		if(marker_found && lpos == llen) // :: marker found (1.2.1) -> marker found at the end of line => add empty token (lines are already separated so marker at the end equals "empty marker", eg. "1;2;" -> 1", "2", "")
			addElem(vect, "", flags);
		if(marker_found) continue;       // :: marker found (1.2.2) -> start searching for next token

		// add character if its not in the ignore array
		if(ignore(line.charAt(lpos), ignored) == false)
		  token += line.charAt(lpos);
		// get next pos
		lpos += 1;

		// end reached? -> add to vector
		if(lpos == llen) addElem(vect, token, flags);
	}

	tokens = new String[vect.size()];
	for(i=0; i<vect.size(); i++)
	{
		token = vect.elementAt(i).toString();
		
		if((flags & TOLOWER) == TOLOWER) token = token.toLowerCase();
		if((flags & TOUPPER) == TOUPPER) token = token.toUpperCase();
		if((flags & TRIMSPACE) == TRIMSPACE) token = token.trim();
		if((flags & TRIMQUOTE) == TRIMQUOTE)
		{
			if(token.startsWith("\"")) token = token.substring(1, token.length());
			if(token.endsWith("\"")) token = token.substring(0, token.length() - 1);
		}
		
    	tokens[i] = token;
	}
    	
	return tokens;
	}

public String[] getNextTokenizedLine(String[] markers, char[] ignored, int flags) throws IOException
	{
	String line[] = null;
	
	if((line = getNextLine()) == null) return line;

	return splitLine(line[0], markers, ignored, flags);
	}

/*public int parseDateTime2Int(String date, String time)
	{
	int dt = 0;
	String[] dates = null;
	String[] times = null;
	
	try
	{
		// dd.mm.yyyy hh:mm > bits: yyyyymmmmmdddddhhhhhmmmmmm  25-21, 20-16, 15-11, 10-6, 5-0
		if((dates = splitLine(date, PARSEDATE, IGNORENONE, 0)).length < 3) return 0;
		if((times = splitLine(time, PARSETIME, IGNORENONE, 0)).length < 2) return 0;
			
		dt = (Integer.parseInt(dates[2]) << 21) +
			 (Integer.parseInt(dates[1]) << 16) +
			 (Integer.parseInt(dates[0]) << 11) +
			 (Integer.parseInt(times[0]) <<  6) +
			  Integer.parseInt(times[1]);
	}
	catch(NumberFormatException e)
	{ return 0; }	
		
	return dt;
	}*/

private static boolean ignore(char chr, char[] ignored)
	{
	for(int i=0; i<ignored.length; i++)
		if(chr == ignored[i]) return true;
	
	return false;
	}

private static void addElem(Vector vect, String token, int flags)
	{
	if((flags&IGNOREEMPTY) == IGNOREEMPTY && token.equals("")) return;
	
	vect.addElement(token);
	}
}