package com.enporia.ttime;

import java.io.*;

public class WorkPlaceParser
{
private InputStreamReader reader=null;
private char[] buffer=new char[512];
int num=0;

public WorkPlaceParser(InputStream stream)
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
			while (tint=='\r')
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
	
	String[] ret= new String[6];
	ret[0]="";
	ret[1]="";
	ret[2]="";
	ret[3]="";
	ret[4]="";
	ret[5]="";
	
	int startindex=0;
	int endindex=0;
	//parse WorkPlaceFolderName
	
	
	for (int i=0; i<6; i++)
		{
		endindex=temp.indexOf("	",startindex);
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

/*
public static void main(String[] args) throws Exception
	{
	FileInputStream stream=new FileInputStream("molista.txt");
	WorkPlaceParser parser=new WorkPlaceParser(stream);
	String [] temp=new String[5];
	while ((temp=parser.getNext()) !=null)
		{
		System.out.print(temp[1]+"	"+temp[2]+"	"+temp[3]+"	"+temp[4]+"\n");
		}
	}
*/
}
