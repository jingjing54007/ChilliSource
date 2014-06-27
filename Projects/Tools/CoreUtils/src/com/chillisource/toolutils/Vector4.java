/**
 * Vector4.java
 * Chilli Source
 * Created by Ian Copland on 30/01/2013
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Tag Games Limited
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

package com.chillisource.toolutils;

public class Vector4 
{
	//------------------------------------------------------------
	/// public member data.
	//------------------------------------------------------------
	public float x;
	public float y;
	public float z;
	public float w;
	//------------------------------------------------------------
	/// Constructor
	//------------------------------------------------------------
	public Vector4()
	{
		x = y = z = w = 0.0f;
	}
	//------------------------------------------------------------
	/// Constructor
	//------------------------------------------------------------
	public Vector4(float infX, float infY, float infZ, float infW)
	{
		x = infX;
		y = infY;
		z = infZ;
		w = infW;
	}
	//------------------------------------------------------------
	/// Copy
	///
	/// @return a copy of this vector.
	//------------------------------------------------------------
	public Vector4 copy()
	{
		return new Vector4(z, y, z, w);
	}
	//------------------------------------------------------------
	/// Equals
	///
	/// @param any object.
	/// @return whether or not this equals the given object.
	//------------------------------------------------------------
	public boolean equals(Object inObj)
	{
	    if ( this == inObj ) 
	    	return true;
	    if ((inObj instanceof Vector4) == false) 
	    	return false;
	    Vector4 vec = (Vector4)inObj;
	    if (Float.floatToIntBits(x) == Float.floatToIntBits(vec.x) && Float.floatToIntBits(y) == Float.floatToIntBits(vec.y)  && Float.floatToIntBits(z) == Float.floatToIntBits(vec.z) && Float.floatToIntBits(w) == Float.floatToIntBits(vec.w))
	    	return true;
	    return false;
	}
	//------------------------------------------------------------
	/// To String
	///
	/// @return this vector in string form.
	//------------------------------------------------------------
	public String toString()
	{
		return "(" + x + ", " + y + ", " + z + "," + w + ")";
	}
}
