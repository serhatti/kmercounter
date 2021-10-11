// A k-mer counting class utilizing a counting bloom filter.
// The basic usage is to call Process() method in a sequence loop and Finalize() for post-processing (for example printing results, sorting, removing. etc)
// The results are put in a sparshe hash map. Each nucleotide is encoded in two bits for memory gain. 
// The bloom filter parameters are by default hardcoded for a large FASTQ file with around 72M sequences where each sequence has a size of 100.
// Counting bits are hardcoded to 5...

//Author	: Serhat Istin
//Contact	: istins@gmail.com

#ifndef KmerCounter_H
#define KmerCounter_H

#include <vector>
#include <bf/bloom_filter/counting.hpp>
#include <sparsehash/sparse_hash_map>


typedef std::vector<bool> Bits;
typedef google::sparse_hash_map<Bits, unsigned int, std::hash<Bits> > SparseHash;
typedef bf::counting_bloom_filter CBF;


class KmerCounter{
	
	public:
	  KmerCounter(unsigned short int K=30);
	  ~KmerCounter();
	  void Encode(const std::string&);//pack each letter into two bits...
	  static std::string Decode(const Bits&);//unpack the bits to get letters A T G C back 
	  void Process(const std::string& /*a sequence comes here*/);
	  void GetKmer(const std::string& ,unsigned int&);
	  void Finalize();//Any post-processing routines should come here....
	private:
		CBF* cbf=NULL;
		SparseHash kmerlist;
		Bits encoded_kmer;
		std::string curr_kmer="None";
		unsigned int nhash;//no of hash functions to be used for the bloom filter
		unsigned int counterbits;
		unsigned int mnratio;
		unsigned long int nmax_seqs;
		unsigned short int K;
		bool multihash;
		unsigned short int CUTOFF;//the cutoff frequency. mers with occurences below this are highly suppressed!
};
#endif