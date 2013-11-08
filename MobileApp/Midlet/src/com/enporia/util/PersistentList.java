package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;
import java.io.*;

/**
Persistent MIDP list component.
This component is a persistent collection of DataObjects. 
*/

public class PersistentList extends ShowableList implements CommandListener
{
private DataStore store=null;
private DataStore orderstore=null;
//private DataOutputStream output=null;
//private ByteArrayOutputStream byteoutput=null;

protected Class itemclass=null;



// Vector of ints holding the ofder of this PersistentList
private OrderObject orderobject=null; 
private Vector ordervector=null;
private String sprefix="";

/**
*Creates new PersistentList object
*@param name The name of the list 
*@param parentmidlet the parent midlet
*@param parentlistener parentlistener
*@param itemclass the class of the items to be stored in this list
*/

public PersistentList(String name, MIDlet parentmidlet, CommandListener parentlistener, Class itemclass, String pprefix)
	{
	super(name,parentmidlet,parentlistener);
	this.sprefix=pprefix;
	this.itemclass=itemclass;
	
	//this.byteoutput=new ByteArrayOutputStream();
	//this.output=new DataOutputStream(this.byteoutput);
	
	this.store=new DataStore(sprefix+name, itemclass);
	Class tclass=null;
	try	{
		tclass=Class.forName("com.enporia.util.OrderObject");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}	
	this.orderstore=new DataStore(sprefix+name+"order",tclass);
	
	if (!"".equals(name))
		{
		this.store.open();
		this.orderstore.open();
	
		this.orderobject=(OrderObject)this.orderstore.getSavedObject();
		if (this.orderobject==null)
			this.orderobject=new OrderObject();
		this.ordervector=this.orderobject.getIntegerVector();
		}
	}

public void deleteFromDisk()
	{
	this.clear();
	this.store.deleteFromDisk();
	this.orderstore.deleteFromDisk();
	}	

public void buildVisibleList()
	{
	this.list=new List(getRenderingName(), List.IMPLICIT);
		
	try	{
		DataObject tempobject=null; //(DataObject)itemclass.newInstance();
		for (int i=0; i<ordervector.size(); i++)
			{
			int targetid=((Integer)ordervector.elementAt(i)).intValue();
			tempobject=this.store.getObject(targetid);
			super.append(tempobject.getRenderingName(),tempobject.getRenderingImage());
			}
		super.append(" ",null);
		}
	catch (Exception e)
		{	
		e.printStackTrace();
		}
	}
	
/**
* Sets the name of this list, closes old recordstore and opens a new one
* If GUI list object exists, this destroys it
*/

public void setName(String name)
	{
	this.name=name;
	this.store.setName(sprefix+name);
	this.orderstore.setName(sprefix+name+"order");
	
	this.orderobject=(OrderObject)this.orderstore.getSavedObject();
	if (this.orderobject==null)
		this.orderobject=new OrderObject();
	this.ordervector=this.orderobject.getIntegerVector();
	if (super.list!=null)
		this.buildVisibleList();
	System.gc();
	}

/**
* Renames this list. This is a costly operation, since all the elements must be copied to another recordStore
* @param newName the new name of this list
*/

public void rename(String newName)
	{
	PersistentList templist=new PersistentList(newName, parentmidlet, parentlistener,itemclass,sprefix);
	for (int i=0; i<size(); i++)
		{
		templist.addElement(this.elementAt(i));
		}
	templist.orderstore.close();
	templist.store.close();
	this.deleteFromDisk();
	System.gc();
	this.setName(newName);
	}


/**
* Adds a DataObject to this PersistentList
* @param obj the DataObject to be added to the end of this PersistentList
*/
public void addElement(DataObject obj)
	{
	try	{
		if (this.list!=null)
			super.insert(this.ordervector.size(),obj.getRenderingName(),obj.getRenderingImage());
		int ret=this.store.addObject(obj);
		ordervector.addElement(new Integer(ret));
		saveOrder();
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

/**
* Adds a DataObject to this PersistentList at intdex i
* @param obj the DataObject to be added to the end of this PersistentList
* @param i the index the object is to be inserted at
*/
public void insertElementAt(DataObject obj, int i)
	{
	try	{
		if (this.list!=null)
			super.insert(i,obj.getRenderingName(),obj.getRenderingImage());
		int ret=this.store.addObject(obj);
		if (ordervector.size()>0)
			ordervector.insertElementAt(new Integer(ret),i);
		else ordervector.addElement(new Integer(ret));
		saveOrder();
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

/**
* Swaps two items in this list
* @param i first index
* @param j second index
*/
public void swapElements(int i, int j)
	{
	if (this.list!=null)
		{
		Image im=super.getImage(j);
		String st=super.getString(j);
		super.set(j,super.getString(i),super.getImage(i));
		super.set(i,st,im);
		}
	Object o=ordervector.elementAt(j);
	ordervector.setElementAt(ordervector.elementAt(i),j);
	ordervector.setElementAt(o,i);
	saveOrder();
	}

/**
* Sets DataObject obj at i in this list
* @param obj the object to be saved at index i
* @param i the index to which the object should be saved into 
*/
public void setElementAt(DataObject obj, int i)
	{
	try	{
		if (this.list!=null)
			super.set(i,obj.getRenderingName(),obj.getRenderingImage());
		int tid=((Integer)this.ordervector.elementAt(i)).intValue();
		this.store.setObject(obj,tid);
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

/**
* Removes element at index i from this list 
* @param i the index of the element to be removed
*/

public void removeElementAt(int i)
	{
	try	{
		if (this.list!=null)
			super.delete(i);
		int tid=((Integer)this.ordervector.elementAt(i)).intValue();	
		this.store.deleteObject(tid);
		ordervector.removeElementAt(i);
		saveOrder();
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

/**
* Gets the dataobject at index i 
* @param i the index of the dataobject to be fetched
*/


public DataObject elementAt(int i)
	{
	try	{
		int targetid=((Integer)ordervector.elementAt(i)).intValue();
		return this.store.getObject(targetid);
		}
	catch (Exception e)
		{
		e.printStackTrace();
		return null;
		}
	
	}

/**
 * Gets the object with id i
 *
 */

public DataObject getElementById(int id)
	{
	try	{
		return this.store.getObject(id);
		}
	catch (Exception e)
		{
		e.printStackTrace();
		return null;
		}
	}

/**
 *Sets the selected element to be the element with id 
 *
 */
public void setSelectedId(int id)
	{
	int temp=-1; 
	for (int i=0; i<this.ordervector.size();i++)
		{
		temp = ((Integer)ordervector.elementAt(i)).intValue();
		if (temp==id)
			super.setSelectedIndex(i);
		}
	}

 

/**
* Gets the currently selected dataobject from this list
* @return the currently selected dataobject
*/
public DataObject getSelectedElement()
	{
	return elementAt(super.getSelectedIndex());
	}	

/**
* Returns a Vector of elements stored in this PersistentList
* @return Vector of elements stored in this PersistentList
*/

public Vector getElements()
	{
	Vector ret= new Vector();
	
	try	{
		for (int i=0; i<ordervector.size(); i++)
			{
			int targetid=((Integer)ordervector.elementAt(i)).intValue();
			ret.addElement(this.store.getObject(targetid));
			}
		}
	catch (Exception e)
		{	
		e.printStackTrace();
		}
	
	return ret;
	}

/**
* Gets the renderingnames of the elements in this list
*/

public String[] getElementRenderingNames()
	{
	String[] ret=null;
	if (this.list!=null)
		{
		ret=super.getStrings();
		}
	
	else	{
		ret = new String[this.ordervector.size()];
		try	{
			DataObject tempobject=null; //(DataObject)itemclass.newInstance();
			for (int i=0; i<ordervector.size(); i++)
				{
				int targetid=((Integer)ordervector.elementAt(i)).intValue();
				tempobject=this.store.getObject(targetid);
				ret[i]=tempobject.getRenderingName();
				}
			}
		catch (Exception e)
			{	
			e.printStackTrace();
			}
		}
		
	return ret;
	}  

/**
* Gets the name of the element at inde i in this list
* @param i the index of the element the name of which is wanted
* @return the name of the element at index i in this list
*/

public String getNameAt(int i)
	{
	return elementAt(i).getName();
	}

/**
* Finds the index of the object with the name and returns its index
* Reads the objects from memory one by one, it is slow but saves memory
* @param nam the name of the object to look for
* @return the index of the found object or -1 if object wasnot found
*/

public int indexOf(String nam)
	{
	for (int i=0; i<this.size(); i++)
		{
		if ( nam.equals(this.elementAt(i).getName()) )
			return i;
		}
	return -1;
	}
	
/**
* Finds the index of the object with the name and returns its index
* Compare operation is done with lower case strings and startsWith()
* Reads the objects from memory one by one, it is slow but saves memory
* @param nam the name of the object to look for
* @param begin the index to begin the search from
* @return the index of the found object or -1 if object wasnot found
*/

public int indexOf(String nam, int begin)
	{
	String tnam=nam.toLowerCase().trim();
	if (begin>size())
		return -1;
	for (int i=begin; i<this.size(); i++)
		{
		if ((this.elementAt(i).getName().toLowerCase().trim().startsWith(tnam) ) )
			return i;
		}
	return -1;
	}
	

/**
* Shows this list, creates visible list if needed.
*/
public void show()
	{
	if (this.list==null)
		this.buildVisibleList();
		/*
		{
		if (this.list==null)
			this.list=new List(this.name, List.IMPLICIT);
		
	
		try	{
			DataObject tempobject=(DataObject)itemclass.newInstance();
			for (int i=0; i<ordervector.size(); i++)
				{
				int targetid=((Integer)ordervector.elementAt(i)).intValue();
				tempobject=this.store.getObject(targetid);
				super.append(tempobject.getRenderingName(),tempobject.getRenderingImage());
				}
			super.append(" ",null);
			}
		catch (Exception e)
			{	
			e.printStackTrace();
			}
		
		}
	*/
	super.show();
	}


/**
* Clears all the elements from tis list. Also clears the visible list.  
*/

public void clear()
	{
	for (int i=0; i<size(); i++)
		removeElementAt(i);
	} 


/**
* Returns the size of this list
* @return the size of this list
*/

public int size()
	{
	return this.ordervector.size();
	}


		
/**
* Saves the order of this PersistentList
*/

private void saveOrder()
	{
	try	{
		this.orderstore.saveObject(this.orderobject);	
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}	
	}
}
