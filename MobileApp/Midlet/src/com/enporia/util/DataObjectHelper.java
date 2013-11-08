package com.enporia.util;

import java.util.Vector;

public class DataObjectHelper
{
public static int indexOf(Vector vec, String name)
	{
	//System.out.println("#"+name+"#");
	for (int i=0; i<vec.size(); i++)
		{
		//System.out.println("#"+((DataObject)vec.elementAt(i)).getName()+"#");
		if (name.toLowerCase().equals(((DataObject)vec.elementAt(i)).getName().toLowerCase() ) )
			return i;
		}
	return -1;
	}

}
