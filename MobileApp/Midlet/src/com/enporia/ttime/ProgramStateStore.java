package com.enporia.ttime;

import com.enporia.util.*;
import com.enporia.util.*;
import javax.microedition.lcdui.Image;
import java.io.*;

public class ProgramStateStore extends DataStore
{
private static ProgramStateStore _instance=null;
private static Class _cla=null;

private ProgramStateStore()
	{
	super("ProgramState",_cla);
	super.open();
	}

public static ProgramStateStore instance()
	{
	if (_instance==null)
		{
		try 	{
			_cla=Class.forName("com.enporia.ttime.ProgramState");
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}		
		_instance=new ProgramStateStore();
		}
	return _instance;
	}
}
