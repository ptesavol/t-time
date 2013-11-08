package com.enporia.ttime;


import com.enporia.util.*;
import java.util.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.util.*;

public class SalesUnit extends MutableObject implements Sendable
{
private static Calendar cal=Calendar.getInstance();
private static Date dat=new Date();
private final static byte[] DOT=".".getBytes();
private final static byte[] SPACE=" ".getBytes();
private final static byte[] TAB="	".getBytes();
private final static byte[] LF="\n".getBytes();
//private final static byte[] ONCE="kerta".getBytes();

private String customerName="";
private String productName="";
private String productId="";
private String unit="";
private FixedFloat amount= new FixedFloat();
private FixedFloat unitPrice=new FixedFloat();
private FixedFloat totalPrice=new FixedFloat();
private FixedFloat vatPercent=new FixedFloat();
private long salesTime=-1;
private String worker="";
private String contractor="";
private int id=-1;
private boolean sent=false;
private String customerListName="";
private String productGroupName="";  // 30.9.2008, J.V.

public SalesUnit()
	{}

public SalesUnit(String customerName, String productName, String unit, FixedFloat amount,
		FixedFloat unitPrice, FixedFloat totalPrice, long salesTime, String worker, String contractor, FixedFloat vat, String productGroupName)
	{
	this.customerName=customerName;
	this.productName=productName;
	this.unit=unit;
	this.amount=amount;
	this.unitPrice=unitPrice;
	this.totalPrice=totalPrice;
	this.salesTime=salesTime;
	this.worker=worker;
	this.contractor=contractor;
	this.vatPercent=vat;
	this.productGroupName = productGroupName; // 30.9.2008, J.V.
	}

	
public void setCustomerName(String name)
	{
	this.customerName=name;
	}

public void setCustomerListName(String name)
	{
	this.customerListName=name;
	}
	
public void setProductName(String productName)
	{
	this.productName=productName;
	}

public void setUnit(String unit)
	{
	this.unit=unit;
	}	
	
public void setAmount(FixedFloat amount)
	{
	this.amount=amount;
	}

public void setUnitPrice(FixedFloat price)
	{
	this.unitPrice=price;
	}	
	
public void setTotalPrice(FixedFloat price)
	{
	this.totalPrice=price;
	}
		
	
public void setSalesTime(long time)
	{
	this.salesTime=time;
	}

public void setWorker(String worker)
	{
	this.worker=worker;
	}

public void setContractor(String contractor)
	{
	this.contractor=contractor;
	}

public void setProductId(String pid)
	{
	this.productId=pid;
	}
	
public void setID(int id)
	{
	this.id=id;
	}

public void setSent(boolean sent)
	{
	this.sent=sent;
	}
		
public void setVatPercent(FixedFloat per)
	{
	this.vatPercent=per;
	}

public void setProductGroupName(String productGroupName) // 30.9.2008, J.V.
	{
	this.productGroupName = productGroupName;
	}
	
public String getCustomerName()
	{
	return this.customerName;
	}

public String getCustomerListName()
	{
	return this.customerListName;
	}
	
public String getProductName()
	{
	return this.productName;
	}
	
public String getUnit()
	{
	return this.unit;
	}
	
public FixedFloat getAmount()
	{
	return this.amount;
	}	

public FixedFloat getUnitPrice()
	{
	return this.unitPrice;
	}	

public FixedFloat getTaxedUnitPrice()
	{
	FixedFloat ret= new FixedFloat(this.unitPrice);
	String vatString=this.vatPercent.getIntString();
	if (vatString.length()<2)
		vatString="0"+vatString;
	FixedFloat tempVat=new FixedFloat("1",vatString);
	ret.multiplyBy(tempVat);
	return ret;
	}
	
public FixedFloat getTotalPrice()
	{
	return this.totalPrice;
	}	

public FixedFloat getTaxedTotalPrice()
    	{
    	FixedFloat ret= new FixedFloat(this.totalPrice);
	String vatString=this.vatPercent.getIntString();
	if (vatString.length()<2)
		vatString="0"+vatString;
	FixedFloat tempVat=new FixedFloat("1",vatString);
	ret.multiplyBy(tempVat);
	return ret;
    	}
	
public long getSalesTime()
	{
	return this.salesTime;
	}

public String getWorker()
	{
	return this.worker;
	}
	
public String getContractor()
	{
	return this.contractor;
	}
	
public int getID()
	{
	return this.id;
	}
	
public String getProductId()
	{
	return this.productId;
	}	
	
public boolean isSent()
	{
	return this.sent;
	}	
	
public FixedFloat getVatPercent()
	{
	return this.vatPercent;
	}
	
public String getProductGroupName() // 30.9.2008, J.V.
	{
	return this.productGroupName;
	}
/*
public String getXml()
	{
	return "<workunit>\n"+
	"<id>"+this.id+"</id>\n"+
	"<workplace><![CDATA["+this.workPlace+"]]></workplace>\n"+
	"<worktype><![CDATA["+this.workType+"]]></worktype>\n"+ 
	"<starttime>"+this.startTime+"</starttime>\n"+
	"<endtime>"+this.endTime+"</endtime>\n"+
	"<effectivetime>"+this.effectiveTime+"</effectivetime>\n"+
	"</workunit>\n";

	}
	
public String getXml2()
	{
	return "<a>"+	
	"<b>"+this.id+"</b>"+
	"<c><![CDATA["+this.workPlace+"]]></c>"+
	"<d><![CDATA["+this.workType+"]]></d>"+ 
	"<e>"+this.startTime+"</e>"+
	"<f>"+this.endTime+"</f>"+
	"<g>"+this.effectiveTime+"</g>"+
	"</a>\n";
	}
*/
/*
public void bufferXml(StringBuffer buf)
	{
	
	}
	
public void bufferAscii(StringBuffer buffer)
	{
	buffer.append(this.workPlace);
	buffer.append(TAB);
	buffer.append(this.workType);
	buffer.append(TAB);
	dat.setTime(this.startTime);
	cal.setTime(dat);
	buffer.append(cal.get(Calendar.DAY_OF_MONTH));
	buffer.append(DOT);
	buffer.append(DateHelper.getMonth(cal));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.YEAR));
	buffer.append(TAB);
	buffer.append(cal.get(Calendar.HOUR_OF_DAY));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.MINUTE));
	buffer.append(TAB);
	dat.setTime(this.endTime);
	cal.setTime(dat);
	buffer.append(cal.get(Calendar.DAY_OF_MONTH));
	buffer.append(DOT);
	buffer.append(DateHelper.getMonth(cal));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.YEAR));
	buffer.append(TAB);
	buffer.append(cal.get(Calendar.HOUR_OF_DAY));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.MINUTE));
	buffer.append(TAB);
	if (this.effectiveTime==-1)
		buffer.append(ONCE);
	else buffer.append(this.effectiveTime/60000);
	buffer.append(LF);
	}
*/
public void bufferAsciiBytes(OutputStream buffer)
	{
	
	try	{
	buffer.write(this.customerName.getBytes());
	buffer.write(TAB);
	buffer.write(this.productName.getBytes());
	buffer.write(TAB);
	dat.setTime(this.salesTime);
	cal.setTime(dat);
	buffer.write((cal.get(Calendar.DAY_OF_MONTH)+"").getBytes());
	buffer.write(DOT);
	buffer.write((DateHelper.getMonth(cal)+"").getBytes());
	buffer.write(DOT);
	buffer.write((cal.get(Calendar.YEAR)+"").getBytes());
	buffer.write(SPACE);
	buffer.write((DateHelper.getHoursAndMinutes(cal)+"").getBytes());
	buffer.write(TAB);
	buffer.write(this.unit.getBytes());
	buffer.write(TAB);
	buffer.write((this.amount.toStringWithDot()).getBytes());
	buffer.write(TAB);
	buffer.write("TYPE_SALESUNIT".getBytes());
	buffer.write(TAB);
	buffer.write((this.unitPrice.toStringWithDot()).getBytes());
	buffer.write(TAB);
	buffer.write((this.totalPrice.toStringWithDot()).getBytes());
	buffer.write(TAB);
	buffer.write(this.productId.getBytes());
	buffer.write(TAB);
	buffer.write((this.vatPercent.toStringWithDot()).getBytes());
	buffer.write(TAB);
	buffer.write(this.customerListName.getBytes());
	buffer.write(TAB); // 30.9.2008, J.V.
	buffer.write(this.productGroupName.getBytes()); // 30.9.2008, J.V.
	buffer.write(LF);
	}
	catch (Exception e) {e.printStackTrace();}
	
	}	
/*				
public String toString()
	{
	String ret="";
	ret+=this.workPlace+"	"+this.workType+"	";
	Calendar cal=Calendar.getInstance();
	cal.setTime(new Date(this.startTime));
	ret+=cal.get(Calendar.DAY_OF_MONTH)+"."+DateHelper.getMonth(cal)+".";
	ret+=cal.get(Calendar.YEAR)+" "+cal.get(Calendar.HOUR_OF_DAY)+"."+cal.get(Calendar.MINUTE)+"	";
	cal.setTime(new Date(this.endTime));
	ret+=cal.get(Calendar.DAY_OF_MONTH)+"."+DateHelper.getMonth(cal)+".";
	ret+=cal.get(Calendar.YEAR)+" ";
	String temp=""+cal.get(Calendar.HOUR_OF_DAY);
	if (temp.length()==1)
		temp="0"+temp;
	ret+=temp+".";
	temp=""+cal.get(Calendar.MINUTE);
	if (temp.length()==1)
		temp="0"+temp;
	String seftime="";
	if (this.effectiveTime==-1) 
		seftime="kerta";
	else seftime=""+(this.effectiveTime/60000);
	ret+=temp+"	"+seftime+"\n";
	return ret;
	}
*/
public String getRenderingName()
	{
	String ret= DateHelper.getHoursAndMinutes(this.salesTime)+" "
	+ this.customerName+" "+this.productName+" ";
	return ret;
	}

public Image getRenderingImage()
	{
	return  this.sent ? null : ImageLoader.instance().getUnsentIcon();	
	}

public String getBillRenderingName()
    {
    String ret=this.productName+" "+this.amount.toString()+this.unit+" = ";
    ret+=this.totalPrice.toString()+Props.get("common_euro");
    return ret;
    }
public byte[] getBytes()
	{
	byte[] data=null;
	try	{	
		super.output.writeUTF(this.customerName);
		super.output.writeUTF(this.productName);
		super.output.writeUTF(this.unit);
		super.output.writeLong(this.amount.getValue());
		super.output.writeLong(this.unitPrice.getValue());
		super.output.writeLong(this.totalPrice.getValue());
		super.output.writeLong(this.salesTime);
		super.output.writeUTF(this.worker);
		super.output.writeUTF(this.contractor);
		super.output.writeBoolean(this.sent);
		super.output.writeUTF(this.productId);
		super.output.writeLong(this.vatPercent.getValue());
		super.output.writeUTF(this.customerListName);
		super.output.writeUTF(this.productGroupName); // 30.9.2008, J.V.
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
	
public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);

		this.customerName=dinput.readUTF();
		this.productName=dinput.readUTF();
		this.unit=dinput.readUTF();
		this.amount.setValue(dinput.readLong());
		this.unitPrice.setValue(dinput.readLong());
		this.totalPrice.setValue(dinput.readLong());
		this.salesTime=dinput.readLong();
		this.worker=dinput.readUTF();
	  	this.contractor=dinput.readUTF();
		this.sent=dinput.readBoolean();
		this.productId=dinput.readUTF();
		this.vatPercent.setValue(dinput.readLong());
		this.customerListName=dinput.readUTF();
		this.productGroupName = (dinput.available() > 0 ? dinput.readUTF() : "Oletus");	// 30.9.2008, 26.6.2013, J.V.
		dinput.close();
		tinput.close();
		}
	catch (Exception e)
		{
		System.out.println(e);
		}
	}

public AddForm getAddForm()
	{
	return null;
	}

public ModifyForm getModifyForm(DataObject obj)
	{
	return ModifySalesUnitForm.instance(this);
	}

public CommonRemoveForm getRemoveForm(DataObject obj)
	{
	return CommonRemoveForm.instance(this,Props.get("remove_salesunit_confirmation"));
	}	

public ViewForm getViewForm(DataObject obj)
	{
	return ViewSalesUnitForm.instance(this);
	}

}
