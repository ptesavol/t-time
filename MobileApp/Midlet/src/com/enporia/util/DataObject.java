package com.enporia.util;

import javax.microedition.lcdui.Image;
import java.io.*;

/**
Superclass of all objects to be stored in a PersistentList
*/

public abstract class DataObject
{
protected static ByteArrayOutputStream byteoutput=new ByteArrayOutputStream();
protected static DataOutputStream output=new DataOutputStream(byteoutput);

protected int id=-1;
protected String name="";

/**
Sets the id of this DataObject
@param id id
*/

public void setID(int id)
	{
	this.id=id;
	}
	
/**
Gets the id of this DataObject
@return id of this DataObject
*/

public int getID()
	{
	return this.id;
	}


/**
*Sets the name of this dataobject
*@param name the name to be set to this dataobject
*/

public void setName(String name)
	{
	this.name=name;
	}	

/**
*Gets the name of this dataobject
*@return the name of this dataobject
*/

public String getName()
	{
	return this.name;
	}


/**
Gets the name of this dataobject ready to be rendered to a gui component.
@return the name of this dataobject ready to be rendered to a gui component
*/

public String getRenderingName()
	{
	return "";
	}

/**
Gets the image of this dataobject ready to be rendered to a gui component.
@return the image of this dataobject ready to be rendered to a gui component
*/

public Image getRenderingImage()
	{
	return null;
	}	

/**
Sets the contents of this DataObject
@param bytes Contents of this DataObject in a DataOutputStream form
*/

public abstract void setBytes(byte[] bytes);

/**
Sets the contents of this DataObject
@return Contents of this DataObject in a DataOutputStream form
*/

public abstract byte[] getBytes();


}
