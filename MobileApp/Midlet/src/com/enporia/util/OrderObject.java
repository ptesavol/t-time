package com.enporia.util;

import com.enporia.util.*;
import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;
import java.io.*;

public class OrderObject extends DataObject
{
private Vector vector=new Vector();

public String getRenderingName()
	{
	return null;
	}
	
public Image getRenderingImage()
	{
	return null;
	} 
	
public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		while (true)
			{
			try	{
				this.vector.addElement(new Integer(dinput.readInt()));
				}
			catch (Exception e) 
				{
				break;
				}
			}
		
		}
	catch (Exception e)	
		{
		e.printStackTrace();
		}
	}

public byte[] getBytes()	
	{
	byte[] data=null;
	try	{	
		for (int i=0; i<this.vector.size(); i++)
			super.output.writeInt(((Integer)this.vector.elementAt(i)).intValue());
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
	
public Vector getIntegerVector()
	{
	return this.vector;
	}

public void setIntegerVector(Vector vec)
	{
	this.vector=vec;
	}
}
