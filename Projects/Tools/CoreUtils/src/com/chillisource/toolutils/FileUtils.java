/**
 * FileUtils.java
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

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class FileUtils 
{
	/**
	 * Reads the entire contents of a file into a string.
	 * 
	 * @author Ian Copland
	 * 
	 * @param The file path.
	 * 
	 * @return The contents of the file. Failure will return an
	 * empty string.
	 */
	public static String readFile(String in_filePath)
	{	
		String output = "";
		try
		{
			byte[] encoded = Files.readAllBytes(Paths.get(in_filePath));
			output = new String(encoded, StandardCharsets.UTF_8);
		}
		catch (Exception e)
		{
		}
		
		return output;
	}
	/**
	 * Writes the contents of a string to file.
	 * 
	 * @author Ian Copland
	 * 
	 * @param The output file path.
	 * @param The string to write.
	 * 
	 * @return Whether or not the write was successful.
	 */
	public static boolean writeFile(String in_filePath, String in_contents)
	{
		try
		{
			Files.write(Paths.get(in_filePath), in_contents.getBytes());
			return true;
		}
		catch (Exception e)
		{
			return false;
		}
	}
	/**
	 * Write a byte array to file.
	 * 
	 * @author Ian Copland
	 * 
	 * @param The filename.
	 * @param The data to be written to file.
	 * @return Whether or not the file was successfully written.
	 */
	public static boolean writeFile(final String in_filePath, final byte[] in_contents)
	{
		boolean bSuccess = false;
		try
		{
			OutputStream stream = null;
			try
			{
				File file = new File(in_filePath);
				stream = new BufferedOutputStream(new FileOutputStream(file));
				stream.write(in_contents);
				bSuccess = true;
			}
	        catch (Exception e)
	        {
	        	throw e;
	        }
			finally
			{
				if (stream != null)
				{
					stream.close();
				}
			}
		}
		catch (Exception e)
		{
			Logging.logError(StringUtils.convertExceptionToString(e));
		}
		return bSuccess;
	}
	/**
	 * Copies a file from one location to another.
	 * 
	 * @author Ian Copland
	 * 
	 * @param the input filename.
	 * @param the output filename.
	 * 
	 * @return whether or not this was successful.
	 */
	public static boolean copyFile(String in_inputFilePath, String in_outputFilePath)
	{
		try
		{
			InputStream reader = new FileInputStream(in_inputFilePath);
			OutputStream writer = new FileOutputStream(in_outputFilePath);
			
			byte[] abyBuffer = new byte[1024];
			int dwLength;
			while ((dwLength = reader.read(abyBuffer)) > 0) 
			{
				writer.write(abyBuffer, 0, dwLength);
			}
			
			reader.close();
			writer.close();
		}
		catch(Exception e)
		{
			Logging.logError("Failed to copy file '" + in_inputFilePath + "' to '" + in_outputFilePath + "'");
			return false;
		}
		
		return true;
	}
	/**
	 * Copies a directory from one location to another.
	 * 
	 * @author Ian Copland
	 * 
	 * @param the input directory.
	 * @param the output directory.
	 * @param whether or not to ignore dot directories and files.
	 * 
	 * @return whether or not this was successful.
	 */
	public static boolean copyDirectory(String in_inputDirectoryPath, String in_outputDirectoryPath, LinkedList<String> in_directoryPathsToIgnore)
	{
		try
		{
			//ignore some dirs.
			for (String strIgnore : in_directoryPathsToIgnore)
			{
				if (in_inputDirectoryPath.contains(strIgnore) == true)
				{
					//This doesn't count as failure as we are choosing to ignore these dirs.
					return true;
				}
			}
			
			//if the directory doesn't exist, then create it!
			File destinationDir = new File(in_outputDirectoryPath);
			if (destinationDir.exists() == false)
			{
				destinationDir.mkdir();
			}
			
			
			//navigate the directory
			File sourceDir = new File(in_inputDirectoryPath);
			String[] astrList = sourceDir.list();
			if (astrList != null) 
			{
				for (int i = 0; i < astrList.length; i++) 
				{
					File entry = new File(sourceDir, astrList[i]);
					if (entry.isDirectory())
					{
						copyDirectory(StringUtils.standardiseDirectoryPath(in_inputDirectoryPath) + StringUtils.standardiseDirectoryPath(astrList[i]),
								StringUtils.standardiseDirectoryPath(in_outputDirectoryPath) + StringUtils.standardiseDirectoryPath(astrList[i]), in_directoryPathsToIgnore);
					}
					else
					{
						copyFile(StringUtils.standardiseDirectoryPath(in_inputDirectoryPath) + StringUtils.standardiseFilePath(astrList[i]),
								StringUtils.standardiseDirectoryPath(in_outputDirectoryPath) + StringUtils.standardiseFilePath(astrList[i]));
					}
				}
			}
		}
		catch(Exception e)
		{
			Logging.logError("Failed to copy directory '" + in_inputDirectoryPath + "' to '" + in_outputDirectoryPath + "'");
			return false;
		}
		
		return true;
	}
	/**
	 * Deletes a file.
	 * 
	 * @author I Copland
	 * 
	 * @param the filename.
	 * 
	 * @return whether or not this was successful.
	 */
	public static boolean deleteFile(String in_filePath)
	{
		File file = new File(in_filePath);
		return deleteFile(file);
	}
	/**
	 * Deletes a file.
	 * 
	 * @author I Copland
	 * 
	 * @param the file.
	 * 
	 * @return whether or not this was successful.
	 */
	public static boolean deleteFile(File in_file)
	{
		if(!in_file.exists() || !in_file.isFile())
			return false;
		
		return in_file.delete();
	}
	/**
	 * Recursively creates directories.
	 * 
	 * @author Ian Copland
	 * 
	 * @param The directory to create
	 * 
	 * @return Whether or not this was successful. Failure to create the directory 
	 * because it already exists counts as success.
	 */
	public static boolean createDirectory(String in_directoryPath)
	{
		//break the path onto sections.
		String strDirectory = StringUtils.standardiseDirectoryPath(in_directoryPath);
		String[] strPathSections = strDirectory.split("/");
		
		String strPathSoFar = "";
		for (String strPathSection: strPathSections)
		{
			strPathSoFar += strPathSection + "/";
			
			File newDir = new File(strPathSoFar);
			if (newDir.exists() == false)
			{
				if (newDir.mkdir() == false)
				{
					Logging.logError("Failed to create directory: " + strPathSoFar);
					return false;
				}
			}
		}
		
		return true;
	}
	/**
	 * Deletes a directory and all its contents.
	 * 
	 * @author Ian Copland
	 * 
	 * @param The directory to delete.
	 * @return Whether or not this was successful. Failure to delete the directory because it does not exist counts as success.
	 */
	public static boolean deleteDirectory(String in_directoryPath)
	{
		File directory = new File(in_directoryPath);

		if (!directory.exists())
			return true;
		if (!directory.isDirectory())
			return false;
		
		String[] astrList = directory.list();
		if (astrList != null) 
		{
			for (int i = 0; i < astrList.length; i++) 
			{
				File entry = new File(directory, astrList[i]);
				if (entry.isDirectory())
				{
					if (!deleteDirectory(entry.getAbsolutePath()))
						return false;
				}
				else
				{
					if (!entry.delete())
						return false;
				}
			}
		}
		return directory.delete();
	}
	/**
	 * Returns all the file paths in the given directory.
	 * 
	 * @author Ian Copland
	 * 
	 * @param the directory path.
	 * 
	 * @return the list of file paths.
	 */
	static public String[] getFilePaths(String in_directoryPath)
	{
		String strDirectory = StringUtils.standardiseDirectoryPath(in_directoryPath);
		String[] astrFilenames = getFullFilePaths(strDirectory);
		
		for (int i = 0; i < astrFilenames.length; ++i)
			astrFilenames[i] = astrFilenames[i].substring(strDirectory.length());
		
		return astrFilenames;
	}
	/**
	 * Returns all the directory paths in the given directory.
	 * 
	 * @author Ian Copland
	 * 
	 * @param the directory path.
	 * 
	 * @return the list of directory paths.
	 */
	static public String[] getDirectoriesInDirectory(String in_directoryPath)
	{
		String strDirectory = StringUtils.standardiseDirectoryPath(in_directoryPath);
		String[] astrDirectories = getFullDirectoryPaths(strDirectory);
		
		for (int i = 0; i < astrDirectories.length; ++i)
			astrDirectories[i] = astrDirectories[i].substring(strDirectory.length());
		
		return astrDirectories;
	}
	/**
	 * Calculates the MD5 checksum for the file at the given path.
	 * 
	 * @param The file path.
	 * 
	 * @return The MD5 Checksum.
	 */
	static public String calculateFileChecksumMD5(String in_filePath)
	{
		String strChecksum = "";
		
		try
		{
			InputStream fis =  new FileInputStream(in_filePath);
	
			byte[] buffer = new byte[1024];
			MessageDigest complete = MessageDigest.getInstance("MD5");
			int numRead;
			
			do 
			{
			    numRead = fis.read(buffer);
			    if (numRead > 0) 
			    {
			        complete.update(buffer, 0, numRead);
			    }
			} 
			while (numRead != -1);
			
			fis.close();
			byte[] abyChecksum = complete.digest();
			
			for (int i=0; i < abyChecksum.length; i++) 
			{
				strChecksum += Integer.toString((abyChecksum[i] & 0xff) + 0x100, 16).substring(1);
		    }
		}
		catch (Exception e)
		{
			Logging.logError("Could not calculate checksum for file: " + in_filePath);
		}
		
		return strChecksum;
	}
	/**
	 * @author Ian Copland
	 * 
	 * @return the full path to the jar file's location. Note that this does not
	 * work if the jar is exported as a Runnable Jar, or while compiling from
	 * eclipse.
	 */
	static public String getPathToHere()
	{
		String strPathToHere = "";
		try
		{
			final File file = new File(FileUtils.class.getProtectionDomain().getCodeSource().getLocation().getPath());
			String jarPath = StringUtils.standardiseFilePath(file.getAbsolutePath());
			
			int slashIndex = jarPath.lastIndexOf('/');
			if (slashIndex != -1)
			{
				strPathToHere = jarPath.substring(0, slashIndex + 1);
			}
		}
		catch (Exception e)
		{
			Logging.logError("Failed to get path to here.");
		}
		return strPathToHere;
	}
	/**
	 * Returns all the filenames in the given directory. Files names include 
	 * the input directory.
	 * 
	 * @author I Copland
	 * 
	 * @param the directory path.
	 * 
	 * @return the list of file paths.
	 */
	private static String[] getFullFilePaths(String in_directoryPath)
	{
		String strDirectory = StringUtils.standardiseDirectoryPath(in_directoryPath);
		ArrayList<String> astrFilenames = new ArrayList<String>();
		
		File directory = new File(strDirectory);
		if (!directory.exists() || !directory.isDirectory())
			return new String[0];
		
		String[] astrList = directory.list();
		if (astrList != null) 
		{
			for (int i = 0; i < astrList.length; i++) 
			{
				File entry = new File(directory, astrList[i]);
				if (entry.isDirectory())
				{
					String[] astrMoreFilenames = getFullFilePaths(entry.getPath());
					astrFilenames.addAll(Arrays.asList(astrMoreFilenames));
				}
				else
				{
					astrFilenames.add(entry.getPath());
				}
			}
		}
		
		String[] astrOutput = new String[astrFilenames.size()];
		astrFilenames.toArray(astrOutput);
		return astrOutput;
	}
	/**
	 * Returns all the directory paths in the given directory. directory paths
	 * include the input directory.
	 * 
	 * @author I Copland
	 * 
	 * @param the directory path.
	 * 
	 * @return the list of directory paths.
	 */
	private static String[] getFullDirectoryPaths(String in_directoryPath)
	{
		String strDirectory = StringUtils.standardiseDirectoryPath(in_directoryPath);
		ArrayList<String> astrDirectories = new ArrayList<String>();
		
		File directory = new File(strDirectory);
		if (!directory.exists() || !directory.isDirectory())
			return new String[0];
		
		String[] astrList = directory.list();
		if (astrList != null) 
		{
			for (int i = 0; i < astrList.length; i++) 
			{
				File entry = new File(directory, astrList[i]);
				if (entry.isDirectory())
				{
					astrDirectories.add(entry.getPath());
					String[] astrMoreDirectories = getFullDirectoryPaths(entry.getPath());
					astrDirectories.addAll(Arrays.asList(astrMoreDirectories));
				}
			}
		}
		
		String[] astrOutput = new String[astrDirectories.size()];
		astrDirectories.toArray(astrOutput);
		return astrOutput;
	}
}
