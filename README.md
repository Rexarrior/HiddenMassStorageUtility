# HiddenMassStorageUtility
Utility to making a hidden sectors in massstorage devices


Usage: 

  * -m - Work mode. Can be r,rd, w, wd - read mbr, read data, write mbr, write data. Data modes require -o argument, wd require -b argument
	
  * -f - Specified file name. Use for saving or loading some data
	
  * -o - Offset for reading or writing data to drive
	
  * -d --drive - Physical drive for apply specidied action
	
  * -b --bytes - Bytes to read. To use with rd mode
  
Sample:

.\HiddenMassStorageUtility.exe -f mbr.img -m r -d \\.\PHYSICALDRIVE1 


.\HiddenMassStorageUtility.exe -f folder8.bin -m rd -d \\.\PHYSICALDRIVE1 -o 1073741824 


.\HiddenMassStorageUtility.exe -f folder8.bin -m wd -d \\.\PHYSICALDRIVE1 -o 1073741824 -b 1211640
