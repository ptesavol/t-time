package com.enporia.util;

public class CustomException extends Exception
{
private String msgexc = "";
	
public CustomException() {}

public CustomException(String exc)
	{
	super(exc);
	msgexc = exc;
	}

public String toString()
	{
	return msgexc;
	}
}
