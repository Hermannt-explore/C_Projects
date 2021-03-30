#!/bin/bash -e
lru="lru"
no_lru="no_lru"
clean="clean"
if [[ "$1" == "$lru" ]]
then
	gcc mmu_lru.c -o mmu_lru
	./mmu_lru BACKING_STORE.bin addresses.txt 

elif [[ "$1" == "$no_lru" ]]
then
	gcc mmu.c -o mmu
	./mmu BACKING_STORE.bin addresses.txt 
elif [[ "$1" == "$clean" ]]
then 
	rm mmu mmu_lru 2>/\dev/null
else
	echo "For mmu wihtout lru functionality, type in (bash test.sh no_lru) ."
	echo "For mmu with lru functionality, type in (bash test.sh lru) ."
	echo "To remove object files from your directory, type in (bash test.sh clean) ."
fi

