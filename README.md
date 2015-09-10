# MultithreadRun
This is a program aims at running a bunch of similar programs in a multithreaded mode.
First the file need to be compiled by using -lpthread, e. g.
gcc MultithreadRun.c -lpthread -o MultithreadRun
Then running jobs using the following command,
./MultithreadRun Filename NumberOfThreads OutputPrefix
then the Filename will run NumberOfThreads times where each running takes a input integer from 0 to NumberOfThreads-1.
The output directed into OutputPrefix1 to OutputPrefix24.
An example would be,
./MultithreadRun ./a.out 24 output_
The program need at least Filename input. The default NumberOfThreads equals to 8 and the default OutputPrefix is "output_"