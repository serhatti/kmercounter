# kmercounter
#author : Serhat Istin
#	  istins@gmail.com
A small package utilizing a counting Bloom filter to count most abundant k-mers.  The packge  depends on google sparse hash map, libbf and seqtk(kseq.h).
  

Implementation is based on the ideas in the reference paper here :
  Efficient counting of k-mers in DNA sequences using a bloom filter 
  http://www.biomedcentral.com/1471-2105/12/333


Dependencies and building :
You must have git and zlib installed in your system.
To build the package use cmake.
Append to path by :
> source install/setup.sh

Running:
For help and to see cl options,  run :
>count_kmers

Serhat Istin
istins@gmail.com
