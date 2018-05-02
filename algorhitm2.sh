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


convert_morse(){
replace_dots
while read line; do
    for word in $line; do
        bind_letter $word
    done
done < tempSecret.txt
}

plainText=$(convert_morse)

translateWord(){

keyWord="FUEHRER"
result=$keyWord
offset=$(($(ord $1) - 65))

for (( i=0; i<${#keyWord}; i++ )); do
    currVal=$(($(ord ${keyWord:i:1}) - $offset))
    if [ $currVal -lt 65 ]; then
       currVal=$((91 - $((65 - $currVal))))
    fi
    result=$(echo "$result" | sed "s/./$(chr $currVal)/$(($i + 1))")
done 
echo $result
}

allTranslations(){
   for letter in {A..Z}; do
	echo "$1" | grep -q "$(translateWord $letter)" && echo $letter
   done
}

decypher(){
   text=$1 
   key=$(allTranslations $1)
   offset=$(($(ord $key) - 65))
   
for (( i=0; i<${#text}; i++ )); do
    currVal=$(($(ord ${text:i:1}) + $offset))
    if [ $currVal -gt 90 ]; then
	currVal=$((64 + $currVal - 90))
    fi
    text=$(echo $text | sed "s/./$(chr $currVal)/$(($i + 1))")
done
echo $text  
}

encrypt(){
    text=$1
    for letter in {A..Z}; do
        result=$text
	offset=$(($(ord $letter) - 65))
       for (( i=0; i < ${#text}; i++)); do
	   currVal=$(($(ord ${text:i:1}) - $offset ))
           if [ $currVal -lt 65 ]; then
		currVal=$((91 - $((65 - $currVal))))
	   fi
        result=$(echo $result | sed "s/./$(chr $currVal)/$(($i + 1))")
      done
   echo "$letter $result $(decypher $result)"
done	
}

#encrypt "THEFUEHRERWASAVERYBADMAN"
decypher $plainText

