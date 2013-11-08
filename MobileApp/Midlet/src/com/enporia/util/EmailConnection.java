package com.enporia.util;
import java.io.*;

public interface EmailConnection
{
public void open(String url, String localhost) throws IOException, EmailException;
public void close();
public void sendEmail(String from, String to, String subject, byte[] payload) throws IOException, EmailException; 
}
