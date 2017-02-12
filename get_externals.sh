#/!bin/bash

workdir=$PWD

if [ ! -f external ];then
	mkdir -p external
fi

if [ ! -d external/sparsehash ];then
	git clone https://github.com/sparsehash/sparsehash external/sparsehash
fi

if [ ! -d external/libbf ];then
	git clone https://github.com/mavam/libbf external/libbf
fi

if [ ! -d external/install/libbf ];then
	mkdir external/install/libbf
fi

if [ ! -d external/install/sparsehash ];then
        mkdir external/install/sparsehash
fi



cd external/sparsehash
./configure --prefix=$workdir/external/install/sparsehash
make -j4;make install
cd $workdir

cd external/libbf
./configure --prefix=$workdir/external/install/libbf
make -j4;make install
cd $workdir
