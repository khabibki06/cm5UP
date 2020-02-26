# cm5UP
cm5UP is a small program to calculate CM5 charge group from ORCA output file. It is inspired from similiar python program [ligpargen]https://github.com/leelasd/ligpargen/wiki/How-to-get-CM5-charges-for-Condensed-Phase-Simulations. 

I created this c++ program without needed any dependence with other packages. So, it can be used in any computer without need any previous program/add ons as long as the OS is be supported. 

The binary for win_64 and linux can be downloaded in the binary folder. It also can be compiled in any OS with standard C++ library.

## How to use
1. You need ORCA log file containing Hirshfeld charge analysis. It can be accomplished by adding these lines in ORCA input file

    %output
  
     Print[ P_Hirshfeld] 1
  
    end
  
2. To generate CM5 charge group

   Syntax: cm5UP -i orcaoutputfilename -o outputname
   
    -i orcaoutputfilename : (mandatory) orca log file.
    
    -o outfilename : (optional)  base name the output csv and xyz file. If it is not given. The basename will be extracted from orcaoutputfilename.
3. The program will show the result in screen and produce two output file:

    a. CSV file containing coordinate, Hirshfeld, CM5 charge, and 1.2 * CM5 Charge
    
       The 1.2 * CM5 Charge is suitable for OPLS FF based on (Vilseck, Tirado-Rives, & Jorgensen, 2014)
       
    b. XYZ file of the last structure in ORCA log file.
    
There are some examples : orca input file, orca log file, csv output file and XYZ file in examples folder

Regards,
Khabib Khumaini
Department of Chemistry, Universitas Pertamina

