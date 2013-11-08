package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;
import java.io.*;

public class Product extends MutableObject
{
public static final int TYPE_NUMERIC=0;
public static final int TYPE_TIME=1;
public static final int TYPE_TRAVEL=2;

private String productid="";
private String unit="";
private FixedFloat buyprice = new FixedFloat();
private FixedFloat sellprice = new FixedFloat();
private FixedFloat instock = new FixedFloat();
private int unittype = 0;
private FixedFloat vatpercent = new FixedFloat();

public Product()
	{}

public Product(String _name, String _id, String _unit, 
				FixedFloat _buyprice, FixedFloat _sellprice, FixedFloat _instock, int _unittype, 
				FixedFloat _vatpercent)
	{
	this.name=_name;
	this.productid=_id;
	this.unit=_unit;
	this.buyprice=_buyprice;
	this.sellprice=_sellprice;
	this.instock=_instock;
	this.unittype=_unittype;
	this.vatpercent=_vatpercent;
	}


public void setProductId(String id)
	{
	this.productid=id;
	}

public void setUnit(String unit)
	{
	this.unit=unit;
	}
	
public void setBuyPrice(FixedFloat price)
	{
	this.buyprice=price;
	}
	
public void setSellPrice(FixedFloat price)
	{
	this.sellprice=price;
	}

public void setInStock(FixedFloat st)
	{
	this.instock=st;
	}		
	
public void setUnitType(int type)
	{
	this.unittype=type;
	}

public void setVatPercent(FixedFloat percent)
	{
	this.vatpercent=percent;
	}
		
public String getProductId()
	{
	return this.productid;
	}	

public String getUnit()
	{
	return this.unit;
	}		

public FixedFloat getBuyPrice()
	{
	return this.buyprice;
	}
	
public FixedFloat getSellPrice()
	{
	return this.sellprice;
	}	
	
public FixedFloat getTaxedSellPrice()
	{
	FixedFloat ret= new FixedFloat(this.sellprice);
	String vatString=this.vatpercent.getIntString();
	if (vatString.length()<2)
		vatString="0"+vatString;
	FixedFloat tempVat=new FixedFloat("1",vatString);
	ret.multiplyBy(tempVat);
	return ret;
	}

public FixedFloat getInStock()
	{
	return this.instock;
	}	
	
public int getUnitType()
	{
	return this.unittype;
	}	

public FixedFloat getVatPercent()
	{
	return this.vatpercent;
	}	
	
// DataObject implementation

public String getRenderingName()
	{
	return this.name;
	}
	
public Image getRenderingImage()
	{
	return null;
	}

public void setBytes(byte[] bytes) 
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		
		this.name=dinput.readUTF();
		this.productid=dinput.readUTF();
		this.unit=dinput.readUTF();
		this.buyprice.setValue(dinput.readLong());
		this.sellprice.setValue(dinput.readLong());
		this.instock.setValue(dinput.readLong());
		this.unittype=dinput.readInt();
		this.vatpercent.setValue(dinput.readLong());
		dinput.close();
		tinput.close();
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}
	}
	
public byte[] getBytes() 
	{
	byte[] data=null;
	try	{	
		super.output.writeUTF(this.name);
		super.output.writeUTF(this.productid);
		super.output.writeUTF(this.unit);
		super.output.writeLong(this.buyprice.getValue());
		super.output.writeLong(this.sellprice.getValue());
		super.output.writeLong(this.instock.getValue());
		super.output.writeInt(this.unittype);
		super.output.writeLong(this.vatpercent.getValue());
		
		super.output.flush(); 
		data=super.byteoutput.toByteArray(); 
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}
	super.byteoutput.reset();	
	return data;
	}

public AddForm getAddForm() 
	{
	return AddProductForm.instance();
	}
public ModifyForm getModifyForm(DataObject obj) 
	{
	return ModifyProductForm.instance(obj);
	}
public CommonRemoveForm getRemoveForm(DataObject obj) 
	{
	return CommonRemoveForm.instance(obj,Props.get("remove_product_confirmation"));
	}
public ViewForm getViewForm(DataObject obj) 
	{
	return ViewProductForm.instance(obj);
	}
}
