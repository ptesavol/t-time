package com.enporia.util;


import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class OwnStringItem
{

public static final int NORMAL = 0;
public static final int BIG = 1;
public static final int BIGENTERS = 2;


private static int mode = NORMAL;


private StringItem labelItem=null;
private StringItem textItem=null;
//private StringItem enterItem=null;

private int index=-1;
//private int textIndex=-1;

//private StringItem enterItem=null;

public static void init(int m)
	{
	mode=m;
	}
public OwnStringItem(String label, String text)
	{
	if (mode==NORMAL)
		{
		this.textItem=new StringItem(label,text);
		this.textItem.setLayout(Item.LAYOUT_NEWLINE_AFTER);
		}
	if (mode==BIG)
		{
		this.labelItem=new StringItem(label,"");
		this.textItem=new StringItem(text,"");
		}
	if (mode==BIGENTERS)
		{
		this.labelItem=new StringItem(label,"");
		this.textItem=new StringItem(text,"");
		//midp 2.0
		this.textItem.setLayout(Item.LAYOUT_NEWLINE_AFTER);
		}
	}

public String getLabel()
	{
	if (mode==NORMAL)
		{
		return this.textItem.getLabel();
		}
	if (mode==BIG || mode==BIGENTERS)
		{
		return this.labelItem.getLabel();
		}	
	return "";
	} 
	
public String getText()
	{
	if (mode==NORMAL)
		{
		return this.textItem.getText();
		}
	if (mode==BIG || mode==BIGENTERS)
		{
		return this.textItem.getLabel();
		}	
	return "";
	} 
	
public void setLabel(String label)
	{
	if (mode==NORMAL)
		{
		this.textItem.setLabel(label);
		}
	if (mode==BIG || mode==BIGENTERS)
		{
		this.labelItem.setLabel(label);
		}
	
	}

public void setText(String text)
	{
	if (mode==NORMAL)
		{
		this.textItem.setText(text);
		}
	if (mode==BIG || mode==BIGENTERS)
		{
		this.textItem.setLabel(text);
		}
	
	}

public void appendToForm(Form form)
	{
	if (mode==NORMAL)
		{
		this.index=form.append(this.textItem);
		}
	if (mode==BIG)
		{
		this.index=form.append(this.labelItem);
		form.append(this.textItem);
		}
	if (mode==BIGENTERS)
		{
		this.index=form.append(this.labelItem);
		form.append(this.textItem);
		}
	}

public void deleteFromForm(Form form)
	{
	if (mode==NORMAL )
		{
		if (this.index!=-1)
			{
			form.delete(this.index);
			this.index=-1;
			}
		}
	if (mode==BIG || mode==BIGENTERS)
		{
		if (this.index!=-1)
			{
			form.delete(this.index);
			form.delete(this.index);
			this.index=-1;
			}
			
		}
	}
}
