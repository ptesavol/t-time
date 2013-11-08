package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class ProductList extends BasicList 
{
private static ProductList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;
private static String _titleprefix="";
private FindBox findBox=null;
//private TravelBox travelBox=null;
private int sellIndex=0;

private ShowBillForm showBillForm=null;

private static final String _prefix="prodl";
private static Command TO_PRODUCTFOLDERLIST = new Command(Props.get("productlist_folderlists"), Command.ITEM, 2);
private static Command BACK_PRODUCTLIST = new Command(Props.get("common_back"), Command.BACK, 2);
private static Command FIND_PRODUCT = new Command(Props.get("productlist_find"), Command.ITEM, 4);
private static Command SELL_PRODUCT = new Command(Props.get("productlist_sell"), Command.ITEM, 4);
private static Command SHOW_BILL = new Command(Props.get("productlist_showbill"),Command.SCREEN,5);

private SellNumericForm sellNumericForm=null;

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_titleprefix=Props.get("productlist_title");
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.ttime.Product");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}
	
private ProductList()
	{
	super("",_midlet,_listener,_iclass,_prefix);
	
	}

public static ProductList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new ProductList();
	return _instance;
	}	
	
public void setName(String namee)
	{
	super.setName(namee);
	ProgramState.instance().setSelectedProductFolder(namee);
	ProgramState.instance().save();
	}
	
public void addScreenCommands()
	{
	super.addScreenCommands();
	addCommand(BACK_PRODUCTLIST);
	addCommand(TO_PRODUCTFOLDERLIST);
	addCommand(FIND_PRODUCT);
	addCommand(SHOW_BILL);
    }

public void addItemCommands()
	{
	super.addItemCommands();
	addCommand(SELL_PRODUCT); 
	}	

public void removeItemCommands()
	{
	super.removeItemCommands();
	removeCommand(SELL_PRODUCT);	
	}		
	
public String getRenderingName()
	{
	return _titleprefix+" "+name;
	}	


public void saveSalesUnit(DataObject obj)
	{
	SalesUnit unit=(SalesUnit)obj;
	String daystring=DateHelper.getDayString();
	WorkUnitList.instance().setName(daystring);
	WorkUnitList.instance().insertElementAt(unit,0);
	FolderName fname=new FolderName(daystring);
	if ( WorkUnitFolderList.instance().size()==0 || 
		(WorkUnitFolderList.instance().size()>0 && 
		WorkUnitFolderList.instance().indexOf(daystring)==-1) )
		{
		WorkUnitFolderList.instance().insertElementAt(fname,0);
		}
	}

/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	
	if (c==TO_PRODUCTFOLDERLIST)
		{
		ProductFolderList.instance().show();
		}
	
	
	if (c==FIND_PRODUCT)
		{
		this.findBox=FindBox.instance("");
		this.findBox.setCommandListener(this);
		super.display.setCurrent(this.findBox);
		}
		
	
	if (c==FindBox.FIND_OK)
		{
		if (this.findBox.getString()!=null && !"".equals( this.findBox.getString()))
			{
			FindForm.instance().setCommandListener(this);
			super.display.setCurrent(FindForm.instance());
			FindForm.instance().find(this.findBox.getString(), this, ProductFolderList.instance());
			}
		}
		
	if (c==BACK_PRODUCTLIST)
		{
		WorkPlaceList.instance().show();
		}
		
		
	if (c==SELL_PRODUCT)
		{
		if (getSelectedIndex()!=size() )
			{
			Product temp=(Product)elementAt(getSelectedIndex());
			this.sellIndex=getSelectedIndex();
			//if (temp.getUnitType()==Product.TYPE_NUMERIC)
				//{
				this.sellNumericForm=SellNumericForm.instance(temp);
				this.sellNumericForm.setCommandListener(this);
				
				super.display.setCurrent(this.sellNumericForm);
				//}
			}
		}
	
	if (c==SellNumericForm.OK)
		{
		SalesUnit su=(SalesUnit)this.sellNumericForm.getObject();
		su.setProductGroupName(name); // 30.9.2008, J.V.
		System.out.println(name);
		this.saveSalesUnit(su);
		Product tp=(Product)this.sellNumericForm.getProduct();
		
		FixedFloat news=tp.getInStock();
		news.subtract(su.getAmount());
		
		if (news.getValue()<0)
			news.setValue(0);
		tp.setInStock(news);	
		
		super.setElementAt(tp, sellIndex);
		
        this.showBillForm=ShowBillForm.instance();
        this.showBillForm.calculate(WorkPlaceList.instance().getSelectedElement().getName(),true);
        this.showBillForm.setCommandListener(this);    
		super.display.setCurrent(this.showBillForm);
        }
	
    if (c==ShowBillForm.OK)
        {
        this.show();
        }
    
    if (c==ShowBillForm.CANCEL)
        {
        WorkUnitList.instance().removeElementAt(0);
        this.show();
        }	
	
    if (c==SHOW_BILL)
        {
        this.showBillForm=ShowBillForm.instance();
        if (this.showBillForm.calculate(WorkPlaceList.instance().getSelectedElement().getName(),false))
        	{
			this.showBillForm.setCommandListener(this);    
			super.display.setCurrent(this.showBillForm);
        	}
		}
        
	if (c == List.SELECT_COMMAND)
		this.onViewItem();

    if (c==FindBox.FIND_CANCEL || c==FindForm.FINDFORM_OK || c==SellNumericForm.CANCEL)
		this.show();
			
	super.commandAction(c,d);
	}


}	
	
