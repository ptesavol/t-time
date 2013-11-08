package com.enporia.util;
import javax.microedition.midlet.*;
import java.util.*;
import java.io.*;


public class Props
{
private static Hashtable map=null;
	
public static String get(String key)
	{
	if (map==null)
		{
		map=new Hashtable();
		InputStream stream=null;
		try	{
			stream=Class.forName("com.enporia.util.Props").getResourceAsStream("/taika.properties");
			PropertiesParser parser=new PropertiesParser(stream);
			String [] temp=null;
			while ((temp=parser.getNext()) !=null)
				{
				map.put(temp[0],temp[1]);
				}	
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}	
		
		}
	
	return (String)map.get(key);
	}

}
