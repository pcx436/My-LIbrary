"""
This code is written by Jacob Malcy. It simply 'scrambles' all the txt files in the current directory.
All scrambled that get scrambled get written to '.enc' files while descrambled ones go to txt files
Command line parameters:
	If you enter "scrm" or nothing, all txts will be turned into encs
	If you enter "dscm", all encs will be turned to txts
"""
from pathlib import Path
import base64
import sys
import binascii

p = Path('.')
# used to determine if we're scrambling or unscrambling
if len(sys.argv) == 1 or sys.argv[1] == "scrm":
	ext = ".txt"
	notExt = ".enc"
else:
	ext = ".enc"
	notExt = ".txt"

# if there are no files to operate on then we don't need to run the program at all
extList = list(p.glob('*' + ext))
if len(extList) == 0:
	print("No files to be changed.")
	sys.exit()# exit the script

for x in extList:
	newFileName = x.stem + notExt
	with x.open('rb') as originalFile, open(newFileName, 'wb') as newFile:
		base64.encode(originalFile, newFile) if ext == '.txt' else base64.decode(originalFile, newFile)
	x.unlink()


print("Files converted.")
