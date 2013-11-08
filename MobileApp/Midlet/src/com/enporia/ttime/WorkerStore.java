package com.enporia.ttime;

import com.enporia.util.*;
import com.enporia.util.*;
import javax.microedition.lcdui.Image;
import java.io.*;

public class WorkerStore extends DataStore
{
private static WorkerStore _instance=null;
private static Class _cla=null;

private WorkerStore()
	{
	super("worker",_cla);
	super.open();
	}

public static WorkerStore instance()
	{
	if (_instance==null)
		{
		try 	{
			_cla=Class.forName("com.enporia.ttime.Worker");
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}		
		_instance=new WorkerStore();
		}
	return _instance;
	}
}
