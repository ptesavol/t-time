package com.enporia.util;

public class Index // 4.10.2008, J.V.
{
	class _item
	{
		public int id = 0;
		public String key = "";
	}
	
	_item[] index = null;
	int size = 0;
	int pos = 0;

	public Index()
	{
		this.index = null;
		this.size = 0;
		this.pos = 0;
	}
	
	public Index(int size)
	{
		this.pos = 0;
		this.size = size;
		this.index = new _item[size];
		for(int i=0; i<this.size; i++)
			this.index[i] = new _item();
	}
	
	public void put(String key, int id)
	{
		if(this.pos >= this.size) this.reallocate();

		this.index[this.pos].key = key;
		this.index[this.pos++].id = id;
	}

	public int get(String key)
	{
		if(this.index == null) return -1;

		for(int i=0; i<this.size; i++)
		  if(this.index[i].key.equals(key)) return this.index[i].id;

		return -1;
	}
	
	private void reallocate()
	{
		_item[] nindex = null;
		int nsize = 0;
		
		//nsize = (int)((float)this.size * 1.75f); // wrong
		nsize = this.size + 10;
		nindex = new _item[nsize];
		for(int i=0; i<nsize; i++)
			nindex[i] = new _item();
		
		System.arraycopy(this.index, 0, nindex, 0, this.size);
		this.size = nsize;
		this.index = nindex;
	}
	
	public int size() { return this.pos; }
}

