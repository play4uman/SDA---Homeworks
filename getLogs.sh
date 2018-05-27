#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: <directory> <option>"
fi

if [ ! -d $1 ]; then
	echo "Directory does not exists!"
	exit 1
fi

if [  $2 != outliers -a $2 != unique -a $2 != cross_check -a $2 != participants ]; then
	echo  "Invalid second parameter. Options are: <\"participants\"> <\"outliers\"> | <\"unique\"> | <\"cross_check\">"
	exit 3
fi

lognames=$(find $1 -maxdepth 1 -type f -name '*.txt')

log_posiv(){
	START="$(grep -n -m 1 "QSO" $1 | cut -d ':' -f 1)"
	tail -n +$START $1 | head -n -1 | sed 's/\t/ /g' | tr -s ' ' | cut -d ' ' -f 9
}

get_9_field(){
    for file in $lognames; do
        log_posiv $file > ${1}/DebugLogs/uniq_logs_cache/${file}_uniq.txt
    done
}

participants=$(find $1 -maxdepth 1 -type f -name '*.txt' -exec sh -c 'basename {} | cut -d '.' -f 1 ' \;)


if [ ! -d ${1}/DebugLogs ]; then
	mkdir ${1}/DebugLogs
fi

if [ ! -d ${1}/DebugLogs/uniq_logs_cache ]; then
	mkdir ${1}/DebugLogs/uniq_logs_cache
	get_9_field ${1}
fi


#SEARCH FOR ALL NON PARTICIPANTS IN THE LOGS
non_part(){
	COUNTER=
	> ${1}/DebugLogs/cachedNOTpart.txt
	for file in $lognames; do
		COUNTER=$((COUNTER + 1))
		echo FILE: $COUNTER
		for participant in $(log_posiv $file); do
			if ! grep -q "^$participant$" ${1}/DebugLogs/cachedNOTpart.txt; then
				if ! echo "$participants" | grep -q "^$participant$"; then
					echo $participant >> ${1}/DebugLogs/cachedNOTpart.txt
				fi
			fi
		done
	done
	cat ${1}/DebugLogs/cachedNOTpart.txt
}

#DONE

unique_check(){
	ALLPOSIV="${participants}\n$(cat ${1}/DebugLogs/cachedNOTpart.txt)"
	> ${1}/DebugLogs/uniq.txt
	COUNTPROGRESS=0
	for POSIV in $(echo -e "$ALLPOSIV"); do
		COUNTPROGRESS=$((COUNTPROGRESS + 1))
		echo "POSIV: $COUNTPROGRESS"

		COUNT=0
		for file in ${1}/DebugLogs/uniq_logs_cache/*; do
			if grep -q "^${POSIV}$" $file; then
				COUNT=$((COUNT + 1))
				if [ $COUNT -eq 3 ]; then
					break 1;
				fi
			fi
		done
		if [ $COUNT -ne 3 ]; then
		echo $POSIV >> ${1}/DebugLogs/uniq.txt
		fi
	done
	cat ${1}/DebugLogs/uniq.txt
}


#CROSS CHECK

cross_check(){
	> ${1}/DebugLogs/cross_negative.txt
	PROGRESSCOUNT=0

	for file in $lognames; do
		PROGRESSCOUNT=$((PROGRESSCOUNT + 1))
		echo "FILE: $PROGRESSCOUNT"
	
		POSIVNAME=$(basename $file | cut -d "." -f 1)
		for CURRPOSIV in $(cat ${1}/DebugLogs/uniq_logs_cache/${POSIVNAME}.txt_uniq.txt); do
			if [ -f "$1/${CURRPOSIV}.txt" ]; then
				if ! cat ${1}/DebugLogs/uniq_logs_cache/${CURRPOSIV}.txt_uniq.txt | grep -q "^$POSIVNAME$"; then
					cat $file | grep "$CURRPOSIV" >> ${1}/DebugLogs/cross_negative.txt
				fi
			fi
		done
	done
	cat ${1}/DebugLogs/cross_negative.txt
}
#DONE

case $2 in
	participants)
		echo -e "$participants"
	;;
	outliers)
		non_part $1
	;;
	unique)
		unique_check $1
	;;
	cross_check)
		cross_check $1
	;;
esac
