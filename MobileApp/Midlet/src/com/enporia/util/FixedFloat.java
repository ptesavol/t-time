package com.enporia.util;

public class FixedFloat
{

public static final int ACCURACY=2;
public static final long NUMBER_ONE = 10000000;	//(2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2 *2*2*2*2); 

private long value=0;	

public FixedFloat()
	{}

public FixedFloat(long v)
	{
	this.value=v;
	}

public FixedFloat(String input)
	{
	try	{
		int i=input.indexOf(".");
		
		String intPart="";
    	String decPart="";

		if (i!=-1)
			{
			intPart=input.substring(0,i);
    		decPart=input.substring(i+1);
			}
		else intPart=input;	
		this.fromStrings(intPart,decPart);
		}
	catch (Exception e) 
		{}
	}

public FixedFloat(FixedFloat other)
	{
	this.value=other.getValue();
	}

public FixedFloat(String i, String d)
	{
	this.fromStrings(i,d);
	}
	
public long getValue()
	{
	return this.value;
	}

public void setValue(long v)
	{
	this.value=v;
	}

public void fromStrings(String intpart, String decpart)
	{
	long whole=0;
	try	{
		whole=Long.parseLong(intpart);
		}
	catch (Exception e)
		{}

	whole=whole*NUMBER_ONE;
	
	long digit=0;
	long divider=10;
	long fract=0;
	try	{
		for (int i=0; i<decpart.length(); i++)
			{
			digit=Long.parseLong(""+decpart.charAt(i));
			digit=digit*NUMBER_ONE;
			fract+=digit/divider;
			divider=divider*10;
			}
		}
	catch (Exception e)
		{
		}
	this.value=whole+fract;
	}

public void multiplyBy(FixedFloat other)
	{
	this.value=((this.value*other.getValue())/NUMBER_ONE);
	}

public void divideBy(FixedFloat other)
	{
	this.value=(this.value*NUMBER_ONE)/(other.getValue());
	}

public void add(FixedFloat other)
	{
	this.value+=other.getValue();
	}

public void subtract(FixedFloat other)
	{
	this.value-=other.getValue();
	}

public String getIntString()
	{
	long whole=this.value/NUMBER_ONE;
	if (ACCURACY<=0)
		{
		if( (this.value%NUMBER_ONE) >= (NUMBER_ONE/2) )
			whole++;
		}
		
	return ""+whole;
	}

public String getDecString()
	{
	String ret="";
	long frac=this.value%NUMBER_ONE;
	long divider=10;
	long tlong=0;
	for (int i=0; i< ACCURACY; i++)
		{
		tlong=(frac/(NUMBER_ONE/divider)); 
		
		if (i==(ACCURACY-1))
			{
			if ( (frac%(NUMBER_ONE/divider))>=( (NUMBER_ONE/divider)/2 ) )
				tlong++;
			}
		if (tlong<10)
			ret+=""+tlong;
		else ret+="9";
		frac=(frac%(NUMBER_ONE/divider));
		divider=divider*10;
		}
	return ret;
	}


public String toString()
	{
	String ret="";
	ret+=this.getIntString();
	if (ACCURACY>0)
		ret+=","+this.getDecString();
	return ret;
	}

public String toStringWithDot()
	{
	String ret="";
	ret+=this.getIntString();
	if (ACCURACY>0)
		ret+="."+this.getDecString();
	return ret;
	}

public static void main(String [] args)
	{
	//FixedFloat luku=new FixedFloat();
	FixedFloat verollinen=new FixedFloat("0.40");
	FixedFloat prosentti=new FixedFloat("1.22");
	
	verollinen.divideBy(prosentti);
	
	System.out.println(verollinen);
	//for (int i=0; i<100 ;i++)
	//	{
		
		//luku.fromStrings("1","04");
		//luku.multiplyBy(kerroin);
		//System.out.println(luku);
		//System.out.print("   ");
	//	}
	}

}