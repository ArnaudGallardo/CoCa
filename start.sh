#!/bin/sh
#Project : Complexité et Calculabilité 2016, Coloration de graphe
#Author : Arnaud GALLARDO and Khaled FAYSAL AHMED
#Master 1 Informatique, Université de Bordeaux
#start.sh : Allows the user to find a solution to the graph coloration problem
#How to : ./start.sh <graph.c> <nb_colors>

gcc -std=c99 -Wall $1 dmSat.c -o dmSat
if [ $? -ne 0 ]; then
    echo "Error while compiling dmSat"
    exit
fi
gcc -std=c99 -Wall $1 dmSatParser.c -o dmSatParser
if [ $? -ne 0 ]; then
    echo "Error while compiling dmSatParser"
    exit
fi
./dmSat $2
if [ $? -ne 0 ]; then
    echo "Error while computing dmSat"
    exit
fi
cd glucose-syrup/simp
./glucose -model ../../GtoD.txt > ../../result.tmp
resultGl="$?"
if [ "$resultGl" == "10" ]; then
    cd ../../
    echo -e "The SAT formula is \033[32mSATISFIABLE\033[0m"
    ./dmSatParser $2 result.tmp
    if [ $? -ne 0 ]; then
        echo "Error while computing dmSatParser"
        exit
    fi
    if [ $2 -lt 13 ]; then
        while true; do
            read -p "Display a visual representation of the graph? (y/n)" yn
            case $yn in
                [Yy]* ) echo -e "Server is starting... Your page will be accessible soon here : \033[4mhttp://localhost:3001\033[0m"; echo -e "\033[1mPress Ctrl-C to exit.\033[0m"; cd web/; python -m SimpleHTTPServer 3001; exit;;
                [Nn]* ) exit;;
                * ) echo "Please answer yes or no.";;
            esac
        done
    fi
elif [ "$resultGl" == "20" ]; then
    echo -e "The SAT formula is \033[33mUNSATISFIABLE\033[0m"
    exit
else
    echo "Error while computing glucose"
    exit
fi