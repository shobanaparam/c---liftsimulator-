lift_sim_A.c 
generates sim_out.txt file as an output 
inputfile is sim_input which has the integer numbers we are going to input in a buffer
Compile using “gcc lift_sim_A.c -lpthread “ command 
Compiler command creates “a.out” file in the same directory 
run: ./a.out
lift_sim_A belongs to sim_input.txt, lift_sim_A.c , sim_out.txt ,a.out

 


lift_sim_B.c
not completed only completed parent creates shared memory .
compile : gcc_lift_sim_B.c -osharedmem
run: ./sharedmem

lift_sim_B belongs to lift_sim_B.c ,sharedmem 

Both lift_sim_A.c and lift_sim.B.c should compile and run separately as I mentioned above 
Because lift_sim_A.c completed using only thread and global variables, lift_sim_B.c not completed 



