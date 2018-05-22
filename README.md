# RootkitHashCracker
RootkitHashCracker it's a little program I developed to crack the antivirus processes names stored as hashes in the HackAV Rootkit.  
Works in x86/x64 systems.

## Releases

Go to the Releases tab and download the compiled executables.

## Usage

In order to work it needs a file with the hashes each one in a different line and the dictionary with the processes to bruteforce with the same format.

```
RootkitHashCracker.exe HASHES_FILE DICTIONARY_FILE
```
### Example

```
RootkitHashCracker.exe Hashes.txt Dictionary.txt
```

### Hashes File Format Example

164CFA74  
45470A4A  
4FEDA50D  
19C93F2D  
13CA8828

### Dictionary File Format Example

Olly.exe  
LordPE.exe  
ipfs.exe  
SWIS.exe  
PEiD.exe
