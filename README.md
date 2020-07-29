# Chackme
'hack me' exercise discussion repo

		Author:MD.Nazmuddoha Ansary


# Compile 
* compile with the **-ggdb** option 
        
        $ gcc -ggdb hackme.c -no-pie -o hackme

> The **-ggdb** option tells the compiler to insert debugging information into the compiled code
> The **-no-pie** is to ensure the binary to be a : **ELF 64-bit LSB executeable** instead of a **ELF 64-bit LSB shared object**
* The compiled binary should have the following file info:

            $ file hackme
            hackme: ELF 64-bit LSB executable, x86-64, 
            version 1 (SYSV), dynamically linked, interpreter /lib64/l, 
            for GNU/Linux 3.2.0, BuildID[sha1]=972e94f168fca115ec83d5cadfc46178c79dacc9, 
            with debug_info, not stripped

# Invalid Log file 
* The following code is used to create an invalid log file
> The choice of using **35** As is purely arbitiary. *(since **log.h** shows that the **header.name** is given the size of 32)*
> Also please keep in mind that the contents **invalid.dat** file ends with a ***newline*** char. 
 
        $ python -c 'print "A"*(35)' > invalid.dat

# Program Crash
* run the compiled binary **hackeme** (or any given name) with the **invalid.dat** file as argument

        $ ./hackme invalid.dat

**Segmentation Fault**

![](/src_img/seg_error.png?raw=true )


# Interesting Notes:
* Inspecting the source code from **hackme.c** shows the useage of same **fd** in **open** and **read** function. A point to note is the **BUGS** section of **read** function:
        
        $ man read

![](/src_img/read_bug.png?raw=true )


* A close inspection of the output before **segmentation fault** occurs shows that the **record numbers** are printing values from **environment variables**.A side by side matching example is shown in the following figure:

![](/src_img/env_match.png?raw=true )


**ENVIRONMENT**  

    OS          : Ubuntu 18.04.3 LTS (64-bit) Bionic Beaver        
    Memory      : 7.7 GiB  
    Processor   : Intel® Core™ i5-8250U CPU @ 1.60GHz × 8    
    Graphics    : Intel® UHD Graphics 620 (Kabylake GT2)  
    Gnome       : 3.28.2  

