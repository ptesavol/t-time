package com.enporia.util;

public class Num
{

public static String dec(int i)
	{
	String ret=""+(i%100);
	if (ret.length()<2)
		ret="0"+ret;
	return ret;
	}
}