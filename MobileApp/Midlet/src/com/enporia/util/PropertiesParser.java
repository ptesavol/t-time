package com.enporia.util;
import javax.microedition.midlet.*;
import java.io.*;

public class PropertiesParser
{
private InputStreamReader reader=null;
private char[] buffer=new char[512];
int num=0;

public PropertiesParser(InputStream stream)
	{
	try	{
		this.reader=new InputStreamReader(stream);
		}
	catch (Exception e) {}
	} 

public String[] getNext()
	{
	//Read the stream until a \n or EOF has been reached
	int tint=0;
	for (int i=0; i< this.buffer.length; i++)
		{
		try	{
			tint=this.reader.read();
			}
		catch (Exception e) 
			{
			tint=-1;
			}	
		if (tint==-1 || tint =='\n')
			{
			this.num=i;		
			break;
			}
		this.buffer[i]=(char)tint;
		}
	if (this.num==0)
		return null;
	String temp=new String(this.buffer,0,this.num);
	temp+="	";
	//parse the line
	
	String[] ret= new String[2];
	ret[0]="";
	ret[1]="";
	
	int startindex=0;
	int endindex=0;
	//parse PropertyLine
	
	
	for (int i=0; i<2; i++)
		{
		if (i==0)
			endindex=temp.indexOf(":",startindex);
		else	endindex=temp.length();
		if (endindex==-1)
			break;
		if ((endindex-startindex) != 0)
			ret[i]=temp.substring(startindex,endindex).trim();
		startindex=endindex+1;
		if (startindex>=temp.length())
			break;
		}
	return ret;
	}
}
