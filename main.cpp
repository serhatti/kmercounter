//A driving program for KmerCounter Class
//Author	: Serhat Istin
//Contact	: istins@gmail.com

#include "anyoption.h"
#include "KmerCounter.h"
#include <fstream>
#include <map>
#include <zlib.h>
//#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(int argc,char* argv[]){
	
	AnyOption *opt = new AnyOption();
    opt->addUsage( "" );
    std::string help="-h";
    opt->addUsage( "Usage: " );
    opt->addUsage( "" );
    opt->addUsage( " -h  --help  	          : Prints this help " );
    opt->addUsage( " -f  --filename           : Input FASTQ file (mandatory)" );
    opt->addUsage( " -k  --kmersize           : kmersize (mandatory)" );
    opt->addUsage( " -t  --topcount           : topcount (optional default is  set to -1 to dump all)" );
    opt->addUsage( " -s  --skip               : number of sequences to skip (optional)" );
    opt->addUsage( " -n  --nproc              : number of sequences to process (optional)" );
    opt->addUsage( "" );
    opt->setFlag("help", 'h' );
    opt->setOption("filename",'f');
    opt->setOption("kmersize",'k');
    opt->setOption("topcount",'t');
    opt->setOption("skip",'s');
    opt->setOption("nproc",'n');

    opt->processCommandArgs( argc, argv );

    if( ! opt->hasOptions() ||opt->getFlag( "help" ) || opt->getFlag( 'h' )) { /* print usage if no options */
      opt->printUsage();
      delete opt;
      return 0;
    }

    if( opt->getValue( 'f' )==NULL){
      std::cerr<<"CommandLine error. Input file not supplied."<<std::endl;
      opt->printUsage();
      exit(8);
     }
    if( opt->getValue('k' )==NULL){
      std::cerr<<"CommandLine error. k-mer size not supplied."<<std::endl;
      opt->printUsage();
      exit(8);
     }
    /*
    if( opt->getValue( 't' )==NULL){
      std::cerr<<"CommandLine error. Top Count not supplied."<<std::endl;
      opt->printUsage();
      exit(8);
     }
     */
    int nskip=0;
    if( opt->getValue( 's' )!=NULL){
      nskip=atoi(opt->getValue('s'));
     }
    int NMAX=-1;
    if( opt->getValue( 'n' )!=NULL){
      NMAX=atoi(opt->getValue('n'));
     }
    const char* filename=opt->getValue('f');
    unsigned int K=atoi(opt->getValue('k'));
    int topcount=-1;
    if(opt->getValue('t')!=NULL)
    topcount=atoi(opt->getValue('t'));

    //*****************End of Commandline parsing***********************
    std::ifstream thefile(filename);
    if(!thefile.good()){
      std::cerr<<"No such file: "<<filename<<std::endl;
    }
	gzFile fp;
	kseq_t *seq;
	fp = gzopen(filename, "r");
	KmerCounter *kc=new KmerCounter(K);
	std::string SEQ="";
	int proc_ctr=0;
	int skipctr=0;
	int l=-1;
	seq = kseq_init(fp);
	while ((l = kseq_read(seq)) >= 0) {//main seq loop
		if(skipctr++<nskip) continue;
		SEQ.assign(seq->seq.s);
		kc->Process(SEQ);
		proc_ctr++;
		if(proc_ctr==NMAX) break;
	}
	kc->Finalize();
  return 0;	
}
