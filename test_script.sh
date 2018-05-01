#!/bin/bash

replace_dots(){
  sed 's/\./z/g' morse.txt > tempMorse.txt
  sed -i 's/$/y/g' tempMorse.txt
  sed 's/\./z/g' scrt.txt > tempSecret.txt
}

bind_letter(){
  grep " $1y" tempMorse.txt | cut -d " " -f 1 | tr '\n' ',' | sed 's/,//g' 
  return
}

ord(){
        printf "%d" "'$1"
}

chr(){
    [ "$1" -lt 256 ] || return 1
    printf "\\$(printf %o "$1")"
}

find_fuhrer(){
 foo=$1

 for((i=0; i<$((${#foo}-5)); i++));do {
        val=$(ord ${foo:i:1})
        val2=$(($(ord ${foo:i+1:1})-15))
	val3=$(($(ord ${foo:i+2:1})+1))
        val4=$(($(ord ${foo:i+3:1})-2))
        val5=$(($(ord ${foo:i+4:1})-12))
        val6=$(($(ord ${foo:i+5:1})+1))
        val7=$(($(ord ${foo:i+6:1})-12))
        if [ $val -eq $val2 -a $val -eq $val3 -a $val -eq $val4 -a $val -eq $val5 -a $val -eq $val6 -a $val -eq $val7 ]; then
           chr $val
           chr $(($val+15))
	   chr $(($val-1))
           chr $(($val+2))
           chr $(($val+12))
           chr $(($val-1))
           chr $(($val+12))
        fi
}
done
}

convert_morse(){
replace_dots
while read line; do
    for word in $line; do
        bind_letter $word
    done
done < tempSecret.txt
}

find_fuhrer $(convert_morse)
