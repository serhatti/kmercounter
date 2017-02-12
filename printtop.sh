#File includes a rcuntion body and should not be used alone

 printtop(){
  if [[ $# -ne 2 ]];then
   echo "printtop Error!. Usage :  printtop <infile> <topcount>"
   exit
  fi
  tc=$2
  let ctr=0
  
   currcount=`awk 'FNR == 1 {print $2}' $1`
  while read L;do
    echo $L
    let currno=`echo $L | cut -d " " -f 2`
    if [ $currno -lt $currcount ];then
      let ctr=$ctr+1
    fi
    currcount=`echo $L | cut -d " " -f 2`
    if [ "$ctr" == "$2" ];then
      break
    fi
  done<$1
}

