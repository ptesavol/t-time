package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ShowBillForm extends Form
{
public static Command OK= new Command(Props.get("common_ok"), Command.OK, 1);
public static Command CANCEL= new Command(Props.get("showbill_cancel"), Command.CANCEL, 1);

private static ShowBillForm _instance=null;
private OwnStringItem headerItem=null;
private OwnStringItem contentItem=null;
private OwnStringItem totalItem=null;

public static ShowBillForm instance()
	   {
	   if (_instance==null)
            _instance=new ShowBillForm();
       return _instance;     
	   }

public ShowBillForm()
    {
    super(Props.get("showbill_title"));
    this.headerItem=new OwnStringItem("","");
    this.contentItem=new OwnStringItem("","");
    this.totalItem=new OwnStringItem("","");
    
    this.headerItem.appendToForm(this);
    this.contentItem.appendToForm(this);
    this.totalItem.appendToForm(this);
   
    }

public boolean calculate(String placename, boolean currentlySelling)
    {
    this.removeCommand(OK);
    this.removeCommand(CANCEL);
    String oldwuname=WorkUnitList.instance().getName();
    String wuname= DateHelper.getDayString();    
    WorkUnitList.instance().setName(wuname);
    if (WorkUnitList.instance().size()<=0)
		return false;
	DataObject  obj=null;
    SalesUnit tunit=null;
    FixedFloat totalPrice=new FixedFloat();
    FixedFloat taxedTotalPrice=new FixedFloat();
    String content="";
    for (int i=0; i<WorkUnitList.instance().size(); i++)
        {
        obj=WorkUnitList.instance().elementAt(i);
        //if ( "com.enporia.ttime.SalesUnit".equals(obj.getClass().getName()) )	// 28.6.2013 J.V., returns obfuscated class name => use instanceof instead
        if(obj instanceof SalesUnit)
            {
            tunit=(SalesUnit)obj;    
            if (placename.equals(tunit.getCustomerName()))
                    {
                    content+=tunit.getBillRenderingName()+"\n";
                    totalPrice.add(tunit.getTotalPrice());
                    taxedTotalPrice.add(tunit.getTaxedTotalPrice());
                    }
            }
        }
   
    FixedFloat taxAmount=new FixedFloat(taxedTotalPrice);
	taxAmount.subtract(totalPrice);
    
    String header=Props.get("showbill_bill")+" "+placename+"\n\n";
    String total=Props.get("showbill_line")+"\n"+Props.get("showbill_total")+"\n"+Props.get("showbill_taxfree")+" ";
    total+=(totalPrice.toString())+Props.get("common_euro")+"\n"; 
    total+=Props.get("showbill_vat")+" "+(taxAmount.toString())+Props.get("common_euro")+"\n";
    total+=Props.get("showbill_taxed")+" "+(taxedTotalPrice.toString())+Props.get("common_euro");
    this.headerItem.setText(header);      
    this.contentItem.setText(content);
    this.totalItem.setText(total);
    WorkUnitList.instance().setName(oldwuname);
    this.addCommand(OK);
    if (currentlySelling)
        {
        this.addCommand(CANCEL);
        }
    return true;
	}
}