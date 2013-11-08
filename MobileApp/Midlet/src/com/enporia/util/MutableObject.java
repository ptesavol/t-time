package com.enporia.util;

public abstract class MutableObject extends DataObject
{
/**
Gets the form for adding this kind of DataObject
*/
public abstract AddForm getAddForm();

/**
Gets the form for modifying this kind of DataObject
*/
public abstract ModifyForm getModifyForm(DataObject obj);

/**
Gets the form for removing this kind of DataObject
*/
public abstract CommonRemoveForm getRemoveForm(DataObject obj);

/**
Gets the form for viewing this kind of DataObject
*/
public abstract ViewForm getViewForm(DataObject obj);
}
