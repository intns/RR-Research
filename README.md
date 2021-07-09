# Rabbids Go Home Research
## reading-bigfile
This folder has the code for reading and parsing BigFiles (*.bf) 

# Rayman Origins Research
## IPK files
File structure is as such: (ints are 4 bytes and chars are 2 bytes)
- Header
  - unknown int
  - amount of files
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
- Files
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - unknown int
  - Length of string
  - String ("length of string" characters long)
