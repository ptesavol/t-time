package com.enporia.ttime;

import java.io.*;

public interface Sendable
{
public void bufferAsciiBytes(OutputStream buffer);
public String getContractor();
public boolean isSent();
public void setSent(boolean sent);
}
