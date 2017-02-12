#include "KmerCounter.h"

KmerCounter::KmerCounter(unsigned short int kmersize){
	K=kmersize;
	multihash=true;
	nhash=2;
	counterbits=5;
	mnratio=4;
	nmax_seqs=72E6;
	unsigned long int nqueries=(100-K+1)*nmax_seqs;
	unsigned long int filterwidth=mnratio*nqueries/counterbits;
	cbf=new CBF(bf::make_hasher(nhash),filterwidth,counterbits,multihash);
	CUTOFF=(1<<counterbits)-1;
}

KmerCounter::~KmerCounter(){
	if (cbf) delete cbf;
	//delete kmerlist;
	//delete encoded_kmer;
}

void KmerCounter::Encode(const std::string& kmer ){
	encoded_kmer.clear();
    char curr;
    for (unsigned int i=0;i<kmer.size();i++){
		curr=kmer[i];
		switch(curr){
	      case('A') :
	        encoded_kmer.push_back(0);
	        encoded_kmer.push_back(0);
	        break;
	      case ('T'):
	        encoded_kmer.push_back(0);
	        encoded_kmer.push_back(1);
	        break;
	      case ('G'):
	        encoded_kmer.push_back(1);
	        encoded_kmer.push_back(0);
	        break;
	      case ('C'):
	        encoded_kmer.push_back(1);
	        encoded_kmer.push_back(1);
	        break;
	      default :
	        std::cerr<<"Unknown character in DNA word"<<std::endl;
	        exit(8);
		}
	}
	return;
}


std::string KmerCounter::Decode(const Bits& B){
   
  std::string res="";
  for(auto it=B.begin();it!=B.end();++it){
	  if(*it==0 && *(it+1)==0){
		   res.append("A");
		   it++;
		   continue;
	  }
	  if(*it==0 && *(it+1)==1){
	      res.append("T");
	      it++;
	   continue;
      }
	  if(*it==1 && *(it+1)==0){
		   res.append("G");
		   it++;
		   continue;
	  }
	  if(*it==1 && *(it+1)==1){
		   res.append("C");
		   it++;
		   continue;
	  }//ififif bad practice ill fix it
  }
  return res;
}


void KmerCounter::GetKmer(const std::string& seq,unsigned int& i){
	curr_kmer.clear();
    curr_kmer=seq.substr(i,K);
}



void KmerCounter::Process(const std::string& curr_seq){
	int L=curr_seq.size();
	for(unsigned int i=0;i<L-K+1;i++){//k-mer loop
        GetKmer(curr_seq,i);
		if(curr_kmer.find('N')!=std::string::npos) continue;
		//if the encountered k-mer appears in the filter less than the cutoff times,
		//and if it does not exist in the hash table then add it to the filter and skip into the next k-mer
		if (cbf->lookup(curr_kmer)<CUTOFF){
			cbf->add(curr_kmer);
			continue;
			}
		Encode(curr_kmer);
		bool exists=kmerlist.find(encoded_kmer)!=kmerlist.end();
		if(exists){
		  (kmerlist)[encoded_kmer]++;
		  //curr_bits.clear();
		  continue;
		}
		//std::cout<<curr_kmer<<std::endl;
        //if the encountered k-mer is already in the hash table then initialize its  counter by cutoff+1
        else {
		  (kmerlist)[encoded_kmer]=CUTOFF+1;
		   //std::cout<<"Lililililil"<<std::endl;
        }
     }
	return;
}

void KmerCounter::Finalize(){//just print the contents of the map
	if (cbf) delete cbf;
    for( SparseHash::const_iterator it=kmerlist.begin(); it!=kmerlist.end(); ++it) {
        std::cout<<Decode(it->first) <<" "<<it->second<<std::endl;
		
   }
}