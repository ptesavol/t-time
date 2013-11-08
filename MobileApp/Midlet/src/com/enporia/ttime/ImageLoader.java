package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class ImageLoader
{
private static ImageLoader _instance=null;

private Image unsentIcon=null;
private Image noteIcon=null;


private ImageLoader()
	{
	try 	{
		this.noteIcon=Image.createImage(Props.get("noteIcon"));
		this.unsentIcon=Image.createImage(Props.get("unsentIcon"));
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	
	}
	
public static ImageLoader instance()
	{
	if (_instance==null)
		_instance=new ImageLoader();
	return _instance;
	}
	
public Image getUnsentIcon()
	{
	return this.unsentIcon;
	}

public Image getNoteIcon()
	{
	return this.noteIcon;
	}
}
