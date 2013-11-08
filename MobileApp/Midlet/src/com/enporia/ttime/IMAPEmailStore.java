package com.enporia.ttime;

import com.enporia.util.*;

public class IMAPEmailStore extends DataStore
{
private static IMAPEmailStore _instance=null;
private static Class _cla=null;

private IMAPEmailStore()
	{
	super("imapemail",_cla);
	super.open();
	}

public static IMAPEmailStore instance()
	{
	if (_instance==null)
		{
		try { 
			_cla=Class.forName("com.enporia.ttime.IMAPEmail");
			}
		catch (Exception e)
			{ 
			e.printStackTrace();
			}
		_instance=new IMAPEmailStore();
		}
		return _instance;
	}
}
