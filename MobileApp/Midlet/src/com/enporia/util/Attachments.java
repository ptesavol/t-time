package com.enporia.util;

import java.util.Vector;

import com.enporia.ttime.IMAPGetListsForm;

public class Attachments
{
	public class Attachment
	{
	private String name = "";
	private String encoding = "";
	private byte[] attachment_bytes = null;
	}

	private static Attachments _instance = null;
	
	private Vector attachment_vector = new Vector();
	private static final String INDEXOVERFLOW = "#INDEXOVERFLOW#";
	public static final int STORE = 0;
	public static final int DECODE = 1;

public Attachments()
	{}
	
public static Attachments instance()
	{
	if (_instance==null)
		_instance=new Attachments();
	
	return _instance;
	}


public boolean addAttachment(byte[] attachment, String name, String encoding, int mode)
	{ // Add new attachment
	try
	{
	byte[] byt_att = null;
	Attachment at = new Attachment();

	at.name = name;
	at.encoding = encoding;
	
	if(mode == STORE)
		byt_att = attachment;
	else if(mode == DECODE)
	{
		if(encoding.equalsIgnoreCase("base64"))
			byt_att = Base64.decode(attachment, 0, attachment.length, Base64.NO_OPTIONS);
		else
			byt_att = attachment;
	}
	at.attachment_bytes = byt_att;
	
	attachment_vector.addElement(at);
	}
	catch(Exception e)
	{ return false; }
	
	return true;
	}

public int getSize()
	{ // Return count of attachments
	return this.attachment_vector.size();
	}

public String getAttachmentName(int index)
	{
	if(index >= 0 && index < this.attachment_vector.size())
		return ((Attachment)this.attachment_vector.elementAt(index)).name;
	else
		return INDEXOVERFLOW;
	}

public byte[] getAttachmentBytes(int index)
	{
	if(index >= 0 && index < this.attachment_vector.size())
		return ((Attachment)this.attachment_vector.elementAt(index)).attachment_bytes;
	else
		return null;
	}

public void clear()
	{
	attachment_vector.removeAllElements();
	}
}
