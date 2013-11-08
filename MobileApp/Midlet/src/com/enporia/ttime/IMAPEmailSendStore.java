package com.enporia.ttime;

import com.enporia.util.*;

public class IMAPEmailSendStore extends DataStore
{
private static IMAPEmailSendStore _instance=null;
private static Class _cla=null;

private IMAPEmailSendStore()
	{
	super("imapemailsend",_cla);
	super.open();
	}

public static IMAPEmailSendStore instance()
	{
	if (_instance==null)
		{
		try { 
			_cla=Class.forName("com.enporia.ttime.IMAPEmailSend");
			}
		catch (Exception e)
			{ 
			e.printStackTrace();
			}
		_instance=new IMAPEmailSendStore();
		}
		return _instance;
	}
}

